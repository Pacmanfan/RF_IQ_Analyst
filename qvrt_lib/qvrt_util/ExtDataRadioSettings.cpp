#include <qvrt_tools.h>
#include "include/rapidjson/prettywriter.h" // for stringify JSON
#include <cstdio>
#include <string>
#include <vector>
using namespace rapidjson;
using namespace std;


ExtDataRadioSettings::ExtDataRadioSettings()
{
    m_BandwidthHz = 1000000; // 1mhz by default
    m_centerFreq = 101.1; // Mhz
    m_ReceiveGain = 0.0;
    m_ReceiveOffset = -40.3;// ?
    m_Span = 1;// 1Mhz
    m_TunerType = "Type D";
    m_TunerRange = "50000000 - 6000000000";

}

void ExtDataRadioSettings::CopyTo(ExtDataRadioSettings *target)
{
    target->m_BandwidthHz = m_BandwidthHz;
    target->m_centerFreq = m_centerFreq;
    target->m_ReceiveGain = m_ReceiveGain;
    target->m_ReceiveOffset = m_ReceiveOffset;
    target->m_Span = m_Span;
    target->m_TunerRange = m_TunerRange;
    target->m_TunerType = m_TunerType;
}

void ExtDataRadioSettings::Dump()
{
    cout << "**Radio Settings" << "\r\n";
    cout << "Center Frequency " << m_centerFreq << "\r\n";
    cout << "Bandwidth " << m_BandwidthHz << "\r\n";
    cout << "Span " << m_Span << "\r\n";
    cout << "Receive Offset " << m_ReceiveOffset << "\r\n";
    cout << "Receive Gain " << m_ReceiveGain << "\r\n";
    cout << "Tuner Type " << m_TunerType << "\r\n";
    cout << "Tuner Range " << m_TunerRange << "\r\n";
}
/*
template <typename Writer>
void ExtDataRadioSettings::Serialize(Writer& writer) //const
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
    writer.String(m_TunerType.c_str(),(SizeType)m_TunerType.length());
  //  writer.String(m_TunerType.c_str(),m_TunerType.length());

    writer.String("Tuner Range");
    writer.String(m_TunerRange.c_str(),(SizeType)m_TunerRange.length());
  //  writer.String(m_TunerRange.c_str(),m_TunerRange.length());

    writer.EndObject();
}
*/
