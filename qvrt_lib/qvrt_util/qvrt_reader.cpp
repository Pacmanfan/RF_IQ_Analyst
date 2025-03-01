#include "qvrt_tools.h"
#include <math.h>
/*********************************************************************************************************/


IQ_Reader::IQ_Reader()
{
    fp=0;
}

IQ_Reader::~IQ_Reader()
{

}
/*

void IQ_Reader::SetStreamInfo(StreamInfo *si)
{
    CF = si->CenterFreqHz;
    BW = si->BandwidthHZ;
    SPS,RefLevDB;
    double gain1,gain2,offset;
}
*/
bool IQ_Reader::Open(std::string filename)
{
    fp = fopen(filename.c_str(),"rb");
    if(!fp)
        return false;
    return true;
}

void IQ_Reader::Close()
{
    fclose(fp);
    fp =0;
}

bool IQ_Reader::IsOpen()
{
    if(fp != 0)
        return true;
    return false;
}

// returns file length in bytes
// or -1 if there is a problem
long IQ_Reader::FileLength()
{
    if(IsOpen())
    {
        long savepos = TellP();
        fseek(fp,0,SEEK_END);
        long endpos = TellP();
        fseek(fp,savepos,SEEK_SET);
        return endpos;
    }else
    {
        return -1;
    }
}

long IQ_Reader::ReadSamples(CircBuff<complex<float> > *samplebuffer,unsigned int numsamples)
{
    UNUSED(samplebuffer);
    UNUSED(numsamples);
    return 0;
}

long IQ_Reader::ReadSamples(complex<float> *samplebuffer,unsigned int numsamples)
{
    UNUSED(samplebuffer);
    UNUSED(numsamples);
    return 0;
}

/*********************************************************************************************************/

QVRT_Reader::QVRT_Reader() : IQ_Reader()
{
    streamid = 1;
    buffer = nullptr;
    buffersize = 0;
    m_iqbuff = nullptr;

}

QVRT_Reader::~QVRT_Reader()
{
    if(buffersize !=0)
    {
        buffersize = 0;
        delete []buffer;
    }
    if(m_iqbuff != nullptr)
    {
        delete m_iqbuff;
    }
}

/*
The QVRT implementation may return more data than asked, because it reads from
chunks of fixed sample size
//we should probasbly change it so it returns the exact amount of samples requested
and buffers the remainder from the IQ_Data packet interanally in a buffer
*/
long QVRT_Reader::ReadSamples(CircBuff<complex<float> > *samplebuffer,unsigned int numsamples)
{
    #pragma message("ReadSamples function deprecated, use the ReadSamples with the neewer interface.")
    // this is going to have to keep reading packets
    // until it reads enough data packets to satisfy the number of samples requested
    // it also needs to handle the condition at the end of the file
    QVRT_Header *header = ReadNextPacket();
    QVRT_IQDataPacket datapacket;
    QVRT_IFContext_Packet ctx;
    unsigned int numread = 0;
    unsigned char *pdata = 0;
    bool done = false;
    while (header != 0 && !done)
    {
        pdata = CurrentBufferPos();
        switch(header->packetType)
        {
            case QVRT_IF_CONTEXT:                


            break;
            case QVRT_IQ_DATA:
                if(datapacket.Decode(pdata,samplebuffer,streamid))
                {
                    numread += datapacket.m_numsamples;
                }
                if(numread >= numsamples)
                {
                    done = true;
                }
            break;
        }
        if(!done)
            header = ReadNextPacket();
    }
    return numread;
}


/*
This function uses an internal sample buffer to read samples from the file and
return the EXACT number of samples requested.
This is the preferred interface to the above
*/
// I think there's an error in here causing it skip half the data
/*
long QVRT_Reader::ReadSamples(complex<float> *outbuffer, unsigned int numsamples)
{
    static CircBuff<complex<float> > *samplebuffer = nullptr;

    if(samplebuffer == nullptr) // not allocated yet
    {
        samplebuffer = new CircBuff<complex<float>>(MAX_DATA_PACKET_SAMPLES * 2); //allocate storage space
    }

    if(samplebuffer->size() >= numsamples) //see if we've got enough samples right off the bat
    {
        return samplebuffer->read(outbuffer,numsamples);
    }
    long ret = ReadSamples(samplebuffer,numsamples);

    return samplebuffer->read(outbuffer,numsamples);

}
*/

long QVRT_Reader::ReadSamples(complex<float> *outbuffer, unsigned int numsamples)
{
    if(m_iqbuff == nullptr) // not allocated yet
    {
        m_iqbuff = new CircBuff_No_lock<complex<float>>(MAX_DATA_PACKET_SAMPLES * 2); //allocate storage space
    }

    if(m_iqbuff->size() >= numsamples) //see if we've got enough samples right off the bat
    {
        return m_iqbuff->read(outbuffer,numsamples);
    }

    //we have to keep reading in chunks to satisfy the requested amount
    // this is going to have to keep reading packets
    // until it reads enough data packets to satisfy the number of samples requested
    // it also needs to handle the condition at the end of the file
    QVRT_Header *header;// = ReadNextPacket();
    QVRT_IQDataPacket datapacket;
    QVRT_IFContext_Packet ctx;
    uint32_t samples_processed  = 0;// how many samples have we satified so far
    uint32_t samplesremaining = numsamples; // how many more we need to read / process
    unsigned char *pdata = nullptr;

    while (samplesremaining > 0)
    {
        //determine how many more samples we need
        samplesremaining = numsamples - samples_processed;
        //figure out how many more we need to read
       // uint32_t capminussize = m_iqbuff->capacity() - m_iqbuff->size();
        uint32_t num_to_read = min(samplesremaining,(uint32_t)m_iqbuff->size());
        if(num_to_read > 0)
        {
            //copy them to the right position in the outbuffer
            unsigned int actualread = m_iqbuff->read(&outbuffer[samples_processed],num_to_read);
            //increment the total number of samples we've read
            samples_processed += actualread;//
            samplesremaining = numsamples - samples_processed; // recalculate
            if(samplesremaining == 0)
                break;
        }
        header = ReadNextPacket();
        if(header == nullptr) // end of file
            break;

        pdata = CurrentBufferPos();
        switch(header->packetType)
        {
            case QVRT_IF_CONTEXT:
                //get the latest GPS info as well as the bearing info

            break;
            case QVRT_IQ_DATA:
                //read samples into the buffer
                datapacket.Decode(pdata,m_iqbuff,streamid);
            break;
        }
    }
    return samples_processed;
}


QVRT_Header *QVRT_Reader::ReadNextPacket()
{
    long header;
    if(!fp)
        return nullptr;

    if(feof(fp) != 0)
        return nullptr;

    //read the header
    long bytesread = fread(&header,1,4,fp);
    if(bytesread != 4) // header size
        return nullptr;
    if(header == 0) // header is empty
        return nullptr;
    //now, decode the header
    packetheader.Decode((unsigned char *)&header);
    //make sure we've got enough room in the buffer
    long numbytes = (packetheader.size - 1 )* 4; //?
    if(packetheader.size == 0)
        return nullptr;
    if(numbytes > buffersize) // if our buffer isn't big enough, re-allocate space
    {
        if(buffer != nullptr)
            delete []buffer;
        buffer = new unsigned char[numbytes + 4]; // allocate storage space
        buffersize = numbytes + 4; // save the size
    }
    memcpy(buffer,&header,4); // copy the 4 bytes of the header to the start of the buffer
    //now read the raw data into the buffer
    bytesread = fread(&buffer[4],1,numbytes,fp);
    if(bytesread != numbytes) // make sure we read it all
    {
        return 0;
    }
    return &packetheader; // return the header
}

long QVRT_Reader::PyReadSamples(long outbuffer, int numsamples)
{
    complex<float> *buff = (complex<float> *) outbuffer;
    return ReadSamples(buff, numsamples);
}
/*
long QVRT_Reader::ReadSamples(void *outbuffer, uint32_t numsamples)
{
    complex<float> *ptr = (complex<float> *)outbuffer;
    return ReadSamples(ptr,numsamples);
}
*/
