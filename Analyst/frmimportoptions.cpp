#include "frmimportoptions.h"
#include "ui_frmimportoptions.h"
#include <string>
#include <QScrollBar>
#include <qvrt_tools.h>
#include <srifile.h>
#include <dlgstreamoptions.h>
#include <utils.h>
using namespace std;

extern QVRT_FileInfo qvrt_fileinfo;

double Estimate_Num_Samples(StreamInfo *si)
{
    QFileInfo fi(si->name.c_str());
    // get the file length
    double filelen = fi.size();
    double divisor  = 1;
    switch(si->m_format)
    {
        case eU8:
        case eS8:
        divisor = 2;
        break;
        case eS16:
        case eU16:
        divisor = 4;
        break;
        case e32:
        divisor = 8;
        break;
    }
    return filelen / divisor;
}
/*
QString EstimateFileDuration16T(string fn)
{
    QString stime = "";
    QFileInfo fi(fn.c_str());
    // get the file length
    double filelen = fi.size();
    //divide by 4 to get number of samples
    filelen /= 4.0;
    //check to see if it's a 16t file
    QString sriname = fi.absolutePath() + "/" + fi.completeBaseName() + ".sri";
    double playbacktime;
    SRIFile srifile;
    if(srifile.Load(sriname))
    {
        playbacktime = filelen / srifile.SPS;
        stime = QString::number(playbacktime);
    }
    return stime;
}
*/

frmImportOptions::frmImportOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmImportOptions)
{
    ui->setupUi(this);
}

frmImportOptions::~frmImportOptions()
{
    delete ui;
}

void frmImportOptions::Setup(string filename)
{
    m_lstStreams.clear();
    ui->cmbStreamID->clear();
    ui->tblRecInfo->clear();
    try
    {
        _fileName = filename;
        ui->cmbStreamID->clear(); // remove all previous options

        QFileInfo fi(filename.c_str());
        //check to see if it's a 16t file
        if(fi.suffix().toLower() == "16t" ||
                fi.suffix().toLower() == "s16" ||
                fi.suffix().toLower() == "u16" ||
                fi.suffix().toLower() == "s8" ||
                fi.suffix().toLower() == "u8" ||
                fi.suffix().toLower() == "raw" ||
                fi.suffix().toLower() == "cfile")
        {
            //16t/u8/s16 file
            QFileInfo fi(filename.c_str());
            //check to see if it's a 16t/u8/s16 file
            QString sriname = fi.absolutePath() + "/" + fi.completeBaseName() + ".sri";
            SRIFile srifile;
            if(srifile.Load(sriname))
            {
                StreamInfo *si = new StreamInfo();
                si->StreamID = 1; // since this file contains only 1 stream, give it the first.
                si->BandwidthHZ = srifile.BW;
                si->CenterFreqHz = srifile.CF;
                si->dIFGain = srifile.gain2;
                si->dRFGain = srifile.gain1;
                si->dReferenceLevel = srifile.RefLevDB;
                si->SampleRateHz = srifile.SPS;
                si->minFreqHz = si->CenterFreqHz - (si->SampleRateHz / 2.0);
                si->maxFreqHz = si->CenterFreqHz + (si->SampleRateHz / 2.0);
                si->dRFReferenceFrequency = srifile.CF;
                si->dRFReferenceFrequencyOffset = srifile.offset;
                si->name = filename;
                si->m_format = DetermineFormat(si->name.c_str());
                si->num_samples_est = Estimate_Num_Samples(si);
                si->duration_est_seconds =((double) si->num_samples_est) / si->SampleRateHz;
                si->valid = true;

                m_lstStreams.append(si);
                ui->cmbStreamID->addItem("Stream " + QString::number(si->StreamID));
            }else
            {
                //if there is no SRI file, prompt the user for that information
                dlgStreamOptions streamoptions;
                if(streamoptions.exec() == QDialog::Accepted)
                {
                    //get the info
                    StreamInfo *si = new StreamInfo();
                    *si = streamoptions.GetStreamInfo();
                    si->name = filename;
                    si->num_samples_est = Estimate_Num_Samples(si);
                    si->duration_est_seconds =((double) si->num_samples_est) / si->SampleRateHz;
                    si->valid = true;
                    m_lstStreams.append(si);
                    ui->cmbStreamID->addItem("Stream " + QString::number(si->StreamID));
                }else
                {
                    reject();
                }
            }
        }
        else if(fi.suffix().toLower() == "qvrt")
        {
            qvrt_fileinfo.GatherInfo(filename);
            for(int c= 0 ; c < qvrt_fileinfo.NumStreams(); c++)
            {
                StreamInfo *si = qvrt_fileinfo.GetStreamInfoIndex(c);
                si->valid = true;
                si->name = filename;
                m_lstStreams.append(si);
                ui->cmbStreamID->addItem("Stream " + QString::number(si->StreamID));
            }
        }
    }
    catch(...)
    {
        printf("exception\r\n");
    }
    //now, select the first stream
    if(m_lstStreams.size() >0 )
    {
        ui->cmbStreamID->setCurrentIndex(0);
        ShowStreamInfo(m_lstStreams[0]);
    }
}

StreamInfo *frmImportOptions::GetImportOptions()
{
    int idx = ui->cmbStreamID->currentIndex();
    if(idx == -1)
        return nullptr;
    StreamInfo *si = m_lstStreams[idx];
    return si;
}


/*
Show the information for this stream in the table
*/
void frmImportOptions::ShowStreamInfo(StreamInfo *si)
{
    ui->tblRecInfo->setColumnCount(2);

    int rowcnt = 0;
    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("File Name"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(si->name.c_str()));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("File Duration (S)"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(QString::number(si->duration_est_seconds,'f',4)));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("Stream Bandwidth (MHz)"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(QString::number(si->BandwidthHZ/1000000,'f',6)));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("Stream Center Freq (MHz)"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(QString::number(si->CenterFreqHz /1000000,'f',6)));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("Stream Span (MSPS)"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(QString::number(si->SampleRateHz/ 1000000)));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("Stream IF Gain"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(QString::number(si->dIFGain)));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("Stream RF Gain"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(QString::number(si->dRFGain)));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("Stream Reference Level"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(QString::number(si->dReferenceLevel)));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("Stream Reference Frequency Mhz"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(QString::number(si->dRFReferenceFrequency/1000000,'f',3)));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("Stream Ref Freq Offset"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(QString::number(si->dRFReferenceFrequencyOffset)));

    ui->tblRecInfo->setItem(rowcnt,0,new QTableWidgetItem("File format"));
    ui->tblRecInfo->setItem(rowcnt++,1,new QTableWidgetItem(FileFormat2Str(si->m_format).c_str()));


    ui->tblRecInfo->setRowCount(rowcnt);

    ui->tblRecInfo->setColumnWidth(0,200);
    ui->tblRecInfo->setColumnWidth(1,300);
    ui->tblRecInfo->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 35px; }");
}

void frmImportOptions::on_cmbStreamID_currentIndexChanged(int index)
{
    int idx = ui->cmbStreamID->currentIndex();
    if(idx == -1)
        return;
    StreamInfo *si = m_lstStreams[idx];
    ShowStreamInfo(si);
}
