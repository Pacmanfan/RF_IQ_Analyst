#include "dlgstreamoptions.h"
#include "ui_dlgstreamoptions.h"

dlgStreamOptions::dlgStreamOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgStreamOptions)
{
    ui->setupUi(this);
}

dlgStreamOptions::~dlgStreamOptions()
{
    delete ui;
}

void dlgStreamOptions::on_cmdOK_clicked()
{
    double bw,cf,sps;
    m_si.StreamID = 1; // since this file contains only 1 stream, give it the first.
    bool ok = false;
    bw = ui->leBandwidth->text().toDouble(&ok);
    if(!ok)
        reject();
    cf = ui->leCF->text().toDouble(&ok);
    if(!ok)
        reject();

    sps = ui->leSampleRate->text().toDouble(&ok);
    if(!ok)
        reject();

    int idx = 0;
    idx = ui->cmbDataType->currentIndex();
    if(idx == -1)
        reject();

    m_si.m_format = (file_format)idx;
    m_si.BandwidthHZ = bw;
    m_si.CenterFreqHz = cf;
    m_si.dIFGain = 0;
    m_si.dRFGain = 0;
    m_si.dReferenceLevel = 0;
    m_si.SampleRateHz =sps;
    m_si.dRFReferenceFrequency = cf;
    m_si.dRFReferenceFrequencyOffset = 0;
    m_si.duration_est_seconds = -1;//EstimateFileDuration16T(filename).toDouble();
    m_si.maxFreqHz = m_si.CenterFreqHz + (m_si.SampleRateHz /2.0);
    m_si.minFreqHz = m_si.CenterFreqHz - (m_si.SampleRateHz /2.0);

    m_si.valid = true;
    accept();
}
