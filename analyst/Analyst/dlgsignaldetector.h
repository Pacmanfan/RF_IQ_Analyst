#ifndef DLGSIGNALDETECTOR_H
#define DLGSIGNALDETECTOR_H

#include <QDialog>
#include <signalstreamscanner.h>
#include <qvrt_tools.h>

namespace Ui {
class dlgSignalDetector;
}

class dlgSignalDetector : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSignalDetector(SignalStreamScanner *ssscanner,StreamInfo *info,QWidget *parent = nullptr);
    ~dlgSignalDetector();

private:
    Ui::dlgSignalDetector *ui;
    SignalStreamScanner *m_ssscanner;
    StreamInfo *m_info;
public slots:
    void onProgress(QString message,float percent);
    void onCompleted(bool cancelled);
private slots:
    void on_cmdStart_clicked();
    void on_sldFFT_valueChanged(int value);
};

#endif // DLGSIGNALDETECTOR_H
