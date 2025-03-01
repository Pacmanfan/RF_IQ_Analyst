#include "qvrt_tools.h"

#define USELUT 1

#if(USELUT==1)
static float IQLUT[65536]; // for converting from unsigned short to floats
static bool lutinited = false;
void InitializeLUT();
#endif


void QVRT_IQDataPacket::Dump(CircBuff< complex <float> > *samples)
{
    QVRT_Packet::Dump();
    printf("**QVRT_IQDataPacket\r\n");
    static complex<float> fdata[MAX_DATA_PACKET_SAMPLES]; // m_numsamples total samples, each with I/Q
    //dumping samples is optional
    if(samples == nullptr)
        return;

    samples->read(fdata,m_numsamples);
    float *fpos = (float *)fdata; // cast as float for iteration
    for(uint32_t c=0; c < m_numsamples ; c++)
    {
        float I,Q;
        I = *fpos;
        fpos++;
        Q = *fpos;
        fpos++;
        printf("%f,%f\r\n ",I,Q);
    }

    printf("\r\n");
}

#if(USELUT==1)
void InitializeLUT()
{
    lutinited = true;
    unsigned short idx;// = -32767; // -32767 .. +32767
    short sval;
    //short
    float v;
    for(unsigned c = 0; c < 65536; c++)
    {
        idx = QVRTSwap16(c);
        sval = (short)idx;
        v = ((float)sval) / 32768.0f;
        IQLUT[c] = v;//
    }
}
#endif

QVRT_IQDataPacket::QVRT_IQDataPacket()
{
    //set up some default values
    StreamID = 1;
    Frac_Sec_TS = 0;
    trailer = 0x00100000;
    //initialize look up table
#if(USELUT==1)
    if(lutinited == false)
        InitializeLUT();
#endif
}

// copy data from this to the target
void QVRT_IQDataPacket::CopyTo(QVRT_IQDataPacket *target)
{
    target->StreamID = StreamID;
    target->Frac_Sec_TS = Frac_Sec_TS;
    target->trailer = trailer;
}

bool QVRT_IQDataPacket::Match(unsigned char *data, unsigned int SID)
{
    unsigned int * dp = (unsigned int *)data;
    dp++; // skip over header

    //we're using this as a filter, we don't know ahead of time which IQDataPackets
    //hold data for which stream, if this is not the stream we're decoding, simply move on...
    StreamID = QVRTSwap32 (*dp);
    if(SID != StreamID)
        return false;

    return true;
}

bool QVRT_IQDataPacket::Decode(unsigned char *data,CircBuff<complex<float>> *samplesout, unsigned int SID)
{
    static float fdata[MAX_DATA_PACKET_SAMPLES*2]; // MAX_DATA_PACKET_SAMPLES total samples, each with I/Q
    uint32_t * dp = (uint32_t *)data;
    dp += QVRT_Packet::Decode(data); //decode the common stuff
    m_numsamples = datasize;
    //we're using this as a filter, we don't know ahead of time whcih IQDataPackets
    //hold data for which stream, if this is not the stream we're decoding, simply move on...
    if(SID != StreamID)
        return false;

    //we should now have the proper number of samples
    //dp now points to the start of the data section
    unsigned short * spos = (unsigned short *)dp;
    float *fpos = fdata;
    for(uint32_t c= 0; c < m_numsamples; c++)
    {
        *fpos = IQLUT[*spos];
        fpos++;
        spos++;

        *fpos = IQLUT[*spos];
        fpos++;
        spos++;
    }
    //get a complex pointer to the data by casting
    complex<float> *cp_ptr = (complex<float> *)fdata;
    //write the converted samples into the circular buffer
    samplesout->write(cp_ptr,m_numsamples);
    dp += m_numsamples; // move past the data portion
    if(header.trailer_present)
    {
        //read the trailer
        trailer = QVRTSwap32 (*dp);
        dp++;
    }
    return true;
}


bool QVRT_IQDataPacket::Decode(unsigned char *data,CircBuff_No_lock<complex<float>> *samplesout, unsigned int SID)
{
    static float fdata[MAX_DATA_PACKET_SAMPLES*2]; // MAX_DATA_PACKET_SAMPLES total samples, each with I/Q
    uint32_t * dp = (uint32_t *)data;
    dp += QVRT_Packet::Decode(data); //decode the common stuff

    m_numsamples = datasize;
    //we're using this as a filter, we don't know ahead of time whcih IQDataPackets
    //hold data for which stream, if this is not the stream we're decoding, simply move on...
    if(SID != StreamID)
        return false;

    //we should now have the proper number of samples
    //dp now points to the start of the data section
    unsigned short * spos = (unsigned short *)dp;
    float *fpos = fdata;
    for(uint32_t c= 0; c < m_numsamples; c++)
    {
        *fpos = IQLUT[*spos];
        fpos++;
        spos++;

        *fpos = IQLUT[*spos];
        fpos++;
        spos++;
    }
    //get a complex pointer to the data by casting
    complex<float> *cp_ptr = (complex<float> *)fdata;
    //write the converted samples into the circular buffer
    samplesout->write(cp_ptr,m_numsamples);
    dp += m_numsamples; // move past the data portion
    if(header.trailer_present)
    {
        //read the trailer
        trailer = QVRTSwap32 (*dp);
        dp++;
    }
    return true;
}



/*
    This function takes a pointer to a circular buffer that holds floats
    It generates a stream of interleaved I/Q data into the buffer
*/
/*
bool QVRT_IQDataPacket::Decode(unsigned char *data,CircBuff<float> *samplesout, unsigned int SID)
{
    static float fdata[MAX_DATA_PACKET_SAMPLES*2]; // MAX_DATA_PACKET_SAMPLES total samples, each with I/Q
    unsigned int * dp = (unsigned int *)data;
    header.Decode(data);
    dp++; // skip over header

    StreamID = QVRTSwap32 (*dp);
    dp++; // move to the next position

    m_numsamples = header.size;
    m_numsamples -= 2; // take away 2 words for header and stream ID

    if(header.TSI)
    {
        Int_Sec_TS = QVRTSwap32 (*dp);
        dp++; // move past the int timestamp
        m_numsamples -= 1; //take away 1 for integer header
    }
    if(header.TSF)
    {
        unsigned long long int *ldp;
        ldp = (unsigned long long int *)dp;
        Frac_Sec_TS = QVRTSwap64(*ldp);
        dp += 2;
        m_numsamples -= 2; //take away 2 words for fractional header
    }

    if(header.trailer_present)
    {
        m_numsamples -= 1; // take away 1 word for trailer space
    }

    //we're using this as a filter, we don't know ahead of time whcih IQDataPackets
    //hold data for which stream, if this is not the stream we're decoding, simply move on...
    if(SID != StreamID)
        return false;

    //we should now have the proper number of samples
    //dp now points to the start of the data section
    unsigned short * spos = (unsigned short *)dp;
    float *fpos = fdata;
#if(USELUT == 0)    // declare these vars when NOT using the LUT
    short Isval,Qsval;
    float Ifval,Qfval;
#endif
    for(uint32_t c= 0; c < m_numsamples; c++)
    {
#if(USELUT == 1)
        *fpos = IQLUT[*spos];
        fpos++;
        spos++;

        *fpos = IQLUT[*spos];
        fpos++;
        spos++;
#else
        //get I and Q in encoded shorts
        //swap endianess
        Isval = swapOrder16(*spos);
        spos ++;
        Qsval = swapOrder16(*spos);
        spos++;
        //decode the samples into floats and store them in the circular buffer

         Ifval = Isval;
         Ifval /= 32768.0f;

         Qfval = Qsval;
         Qfval /= 32768.0f;

        *fpos = Ifval;
        fpos++;
        *fpos = Qfval;
        fpos++;
#endif
    }
    //write the converted samples into the circular buffer
    samplesout->write(fdata,m_numsamples * 2);
    dp += m_numsamples; // move past the data portion
    if(header.trailer_present)
    {
        //read the trailer
        trailer = QVRTSwap32 (*dp);
        dp++;
    }
    return true;
}
*/
/*
This function is used to encode the IQ data into signed shorts that are packed
into the *data pointer.
IN:
unsigned char *data : This is a pre-allocated 4k block where the data will be written
circ_buff *samplesin : This is a circular buffer that holds I/Q data samples to be packed.

Note:
    StreamID and Frac_Sec_TS should both be correct prior to encoding

    This is the 2.6.5 style of encoding data packets, the 3.0 version is different
*/
void QVRT_IQDataPacket::Encode(unsigned char *data,CircBuff<float> *samplesin)
{
   // printf("QVRT_IQDataPacket::Encode 1\r\n");
    static QVRT_Header header;
    static bool first = true;
    if(first)
    {
 //           printf("QVRT_IQDataPacket::Encode 2\r\n");
        first = false;
        header.packetType = 1;
        header.class_id_present = 0;
        header.trailer_present = 1;
        header.reserved = 0;
        header.TSM = 0;
        header.TSI = 0;
        header.TSF = 3;
        header.size = 1000;
    }
//    printf("QVRT_IQDataPacket::Encode 3\r\n");
    unsigned int * dp = (unsigned int *)data;
    dp++; // skip over header
    *dp = QVRTSwap32 (StreamID); // pack the stream ID in the correct endian order
    dp++;
 //       printf("QVRT_IQDataPacket::Encode 4\r\n");
    unsigned long long int *ldp;
    // get a 64bit pointer to the current position
    ldp = (unsigned long long int *)dp;
    // write the fractional timestamp
    *ldp = QVRTSwap64(Frac_Sec_TS);
    // increment the pointer 2 x 32 bits forward
    dp += 2;
    //dp now points to the start of the data section
    static float fdata[995*2]; // 995 total samples, each with I/Q
    short *spos = (short *)dp;
    short Isval,Qsval;
    float Ifval,Qfval;
    float *fpos = fdata;
//    printf("QVRT_IQDataPacket::Encode 5\r\n");
    //read in 995 samples to encode
    int read = samplesin->read(fdata,995 * 2);
    if(read != 995*2)
    {
        printf("Error with IQ samples\r\n");
    }
    for(int c= 0; c < 995; c++)
    {
        // get the current I / Q into some floats
        Ifval = *fpos;
        fpos++;
        Qfval = *fpos;
        fpos++;
        //convert those floats into fixed point shorts
        Isval = (short)(Ifval * 32768);
        Qsval = (short)(Qfval * 32768);
        *spos = QVRTSwap16(Isval);
        spos++;
        *spos = QVRTSwap16(Qsval);
        spos++;
    }
 //       printf("QVRT_IQDataPacket::Encode 6\r\n");
    //write trailer
    //get int pointer to area
    dp = (unsigned int *)spos;
    *dp = QVRTSwap32 (0x00100000);
    header.count++;
    header.Encode(data);

}

