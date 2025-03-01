#include "signaltablemagextractor.h"

SignalTableMagExtractor::SignalTableMagExtractor(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    //connect(m_timer,&QTimer::timeout,this,&SignalTable::onTimer);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

void SignalTableMagExtractor::setPeakdetector(peak_detector *peakdetector)
{
    m_peakdetector = peakdetector;
}

void SignalTableMagExtractor::setSignaldetector(SignalDetector *signaldetector)
{
    m_signaldetector = signaldetector;
}

void SignalTableMagExtractor::StartAuto()
{
    m_timer->start(100);
}

void SignalTableMagExtractor::onTimer()
{
    m_peakdetector->DetectPeaks();
    m_signaldetector->Update();

}

