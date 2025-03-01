#include "burst_detector.h"
#include <QSettings>
#include <feature_detector.h>

burst_detector::burst_detector()
{
    m_timefudge = .1;
    m_freqfudge = .1;
    m_matchtype = eBoth;
    m_debug = false;
}

bool burst_detector::Load(QString fn)
{
    QSettings settings(fn);
    m_timefudge = settings.value("time_fudge",0.1).toDouble();
    m_freqfudge = settings.value("freq_fudge",0.1).toDouble();
    m_matchtype = (eBurstMatchType)settings.value("MatchType",0).toInt();

    int nentries;
    nentries = settings.beginReadArray("pulse_defs");
    for(int c = 0; c < nentries; c++)
    {
        settings.setArrayIndex(c);
        RFPulseDef *pulse = new RFPulseDef();
        pulse->Load(&settings);
        m_pulsedefs.push_back(pulse);
    }
    settings.endArray();
    return true;
}

bool burst_detector::Save(QString fn)
{
    QSettings settings(fn);
    settings.setValue("time_fudge",m_timefudge);
    settings.setValue("freq_fudge",m_freqfudge);
    settings.setValue("MatchType",(int)m_matchtype);


    int nentries = m_pulsedefs.size();
    settings.beginWriteArray("pulse_defs",nentries);
    for(int c = 0; c < m_pulsedefs.size(); c++ )
    {
        settings.setArrayIndex(c);
        m_pulsedefs.at(c)->Save(&settings);
    }
    settings.endArray();
    return true;
}

/*
This function runs the feature detector, then examines each pulse to see if they match
any of the specified pulse definitions
*/

QVector<ftmarker *> burst_detector::Detect(FFT_Hist *helper, bool autorange, float rlow, float rhigh, FD_Source src)
{
    QVector<ftmarker *> pulses;
    feature_detector detector;
    QVector<ftmarker *> features;
    features = detector.DetectFeatures(helper, autorange , rlow , rhigh,src );
    if(m_debug)
    {
        printf("Markers\r\n");
    }
    for (int c = 0; c < features.size(); c++)
    {
        ftmarker *ftm = features.at(c);
        if(m_debug)
        {
           // printf("%s\r\n",ftm->toString().toLatin1().data());
        }
        for(int d = 0; d< m_pulsedefs.size(); d ++)
        {
            RFPulseDef *pd = m_pulsedefs.at(d);
            if(m_debug)
            {
                printf("%s\r\n",pd->toString().toLatin1().data());

            }
            //now, do a fuzzy match
            bool durmatch = false;
            bool bwmatch = false;

            if(ftm->BW_Hz() >= (pd->m_bandwidthHz - (pd->m_bandwidthHz * m_freqfudge ) ) &&
               ftm->BW_Hz() <= (pd->m_bandwidthHz + (pd->m_bandwidthHz * m_freqfudge ) ))
            {
                bwmatch = true;
            }

            if(ftm->Duration_S() >= (pd->m_durationuS - (pd->m_durationuS * m_timefudge ) ) &&
               ftm->Duration_S() <= (pd->m_durationuS + (pd->m_durationuS * m_timefudge ) ))
            {
                durmatch = true;
            }

            switch(m_matchtype)
            {
                case eBoth:
                    if(durmatch && bwmatch)
                    {
                        pulses.append(ftm);
                        ftm->setName(pd->m_name);
                    }
                break;
                case eBW:
                    if(bwmatch)
                    {
                        ftm->setName(pd->m_name);
                        pulses.append(ftm);
                    }
                break;
                case eDuration:
                    if(durmatch)
                    {
                        ftm->setName(pd->m_name);
                        pulses.append(ftm);
                    }
                break;
            }
        }
    }
    return pulses;
}


RFPulseDef::RFPulseDef()
{

}


QString RFPulseDef::toString()
{
    QString retval  = "BW_Hz:" + QString::number(m_bandwidthHz,'g',3);
    retval += "Duration_uS:" + QString::number(m_durationuS,'g',3);
    return retval;
}

void RFPulseDef::Save(QSettings *settings)
{
    settings->setValue("BW_Hz",m_bandwidthHz);
    settings->setValue("Duration",m_durationuS);
    settings->setValue("Name",m_name);
}

void RFPulseDef::Load(QSettings *settings)
{
    m_bandwidthHz = settings->value("BW_Hz",0).toDouble();
    m_durationuS = settings->value("Duration",0).toDouble();
    m_name = settings->value("Name",m_name).toString();
}
