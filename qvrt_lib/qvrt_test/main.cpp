/*
#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <boost/program_options.hpp> // for command line parsing

#include "qvrt_tools.h"

using namespace std;

#define DEBUG

namespace po = boost::program_options;
po::variables_map vm;
po::options_description desc("QVRT / 16T Convert options");
bool printheaders = false;
bool mathtest = false;
bool dumpiq = false;
bool dumpgps = false;
int dumpiqcnt =0;


//New test tool
//Stage 1: dump QVRT packets from file
//Stage 2: encode QVRT packets (use random I/Q data)


void SetupOptions();

void DumpGPS(string fn, int streamid)
{
    QVRT_Reader reader;
    if(!reader.Open(fn))
    {
        printf("Could not open file %s\r\n",fn.c_str());
        return;
    }

    QVRT_Header *header;
    QVRT_ExtDataPacket extdata;
    QVRT_IFContext_Packet ifctx;
    QVRT_ExtContext_Packet exctx;
    unsigned char *data = 0;
    long packetnumber = 0;
    long extensionContextCount = 0;

    // read the first chunk
    header = reader.ReadNextPacket();

    ifctx.StartGPSPrint();

    while(header != 0)
    {
        packetnumber++;
        data = reader.CurrentBufferPos();

        switch(header->packetType)
        {
            case QVRT_IQ_DATA:

                break;
            case QVRT_EXT_DATA:
                //extdata.Decode(data);
               // extdata.PrintGPS();

            case QVRT_EXT_DATA_NO_STREAMID:
                extdata.Decode(data);
                extdata.PrintGPS();

                break;
            case QVRT_IF_CONTEXT:
                ifctx.Decode(data);
                if(ifctx.StreamID == streamid)
                    ifctx.PrintGPS();


                break;
            case QVRT_EXT_CONTEXT:
               // extensionContextCount++;
               // exctx.Decode(data);

                break;
            default:

                printf("INVALID PACKET TYPE %d\n",header->packetType);

        }
        header = reader.ReadNextPacket();
    }
    ifctx.EndGPSPrint();

    return;
}

void QVRTSampleTest(std::string fn)
{
    printf("Sampletest 1\r\n");
    QVRT_FileInfo fileinfo;
    fileinfo.GatherInfo(fn);
    fileinfo.Dump();
    printf("Sampletest 2\r\n");

    uint32_t streamid = fileinfo.GetStreamInfoIndex(0)->StreamID;
    QVRT_Reader reader;
    long samplecount = 0;
    long retval = -1;
    if(!reader.Open(fn))
    {
        printf("Could not open file %s\r\n",fn.c_str());
        return;
    }
    printf("Sampletest 3\r\n");

    complex<float> *cbuff = new complex <float>[100000];

    while(retval != 0)
    {
        retval = reader.ReadSamples(cbuff,1024);
        samplecount += retval;
    }



    printf("Sampletest 5\r\n");
    printf("\r\n");
    printf("****************************************************\r\n");
    printf("QVRT Statistics:\r\n");

    printf("Stream %d total samples: %ld\r\n",streamid,samplecount);
    return;


}

//Gather info about streams, but also get detailed info
void DumpInfo(string fn)
{
    QVRT_FileInfo fileinfo;
    fileinfo.GatherInfo(fn);
    fileinfo.Dump();

    QVRT_Reader reader;
    if(!reader.Open(fn))
    {
        printf("Could not open file %s\r\n",fn.c_str());
        return;
    }

    QVRT_Header *header;
    QVRT_IQDataPacket datapacket;
    QVRT_ExtDataPacket extdata;
    QVRT_IFContext_Packet ifctx;
    QVRT_ExtContext_Packet exctx;
    CircBuff<complex <float> > *cbuff = new CircBuff<complex <float> >(4*1024*1024);
    unsigned char *data = 0;
    long packetnumber = 0;
    long IFDataPacketCount_1 = 0;
    long IFDataPacketCount_2 = 0;
    long ExtensionDataPacketCount = 0;
    long IFContextPacketCount_1 = 0;
    long IFContextPacketCount_2 = 0;
    long extensionContextCount = 0;
  //  int stream1_DP_Numsamples = 0;
   // int stream2_DP_Numsamples = 0;

    long samplecount1 = 0;
    long samplecount2 = 0;
    bool extdatadumped = false;
    bool ifctxdumped1 = false;
    bool ifctxdumped2 = false;
    bool iqdatadumped1 = false;
    bool iqdatadumped2 = false;
    bool extctxdumped = false;
    // read the first chunk
    header = reader.ReadNextPacket();
    char timestamp[256];
    while(header != 0)
    {
        packetnumber++;
        data = reader.CurrentBufferPos();

        switch(header->packetType)
        {
            case QVRT_IQ_DATA:

                datapacket.Decode(data,cbuff,999);
                //datapacket.FormatTimestamp(timestamp);
                //printf("IQ Data 0x01: StreamID: %d ; Datasize: %d : %s\r\n",datapacket.StreamID,datapacket.datasize,timestamp);
                //datapacket.Dump(nullptr);
                datapacket.Summary();
                if(datapacket.StreamID == 1)
                {
                    if(dumpiq)
                    {
                        if(dumpiqcnt < 5)
                        {
                            datapacket.Decode(data,cbuff,1); // actually get the data
                           // datapacket.Dump(cbuff); // dump it
                            dumpiqcnt ++;
                        }
                    }
                    else
                    {
                        if(iqdatadumped1 == false)
                        {
                            iqdatadumped1 = true;
                           // datapacket.Dump(0);
                        }
                    }
                    IFDataPacketCount_1++;
                    samplecount1 += datapacket.m_numsamples;


                }
                if(datapacket.StreamID == 2)
                {
                    if(iqdatadumped2 == false)
                    {
                        iqdatadumped2 = true;
                       // datapacket.Dump(0);
                    }
                    IFDataPacketCount_2++;
                    samplecount2 += datapacket.m_numsamples;


                }

                break;
            case QVRT_EXT_DATA_NO_STREAMID: //0x02
                ExtensionDataPacketCount++;
                extdata.Decode(data);
                //printf("Extended Data Context 0x02 - no StreamID ; Datasize: %d\r\n",extdata.datasize);
               // DumpHexBlock(extdata.data_payload,extdata.datasize*4,32);
                //printf("\r\n");
                //extdata.Dump();
                extdata.Summary();

                break;
            case QVRT_EXT_DATA: // 0x03

                extdata.Decode(data);
                //printf("Extended Data Context 0x03: StreamID: %d ; Datasize: %d\r\n",extdata.StreamID,extdata.datasize);
                //DumpHexBlock(extdata.data_payload,extdata.datasize*4,32);
                //printf("\r\n");
                //extdata.Dump();
                extdata.Summary();


                break;
            case QVRT_IF_CONTEXT: // 0x04

                ifctx.Decode(data);
                ifctx.Summary();

                break;
            case QVRT_EXT_CONTEXT: // 0x05
                extensionContextCount++;
                exctx.Decode(data);
                exctx.Summary();

                break;
            default:

                printf("INVALID PACKET TYPE %d\n",header->packetType);

        }
        header = reader.ReadNextPacket();
    }


    printf("\r\n");
    printf("****************************************************\r\n");
    printf("Packet Statistics:\r\n");
    printf("Total number of packets: %ld\r\n",packetnumber);
    printf("Extension Context Packets: %ld\r\n",extensionContextCount);
    printf("IF Context Packets Stream 1: %ld\r\n",IFContextPacketCount_1);
    printf("IF Context Packets Stream 2: %ld\r\n",IFContextPacketCount_2);
    printf("Extension Data Packets: %ld\r\n",ExtensionDataPacketCount);

    printf("IF Data Packets Stream 1: %ld\r\n",IFDataPacketCount_1);
    printf("Stream 1 total samples: %ld\r\n",samplecount1);
    printf("IF Data Packets Stream 2: %ld\r\n",IFDataPacketCount_2);
    printf("Stream 2 total samples: %ld\r\n",samplecount2);
    return;
}

int main(int argc, char** argv)
{
    string filename;


    int streamid = 1;
    bool calcdelta = false;
    bool sampletest  = false;
    printheaders = true;
    SetupOptions();
    try
    {
         po::store(po::parse_command_line(argc, argv, desc),vm); // can throw
        if ( vm.count("help")  )
        {
            std::cout << "QVRT File Utility" << std::endl
                << desc << std::endl;
            return 0;
        }

        if(vm.count("file"))
            filename = vm["file"].as<string>();

        if(vm.count("stream"))
            streamid = vm["stream"].as<int>();

        if(vm.count("delta"))
            calcdelta = true;

        if(vm.count("sampletest"))
            sampletest = true;

        if(vm.count("iqdata"))
            dumpiq = true;

        if(vm.count("gps"))
            dumpgps = true;

        if(vm.count("header"))
            printheaders = true;

        if(vm.count("mathtest"))
            mathtest = true;

        po::notify(vm);
    }
    catch(po::error& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
        return -1;
    }

    if(mathtest)
    {
        //MathTest();
        exit(0);
    }

    if(dumpgps)
    {
        DumpGPS(filename,streamid);
    }

    DumpInfo(filename);

    if(sampletest)
    {
        printf("Running Sample Test");
        QVRTSampleTest(filename);
    }

    if(!sampletest && ! dumpgps)
        DumpInfo(filename);

}

void SetupOptions()
{
    desc.add_options()
        ("help,h", "Print help message")
        ("file,f", po::value<string>()->required(), "qvrt file")
        ("delta,d", "Examine time delta between IF Data packets")
        ("sampletest,x", "Perform a sample counting comparison between the 2 read methods")
        ("iqdata,i", "Dump 5 blocks of IQ data")
        ("gps,g", "Extract GPS information")
        ("header,p", "Print headers")
        ("stream,s", po::value<int>(), "Specify stream ID (normally 1 or 2) [default = 1]");
}

*/

