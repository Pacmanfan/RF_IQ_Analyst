#ifndef SIGNALTABLE_H
#define SIGNALTABLE_H

#include <QObject>
#include <QTimer>
#include <signaldetector.h>
#include <utils.h>

#if (PLAYMAKER_COMPONENT)
#include <wbt_tuner_wrapper.h>
#endif

class SignalTableMagExtractor : public QObject
{
    Q_OBJECT
public:
    explicit SignalTableMagExtractor(QObject *parent = nullptr);
    QTimer *m_timer;
    SignalDetector *m_signaldetector;
    peak_detector *m_peakdetector;
#if (PLAYMAKER_COMPONENT)
    WBT_Tuner_Wrapper *m_tuner_wrapper;
    void setTuner_wrapper(WBT_Tuner_Wrapper *tuner_wrapper);
#endif
    void setSignaldetector(SignalDetector *signaldetector);
    void StartAuto();
    void StopAuto();

    void setPeakdetector(peak_detector *peakdetector);

signals:

public slots:
private slots:
    void onTimer();
};

#endif // SIGNALTABLE_H
