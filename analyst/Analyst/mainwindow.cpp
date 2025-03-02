#include <liquid/liquid.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "frmimportoptions.h"
#include <qvrt_tools.h>
#include <QResource>
#include <QProcess>
#include <QDateTime>
#include <QTime>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <QSettings>
#include <sampleindexer.h>
#include <dlgprogress.h>
#include <fft_filter.h>
#include <signalsource.h>
#include <QVBoxLayout>
#include <audio_util.h>
#include <analystapp.h>
#include "signalstreamscanner.h"
#include <dlgsignaldetector.h>

#define ANALYST_VERSION  "1.0.0.8"

#define MIN_RANGE .2 // 200 Khz
#define FILTER_COEF_LEN 57
#define DEF_WINDOW_FILTERING false
#define DEF_AUTO_RANGE true // the automatic ranging of the FFT and WATERFALL dbM scale
#define DEF_WATERFALL_COLORSCHEME 1 // default waterfall colorscheme is "Hot / 1"

void *audiopumpthreadfn(void *param);
SignalStreamScanner *m_ss_scanner = nullptr;
dlgSignalDetector *dlgsigdetector = nullptr;


static bool showingscope = false;
static bool showingFFT = true;
static bool showingMarkers = false;
static bool showingWaterfall = true;


static bool refreshingGUI = false;
static bool useWindowFilter = DEF_WINDOW_FILTERING;
static bool  WaterfallDirection = true; // top down = true / bottom up = false;
static float WaterDir = 1.0f; // direction of waterfall display

static float *idata = nullptr; // the current timeseries window of data of length _periodsamples
static long iqdatalen = 0; // the array length of idata
static long _periodsamples = 1000;

//static GeoDataPlacemark *cur_location;//



static dlgProgress *dlgprg; // progress dialog box

QVector<ftmarker *> m_exportlist; // list of markers to export
QString m_exportpath; // when we're exporting marker, this is the path to use
double m_exportbwhz; // when exporting, this is the BW to use.

int gradiantindex = 0; // for the waterfall
double waterlow = -150,waterhigh = -30;
bool autowaterrange = DEF_AUTO_RANGE;

static QVector<ftmarker *> selmkrs; // the user-selected markers
static QString markersfilename;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QString Title = "Analyst ";
    Title += ANALYST_VERSION;
    setWindowTitle(Title);
   // setWindowState(Qt::WindowMaximized);

    dlgprg = 0;
    //m_DFWS = new frmDFWorkshop(this);

    gApp.m_indexer = new SampleIndexer(this);
    connect(gApp.m_indexer,SIGNAL(StartBuildIndex()),this,SLOT(onStartBuildIndex()));
    connect(gApp.m_indexer,SIGNAL(EndBuildIndex()),this,SLOT(onEndBuildIndex()));

    _displaytimer = new QTimer(this);

    connect(_displaytimer,SIGNAL(timeout()),this,SLOT(onTimer()));
    frmimport = new frmImportOptions(this);

    InitializeFFT();
    plotWaterfall = ui->wgtWaterfall;
    plotWaterfall->AddTuner(gApp.m_sigtuner.Marker());
    connect(plotWaterfall,SIGNAL(OnMarkersSelected(QVector<ftmarker*>)),this,SLOT(OnMarkersSelectedWaterfall(QVector<ftmarker*>)));
    connect(plotWaterfall,SIGNAL(OnMarkerSelected(ftmarker*,bool)),this,SLOT(OnMarkerSelectedWaterfall(ftmarker*,bool)));
    connect(plotWaterfall,SIGNAL(OnDeleteCurrentMarker()),this,SLOT(OnDeleteCurrentMarker()));

    InitializeScope();
    connect(plotScope,SIGNAL(Pan(double)),this,SLOT(OnPanWaterfall(double)));
    connect(plotScope,SIGNAL(SetPeriodSamples(int)),this,SLOT(onSetPeriodSamples(int)));


    ui->sldWaterRange->setMaximumPosition(-30);
    ui->sldWaterRange->setMinimumPosition(-150);

    //set up a few more connections here.
    connect(plotFFT->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plotWaterfall->plot->xAxis,SLOT(setRange(QCPRange)));
    connect(plotWaterfall->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plotFFT->plot->xAxis,SLOT(setRange(QCPRange)));

    connect(plotFFT,SIGNAL(OnFreqHighlight(double)),this,SLOT(OnFreqHighlightFFT(double)));
    connect(plotWaterfall,SIGNAL(OnFreqHighlight(double)),this,SLOT(OnFreqHighlightFFT(double)));
    connect(plotWaterfall,SIGNAL(OnTimeHighlight(double)),this,SLOT(OnTimeHighlight(double)));
    connect(plotWaterfall,SIGNAL(Pan(double)),this,SLOT(OnPanWaterfall(double)));

    gApp.Intialize();


    ui->wgtScope_Const->setVisible(false);

    //initialize the fft to default parms
    float cf = 100;
    float bw = 5;
    plotFFT->plot->xAxis->setRange(cf - (bw/2),cf + (bw/2));
    plotFFT->plot->xAxis2->setRange(cf - (bw/2),cf + (bw/2));

    connect(plotFFT->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,SLOT(FFTrangeChanged(QCPRange)));
    connect(plotWaterfall->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,SLOT(FFTrangeChanged(QCPRange)));

    plotWaterfall->setXRange(cf - (bw/2),cf + (bw/2));

    _displaytimer->start(40); // 40 ms = 25fps
    UpdateSelInfo();

    LoadSettings();
    //hide a few things for now

    gApp.file_resamp = new file_resampler(this);
    connect(gApp.file_resamp,SIGNAL(EndResample()),this,SLOT(onFileResampEnded()));
    connect(gApp.file_resamp,SIGNAL(StartResample()),this,SLOT(onFileSampleStart()));

    gApp.data_export = new data_exporter(this);
    connect(gApp.data_export,SIGNAL(EndExport()),this,SLOT(onEndExport()));
    connect(gApp.data_export,SIGNAL(StartExport(ftmarker *)),this,SLOT(onStartExport(ftmarker *)));

    // ML classifer setup
    QString apppath = QApplication::applicationDirPath();
    QString clfname = apppath + "/classifiers.ini";
    gApp.m_classifiers.Load(clfname); // load the classifiers information
    ui->wgtClassifiers->SetClassifiers(&gApp.m_classifiers);
    connect(ui->wgtClassifiers,SIGNAL(StartDataExport(bool,QString,double)),this,SLOT(onStartDataExport(bool,QString,double)));
    connect(ui->wgtClassifiers,SIGNAL(ClassifiersUpdated()),this,SLOT(onUpdateClassifyCombo()));
    onUpdateClassifyCombo(); // update it to start off



    connect(gApp.iqplayer,SIGNAL(PlaybackStarted(IQDemodPlayer *)),this,SLOT(onPlaybackStarted(IQDemodPlayer *)));
    connect(gApp.iqplayer,SIGNAL(PlaybackEnded(IQDemodPlayer *)),this,SLOT(onPlaybackEnded(IQDemodPlayer *)));
    connect(gApp.iqplayer,SIGNAL(DataReady(IQDemodPlayer *)),this,SLOT(onPlaybackDataReady(IQDemodPlayer *)));
    SetupAudio();

    connect(gApp.m_sigtuner.Marker(),SIGNAL(MarkerChanged(ftmarker*)),this,SLOT(onMarkerTunerChanged(ftmarker*))); // THE DEFAULT MARKER FOR THE TUNER

    // load the plugins
    LoadPlugins();

    //set up markers table
    markertable = ui->wgtMarkerTable;
    markertable->setVisible(showingMarkers);
    markertable->SetMarkers(&gApp.m_markers);
    connect(markertable,SIGNAL(onMarkerSelected(ftmarker*)),this,SLOT(OnMarkerSelectedTable(ftmarker*)));
    connect(markertable,SIGNAL(onMarkerHighlight(ftmarker*)),this,SLOT(onMarkerHighlightTable(ftmarker*)));
    connect(markertable,SIGNAL(onAddMarker()),this,SLOT(onAddMarkerTable()));
    connect(markertable,SIGNAL(onExportMarker(ftmarker*)),this,SLOT(onExportMarker(ftmarker*)));
    connect(markertable,SIGNAL(onRemoveAllMarkers()),this,SLOT(onRemoveAllMarkers()));
    connect(markertable,SIGNAL(onMerge()),this,SLOT(onMergeMarkers()));
    connect(markertable,SIGNAL(onStartDF(ftmarker *)),this,SLOT(onPerfomRetroDF(ftmarker *)));


    //signals that come from the marker manager
    connect(&gApp.m_markers,SIGNAL(MarkerAdded(ftmarker*)),this,SLOT(onMarkerAdded(ftmarker*)));
    connect(&gApp.m_markers,SIGNAL(MarkerChanged(ftmarker*)),this,SLOT(onMarkerChanged(ftmarker*)));
    connect(&gApp.m_markers,SIGNAL(MarkerRemoved(ftmarker*)),this,SLOT(onMarkerRemoved(ftmarker*)));

    m_audiopumprunning = false;
    ui->wgtMapDoc->setVisible(false);
   // connect(m_ss_scanner,SIGNAL(Completed(bool)),this,SLOT(onSignalScannerCompleted(bool)));

}

void MainWindow::onTimer()
{
    if(gApp.ipo.valid == false)
        return;

    plotWaterfall->Update(gApp.fft_hist,gApp.m_builder->GetTopTimestamp()/ 1000000,gApp.m_builder->GetBottomTimestamp() / 1000000);

    if(showingFFT == true )
    {        
        plotFFT->UpdateFFT(gApp.fft_hist);
        plotFFT->plot->replot();
    }
    if(showingscope == true)
    {
        UpdateScopePlot();
    }

    UpdatePlaybackTimestamp();

    plotWaterfall->plot->replot();
}

void MainWindow::UpdatePlaybackTimestamp()
{
    double currentsample;

    currentsample = gApp.m_builder->sampleindex;
    if(currentsample < 0)
        return;


    float seconds = 0;

    if(gApp.ipo.valid == false )
        return;

    double sps = gApp.ipo.SampleRateHz;

    seconds = currentsample / sps;

    long minutes = 0;
    long hours = 0;
    long iseconds = (long)seconds;
    float fracsec = (seconds - iseconds) * 1000;
    while(seconds >= 60)
    {
        seconds -= 60;
        minutes += 1;
    }
    while(minutes >= 60)
    {
        minutes -= 60;
        hours += 1;
    }
    QTime tm;
    tm.setHMS(hours,minutes,seconds,fracsec);

    ui->lblPlaybackTimestamp->setText(QString("Playback Time : " + tm.toString("hh:mm:ss.z")));

    ui->lblPlaybackIndex->setText("Playback Index : " + QString::number((long)currentsample));

}

void MainWindow::InitializeScope()
{
    plotScope = ui->wgtScope2; // get a pointer to the new scope

    QCPGraph *gr;
    gr = plotScope->AddGraph("FM demod",Qt::green); // general purpose
    gr->setVisible(false);
    gr = plotScope->AddGraph("phase",Qt::blue); // phase
    gr->setVisible(false);
    gr = plotScope->AddGraph("magnitude",Qt::yellow); // phase
    gr->setVisible(false);
    plotScope->AddGraph("I",Qt::red);
    plotScope->AddGraph("Q",Qt::blue);
}


void MainWindow::InitializeFFT()
{
    plotFFT = ui->wgtFFT2; // bind the new fft control
    plotFFT->AddTuner(gApp.m_sigtuner.Marker());
}


MainWindow::~MainWindow()
{

    delete _displaytimer; // to update the screen
    delete ui;
    delete gApp.m_builder;
    //delete fft_filter;
    delete gApp.m_indexer;
    if(dlgprg)
        delete dlgprg;
    delete gApp.fft_hist;
    delete frmimport;
    CloseAudio();
}

void MainWindow::on_actionLoadFile_triggered()
{
    QString curdir ;

    if(QDir("/media/sf_VMShare/IQData").exists())
    {
        curdir = "/media/sf_VMShare/IQData";
    }else
    {
        curdir = QCoreApplication::applicationDirPath();
    }


    QString fileName;
    try
    {
         fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        curdir,
                                                        tr("IQ Files (*.qvrt *.cfile *.16t *.s16 *.u8 *.s8 *.raw)"));
    }catch(...)
    {
        printf("error opening file dialog\r\n");
    }

    if(fileName.trimmed().length() != 0)
    {
        try
        {
            frmimport->Setup(fileName.toLatin1().data());
            frmimport->setModal(true);
            if(frmimport->exec() == QDialog::Rejected)
            {
                return;
            }
        }
        catch(...)
        {
            printf("exception\r\n");
        }
        gApp.ipo = *frmimport->GetImportOptions(); // get the import options
        if(gApp.ipo.valid == false)
            return;

        _displaytimer->stop();

        gApp.fft_hist->Reset(FFT_BIN_SIZE);
        gApp.fft_hist->Set(gApp.ipo.CenterFreqHz,gApp.ipo.SampleRateHz);

        gApp.m_indexer->StartThreadedBuildIndexTable(&gApp.ipo);

         // set up out tuner for tuning into a stream
         gApp.m_sigtuner.Setup(gApp.m_indexer,gApp.ipo.BandwidthHZ,gApp.ipo.CenterFreqHz,gApp.ipo.StreamID);

         QFileInfo qfi(gApp.ipo.name.c_str());
         markersfilename = qfi.absolutePath() + "/" + qfi.completeBaseName() + ".mrk";
         gApp.m_markers.Clear();

         if(gApp.m_markers.Load(markersfilename.toLatin1().data()))
         {
             //QColor green(0,255,0);
             for (int c = 0; c < gApp.m_markers.m_markers.size(); c++)
             {
                 ftmarker *ftm = gApp.m_markers.m_markers[c];
                 plotWaterfall->AddMarker(ftm);
             }
         }
         markertable->UpdateTable();

    }
}

void MainWindow::onStartBuildIndex()
{
    dlgprg = new dlgProgress(this);
    dlgprg->SetMessage("Building File Index");
    dlgprg->show();

}
/*
This is called after the file has been loaded and the build index
process is complete (loaded or built)
*/
void MainWindow::onEndBuildIndex()
{
    if(dlgprg != 0)
    {
        dlgprg->hide();
        delete dlgprg;
        dlgprg = 0;
    }
    gApp.m_indexer->Open();

    gApp.m_builder->GotoTop();
    gApp.m_builder->Build(true);
    _displaytimer->start(40);

    UpdateTunerTimeSeriesData();

    // set up the waterfall auto-range
    if(gApp.ipo.valid && autowaterrange == true)
    {
        waterlow = gApp.fft_hist->GetMinDBM();
        waterhigh = gApp.fft_hist->GetMaxDBM();
        ui->sldWaterRange->setValues(waterlow,waterhigh);
    }

    //inserted from load
    double sps = gApp.ipo.SampleRateHz / 1000000;//lfi.highF_MHz - lfi.lowF_MHz;
    double cf = gApp.ipo.CenterFreqHz / 1000000;//lfi.lowF_MHz + (sps /2);

    gApp.m_sigtuner.Marker()->setCF_MHz(cf);
    gApp.m_sigtuner.Marker()->setBW_MHz(sps/10);

    UpdateSelInfo();
    //set the graph ranges
    plotFFT->SetXRange(gApp.ipo.minFreqHz /1000000, gApp.ipo.maxFreqHz/1000000);//lfi.lowF_MHz,lfi.highF_MHz);
    plotWaterfall->setXRange(gApp.ipo.minFreqHz /1000000, gApp.ipo.maxFreqHz/1000000);

}

void MainWindow::onExportMarker(ftmarker *mrk)
{

    QString filters("QVRT files (*.qvrt);; 16T files (*.16t)");
    QString defaultFilter("QVRT files (*.qvrt)");
    QString outfn = QFileDialog::getSaveFileName(0, "Save file", QDir::currentPath(),
            filters, &defaultFilter);
    if(outfn.length())
    {
        gApp.file_resamp->StartResampling(&gApp.qvrt_fileinfo,mrk,gApp.ipo.name.c_str(),outfn,gApp.ipo.StreamID);
    }
}


void  MainWindow::FFTrangeChanged(const QCPRange &newRange)
{
    if(gApp.ipo.valid == false)
        return;

    double rng = newRange.upper - newRange.lower;
    if(rng > (gApp.ipo.maxFreqHz/1000000) - (gApp.ipo.minFreqHz/1000000) )
    {
        plotFFT->SetXRange((gApp.ipo.minFreqHz/1000000),(gApp.ipo.maxFreqHz/1000000));
    }
}


void MainWindow::UpdateSelInfo()
{
//update the information at the top of the screen about frequency selection and bandwidth

    QString bandwidth =  "Bandwidth: " + QString::number(gApp.ipo.BandwidthHZ/1000000) + " MHz";
    ui->lblBandwidth->setText(bandwidth);

    QString freqrange =  "Range: ( " + QString::number(gApp.ipo.minFreqHz/1000000) + " MHz";
    freqrange += " -> " + QString::number(gApp.ipo.maxFreqHz/1000000) + " MHz )";
    ui->lblFreqRange->setText(freqrange);
   // float sps = lfi.highF_MHz - lfi.lowF_MHz;

    double cf = gApp.ipo.CenterFreqHz/1000000;
    QString centerfreq =  "Center Freq:  " + QString::number(cf,'f',3) + " MHz";
    ui->lblCenterFreq->setText(centerfreq);


    QString Gain = "Gain - RF : " + QString::number(gApp.ipo.dRFGain,'f',1) + "db"
            + " , IF : " + QString::number(gApp.ipo.dIFGain,'f',1) + "db";
    ui->lblGain->setText(Gain);

    QFileInfo fi(gApp.ipo.name.c_str());
    QString base = fi.baseName();  // base = "archive"

    ui->lblName->setText("Name : " + base );//
    ui->lblDuration->setText("Duration : " + QString::number(gApp.ipo.duration_est_seconds));

    UpdateTimeFreqLabels();
    ui->lblPlaybackIndex->setText("Playback Index :" );

}

//checks to see if there are any invalid character
bool FileNameValid(string filename)
{
    char bad_chars[] = "!@%^*~|";
    bool valid = true;
    unsigned int i;
    for (i = 0; i < strlen(bad_chars); ++i)
    {
        if (strchr(filename.c_str(), bad_chars[i]) != NULL)
        {
            valid = false;
            break;
        }
    }
    return valid;
}

void MainWindow::on_cmbWaterfallScheme_activated(int index)
{
    plotWaterfall->colorMap->setGradient((QCPColorGradient::GradientPreset)index);
    gradiantindex = index;
    SaveSettings();
}

void MainWindow::LoadSettings()
{
    QString configPath = QApplication::applicationDirPath() + "/settings.ini";
    QSettings* settings = new QSettings(configPath, QSettings::IniFormat);
    int binsize = settings->value("FFT_BIN_SIZE",DEFAULT_BIN_SIZE).toInt();
    Set_FFT_BinSize(binsize);
    gApp.fft_hist->Reset(binsize);

    int pos = 0;
    switch(binsize)
    {
        case 256: pos = 0; break;
        case 512: pos = 1; break;
        case 1024: pos = 2; break;
        case 2048: pos = 3; break;
        case 4096: pos = 4; break;
        case 8192: pos = 5; break;
        case 16384: pos = 6; break;
    }
    ui->sldFFTRes->setValue(pos);

    int rate = settings->value("FFT_UPDATE_RATE",DEFAULT_FFT_UPDATE_RATE).toInt();
    Set_FFT_Rate(rate);

    switch(rate)
    {
        case 10: ui->sldFFTTimRes->setValue(0);
        break;
        case 20:ui->sldFFTTimRes->setValue(1);
        break;
        case 40:ui->sldFFTTimRes->setValue(2);
        break;
        case 50:ui->sldFFTTimRes->setValue(3);
        break;
        case 100:ui->sldFFTTimRes->setValue(4);
        break;
        case 250:ui->sldFFTTimRes->setValue(5);
        break;
        case 500:ui->sldFFTTimRes->setValue(6);
        break;
        case 1000:ui->sldFFTTimRes->setValue(7);
        break;
        case 2500:ui->sldFFTTimRes->setValue(8);
        break;
        case 5000:ui->sldFFTTimRes->setValue(9);
        break;
        case 10000:ui->sldFFTTimRes->setValue(10);
        break;
        case 25000:ui->sldFFTTimRes->setValue(11);
        break;
        case 50000:ui->sldFFTTimRes->setValue(12);
        break;
        case 100000:ui->sldFFTTimRes->setValue(13);
        break;
        case 200000:ui->sldFFTTimRes->setValue(14);
        break;
        case 400000:ui->sldFFTTimRes->setValue(15);
        break;
        case 800000:ui->sldFFTTimRes->setValue(16);
        break;
    }
    // set the correct index on the gui

    gradiantindex = settings->value("WATERFALL_SCHEME",DEF_WATERFALL_COLORSCHEME).toInt(); // default to 'HOT'
    plotWaterfall->colorMap->setGradient((QCPColorGradient::GradientPreset)gradiantindex);
    ui->cmbWaterfallScheme->setCurrentIndex(gradiantindex);
    // set the correct index on the gui
    UpdateTimeFreqLabels();
    WaterfallDirection = settings->value("WATERFALL_DIRECTION",true).toBool();
    if(WaterfallDirection)
    {
        ui->cmbWaterDir->setCurrentIndex(0);
    }
    else
    {
        ui->cmbWaterDir->setCurrentIndex(1);
    }

    useWindowFilter = settings->value("FILTERING",DEF_WINDOW_FILTERING).toBool();
    ui->chkWindowFilter->setCheckState(useWindowFilter?Qt::Checked:Qt::Unchecked);

    autowaterrange = settings->value("autorange",DEF_AUTO_RANGE).toBool();
    plotWaterfall->setAutorange(autowaterrange);
    plotWaterfall->setWaterfallDirection(WaterfallDirection);

    ui->chkAutoRange->setCheckState(autowaterrange?Qt::Checked:Qt::Unchecked);
    plotFFT->setAutorange(autowaterrange);
    delete settings;
}

void MainWindow::SaveSettings()
{
    QString configPath = QApplication::applicationDirPath() + "/settings.ini";
    QSettings* settings = new QSettings(configPath, QSettings::IniFormat);
    settings->setValue("FFT_BIN_SIZE",FFT_BIN_SIZE);
    settings->setValue("FFT_UPDATE_RATE",FFT_UPDATE_RATE);
    settings->setValue("WATERFALL_SCHEME",gradiantindex);
    settings->setValue("WATERFALL_DIRECTION",WaterfallDirection);
    settings->setValue("FILTERING",useWindowFilter);
    settings->setValue("autorange",autowaterrange);
    settings->sync();
    delete settings;

}

void MainWindow::LoadPlugins()
{
    gApp.m_plugmgr.loadPlugins(qApp->applicationDirPath() + "/plugins");
    ui->cmbTool->clear();
    for(int c = 0 ; c < gApp.m_plugmgr.plugins.length(); c++)
    {
        iPluginInterface *iplg = gApp.m_plugmgr.plugins[c];
        ui->cmbTool->addItem(iplg->Name());
    }
}

void MainWindow::UpdatePluginButtons()
{
    /*
    int idx = ui->cmbTool->currentIndex();
    if(idx == -1)
    {
        // no tools selected / available - hide it
        ui->plgControl->setVisible(false);
    }else
    {
        ui->plgControl->setVisible(true);
        //get the plugin
        ui->cmdProcess->setVisible((gApp.iplgSel->Flags() & PLG_FLAG_TOOL)); // supports the longer running 'Tool' method
        ui->cmdDecode->setVisible((gApp.iplgSel->Flags() & PLG_FLAG_STREAM));// supports the stream 'Process' method
    }
    */
}


void MainWindow::on_cmdUp_clicked()
{
    gApp.m_builder->PanFFT(-20 * WaterDir);
    UpdateTunerTimeSeriesData();
}

void MainWindow::on_cmdDown_clicked()
{
    gApp.m_builder->PanFFT(20 * WaterDir);

    UpdateTunerTimeSeriesData();
}

void MainWindow::on_cmdPageup_clicked()
{
    gApp.m_builder->PanFFT(-256 * WaterDir);

    UpdateTunerTimeSeriesData();
}

void MainWindow::on_cmdPageDown_clicked()
{
    gApp.m_builder->PanFFT(256 * WaterDir);
     UpdateTunerTimeSeriesData();
}

void MainWindow::UpdateTimeFreqLabels()
{

    double trs = uS_PER_ROW;
    QString trsunit = " uS";
    if(trs > 1000)
    {
        trs /= 1000;
        trsunit = " mS";
    }
    if(trs > 1000)
    {
        trs /= 1000;
        trsunit = " S";
    }

    ui->lblFFT_LineTime->setText("FFT Time Resolution : " + QString::number(trs,'f',3) + trsunit);
    ui->lblFFT_TimeRes->setText("FFT Rate : " + QString::number(FFT_UPDATE_RATE) + " Hz" );

    double rbw;
    rbw = gApp.ipo.SampleRateHz / (double)(FFT_BIN_SIZE);
    QString rbwunit = " Hz";
    if(rbw > 1000)
    {
        rbw /= 1000;
        rbwunit = " KHz";
    }
    ui->lblRBW->setText("Resolution Bandwidth : " + QString::number(rbw,'f',2) + rbwunit);
    ui->lblNumBinsRBW->setText("FFT Size : " + QString::number(FFT_BIN_SIZE));

}

void MainWindow::on_sldFFTRes_valueChanged(int value)
{
    // calculate the fft bin size
    int fftsize = 256 << value;
    switch(value)
    {
        case 0:fftsize = 256;break;
        case 1:fftsize = 512;break;
        case 2:fftsize = 1024;break;
        case 3:fftsize = 2048;break;
        case 4:fftsize = 4096;break;
        case 5:fftsize = 8192;break;
        case 6:fftsize = 16384;break;
    }
    Set_FFT_BinSize(fftsize); // set the bin size
    gApp.fft_hist->Reset(fftsize);

    gApp.m_builder->SetFFTSize(fftsize);

    if(gApp.ipo.valid)
    {
        gApp.m_builder->Build(true);
    }

    UpdateTimeFreqLabels();
}

void MainWindow::on_sldFFTTimRes_valueChanged(int value)
{
    int vals[] = {10,20,40,50,100,250,500,1000,2500,5000,10000,25000,50000,100000,200000,400000,800000};
    Set_FFT_Rate(vals[value]);
    ui->lblFFT_TimeRes->setText("FFT Rate : " + QString::number(vals[value]) + " Hz" );
    if(gApp.ipo.valid)
    {
        gApp.m_builder->Build(true);
    }
    UpdateTimeFreqLabels();
}


void MainWindow::on_sldWaterRange_valuesChanged(int min, int max)
{
    waterlow = min;
    waterhigh = max;
    plotWaterfall->setRange_dBm(waterlow,waterhigh);
    plotFFT->setRangeY(waterlow,waterhigh);
}

void MainWindow::on_chkAutoRange_stateChanged(int arg1)
{
    if(arg1 != 0)
    {
        autowaterrange = true;
        if(gApp.ipo.valid)
        {
            waterlow = gApp.fft_hist->GetMinDBM();
            waterhigh = gApp.fft_hist->GetMaxDBM();
            ui->sldWaterRange->setValues(waterlow,waterhigh);
            SaveSettings();

        }
    }else
    {
        autowaterrange = false;
    }
    plotFFT->setAutorange(autowaterrange);
    plotWaterfall->setAutorange(autowaterrange);

}


/*
Update the data for the scope plot

*/
void MainWindow::UpdateScopePlot()
{

    complex<float > *samples = (complex<float > *)idata;
    double tps = 1.0 / gApp.ipo.SampleRateHz; // time per sample
    datarange rng = gApp.m_builder->GetTimeRange();
   // double endtime = (_periodsamples * tps * 1000000);// + rng.low;

    if(samples != 0)
        plotScope->UpdateScope(samples,_periodsamples,tps,rng.low);

}


/*
This function updates the data used in the time series based on the current time/sample index
It retrieves time-series data from the sample indexer
It also performs filtering (if needed)
it puts data in the global "float *idata" array (probably should be complex<float> array...
// number of samples is _periodsamples

*/
void MainWindow::UpdateTunerTimeSeriesData()
{
    // exit if we're not showing time - series or constellation data
    if(showingscope == false )
        return;

    // check to make sure we have enough data storage
    if(iqdatalen < _periodsamples)
    {
        if(idata != 0)
        {
            delete []idata;
        }
        idata = new float[_periodsamples * 2];
        iqdatalen = _periodsamples;
    }

    if(useWindowFilter)
    {
        complex<float> * tmpdat = (complex<float> *)idata;
        gApp.m_sigtuner.setPhase(0);
        gApp.m_sigtuner.Produce(gApp.m_builder->sampleindex,_periodsamples,tmpdat);
    }else
    {
        //if there is no filtering, simply put the data into
        gApp.m_indexer->GetSamples(gApp.m_builder->sampleindex,_periodsamples,(complex<float> *)idata);
    }
}


// signals from the marker manager
void MainWindow::onMarkerChanged(ftmarker *mrk)
{
    Q_UNUSED(mrk)
    gApp.m_markers.Save(markersfilename.toLatin1().data());
}

void MainWindow::onMarkerAdded(ftmarker *mrk)
{
    Q_UNUSED(mrk)
    gApp.m_markers.Save(markersfilename.toLatin1().data());
}

void MainWindow::onMarkerRemoved(ftmarker *mrk)
{
    Q_UNUSED(mrk)
    plotWaterfall->RemoveMarker(mrk);
    gApp.m_markers.Save(markersfilename.toLatin1().data());
}

void MainWindow::onRemoveAllMarkers()
{
    plotWaterfall->ClearMarkers();
    gApp.m_markers.Clear();
    gApp.m_markers.Save(markersfilename.toLatin1().data());
}

void MainWindow::onMergeMarkers()
{
    double minX, maxX, minY, maxY;
    double AX,AY;
    double AX2,AY2;
    if(selmkrs.size() == 0) return;
    //merge all rectangles in the selmkrs list
    for(int c= 0; c < selmkrs.size(); c++)
    {
        ftmarker *ftm = selmkrs[c];
        AX = ftm->FreqLowMHz();
        AX2 = ftm->FreqHighMHz();
        AY = ftm->StartTime_S();
        AY2 = ftm->EndTime_S();

        if(c == 0)
        {
            maxX = minX = AX;
            maxY = minY = AY;
        }
        if(AX > maxX)maxX = AX;
        if(AX < minX)minX = AX;
        if(AX2 > maxX)maxX = AX2;
        if(AX2 < minX)minX = AX2;

        if(AY > maxY)maxY = AY;
        if(AY < minY)minY = AY;
        if(AY2 > maxY)maxY = AY2;
        if(AY2 < minY)minY = AY2;
    }
    //create and initialize marker with min max freq and time values
    ftmarker *newmark = new ftmarker();
    //newmark->InitRect(plotWaterfall,Qt::green);
    newmark->setStartTime_S(minY);
    newmark->setEndTime_S(maxY);
    newmark->setFreqLowMHz(minX);
    newmark->setFreqHighMHz(maxX);

    for(int c= 0; c < selmkrs.size(); c++)
    {
        ftmarker *ftm = selmkrs[c];
        gApp.m_markers.RemoveMarker(ftm);
    }

    selmkrs.clear(); // clear the list of selected markers

    //add it
    gApp.m_markers.AddMarker(newmark);
    plotWaterfall->UnselectMarkers(); // unselect all markers
    plotWaterfall->ClearMarkers(); // remove all markers
    // re-add the markers
    for(int c =0; c< gApp.m_markers.m_markers.size(); c++)
    {
        plotWaterfall->AddMarker(gApp.m_markers.m_markers[c]);
    }

    markertable->SetSelected(newmark);
}

void MainWindow::onPerfomRetroDF(ftmarker *mrk)
{
    Q_UNUSED(mrk)
    /*
    if(!m_retrodf.open(gApp.ipo.name.c_str()))
        return; // fail silently
    m_retrodf.set_marker(mrk);
    retro_df_results results = m_retrodf.get_results();
    retro_df_temp_data *rawdat = m_retrodf.m_rawdata;
    //m_DFWS->UpdatePlotData(rawdat);
    cur_location->setCoordinate( -77.08525, 39.05025, 97.0, GeoDataCoordinates::Degree );
    */
}
/*
This is called when the signal stream scanner completes and has results
*/
/*
void MainWindow::onSignalScannerCompleted(bool cancelled)
{
    if(cancelled)
        return;
    QVector<ftmarker *> markers = m_ss_scanner->GetMarkers();

    for(int c = 0; c< markers.size(); c++)
    {
        ftmarker* ftm = markers.at(c);

        gApp.m_markers.AddMarker(ftm);
        //add to waterfall
        plotWaterfall->AddMarker(ftm);
    }

    QFileInfo qfi(lfi.input_fname);
    QString mfn = qfi.absolutePath() + "/" + qfi.completeBaseName() + ".mrk";
    gApp.m_markers.Save(mfn.toLatin1().data());
}
*/

void MainWindow::on_cmbWaterDir_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            WaterfallDirection = true;
            WaterDir = 1;
        break;
        case 1:
            WaterfallDirection = false;
            WaterDir = -1;
        break;
    }
    SaveSettings();
    plotWaterfall->setWaterfallDirection(WaterfallDirection);
    gApp.m_builder->Build(true);
}


void MainWindow::on_chkWindowFilter_clicked()
{
    useWindowFilter = ui->chkWindowFilter->isChecked();
    UpdateTunerTimeSeriesData();
    SaveSettings();
}

void MainWindow::onStartDataExport(bool all, QString path,double bwhz)
{
    //look at the current marker,
    //start the export of the data to the specified directory
    // if the marker is null, exit

    m_exportlist.clear();
    if(all == false)
    {
        if(selmkrs.size())
        {
            ftmarker *mrk = selmkrs.at(0);

            if(mrk->Tags().length() == 0)
                return; // no marker tag
            //add the marker to the export list
            m_exportlist.push_front(mrk);
        }
    }
    else
    {
        //add all markers with tags
        for(int c =0 ; c< gApp.m_markers.m_markers.size(); c++)
        {
            ftmarker *mrk = gApp.m_markers.m_markers.at(c);
            if(mrk->Tags().length() > 0)
            {
                m_exportlist.push_front(mrk);
            }
        }
    }
    m_exportpath = path;
    m_exportbwhz = bwhz;

    if(m_exportlist.size() >0)
    {
        ftmarker *ftm = m_exportlist[0];
        m_exportlist.remove(0);
        QString markerpath = m_exportpath + ftm->Tags() + "/";
        gApp.data_export->StartExporting(&gApp.qvrt_fileinfo,ftm,gApp.ipo.name.c_str(),markerpath,gApp.ipo.StreamID,m_exportbwhz);
    }
}

void MainWindow::onStartExport(ftmarker *ftm)
{
    //make the path if it doesn't exist
    QString markerpath = m_exportpath + ftm->Tags() + "/";
    if(QDir(markerpath).exists() == false)
    {
        if(!QDir().mkdir(markerpath))
        {
            return; // couldn't create the path
        }
    }

    if(dlgprg == 0)
    {
        dlgprg = new dlgProgress(this);
    }
    QString msg = "Exporting Marker " + ftm->Name();
    msg += ", Tag: " + ftm->Tags();
    dlgprg->SetMessage(msg);
    dlgprg->show();
}

void MainWindow::onEndExport()
{

    if(m_exportlist.size() >0)
    {
        ftmarker *ftm = m_exportlist[0];
        m_exportlist.remove(0);
        QString markerpath = m_exportpath + ftm->Tags() + "/";
        gApp.data_export->StartExporting(&gApp.qvrt_fileinfo,ftm,gApp.ipo.name.c_str(),markerpath,gApp.ipo.StreamID,m_exportbwhz);
    }
    else // we're done, clean up
    {
        if(dlgprg != 0)
        {
            dlgprg->hide();
            delete dlgprg;
            dlgprg = 0;
        }
    }
}


void MainWindow::onFileSampleStart()
{
    dlgprg = new dlgProgress(this);
    dlgprg->SetMessage("Resampling File");
    dlgprg->show();
}


void MainWindow::onFileResampEnded()
{
    if(dlgprg != 0)
    {
        dlgprg->hide();
        delete dlgprg;
        dlgprg = 0;
    }
}


void MainWindow::onUpdateClassifyCombo()
{
    ui->cmbClassifySel->clear();
    for (int c =0 ; c< gApp.m_classifiers.m_list.size(); c++)
    {
        Classifier *cl = gApp.m_classifiers.m_list[c];
        ui->cmbClassifySel->addItem(cl->m_name);
    }
    if(gApp.m_classifiers.m_list.size() > 0)
    {
        ui->cmbClassifySel->setCurrentIndex(0);
    }
}

void MainWindow::onClassificationComplete(ftmarker *ftm, QString msg,QMap<QString, float> results)
{
    Q_UNUSED(msg)
    QString txt = "";

    QString cltxt = "";
    float highval = 0;
    //for(int c =0 ; c < results.keys().size(); c++)
    foreach( QString key, results.keys() )
    {

        if(results[key] > highval)
        {
            cltxt = key;
            highval = results[key];
        }
    }

    highval *= 100;

    txt = ftm->Name() + " : " + cltxt + " : " + QString::number(highval,'f',2);
    ui->lblClsRslt->setText(txt);
}



void MainWindow::on_cmdUp_Small_clicked()
{
    gApp.m_builder->PanFFT(-1 * WaterDir);
    UpdateTunerTimeSeriesData();
}

void MainWindow::on_cmdDown_Small_clicked()
{
    gApp.m_builder->PanFFT(1 * WaterDir);

    UpdateTunerTimeSeriesData();
}

void MainWindow::onPlaybackEnded(IQDemodPlayer *player)
{
     Q_UNUSED(player)
     StopAudioPump();
     QPixmap image(":/images/icons/start");
     ui->cmdDecode->setIcon(QIcon(image));
}

void MainWindow::onPlaybackStarted(IQDemodPlayer *player)
{
    Q_UNUSED(player)
    StartAudioPump();
}

void MainWindow::onPlaybackDataReady(IQDemodPlayer *player)
{
    Q_UNUSED(player)

}


//message from the waterfall that one or more markers have been selected

void MainWindow::OnMarkersSelectedWaterfall(QVector<ftmarker *> markers)
{
    for(int c = 0; c < markers.size() ;c ++)
    {
        selmkrs.append(markers[c]);
    }
    //now update the selected markers on the table of markers

    if(markers.size() > 0)
    {
        // select the first row in markers table
       markertable->SetSelected(markers[0]);
    }else
    {

        markertable->SetSelected(0);
    }
}

// single marker selected on waterfall from doubleclick probably - hard select - 'goto'

void MainWindow::OnMarkerSelectedWaterfall(ftmarker *mrk,bool softsel)
{
    selmkrs.clear(); // clear the list of any currently selected markers,
    selmkrs.append(mrk);
    markertable->SetSelected(mrk);
    UpdateTunerTimeSeriesData();
    if(!softsel)
    {
        ui->chkWindowFilter->setCheckState(Qt::Checked);
        //save the check state for the window filter
        SaveSettings();
        // set the frequency window
        gApp.m_sigtuner.Marker()->setBW_MHz(mrk->BW_MHz());
        gApp.m_sigtuner.Marker()->setCF_MHz(mrk->CF_MHz());
        //SetupSelection(mrk->CF(),mrk->BW());
        //set up thje default tuner to go to those freq
        //tell the fft builder to go to the markers time index
        double tm = mrk->StartTime_S();
        if(mrk->HasStartTime() == false)
            tm = 0;
        gApp.m_builder->GotoTimeStamp(tm);
    }
    markertable->SetSelected(mrk);
}

/*
This is when the user clicks the 'goto' button on the marker table widget
*/
void MainWindow::OnMarkerSelectedTable(ftmarker *mrk)
{
    selmkrs.clear(); // clear the list of any currently selected markers,
    selmkrs.append(mrk);

    // the table marker widget selected a marker
    gApp.m_sigtuner.Marker()->setBW_MHz(mrk->BW_MHz());
    gApp.m_sigtuner.Marker()->setCF_MHz(mrk->CF_MHz());

    double tm = mrk->StartTime_S();
    if(mrk->HasStartTime() == false)
        tm = 0;
    gApp.m_builder->GotoTimeStamp(tm);
    ui->chkWindowFilter->setCheckState(Qt::Checked);
    UpdateTunerTimeSeriesData();
}

/*
This is the soft select of the markers table, just show highlights
*/
void MainWindow::onMarkerHighlightTable(ftmarker *mrk)
{
    //soft select
    //clear the list of selected markers from the selection rectanlge
    selmkrs.clear();
    selmkrs.append(mrk);
    plotWaterfall->UnselectMarkers();// unselect all previous
    plotWaterfall->SetMarkerSelected(mrk);

}

// The add button from the marker table widget was clicked
void MainWindow::onAddMarkerTable()
{
    ftmarker *mark = new ftmarker();
    //set it to be in the current screen range

    if(plotWaterfall->HasSelection())
    {
        mark->CopyFrom(plotWaterfall->GetCurSel());
    }
    else
    {
        mark->CopyFrom(gApp.m_sigtuner.Marker());
        mark->setHasStartTime(false);
        mark->setHasEndTime(false);
    }
    gApp.m_markers.AddMarker(mark);

    plotWaterfall->AddMarker(mark);
    plotWaterfall->SetMarkerSelected(mark);
}

void MainWindow::OnDeleteCurrentMarker()
{
    // delete the currently selected marker
    //get the currently highlighted marker o
    if(selmkrs.size() > 0 )
    {
        ftmarker *ftm = selmkrs.at(0);
        gApp.m_markers.RemoveMarker(ftm);
        plotWaterfall->RemoveMarker(ftm);
    }
}

void MainWindow::onMarkerTunerChanged(ftmarker *ftm)
{
    //maybe call the waterfall to update the marker?
    if(ftm == gApp.m_sigtuner.Marker())
    {
        refreshingGUI = true;
        //on windowing changed, here, set up the filter to match
        UpdateTunerTimeSeriesData();
        refreshingGUI = false;
    }
}

void MainWindow::onSetPeriodSamples(int len)
{
    _periodsamples = len;
    UpdateTunerTimeSeriesData();
}


void MainWindow::on_cmdClearMax_clicked()
{
    gApp.fft_hist->ClearMaxValues();

}


///To get a value from the FFT tracer and display it as text on the GUI
void MainWindow::OnFreqHighlightFFT(double val)
{
    ui->lblMOFreq->setText("Frequency : " + QString::number(val) + " MHz");
}

void MainWindow::OnTimeHighlight(double val)
{
    ui->lblMOTime->setText("Timestamp: " + QString::number(val*1000,'f',3) + " ms");
}

void MainWindow::OnPanWaterfall(double val)
{
     gApp.m_builder->PanFFT(val * WaterDir);
     UpdateTunerTimeSeriesData();
}

void MainWindow::on_cmbTool_currentIndexChanged(int index)
{
    //determine what was selected
    // for now, it's a static index    ,
    // once we have loadable plugins, this will change
    if(index == -1)
        return;

    // remove all widgets from ui->plugParent
    QLayout *lay = ui->wgt_tool_parent->layout();
    if(lay != nullptr)
    {
        QLayoutItem *child;
        while ((child = lay->takeAt(0)) != nullptr)
        {
            child->widget()->setParent(nullptr);
            delete child;
        }
    }
    // add the new selected plugin config to the layout
    gApp.iplgSel = gApp.m_plugmgr.plugins[index];
    QWidget *wgt = gApp.iplgSel->GetConfigGUI();
    if(wgt != nullptr) // we have a configuration GUI
    {
        wgt->setParent(ui->wgt_tool_parent);
        if(lay == nullptr)
        {
            QVBoxLayout *qbl = new QVBoxLayout(ui->wgt_tool_parent);
            qbl->addWidget(wgt);
            ui->wgt_tool_parent->setLayout(qbl);
        }else
        {
            lay->addWidget(wgt);
        }
    }
    UpdatePluginButtons();
}


void MainWindow::on_cmdDetect_clicked()
{
    //feature detector sets the time in uS, not seocnds
//    QVector <ftmarker *> mrks = gApp.feat_detector.DetectFeatures(gApp.fft_hist,false, waterlow, waterhigh,eCache,false);
    int thresh = ui->sldDetectSensitivity->value();

    QVector <ftmarker *> mrks = gApp.feat_detector.DetectFeatures2(gApp.fft_hist,thresh,eCache,false);

    double bts = gApp.m_builder->GetTopTimestamp();
    bts /= 1000000;

    for(int c = 0; c< mrks.size(); c++)
    {
        ftmarker* ftm = mrks.at(c);
        //convert from relative time to an absolute timestamp - also convert from uS to seconds

        ftm->setStartTime_S(ftm->StartTime_S()/1000000 + bts);
        ftm->setEndTime_S((ftm->EndTime_S()/1000000 + bts));
        gApp.m_markers.AddMarker(ftm);
        //add to waterfall
        plotWaterfall->AddMarker(ftm);
        //ftm->
    }
    QFileInfo qfi(gApp.ipo.name.c_str());
    QString mfn = qfi.absolutePath() + "/" + qfi.completeBaseName() + ".mrk";
    gApp.m_markers.Save(mfn.toLatin1().data());
}

void MainWindow::on_cmdDecode_clicked()
{
    // if there is not file loaded, return
    if(gApp.ipo.valid == false )
        return;
    if(gApp.iqplayer->Running() == false)
    {
        double starttime = -1,endtime = -1;
        if(selmkrs.size() != 0)
        {
            //get the selected marker
            ftmarker *mrk =selmkrs.at(0);
            //set the tuner frequency
            gApp.m_sigtuner.Marker()->setBW_MHz(mrk->BW_MHz());
            gApp.m_sigtuner.Marker()->setCF_MHz(mrk->CF_MHz());
            //get start and end times if set
            if(mrk->HasStartTime())starttime = mrk->StartTime_S();
            if(mrk->HasEndTime())endtime = mrk->EndTime_S();
        }

        //get current selected plugin
        if(gApp.iplgSel == nullptr)
            return;

        gApp.iqplayer->SetDecoder(gApp.iplgSel);
        gApp.iqplayer->SetTuner(&gApp.m_sigtuner,starttime,endtime);

        gApp.iqplayer->Start();
        //ui->cmdDemod->setText("Stop Demodulator");
//        QPixmap image(":/images/stop");
        QPixmap image(":/images/icons/stop");
        ui->cmdDecode->setIcon(QIcon(image));
    }
    else
    {
        QPixmap image(":/images/icons/start");
        ui->cmdDecode->setIcon(QIcon(image));
        gApp.iqplayer->Stop();
    }
}

// thread func for audio pump
void *audiopumpthreadfn(void *param)
{
    MainWindow *mw = (MainWindow *)param;
    mw->AudioPumpThread();
    return nullptr;
}


void MainWindow::StartAudioPump()
{
    if(m_audiopumprunning)
        return;
    m_audiopumprunning = true;
    pthread_create(&m_audiopump_thread, NULL, audiopumpthreadfn, this);
}

void MainWindow::StopAudioPump()
{
    m_audiopumprunning = false;
    pthread_join(m_audiopump_thread,0);  // wait for completion

}

void MainWindow::AudioPumpThread()
{
    while(m_audiopumprunning)
    {
        CircBuff<float> *data = gApp.iqplayer->GetOutBuff();
        static float tbuf[AUDIO_BUFFER_SIZE];
        while(data->size() >= AUDIO_BUFFER_SIZE)
        {
            //read the float audio data from the output of the player
            int read = (int)data->read(tbuf,AUDIO_BUFFER_SIZE);
            PlayAudio(tbuf, read);
        }
    }
}

void MainWindow::on_cmdClassify_clicked()
{
    //get the index of the current classifier
    int idx = ui->cmbClassifySel->currentIndex();
    if(idx == -1)
        return;
    // get the classifier
    Classifier *cl = gApp.m_classifiers.m_list[idx];
    //now get the current marker (or list)
    if(selmkrs.size() == 0)
        return;
    ftmarker *ftm = selmkrs.at(0);

    ui->lblClsRslt->setText("");
    if(cl->StartClassify(&gApp.qvrt_fileinfo,ftm,gApp.ipo.name.c_str(),gApp.ipo.StreamID))
    {
        connect(cl,SIGNAL(ClassificationComplete(ftmarker*,QString,QMap<QString, float>)),this,SLOT(onClassificationComplete(ftmarker*,QString,QMap<QString, float>)));
    }else
    {
        //error starting the classify
        ui->lblClsRslt->setText("Classify Error : Check Marker Duration");
    }
}


void MainWindow::on_cmdEnergyDetect2_clicked()
{
    if(m_ss_scanner == nullptr)
    {
        m_ss_scanner = new SignalStreamScanner(this);
        dlgsigdetector = new dlgSignalDetector(m_ss_scanner,&gApp.ipo,this);
    }
    dlgsigdetector->exec();

    QVector<ftmarker *> markers = m_ss_scanner->GetMarkers();

    gApp.m_markers.AddMarkers(markers);
    for(int c = 0; c< markers.size(); c++)
    {
        ftmarker* ftm = markers.at(c);
        //add to waterfall
        plotWaterfall->AddMarker(ftm);
    }

    QFileInfo qfi(gApp.ipo.name.c_str());
    QString mfn = qfi.absolutePath() + "/" + qfi.completeBaseName() + ".mrk";
    gApp.m_markers.Save(mfn.toLatin1().data());
    //now, add all these markers from the signal stream detector

}

void MainWindow::on_cmdWorkshop_clicked()
{
    //m_DFWS->show();
}

void MainWindow::on_actionWaterfall_triggered()
{
    showingWaterfall = !showingWaterfall;
    ui->wgtWaterfall->setVisible(showingWaterfall);
    SaveSettings();
}


void MainWindow::on_actionscope_triggered()
{
    //crashing when no data is loaded and scope / constellation is shown.
    showingscope = !showingscope;//ui->chkShowScope->isChecked();
    if(gApp.ipo.SampleRateHz > 0)
    {
        UpdateTunerTimeSeriesData();
        UpdateScopePlot();
    }
    ui->wgtScope_Const->setVisible(showingscope );
}


void MainWindow::on_actionFFT_triggered()
{
    showingFFT = !showingFFT;
    plotFFT->setVisible(showingFFT);
}


void MainWindow::on_actionMarker_triggered()
{
    showingMarkers = !showingMarkers;
    markertable->setVisible(showingMarkers);
}

