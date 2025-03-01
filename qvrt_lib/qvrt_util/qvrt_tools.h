#ifndef QVRT_TOOLS_H
#define QVRT_TOOLS_H
#include <stdio.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>
#include "fixed_t.h"
#include "circbuff.h"
#include <vector>
#include <complex>

using namespace std;

#define RADIO_INVALID -1
#define RADIO_A 0
#define RADIO_B 1
#define RADIO_AB 2

#define QVRT_IQ_DATA_NO_STREAMID    0x00
#define QVRT_IQ_DATA                0x01
#define QVRT_EXT_DATA_NO_STREAMID   0x02
#define QVRT_EXT_DATA               0x03
#define QVRT_IF_CONTEXT             0x04
#define QVRT_EXT_CONTEXT            0x05

#define TSI_NO_INT_TS 0x00 // no Integer timestamp
#define TSI_COORD_UTC 0x01 // Coordinated UTC
#define TSI_GPS       0x02 // no Integer timestamp
#define TSI_OTHER     0x03  // Other

#define TSF_NO_FRAC_TS   0x00  //  No fractional timestamp
#define TSF_SAMPLE_COUNT 0x01  // sample count is used
#define TSF_REAL_TIME    0x02  // Real Time (picoseconds) timestamp
#define TSF_FREE_RUNNING 0x03  // free Running count

#define MAX_DATA_PACKET_SAMPLES 50000
#define UNUSED(x) (void)x;


complex <float > * ALLOC_CF(int size);
void FREE_CF(complex<float> *ptr);
void cos_doubles(double * in_array, double * out_array, int size);
//int TestReadSamples(double *outvec, int n);
int TestReadSamples(double *outvec, int n);
//int TestReadSamplesComplex(complex<float> *fcoutvec, int n);
int TestReadSamplesComplex(void *fcoutvec, int n);
void inplace(double *invec, int n);
//int sum_it_cplx(std::complex<float> *array, int size) ;
int sum_it_cplx(long array, int size);

inline uint16_t QVRTSwap16(uint16_t us)
{
    return (us >> 8) | (us << 8);
}
/*
uint32_t ReverseByteOrder(uint32_t value) {
    return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) | ((value & 0xFF0000) >> 8) | ((value & 0xFF000000) >> 24);
}
*/
inline uint64_t ReverseByteOrder(uint64_t value) {
    return ((value & 0xFFULL) << 56) |
           ((value & 0xFF00ULL) << 40) |
           ((value & 0xFF0000ULL) << 24) |
           ((value & 0xFF000000ULL) << 8) |
           ((value & 0xFF00000000ULL) >> 8) |
           ((value & 0xFF0000000000ULL) >> 24) |
           ((value & 0xFF000000000000ULL) >> 40) |
           ((value & 0xFF00000000000000ULL) >> 56);
}
inline uint32_t QVRTSwap32 (uint32_t value)
{
    return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) | ((value & 0xFF0000) >> 8) | ((value & 0xFF000000) >> 24);//(uint32_t) __builtin_bswap32 ((int32_t) x);  // gcc instrinsics
}

inline uint64_t QVRTSwap64 (uint64_t x)
{
    return ReverseByteOrder(x);//(uint64_t) __builtin_bswap64 ((int64_t) x);  // gcc instrinsics
}


std::string PacketType2Name(int packettype);
std::string hexStr(unsigned char* data, int len);
std::string TSF2Name(int TSF);
std::string TSI2Name(int TSI);

//header class
void DumpHexBlock(unsigned char *data,int size, int columns);

enum file_format // format of the data
{
    eU8, // 2 channel unsigned 8 bit format
    eS8, // 2 channel signed 8 bit format
    eU16, // 2 channel unsigned 16 bit format
    eS16, // also the 16T format
    e32, // 2 channel 32 bit floats (cfile / raw)
    eQVRT,
    eUNK // unknown
};

std::string FileFormat2Str(file_format f);

class QVRT_Header
{
public:
    QVRT_Header();
    uint32_t packetType{0};
    uint32_t size;
    uint32_t count;
    unsigned char class_id_present; // 1 bit
    unsigned char trailer_present; // 1 bit
    unsigned char reserved; // 1 bit
    unsigned char TSM; // indicates course timing is in use when used in a context packet
    unsigned char TSI; // indicates presence and type of integer timestamp field
    unsigned char TSF; //indicates presence and type of fractional timestamp field
    uint32_t encodedheader; // after the header is encoded, it is kept here
    void Decode(unsigned char *data);// the start of the block
    void Encode(unsigned char *data); // stored in encoded header and returned
    void Dump(); // print to screen
    void CopyTo(QVRT_Header *target); // copy data from this to the target
};

//base class with common items
class QVRT_Packet
{
public:
    //QVRT_Packet();
  //  virtual ~QVRT_Packet();
    QVRT_Header header; // header
    uint32_t StreamID{0}; // 32 bits
    uint32_t Int_Sec_TS{0}; // 32 bits
    uint64_t Frac_Sec_TS{0}; // 64 bits
    uint32_t trailer{0}; // 32 bits
    uint32_t datasize{0};
    uint64_t class_id{0};
    unsigned char *data_payload{0}; // the data payload
    uint32_t maxdatasize{0};

    uint32_t Decode(unsigned char *data);
    void Dump();
    void Summary(); // single line summary
    void FormatTimestamp(char *str);
};

class QVRT_IQDataPacket  : public QVRT_Packet
{
public:
    QVRT_IQDataPacket();
    uint32_t m_numsamples; //
    bool Decode(unsigned char *data,CircBuff<complex<float> > *samplesout, uint32_t SID);
    bool Decode(unsigned char *data,CircBuff_No_lock<complex<float> > *samplesout, uint32_t SID); // bad form to have both of these, but we'll change it
    void Encode(unsigned char *data,CircBuff<float> *samplesin);
    bool Match(unsigned char *data, uint32_t SID);
    void Dump(CircBuff<complex <float> > *samples);//
    void CopyTo(QVRT_IQDataPacket *target); // copy data from this to the target
};


//class

class ExtDataRadioSettings
{
public:
    ExtDataRadioSettings();
    double m_centerFreq;
    long m_BandwidthHz;
    double m_Span;
    double m_ReceiveOffset;
    double m_ReceiveGain;
    std::string m_TunerType;
    std::string m_TunerRange;
    //void Decode(char *doc);
   // std::string Encode();
    template <typename Writer>
    void Serialize(Writer& writer) const

    {
        writer.StartObject();

        writer.String("Center Frequency");
        writer.Double(m_centerFreq);

        writer.String("BandwidthHz");
       // writer.Double(m_BandwidthHz);
        writer.Int(m_BandwidthHz);

        writer.String("Span");
        writer.Double(m_Span);

        writer.String("Receive Offset");
        writer.Double(m_ReceiveOffset);

        writer.String("Receive Gain");
        writer.Double(m_ReceiveGain);

        writer.String("Tuner Type");
        //writer.String(m_TunerType.c_str(),(SizeType)m_TunerType.length());
        writer.String(m_TunerType.c_str(),m_TunerType.length());

        writer.String("Tuner Range");
        //writer.String(m_TunerRange.c_str(),(SizeType)m_TunerRange.length());
        writer.String(m_TunerRange.c_str(),m_TunerRange.length());

        writer.EndObject();
    }

    void Dump();
    void CopyTo(ExtDataRadioSettings *target);
};

class QVRT_ExtDataPacket  : public QVRT_Packet// QVRT_EXT_DATA_NO_STREAMID and QVRT_EXT_DATA
{
public:
    QVRT_ExtDataPacket();
    void Decode(unsigned char *data);
    int Encode(unsigned char *data);
    void CopyTo(QVRT_ExtDataPacket *target);
    void Dump();
    void PrintGPS();
    template <typename Writer>
    void Serialize(Writer& writer);
    void setCombined(bool val){_combined = val;}

    std::string m_systemTime;
    std::string m_recordingUUID;
    std::string m_fileDescription;
    std::string m_radioSelection;
    std::string m_unitType;
    std::string m_hardwareVersion;
    std::string m_unitESN;
    std::string m_fimrwareVersion;
    std::string m_WBTLogFileFormatVersion;
    std::string m_radioSettingsA;
    std::string m_radioSettingsB;
    double m_GPSLatitude;
    double m_GPSLongitude;
    double m_GPSAltitude;
    double m_GPSMagneticVariation;
    int m_GPSFixUTCSeconds;
    std::string m_GPSfixStatus;
    ExtDataRadioSettings m_tunerASettings;
    ExtDataRadioSettings m_tunerBSettings;
    ExtDataRadioSettings m_tunerCombinedSettings;
    bool _combined;
    std::string m_docstring; // from loaded

};
//Extension context packet
class QVRT_ExtContext_Packet : public QVRT_Packet
{
public:
    QVRT_ExtContext_Packet();
    void Decode(unsigned char *data);
    void Encode(unsigned char *data);
    void Dump();
};


class QVRT_IFContext_Packet : public QVRT_Packet
{
public:

    uint32_t sourcetunerid;
    uint32_t usertunerid;
    uint32_t tunerid;

    //flags section
    unsigned char f_ContextFieldIndicatorChange;
    unsigned char f_ReferencePointIndicator;
    unsigned char f_Bandwidth;
    unsigned char f_RFReferenceFrequency;
    unsigned char f_RFReferenceFrequencyOffset;
    unsigned char f_ReferenceLevel;
    unsigned char f_Gain;
    unsigned char f_OverRangeCount;
    unsigned char f_SampleRate;
    unsigned char f_TimestampCalibrationTime;
    unsigned char f_FormattedGPSGeolocation;

    uint32_t ReferencePointIndicator; // should be the same as the stream id

    double dBandwidth;

    double dRFReferenceFrequency;
    double dRFReferenceFrequencyOffset;
    double dReferenceLevel;
    uint32_t Gain; // encoded with rf and IF gain in fixed point format
    double dRFGain,dIFGain;
    uint32_t OverRangeCount;
    double dSampleRate;
    uint32_t TimestampCalibrationTime;

    //GPS info follows:
    unsigned char TSI; //  2 bits - 26
    unsigned char TSF; // 2 bits  - 24
    uint32_t GPS_INS_Manufacturer_OUI ; // 0-23
    uint32_t ISTSPF; // Integer-second Timestanp of position fix
    uint32_t FSTPF1; // Fractional second timestamp position fix 1
    uint32_t FSTPF2; // Fractional second timestamp position fix 23
    double Latitude;
    double Longitude;
    double Altitude;
    double SpeedOverGround;
    double HeadingAngle;
    double TrackAngle;
    double MagneticVariation;

    QVRT_IFContext_Packet();
    void Decode(unsigned char *data);//, uint32_t SID =1);
    void Encode(unsigned char *data);
    void CopyTo(QVRT_IFContext_Packet *target);
    void Dump();
    void PrintGPS(); // dump the GPSinfo
    void StartGPSPrint();
    void EndGPSPrint();
};

struct QVRT_GPS_Info
{
    double Latitude;
    double Longitude;
    double Altitude;
    double SpeedOverGround;
    double HeadingAngle;
    double TrackAngle;
    double MagneticVariation;
    bool valid;
};

class StreamInfo;

class IQ_Reader
{
public:
    IQ_Reader();
    virtual ~IQ_Reader();
    virtual bool Open(std::string filename);
    virtual void Close();
    virtual long TellP(){return ftell(fp);}
    virtual void SeekP(long pos){fseek(fp,pos,SEEK_SET);}
    virtual bool IsOpen();
    virtual long FileLength(); // returns file length in bytes
    //each subclass should override the implementations
    // we're using a circular buffer for retrieval to make things easier
    virtual long ReadSamples(CircBuff<complex<float> > *buffer,uint32_t numsamples);
    virtual long ReadSamples(complex<float> *outbuffer,uint32_t numsamples);
    //virtual void SetStreamInfo(StreamInfo *si);
protected :
    FILE *fp;
};

/*
This class is used to read a single QVRT Stream
*/
class QVRT_Reader : public IQ_Reader
{
public:
    QVRT_Reader();
    ~QVRT_Reader();
    QVRT_Header *ReadNextPacket();
    unsigned char *CurrentBufferPos(){return buffer;}   
    long ReadSamples(CircBuff<complex<float> > *samplebuffer,uint32_t numsamples);    //may return more samples than requested
    long ReadSamples(complex<float> *outbuffer,uint32_t numsamples);//will return the exact number of samples requested - you can't mix the 2 reads
    long PyReadSamples(long outbuffer,int numsamples);//will return the exact number of samples requested - you can't mix the 2 reads
    int getStreamid(){return streamid;}
    void setStreamid(int value){streamid = value;}
    QVRT_GPS_Info Get_Last_GPS_Info(){return m_gpsinfo;}

private:
    QVRT_Header packetheader;
    int streamid;
    unsigned char *buffer;
    long buffersize;
    QVRT_GPS_Info m_gpsinfo;
    CircBuff_No_lock<complex<float> > *m_iqbuff; // buffer for the ReadSamples
};


class IQ_Writer
{
public:
    IQ_Writer();
    virtual ~IQ_Writer();
    FILE *fp;
    string m_filename;
    virtual bool Open(std::string filename);
    virtual void Close() ;
    virtual bool IsOpen();
    virtual void Flush();
    virtual void AddData(complex<float> *iq, uint32_t numsamples);
    virtual bool Setup(int streamid,double CF_Hz, double SPS, double BW_Hz, double RFGain, double IFGain);
    virtual void SetGPSData(double Latitude,double Longitude,double Altitude);
};

/*
This class is used to read QVRT Streams
*/
class QVRT_Writer : public IQ_Writer
{
public:
    QVRT_Writer();
    ~QVRT_Writer();
    void AddData(complex<float> *iq, uint32_t numsamples);
    void PyAddData(long dataptr, uint32_t numsamples);
    bool Setup(int streamid,double CF_Hz, double SPS, double BW_Hz, double RFGain, double IFGain);
    void SetGPSData(double Latitude,double Longitude,double Altitude);
    void EncodeContextChunk(unsigned char * contextchunk);
    void Flush();
private :
    int m_streamid;
    double m_CF_Hz;
    double m_SPS;
    double m_BW_Hz;
    double m_RFGain;
    double m_IFGain;    
    CircBuff<float> *m_samples;
    unsigned long m_packetcount;
    QVRT_IFContext_Packet m_ctx;
    QVRT_ExtDataPacket extpacket;
};



class StreamInfo
{
public:
    double BandwidthHZ;
    double CenterFreqHz;
    double SampleRateHz;
    double dRFGain,dIFGain;
    double dRFReferenceFrequency;
    double dRFReferenceFrequencyOffset;
    double dReferenceLevel;
    double minFreqHz;
    double maxFreqHz;
    uint32_t StreamID;
    bool valid;
    string name; // hold stream name or filename depending
    double duration_est_seconds; // string of duration in seconds
    long num_samples_est; // estimate of the number of samples based on rate and file length
    long samples_per_packet;
    file_format m_format; // format of the data stream - u8,s8,u16,s16,e32,eQVRT

    StreamInfo()
    {
        BandwidthHZ = 0;
        CenterFreqHz= 0;
        SampleRateHz= 0;
        dRFGain= 0;
        dIFGain= 0;
        dRFReferenceFrequency= 0;
        dRFReferenceFrequencyOffset= 0;
        dReferenceLevel= 0;
        StreamID= 0;
        valid = false;
        name = "";
        duration_est_seconds = 0;
        samples_per_packet = 0;
        num_samples_est = 0;
        m_format = eQVRT; // assume it's a qvrt until proven otherwise
        minFreqHz = 0;
        maxFreqHz = 0;
    }
    ~StreamInfo()
    {
       // printf("Streaminfo destructor called\r\n");
    }

    void Dump()
    {
        cout << "StreamInfo******************************\r\n";
        cout << "File Name : " << name << "\r\n";
        cout << "Stream ID : " << StreamID << "\r\n";
        cout << "Center Frequency : " << CenterFreqHz << "\r\n";
        cout << "Min Frequency : " << minFreqHz << "\r\n";
        cout << "Max Frequency : " << maxFreqHz << "\r\n";
        cout << "Sample Rate : " << SampleRateHz << "\r\n";
        cout << "Bandwidth : " << BandwidthHZ << "\r\n";
        cout << "RF Gain : " << dRFGain << "\r\n";
        cout << "IF Gain : " << dIFGain << "\r\n";
        cout << "RF Reference Frequency  : " << dRFReferenceFrequency << "\r\n";
        cout << "RF Reference Frequency Offset : " << dRFReferenceFrequencyOffset << "\r\n";
        cout << "Reference Level : " << dReferenceLevel << "\r\n";
        cout << "Duration estimate : " << duration_est_seconds << "\r\n";
        cout << "Estimated Number of samples : " << num_samples_est << "\r\n";
        switch(m_format)
        {
            case eQVRT: cout << "QVRT file format" ; break;
            case eS16: cout << "2 channel signed 16 bit" ; break; // also the S16 format (also .raw files from gqrx)
            case eU16: cout << "2 channel unsigned 16 bit" ; break; // 2 channel unsigned 16 bit format
            case eU8: cout << "2 channel unsigned 8 bit" ; break; // 2 channel unsigned 8 bit format
            case eS8: cout << "2 channel signed 8 bit" ; break; // 2 channel signed 8 bit format
            case e32: cout << "2 channel 32 bit float" ; break; // 2 channel 32 bit floats (cfile / raw)
            case eUNK: cout << "Unknown" ; break; // unknown
        }
    }

    bool Load(FILE *fp)
    {
        if (fread(&BandwidthHZ, sizeof(double), 1, fp) != 1) return false;
        if (fread(&CenterFreqHz, sizeof(double), 1, fp) != 1) return false;
        if (fread(&SampleRateHz, sizeof(double), 1, fp) != 1) return false;
        if (fread(&dRFGain, sizeof(double), 1, fp) != 1) return false;
        if (fread(&dIFGain, sizeof(double), 1, fp) != 1) return false;
        if (fread(&dRFReferenceFrequency, sizeof(double), 1, fp) != 1) return false;
        if (fread(&dRFReferenceFrequencyOffset, sizeof(double), 1, fp) != 1) return false;
        if (fread(&dReferenceLevel, sizeof(double), 1, fp) != 1) return false;
        if (fread(&StreamID, sizeof(uint32_t), 1, fp) != 1) return false;
        if (fread(&valid, sizeof(bool), 1, fp) != 1) return false;
        if (fread(&duration_est_seconds, sizeof(double), 1, fp) != 1) return false;
        if (fread(&num_samples_est, sizeof(long), 1, fp) != 1) return false;
        if (fread(&samples_per_packet, sizeof(long), 1, fp) != 1) return false;

        char nm[256];
        if (fread(nm, sizeof(char), 256, fp) != 256) return false;

        name = nm;
        return true;
    }

    bool Save(FILE *fp)
    {
        fwrite(&BandwidthHZ,sizeof(double),1,fp);
        fwrite(&CenterFreqHz,sizeof(double),1,fp);
        fwrite(&SampleRateHz,sizeof(double),1,fp);
        fwrite(&dRFGain,sizeof(double),1,fp);
        fwrite(&dIFGain,sizeof(double),1,fp);
        fwrite(&dRFReferenceFrequency,sizeof(double),1,fp);
        fwrite(&dRFReferenceFrequencyOffset,sizeof(double),1,fp);
        fwrite(&dReferenceLevel,sizeof(double),1,fp);
        fwrite(&StreamID,sizeof(uint32_t),1,fp);
        fwrite(&valid,sizeof(bool),1,fp);
        fwrite(&duration_est_seconds,sizeof(double),1,fp);
        fwrite(&num_samples_est,sizeof(long),1,fp);
        fwrite(&samples_per_packet,sizeof(long),1,fp);
        char nm[256];
        strcpy(nm,name.c_str());
        fwrite(nm,256,1,fp);
        return true;
    }

    void operator = (const StreamInfo &src)
    {
        BandwidthHZ = src.BandwidthHZ;
        CenterFreqHz = src.CenterFreqHz;
        SampleRateHz = src.SampleRateHz;
        dRFGain = src.dRFGain;
        dIFGain = src.dIFGain;
        dRFReferenceFrequency = src.dRFReferenceFrequency;
        dRFReferenceFrequencyOffset = src.dRFReferenceFrequencyOffset;
        dReferenceLevel = src.dReferenceLevel;
        StreamID = src.StreamID;
        valid = src.valid;
        name = src.name; // h
        samples_per_packet = src.samples_per_packet;
        duration_est_seconds = src.duration_est_seconds;
        m_format = src.m_format;
        maxFreqHz = src.maxFreqHz;
        minFreqHz = src.minFreqHz;
    }

    void operator = (QVRT_IFContext_Packet &ifctx)
    {
        BandwidthHZ = ifctx.dBandwidth;
        CenterFreqHz = ifctx.dRFReferenceFrequency;
        SampleRateHz = ifctx.dSampleRate;
        dRFGain = ifctx.dRFGain;
        dIFGain  = ifctx.dIFGain;
        dRFReferenceFrequency = ifctx.dRFReferenceFrequency;
        dRFReferenceFrequencyOffset  = ifctx.dRFReferenceFrequencyOffset;
        dReferenceLevel  = ifctx.dReferenceLevel;
        StreamID = ifctx.StreamID;
        valid = true;
        maxFreqHz = CenterFreqHz + (SampleRateHz /2);
        minFreqHz = CenterFreqHz - (SampleRateHz /2);

    }
};

/*
This class is gathers information about the QVRT file,
including number of streams, etc..
It will tell you the number of streams present

*/
class QVRT_FileInfo
{
public:
    QVRT_FileInfo();
    ~QVRT_FileInfo();
    bool GatherInfo(string filename);
    bool LoadMeta(string filename);
    bool SaveMeta(string filename);
    bool HasStream(uint32_t streamid);
    std::string Name(){return m_name;}
    StreamInfo *GetStreamInfo(uint32_t streamid);
    StreamInfo *GetStreamInfoIndex(uint32_t idx);
    int NumStreams(){return (int)m_streams.size();} // return the number of streams in this file
    bool IsCombined(){return m_combined;} // are the A/B streams combined?
    void Dump();
    void operator = (const QVRT_FileInfo &src)
    {
        m_name = src.m_name;
        m_combined = src.m_combined;
        for(uint32_t c = 0; c< src.m_streams.size() ; c++)
        {
            StreamInfo *si_src = src.m_streams[c];
            StreamInfo *si = new StreamInfo();
            *si = *si_src;
            m_streams.push_back(si);
        }
    }
private:
    void Release();
    string m_name;
    bool m_combined;
    vector<StreamInfo *> m_streams;
};

#endif // QVRT_TOOLS_H

