
#include "qvrt_tools.h"

QVRT_IFContext_Packet::QVRT_IFContext_Packet()
{
    memset(this,0,sizeof(QVRT_IFContext_Packet));
}

void QVRT_IFContext_Packet::CopyTo(QVRT_IFContext_Packet *target)
{
    memcpy(target,this,sizeof(QVRT_IFContext_Packet));
}

void QVRT_IFContext_Packet::Decode(unsigned char *data)
{
    uint64_t *ldp;
    uint32_t * dp = (uint32_t *)data;
    dp += QVRT_Packet::Decode(data); //decode the common stuff

    tunerid = (StreamID & 0x3f);
    usertunerid = ((StreamID >> 7) & 0xffff);
    sourcetunerid = ((StreamID >> 23) & 0x3f);

    //copy all the data before parsing
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
    //dp += datasize; // don't move past it, we're still parsing...

    // context section
    unsigned int flags = QVRTSwap32(*dp);
    dp ++;
    f_ContextFieldIndicatorChange = (flags >> 31) & 0x01;
    f_ReferencePointIndicator = (flags >> 30) & 0x01;
    f_Bandwidth = (flags >> 29) & 0x01;
    f_RFReferenceFrequency = (flags >> 27) & 0x01;
    f_RFReferenceFrequencyOffset = (flags >> 26) & 0x01;
    f_ReferenceLevel = (flags >> 24) & 0x01;
    f_Gain = (flags >> 23) & 0x01;
    f_OverRangeCount = (flags >> 22) & 0x01;
    f_SampleRate = (flags >> 21) & 0x01;
    f_TimestampCalibrationTime = (flags >> 19) & 0x01;
    f_FormattedGPSGeolocation = (flags >> 14) & 0x01;

    if(f_ContextFieldIndicatorChange != 0 )
    {
        f_ContextFieldIndicatorChange = f_ContextFieldIndicatorChange;
    }

    if(f_ReferencePointIndicator != 0)
    {
        ReferencePointIndicator = QVRTSwap32 (*dp);
        dp++; // move to the next position
    }

    if(f_Bandwidth !=0)
    {
        ldp = (uint64_t *)dp;
        //Bandwidth_Fixed = QVRTSwap64(*ldp);
        dBandwidth = Fixed64ToDouble(QVRTSwap64(*ldp));
        dp++; // move to the next position
        dp++; // move to the next position

    }
    if(f_RFReferenceFrequency != 0)
    {
        ldp = (uint64_t *)dp;
        //RFReferenceFrequency_Fixed = QVRTSwap64(*ldp);
        dRFReferenceFrequency = Fixed64ToDouble(QVRTSwap64(*ldp));
        dp++; // move to the next position
        dp++; // move to the next position       
    }
    if(f_RFReferenceFrequencyOffset != 0)
    {
        ldp = (uint64_t *)dp;
        dRFReferenceFrequencyOffset = Fixed64ToDouble(QVRTSwap64(*ldp));
        dp++; // move to the next position
        dp++; // move to the next position
    }

    if(f_ReferenceLevel != 0)
    {
        unsigned int tref = *dp;
        dReferenceLevel = ((int16_t) (tref & 0xffff)) * 0.0078125f;     // Q8.7 fixed point
        dp++; // move to the next position
    }

    if(f_Gain !=0)
    {
        uint32_t d = QVRTSwap32 (*dp);
        Gain = d;
        dRFGain = ((int16_t) (d & 0xffff)) * 0.0078125f;         // Q8.7 fixed point
        dIFGain = ((int16_t) ((d>>16) & 0xffff)) * 0.0078125f;   // Q8.7 fixed point
        dp++;
    }

    if(f_OverRangeCount !=0)
    {
        OverRangeCount = QVRTSwap32 (*dp);
        dp++;
    }

    if(f_SampleRate !=0)
    {
        ldp = (uint64_t *)dp;
        dSampleRate =  Fixed64ToDouble(QVRTSwap64(*ldp));
        dp++; // move to the next position
        dp++; // move to the next position
    }
    if(f_TimestampCalibrationTime != 0)
    {
        TimestampCalibrationTime = QVRTSwap32 (*dp);
        dp++; // move to the next position
    }
    if(f_FormattedGPSGeolocation !=0)
    {
        // read 11 * 4 bytes and follow document formatting.
        unsigned int itmp = QVRTSwap32(*dp);
        TSI = (itmp >> 26) & 0x03;
        TSF = (itmp >> 24) & 0x03;
        GPS_INS_Manufacturer_OUI = (itmp & 0x00FFFFFF);
        dp++;
        ISTSPF = QVRTSwap32(*dp);
        dp++;
        FSTPF1 = QVRTSwap32(*dp);
        dp++;
        FSTPF2 = QVRTSwap32(*dp);
        dp++;
        Latitude = QVRTAngleNumber(QVRTSwap32(*dp));//Fixed32ToDouble(QVRTSwap32(*dp),22);
        dp++;
        Longitude = QVRTAngleNumber (QVRTSwap32(*dp));//Fixed32ToDouble(QVRTSwap32(*dp),22);
        dp++;
        Altitude = QVRTAltitudeNumber (QVRTSwap32(*dp));//Fixed32ToDouble(QVRTSwap32(*dp),5);
        dp++;
        SpeedOverGround = QVRTSpeedNumber (QVRTSwap32(*dp));//Fixed32ToDouble(QVRTSwap32(*dp),16);
        dp++;
        HeadingAngle = QVRTAngleNumber (QVRTSwap32(*dp));//Fixed32ToDouble(QVRTSwap32(*dp),22);
        dp++;
        TrackAngle = QVRTAngleNumber (QVRTSwap32(*dp));//Fixed32ToDouble(QVRTSwap32(*dp),22);
        dp++;
        MagneticVariation = QVRTAngleNumber (QVRTSwap32(*dp));//Fixed32ToDouble(QVRTSwap32(*dp),22);
        dp++;
    }

    // ----- Read the trailer -----
    if (header.trailer_present)
    {
        trailer = *dp;
        dp++;
        trailer = QVRTSwap32 (trailer);
    }

}


void QVRT_IFContext_Packet::Encode(unsigned char *data)
{
    unsigned int * dp = (unsigned int *)data;
    dp++; // skip over header
    *dp = QVRTSwap32(StreamID);//
    dp++; // move to the next position
    unsigned long long int *ldp;
    ldp = (unsigned long long int *)dp;
    *ldp = QVRTSwap64(Frac_Sec_TS);
    dp += 2;
    unsigned int flags = 0;
    flags |= (f_ContextFieldIndicatorChange & 0x01) << 31;
    flags |= (f_ReferencePointIndicator & 0x01) << 30;
    flags |= (f_Bandwidth & 0x01) << 29;
    flags |= (f_RFReferenceFrequency & 0x01) << 27;
    flags |= (f_RFReferenceFrequencyOffset & 0x01) << 26;
    flags |= (f_ReferenceLevel & 0x01) << 24;
    flags |= (f_Gain & 0x01) << 23;
    flags |= (f_OverRangeCount & 0x01) << 22;
    flags |= (f_SampleRate & 0x01) << 21;
    flags |= (f_TimestampCalibrationTime & 0x01) << 19;
    flags |= (f_FormattedGPSGeolocation & 0x01) << 14;

    *dp = QVRTSwap32(flags);
    dp++;

    if(f_ReferencePointIndicator != 0)
    {
        *dp = QVRTSwap32(ReferencePointIndicator);
        dp++; // move to the next position
    }
    if(f_Bandwidth !=0)
    {
        ldp = (unsigned long long int *)dp;
        *ldp = QVRTSwap64(DoubleTo64Fixed(dBandwidth));
        dp++; // move to the next position
        dp++; // move to the next position
    }

    if(f_RFReferenceFrequency != 0)
    {
        ldp = (unsigned long long int *)dp;
        *ldp = QVRTSwap64(DoubleTo64Fixed(dRFReferenceFrequency));
        dp++; // move to the next position
        dp++; // move to the next position

    }
    if(f_RFReferenceFrequencyOffset != 0)
    {
        ldp = (unsigned long long int *)dp;
        *ldp = QVRTSwap64(DoubleTo64Fixed(dRFReferenceFrequencyOffset));
        dp++; // move to the next position
        dp++; // move to the next position

    }

    if(f_ReferenceLevel != 0)
    {
        *dp = QVRTSwap32(QVRTRefLevelNumber(dReferenceLevel));
        //*dp = QVRTSwap32(DoubleToFixed16(dReferenceLevel,7));// & 0x0000ffff;
        dp++; // move to the next position
    }

    if(f_Gain !=0)
    {
        *dp = QVRTSwap32(QVRTGainStageNumber (dRFGain, dIFGain));
        dp++;
    }
    if(f_OverRangeCount !=0)
    {
        *dp = QVRTSwap32(OverRangeCount);
        dp++;
    }

    if(f_SampleRate !=0)
    {
        ldp = (unsigned long long int *)dp;
        *ldp = QVRTSwap64(DoubleTo64Fixed(dSampleRate));
        dp++; // move to the next position
        dp++; // move to the next position

    }

    if(f_TimestampCalibrationTime != 0)
    {
        *dp = QVRTSwap32(TimestampCalibrationTime);
        dp++; // move to the next position
    }
    if(f_FormattedGPSGeolocation !=0)
    {

        unsigned int itmp = 0;
        itmp |= ((TSI & 0x03) << 26);
        itmp |= ((TSF & 0x03) << 24);
        itmp |= GPS_INS_Manufacturer_OUI;
        *dp = QVRTSwap32(itmp);
        dp++;

        //ISTSPF = QVRTSwap32(*dp);
        *dp = QVRTSwap32(ISTSPF);
        dp++;

        //FSTPF1 = QVRTSwap32(*dp);
        *dp = QVRTSwap32(FSTPF1);
        dp++;

        //FSTPF2 = QVRTSwap32(*dp);
        *dp = QVRTSwap32(FSTPF2);
        dp++;

       // Latitude = Fixed32ToDouble(QVRTSwap32(*dp),22);
        *dp = QVRTSwap32(DoubleToFixed32(Latitude,22));
        dp++;

       // Longitude = Fixed32ToDouble(QVRTSwap32(*dp),22);
        *dp = QVRTSwap32(DoubleToFixed32(Longitude,22));
        dp++;

        //Altitude = Fixed32ToDouble(QVRTSwap32(*dp),5);
        *dp = QVRTSwap32(DoubleToFixed32(Altitude,5));
        dp++;

        //SpeedOverGround = Fixed32ToDouble(QVRTSwap32(*dp),16);
        *dp = QVRTSwap32(DoubleToFixed32(SpeedOverGround,16));
        dp++;

       // HeadingAngle = Fixed32ToDouble(QVRTSwap32(*dp),22);
        *dp = QVRTSwap32(DoubleToFixed32(HeadingAngle,22));
        dp++;

       // TrackAngle = Fixed32ToDouble(QVRTSwap32(*dp),22);
        *dp = QVRTSwap32(DoubleToFixed32(TrackAngle,22));
        dp++;

        //MagneticVariation = Fixed32ToDouble(QVRTSwap32(*dp),22);
        *dp = QVRTSwap32(DoubleToFixed32(MagneticVariation,22));
        dp++;
    }
    //encode the header
    static QVRT_Header header;
    static bool first = true;
    if(first)
    {
        first = false;
        header.packetType = 4;
        header.class_id_present = 0;
        header.trailer_present = 0;
        header.reserved = 0;
        header.TSM = 1;
        header.TSI = 0;
        header.TSF = 1;
        header.count = 0;
        header.size = 26;
    }
    header.count ++;
    header.Encode(data);
}

void QVRT_IFContext_Packet::Dump()
{
    QVRT_Packet::Dump();
    printf("**QVRT_IFContext_Packet\r\n");
    printf("StreamID = %d\r\n",StreamID);
    printf("sourcetunerid = %d\r\n",sourcetunerid);
    printf("usertunerid = %d\r\n",usertunerid);
    printf("tunerid = %d\r\n",tunerid);
    printf("Frac_Sec_TS fixed = %ld\r\n",Frac_Sec_TS);
    printf("Fractional Timestamp  = %f\r\n", Fixed64ToDouble(Frac_Sec_TS));
    printf("Flag f_ContextFieldIndicatorChange:%d\r\n",f_ContextFieldIndicatorChange);
    printf("Flag f_ReferencePointIndicator:%d\r\n",f_ReferencePointIndicator);
    printf("Flag f_Bandwidth:%d\r\n",f_Bandwidth);
    printf("Flag f_RFReferenceFrequency:%d\r\n",f_RFReferenceFrequency);
    printf("Flag f_RFReferenceFrequencyOffset:%d\r\n",f_RFReferenceFrequencyOffset);
    printf("Flag f_ReferenceLevel:%d\r\n",f_ReferenceLevel);
    printf("Flag f_Gain:%d\r\n",f_Gain);
    printf("Flag f_OverRangeCount:%d\r\n",f_OverRangeCount);
    printf("Flag f_SampleRate:%d\r\n",f_SampleRate);
    printf("Flag f_TimestampCalibrationTime:%d\r\n",f_TimestampCalibrationTime);
    printf("Flag f_FormattedGPSGeolocation:%d\r\n",f_FormattedGPSGeolocation);

    if(f_ReferencePointIndicator != 0)
    {
        printf("ReferencePointIndicator : %u\r\n",ReferencePointIndicator);
    }

    if(f_Bandwidth !=0)
    {      
        printf("dBandwidth : %f\r\n",dBandwidth);
    }

    if(f_RFReferenceFrequency != 0)
    {      
        printf("dRFReferenceFrequency : %f\r\n",dRFReferenceFrequency);
    }
    if(f_RFReferenceFrequencyOffset != 0)
    {
        printf("f_RFReferenceFrequencyOffset : %i\r\n",f_RFReferenceFrequencyOffset);
    }

    if(f_ReferenceLevel != 0)
    {      
        printf("dReferenceLevel %f\r\n",dReferenceLevel);
    }

    if(f_Gain !=0)
    {
        printf("Encoded Gain %u\r\n",Gain);
        printf("dRFGain = %f\r\n",dRFGain);
        printf("dIFGain = %f\r\n",dIFGain);
    }
    if(f_OverRangeCount !=0)
    {
        printf("OverRangeCount %u\r\n",OverRangeCount);
    }

    if(f_SampleRate !=0)
    {    
        printf("dSampleRate : %f\r\n",dSampleRate);
    }
    if(f_TimestampCalibrationTime != 0)
    {
        printf("TimestampCalibrationTime : %u\r\n",TimestampCalibrationTime);
    }

    if(f_FormattedGPSGeolocation !=0)
    {
        printf("TSI : %u \r\n",TSI);
        printf("TSF : %u \r\n",TSF);
        printf("GPS_INS_Manufacturer_OUI %u\r\n",GPS_INS_Manufacturer_OUI);
        printf("ISTSPF %u\r\n",ISTSPF);
        printf("FSTPF1 %u\r\n",FSTPF1);
        printf("FSTPF2 %u\r\n",FSTPF2);
        printf("Latitude %f\r\n",Latitude);
        printf("Longitude %f\r\n",Longitude);
        printf("Altitude %f\r\n",Altitude);
        printf("SpeedOverGround %f\r\n",SpeedOverGround);
        printf("HeadingAngle %f\r\n",HeadingAngle);
        printf("TrackAngle %f\r\n",TrackAngle);
        printf("MagneticVariation %f\r\n",MagneticVariation);
    }

}

void QVRT_IFContext_Packet::PrintGPS()
{
    if(f_FormattedGPSGeolocation != 0)
    {
        printf("%f,%f,%f\r\n",Longitude,Latitude,Altitude);
    }
}

void QVRT_IFContext_Packet::StartGPSPrint()
{
    printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
    printf("<kml xmlns=\"http://www.opengis.net/kml/2.2\">\r\n");
    printf("<Document>\r\n");
    printf("<name>Paths</name>\r\n");
    printf("<description>Extracted GPS information from QVRT file </description>\r\n");
    printf("<Style id=\"yellowLineGreenPoly\">\r\n");
    printf("<LineStyle>\r\n");
    printf("<color>7f00ffff</color>\r\n");
    printf("<width>4</width>\r\n");
    printf("</LineStyle>\r\n");
    printf("<PolyStyle>\r\n");
    printf("<color>7f00ff00</color>\r\n");
    printf("</PolyStyle>\r\n");
    printf("</Style>\r\n");
    printf("<Placemark>\r\n");
    printf("<name>Absolute Extruded</name>\r\n");
    printf("<description>Transparent green wall with yellow outlines</description>\r\n");
    printf("<styleUrl>#yellowLineGreenPoly</styleUrl>\r\n");
    printf("<LineString>\r\n");
    printf("<extrude>1</extrude>\r\n");
    printf("<tessellate>1</tessellate>\r\n");
    printf("<altitudeMode>absolute</altitudeMode>\r\n");
    printf("<coordinates>\r\n");
    /*

         -112.2550785337791,36.07954952145647,2357
          -112.2549277039738,36.08117083492122,2357
          -112.2552505069063,36.08260761307279,2357
          -112.2564540158376,36.08395660588506,2357
          -112.2580238976449,36.08511401044813,2357
          -112.2595218489022,36.08584355239394,2357
          -112.2608216347552,36.08612634548589,2357
          -112.262073428656,36.08626019085147,2357
          -112.2633204928495,36.08621519860091,2357
          -112.2644963846444,36.08627897945274,2357
          -112.2656969554589,36.08649599090644,2357
*/
}

void QVRT_IFContext_Packet::EndGPSPrint()
{
    printf(" </coordinates>\r\n");
    printf("</LineString>\r\n");
    printf("</Placemark>\r\n");
    printf("</Document>\r\n");
    printf("</kml>\r\n");
}
