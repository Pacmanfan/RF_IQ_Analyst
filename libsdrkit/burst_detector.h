#ifndef BURST_DETECTOR_H
#define BURST_DETECTOR_H
#include <QString>
#include <QVector>
#include <fft_hist.h>
#include <QSettings>
#include <feature_detector.h>

/*
    The burst detector works by directly examining the waterfall data from the
    FFTHelper
    We're using OpenCV to perform the retangular detections
    we're then comparing against pre-defined bursts
*/

/*
This is a basic definition of a RF pulse
We're looking for pulses emited by TX devices controlling drones
These are frequency hopping pulses that can appear anywhere in the control
frequency spectrum
for DSMX-2 pulse, they are approximately
XXX in bandwidth and
YYY in duration

DJI pulses are approx:
2.236 ms in duration and 1.26 Mhz wide

More than just a pulse definition, this should also describe
some characteristics of the frequency hopping pattern

1) freq range
2) center freq
3) signal BW
4) Hop rate (per sec)
5) Dwell time (duration in uS)
6) Guard time (time between the end of a pulse and the start of the next pulse)
7) Period time (time between the start of a pulse, and the start of the next pulse)
8) Modulation type



*/

class RFPulseDef
{
public:
    RFPulseDef();
    QString m_name;
    double m_bandwidthHz;
    double m_durationuS; // duration in microseconds
    void Save(QSettings *settings);
    void Load(QSettings *settings);
    QString toString();
};


enum eBurstMatchType
{
    eBoth,
    eBW,
    eDuration
};


class burst_detector
{
public:
    float m_timefudge;
    float m_freqfudge;
    bool m_debug;
    eBurstMatchType m_matchtype;
    burst_detector();
    QVector<RFPulseDef *> m_pulsedefs;
    bool Load(QString fn);
    bool Save(QString fn);
    void SetMatchPercentTime(float va){m_timefudge = va;}
    void SetMatchPercentFreq(float va){m_freqfudge = va;}
    void SetMatchType(eBurstMatchType mt){m_matchtype = mt;}
    void SetDebug(bool val){m_debug = val;}

    QVector<ftmarker *> Detect(FFT_Hist *helper,bool autorange = true, float rlow = 0, float rhigh = 0, FD_Source src = eCache);
};

#endif // BURST_DETECTOR_H
