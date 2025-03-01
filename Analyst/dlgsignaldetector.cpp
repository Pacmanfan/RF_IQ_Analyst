#include "dlgsignaldetector.h"
#include "ui_dlgsignaldetector.h"

static ftmarker ss_ftm;

dlgSignalDetector::dlgSignalDetector(SignalStreamScanner *ssscanner,StreamInfo *info,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSignalDetector)
{
    ui->setupUi(this);
    m_ssscanner = ssscanner;
    m_info = info;
    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    connect(m_ssscanner,SIGNAL(Progress(QString,float)),this,SLOT(onProgress(QString,float)));
    connect(m_ssscanner,SIGNAL(Completed(bool)),this,SLOT(onCompleted(bool)));
}

dlgSignalDetector::~dlgSignalDetector()
{
    delete ui;
}

void dlgSignalDetector::onProgress(QString message, float percent)
{
    ui->progressBar->setValue((int)percent);
}

void dlgSignalDetector::onCompleted(bool cancelled)
{
    ui->cmdStart->setText("Start");
    ui->progressBar->setValue(0);

    if(!cancelled)
        close();
}

void dlgSignalDetector::on_cmdStart_clicked()
{
    if(m_ssscanner->Running() == true)
    {
        //send cancel
        m_ssscanner->CancelDetecting();
    }
    else
    {
        ss_ftm.setHasEndTime(false);
        ss_ftm.setHasStartTime(false);

        int adjval = 8 + ui->sldFFT->value();
        double binsize = pow(2, adjval);

        int skiplen = 50000;
        m_ssscanner->StartDetecting(&ss_ftm,m_info->name.c_str(),m_info->StreamID,binsize,skiplen);
        ui->progressBar->setValue(0);
        ui->cmdStart->setText("Cancel");
    }
}

void dlgSignalDetector::on_sldFFT_valueChanged(int value)
{
    // convert this slider value into a power of 2 between 256 and 16384
    /*
    256 = 2^8
    */
    int adjval = 8 + value;
    double binsize = pow(2, adjval);

    ui->lbl_NumBins->setText(QString::number(binsize));

    double rbw = m_info->SampleRateHz / binsize;
    ui->lblRBW->setText(QString::number(rbw,'f',2));

}
