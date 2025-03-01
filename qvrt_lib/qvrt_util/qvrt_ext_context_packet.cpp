#include "qvrt_tools.h"


QVRT_ExtContext_Packet::QVRT_ExtContext_Packet()
{


}

void QVRT_ExtContext_Packet::Decode(unsigned char *data)
{
    uint32_t * dp = (uint32_t *)data;
    dp += QVRT_Packet::Decode(data); //decode the common stuff
    //copy the payload and move past it
    if(maxdatasize < datasize * 4)
    {
        maxdatasize = datasize * 4;
        if(data_payload != nullptr)
        {
            delete []data_payload;
        }
        data_payload = new unsigned char[datasize * 4];
    }
    memcpy(data_payload,dp,datasize * 4);
    // ----- Read the trailer -----
    if (header.trailer_present)
    {
        trailer = *dp;
        dp++;
        trailer = QVRTSwap32 (trailer);
    }
}

void QVRT_ExtContext_Packet::Encode(unsigned char *data)
{
   // data = data = 0; // to quiet the compiler
    UNUSED(data);

}

void QVRT_ExtContext_Packet::Dump()
{
    QVRT_Packet::Dump();

}
