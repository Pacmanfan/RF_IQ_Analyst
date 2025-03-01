
#include <qvrt_tools.h>
#include <include/rapidjson/document.h>
#include <include/rapidjson/prettywriter.h> // for stringify JSON
#include <cstdio>
#include <string>
#include <vector>
#include <stdio.h>      /* puts */
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */


using namespace rapidjson;

QVRT_ExtDataPacket::QVRT_ExtDataPacket()
{
    /*
    UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
    UUID uuid1(generator.create()); // time based
    Poco::DateTime now;
*/
//generate a time string

    time_t rawtime;
    struct tm * timeinfo;
    char timebuff [256];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (timebuff,256,"%Y_%m_%d_%H%M%S",timeinfo);

    m_systemTime = timebuff;//Poco::DateTimeFormatter::format(now, "%Y_%m_%d_%H%M%S" );
    m_fileDescription = "";
    m_recordingUUID = "";//uuid1.toString();
    m_radioSelection = "Radio_A";
    m_unitType = "WBT";
    m_hardwareVersion = "200";
    m_unitESN = "0000-0000";
    m_fimrwareVersion = "3.1.0.0";
    m_WBTLogFileFormatVersion = "2.1";
    m_GPSLatitude = -777777;
    m_GPSLongitude = -777777;
    m_GPSAltitude = -777777;
    m_GPSMagneticVariation = -777777;
    m_GPSFixUTCSeconds = 0;
    m_GPSfixStatus = "No Fix";
    _combined = false;

}

void QVRT_ExtDataPacket::CopyTo(QVRT_ExtDataPacket *target)
{
    target->m_fileDescription = m_fileDescription;
    target->m_fimrwareVersion = m_fimrwareVersion;
    target->m_GPSAltitude = m_GPSAltitude;
    target->m_GPSfixStatus = m_GPSfixStatus;
    target->m_GPSFixUTCSeconds = m_GPSFixUTCSeconds;
    target->m_GPSLatitude = m_GPSLatitude;
    target->m_GPSLongitude = m_GPSLongitude;
    target->m_GPSMagneticVariation = m_GPSMagneticVariation;
    target->m_hardwareVersion = m_hardwareVersion;
    target->m_radioSelection = m_radioSelection;
    target->m_radioSettingsA = m_radioSettingsA;
    target->m_radioSettingsB = m_radioSettingsB;
    target->m_recordingUUID = m_recordingUUID;
    target->m_systemTime = m_systemTime;
    m_tunerASettings.CopyTo(&target->m_tunerASettings);
    m_tunerBSettings.CopyTo(&target->m_tunerBSettings);
    m_tunerCombinedSettings.CopyTo(&target->m_tunerCombinedSettings);
    target->m_unitESN = m_unitESN;
    target->m_unitType = m_unitType;
    target->m_WBTLogFileFormatVersion = m_WBTLogFileFormatVersion;
    target->_combined = _combined;

}


void QVRT_ExtDataPacket::Decode(unsigned char *data)
{
    // ----- Read the header -----
    uint32_t * dp = (unsigned int *)data;
    dp += QVRT_Packet::Decode(data); //decode the common stuff


    char *docstr = (char *)dp; // will be 'size' bytes long
    if(header.packetType == QVRT_EXT_DATA_NO_STREAMID)
    {
        Document doc;
        doc.Parse(docstr);
        m_docstring = docstr;
        m_systemTime = doc["System Time"].GetString();
        m_recordingUUID = doc["Recording UUID"].GetString();
        m_fileDescription = doc["File Description"].GetString();
        m_radioSelection = doc["Radio Selection"].GetString();
        m_unitType = doc["Unit Type"].GetString();
        m_hardwareVersion = doc["Unit Hardware Version"].GetString();
        m_unitESN = doc["Unit ESN"].GetString();
        m_fimrwareVersion = doc["Firmware Version"].GetString();
        m_WBTLogFileFormatVersion = doc["WBT File Format Version"].GetString();
        m_GPSLatitude = doc["GPS Latitude"].GetDouble();
        m_GPSLongitude = doc["GPS Longitude"].GetDouble();
        m_GPSAltitude = doc["GPS Altitude"].GetDouble();
        m_GPSMagneticVariation = doc["GPS Magnetic Variation"].GetDouble();
        m_GPSFixUTCSeconds = doc["GPS Fix UTC Seconds"].GetInt();
        m_GPSfixStatus = doc["GPS Fix Status"].GetString();

        m_tunerASettings.m_centerFreq = doc["Radio Settings - Radio A"]["Center Frequency"].GetDouble();
        m_tunerASettings.m_BandwidthHz = doc["Radio Settings - Radio A"]["BandwidthHz"].GetInt();
        m_tunerASettings.m_Span = doc["Radio Settings - Radio A"]["Span"].GetDouble();
        m_tunerASettings.m_ReceiveOffset = doc["Radio Settings - Radio A"]["Receive Offset"].GetDouble();
        m_tunerASettings.m_ReceiveGain = doc["Radio Settings - Radio A"]["Receive Gain"].GetDouble();
        m_tunerASettings.m_TunerType = doc["Radio Settings - Radio A"]["Tuner Type"].GetString();
        m_tunerASettings.m_TunerRange = doc["Radio Settings - Radio A"]["Tuner Range"].GetString();

        m_tunerBSettings.m_centerFreq = doc["Radio Settings - Radio B"]["Center Frequency"].GetDouble();
        m_tunerBSettings.m_BandwidthHz = doc["Radio Settings - Radio B"]["BandwidthHz"].GetInt();
        m_tunerBSettings.m_Span = doc["Radio Settings - Radio B"]["Span"].GetDouble();
        m_tunerBSettings.m_ReceiveOffset = doc["Radio Settings - Radio B"]["Receive Offset"].GetDouble();
        m_tunerBSettings.m_ReceiveGain = doc["Radio Settings - Radio B"]["Receive Gain"].GetDouble();
        m_tunerBSettings.m_TunerType = doc["Radio Settings - Radio B"]["Tuner Type"].GetString();
        m_tunerBSettings.m_TunerRange = doc["Radio Settings - Radio B"]["Tuner Range"].GetString();

        if(strstr(docstr,"Combined") != 0)
        {
            //check to see if the word 'Combined is in here'
            _combined = true;
            m_tunerCombinedSettings.m_centerFreq = doc["Radio Settings - Combined"]["Center Frequency"].GetDouble();
            m_tunerCombinedSettings.m_BandwidthHz = doc["Radio Settings - Combined"]["BandwidthHz"].GetInt();
            m_tunerCombinedSettings.m_Span = doc["Radio Settings - Combined"]["Span"].GetDouble();
            m_tunerCombinedSettings.m_ReceiveOffset = doc["Radio Settings - Combined"]["Receive Offset"].GetDouble();
            m_tunerCombinedSettings.m_ReceiveGain = doc["Radio Settings - Combined"]["Receive Gain"].GetDouble();
          //  m_tunerCombinedSettings.m_TunerType = doc["Radio Settings - Combined"]["Tuner Type"].GetString();
          //  m_tunerCombinedSettings.m_TunerRange = doc["Radio Settings - Combined"]["Tuner Range"].GetString();
        }
    }else
    {
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
        dp += datasize;
    }
    // ----- Read the trailer -----
    if (header.trailer_present)
    {
        trailer = *dp;
        dp++;
        trailer = QVRTSwap32 (trailer);
    }
}

/*

*/
int QVRT_ExtDataPacket::Encode(unsigned char *data)
{
    static QVRT_Header header;
    static bool first = true;
    if(first)
    {
        first = false;
        header.class_id_present = 0;
        header.count = 0;
        header.packetType = 2;
        header.reserved = 0;
        header.size = 974;
        header.trailer_present = 0;
        header.TSF = 0;
        header.TSI = 0;
        header.TSM = 0;
    }
  //  int length;
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    char tmpbuff[4000]; // temp buffer for replace
    this->Serialize(writer);
    //get the length
    //print it into the temporary buffer
    sprintf(tmpbuff,"%s",sb.GetString());
    //repace the array portion with space (poor man's regex)
    for(unsigned int c = 0; c< sb.GetSize();c++)
    {
        if(tmpbuff[c] == '[')
            tmpbuff[c] = ' ';
        if(tmpbuff[c] == ']')
            tmpbuff[c] = ' ';
    }

    //print the string into the buffer + 4 bytes (allow space for the header)
    char *tmp = (char *)(data + 4);
    sprintf(tmp,"%s",tmpbuff);
    header.Encode(data); // write the header
    return 974 * 4;
}

template <typename Writer>
void QVRT_ExtDataPacket::Serialize(Writer& writer)
{
    writer.StartObject();
    // This base class just write out name-value pairs, without wrapping within an object.

   // writer.String("System Time");
    writer.Key("System Time");
    writer.String(m_systemTime.c_str(), (SizeType)m_systemTime.length());

    writer.Key("Recording UUID");
    writer.String(m_recordingUUID.c_str(), (SizeType)m_recordingUUID.length());

    writer.Key("File Description");
    writer.String(m_fileDescription.c_str(), (SizeType)m_fileDescription.length());

    writer.Key("Radio Selection");
    writer.String(m_radioSelection.c_str(), (SizeType)m_radioSelection.length());

    writer.Key("Unit Type");
    writer.String(m_unitType.c_str(), (SizeType)m_unitType.length());

    writer.Key("Unit Hardware Version");
    writer.String(m_hardwareVersion.c_str(), (SizeType)m_hardwareVersion.length());

    writer.Key("Unit ESN");
    writer.String(m_unitESN.c_str(), (SizeType)m_unitESN.length());

    writer.Key("Firmware Version");
    writer.String(m_fimrwareVersion.c_str(), (SizeType)m_fimrwareVersion.length());

    writer.Key("WBT File Format Version");
    writer.String(m_WBTLogFileFormatVersion.c_str(), (SizeType)m_WBTLogFileFormatVersion.length());


    writer.String("Radio Settings - Radio A");
    writer.StartArray();
    m_tunerASettings.Serialize(writer);
    writer.EndArray();

    writer.String("Radio Settings - Radio B");
    writer.StartArray();
    m_tunerBSettings.Serialize(writer);
    writer.EndArray();

    if(_combined)
    {
        writer.String("Radio Settings - Combined");
        writer.StartArray();
        m_tunerCombinedSettings.Serialize(writer);
        writer.EndArray();
    }

    writer.Key("GPS Latitude");
    writer.Double( m_GPSLatitude );

    writer.Key("GPS Longitude");
    writer.Double( m_GPSLongitude );

    writer.Key("GPS Altitude");
    writer.Double( m_GPSAltitude );

    writer.Key("GPS Magnetic Variation");
    writer.Double( m_GPSMagneticVariation);

    writer.Key("GPS Fix UTC Seconds");
    writer.Int( m_GPSFixUTCSeconds );

    writer.Key("GPS Fix Status");
    writer.String( m_GPSfixStatus.c_str(), (SizeType)m_GPSfixStatus.length() );

    writer.EndObject();

}

void QVRT_ExtDataPacket::Dump()
{        
    QVRT_Packet::Dump();
    if(header.packetType == QVRT_EXT_DATA_NO_STREAMID)
    {
        cout << "\r\n**QVRT_ExtDataPacket Start\r\n";
        cout << "System Time: " << m_systemTime << "\r\n";
        cout << "Recording UUID: " << m_recordingUUID << "\r\n";
        cout << "File Description: " << m_fileDescription << "\r\n";
        cout << "Radio Selection: " << m_radioSelection << "\r\n";
        cout << "Unit Type: " << m_unitType << "\r\n";
        cout << "Unit Hardware Version: " << m_hardwareVersion << "\r\n";
        cout << "Unit ESN: " << m_unitESN << "\r\n";
        cout << "Firmware Version: " << m_fimrwareVersion << "\r\n";
        cout << "WBT File Format Version: " << m_WBTLogFileFormatVersion << "\r\n";
        cout << "Latitude: " << m_GPSLatitude << "\r\n";
        cout << "Longitude: " << m_GPSLongitude << "\r\n";
        cout << "Altitude: " << m_GPSAltitude << "\r\n";
        cout << "Magnetic variation: " << m_GPSMagneticVariation << "\r\n";
        cout << "Fix UTC Seconds: " << m_GPSFixUTCSeconds << "\r\n";
        cout << "Fix Status: " << m_GPSfixStatus << "\r\n";
        cout << "Radio Settings A *********************"<< "\r\n";
        m_tunerASettings.Dump();
        cout << "Radio Settings B *********************"<< "\r\n";
        m_tunerBSettings.Dump();
        if(_combined)
        {
            cout << "Radio Settings Combined  *********************"<< "\r\n";
            m_tunerCombinedSettings.Dump();
        }

        cout << "Raw Doc String : \r\n";
        cout << m_docstring + "\r\n";
        cout << "**QVRT_ExtDataPacket End\r\n";
    }
}

void QVRT_ExtDataPacket::PrintGPS()
{
    printf("%f,%f,%f\r\n",m_GPSLongitude,m_GPSLatitude,m_GPSAltitude);
}
