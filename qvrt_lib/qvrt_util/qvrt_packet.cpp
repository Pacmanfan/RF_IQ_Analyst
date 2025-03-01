#include <qvrt_tools.h>



uint32_t QVRT_Packet::Decode(unsigned char *data)
{
    // ----- Read the header -----
    uint32_t * dp = (unsigned int *)data;
    header.Decode(data);
    dp++; // move past header

    uint32_t rawheader = QVRTSwap32(header.encodedheader);
    datasize = (rawheader & 0xffff) - 1;

    if(header.packetType == QVRT_IQ_DATA ||
            header.packetType == QVRT_EXT_DATA ||
            header.packetType == QVRT_IF_CONTEXT ) // we have a stream ID with this packet
    {
        StreamID = QVRTSwap32 (*dp);
        dp++; // move past StreamID
        datasize--;
    }

    if(header.class_id_present)
    {
        uint64_t *ldp = (uint64_t *)dp;
        class_id = *ldp;
        class_id = QVRTSwap64 (class_id);
        dp++; //
        dp++; //
        datasize -= 2;
    }

    // ----- Read the integer timestamp -----
    if (header.TSI != TSI_NO_INT_TS)
    {
        Int_Sec_TS = QVRTSwap32 (*dp);
        dp++;
        datasize--;
    }

    // ----- Read the fractional timestamp -----
    if (header.TSF != TSF_NO_FRAC_TS)
    {
        uint64_t *ldp = (uint64_t *)dp;
        Frac_Sec_TS = QVRTSwap64 (*ldp);
        dp++;
        dp++;
        datasize -= 2;
    }

    // ----- Check for trailer -----
    if (header.trailer_present)
    {
        datasize--;
    }
    uint32_t num = header.size - datasize; // number of words read
    return  num;
}

void QVRT_Packet::Dump()
{
    cout << "QVRT_Packet:**********************************\r\n";
    cout << "Packet Type : 0x0" << header.packetType << "\r\n";
    cout << "Packet Name :" << PacketType2Name(header.packetType).c_str() << "\r\n";

    if(header.packetType == QVRT_IQ_DATA ||
            header.packetType == QVRT_EXT_DATA ||
            header.packetType == QVRT_IF_CONTEXT ) // we have a stream ID with this packet
    {
        cout << "StreamID: " << StreamID << "\r\n";
    }

    if(header.class_id_present)
    {
        cout << "Class Id : " << class_id << "\r\n";
    }

    if (header.TSI != TSI_NO_INT_TS)
    {
        cout << "Integer Timestamp Type: " << TSI2Name(header.TSI) << "\r\n";
        cout << "Integer Timestamp : " << Int_Sec_TS << "\r\n";
    }

    if (header.TSF != TSF_NO_FRAC_TS)
    {
        cout << "Fractional Timestamp Type: " << TSF2Name(header.TSF) << "\r\n";
        cout << "Fractional Timestamp : " << Fixed64ToDouble(Frac_Sec_TS) << "\r\n";
    }
    cout << "Data Size : " << datasize << " 4-byte words ; " << datasize*4 << " total bytes \r\n";
    cout << "**********************************:QVRT_Packet\r\n";
}

void QVRT_Packet::Summary()
{
    cout << PacketType2Name(header.packetType).c_str() << ": ";
    cout << "0x0" << header.packetType << ": ";
    cout << "Data Size : " << datasize << ": ";

    if(header.packetType == QVRT_IQ_DATA ||
            header.packetType == QVRT_EXT_DATA ||
            header.packetType == QVRT_IF_CONTEXT ) // we have a stream ID with this packet
    {
        cout << "StreamID: " << StreamID << ": ";
    }
    if (header.TSI != TSI_NO_INT_TS)
    {
        cout << TSI2Name(header.TSI) << ": ";
        cout << Int_Sec_TS << ": ";
    }

    if (header.TSF != TSF_NO_FRAC_TS)
    {
        cout << TSF2Name(header.TSF) << ": ";
        cout << Fixed64ToDouble(Frac_Sec_TS) << ": ";
    }
    cout << "\r\n";
}

void QVRT_Packet::FormatTimestamp(char *str)
{
    sprintf(str,"Integer Timestamp Type: %s : %d :: Fractional Timestamp Type: %s : %f ",TSI2Name(header.TSI).c_str(),Int_Sec_TS,TSF2Name(header.TSF).c_str(),Fixed64ToDouble(Frac_Sec_TS));
}
