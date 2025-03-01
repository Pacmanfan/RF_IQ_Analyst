#include "qvrt_tools.h"


QVRT_Header::QVRT_Header()
{
    count = 0;
    memset(this,0,sizeof(QVRT_Header));
}

// copy data from this to the target
void QVRT_Header::CopyTo(QVRT_Header *target)
{
    target->class_id_present = class_id_present;
    target->count = count;
    target->encodedheader = encodedheader;
    target->packetType = packetType;
    target->reserved = reserved;
    target->size = size;
    target->trailer_present = trailer_present;
    target->TSF = TSF;
    target->TSI = TSI;
    target->TSM = TSM;
}


void QVRT_Header::Decode(unsigned char *data)
{
    uint32_t *ptr = (uint32_t *)data;
    uint32_t header = *ptr;
    encodedheader = header;
    uint32_t hs = QVRTSwap32(header); // swap the header
    packetType = (hs >> 28) & 0x000f;
    class_id_present = (hs >> 27) & 0x01;
    trailer_present = (hs >> 26) & 0x01;
    reserved = (hs >> 25) & 0x01;
    TSM = (hs >> 24) & 0x01;
    TSI = (hs >> 22) & 0x03;
    TSF = (hs >> 20) & 0x03;
    count = (hs >> 16) & 0x000f;
    size = hs & 0x0000ffff;
}


void QVRT_Header::Encode(unsigned char *data)
{
    unsigned int *ptr = (unsigned int *)data;
//    unsigned int header = *ptr;
//    encodedheader = header;
    int hs = 0;// QVRTSwap32(header); // swap the header
    //packetType = (hs >> 28) & 0x000f;
    hs |= ((packetType & 0x000f) << 28);
    //class_id_present = (hs >> 27) & 0x01;
    hs |= ((class_id_present & 0x01) << 27);
    //trailer_present = (hs >> 26) & 0x01;
    hs |= ((trailer_present & 0x01) << 26);
    //reserved = (hs >> 25) & 0x01;
    hs |= ((reserved & 0x01) << 25);
    //TSM = (hs >> 24) & 0x01;
    hs |= ((TSM & 0x01) << 24);
    //TSI = (hs >> 22) & 0x03;
    hs |= ((TSI & 0x03) << 22);
   // TSF = (hs >> 20) & 0x03;
    hs |= ((TSF & 0x03) << 20);
    //count = (hs >> 16) & 0x000f;
    hs |= ((count & 0x000f) << 16);
    //size = hs & 0x0000ffff;
    hs |= ((size & 0x0000ffff));
    //save in the encoded header
    encodedheader = QVRTSwap32(hs);
    *ptr = encodedheader;
}

void QVRT_Header::Dump()
{
    /*
    printf("**QVRT Header:\r\n");
    printf("encoded header = %x\r\n",encodedheader);
    printf("encoded header swapped = %x\r\n",QVRTSwap32(encodedheader));
    printf("packetType = %u\r\n",packetType);
    printf("Packet type name  = %s\r\n", PacketType2Name(packetType).c_str());
    printf("class_id_present = %u\r\n",class_id_present);
    printf("trailer_present = %u\r\n",trailer_present);
    printf("reserved = %u\r\n",reserved);
    printf("TSM (Course Timing)= %u\r\n",TSM);
    printf("TSI = %u\r\n",TSI);
    printf("TSI = %s\r\n",TSI2Name(TSI).c_str());
    printf("TSF = %u\r\n",TSF);
    printf("TSF = %s\r\n",TSF2Name(TSF).c_str());
    printf("count = %u\r\n",count);
    printf("size (bytes) = %u\r\n",size * 4);
    printf("**QVRT Header End\r\n");
    */
}
