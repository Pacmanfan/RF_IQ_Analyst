#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QTimer>
#include <fft_hist.h>
#include "qcustomplot.h"
#include "ftmarker.h"
#include <freq_time_marker.h>
#include <QQueue>
#include <frmimportoptions.h>
#include <qconstellationplot.h>
#include "wgt_scope.h"
#include <wgt_fft.h>
#include <wgt_waterfall.h>
#include <wgt_marker_table.h>
#include <iqdemodplayer.h>
//#include <marble/MarbleWidget.h>

//using namespace Marble;


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer *_displaytimer; // to update the screen

    wgt_Scope * plotScope;
    wgt_FFT   * plotFFT;
    wgt_waterfall *plotWaterfall;
    wgt_marker_table *markertable;
    QConstellationPlot * plotConstellation;
    frmImportOptions *frmimport;
    //MarbleWidget *mapWidget;

    void UpdateScopePlot();
    void UpdateTunerTimeSeriesData();
    void InitializeFFT();
    void InitializeScope();
    void InitializeConstellation();
    void UpdateCursorDotPosition(double xCenterIn);

    void UpdateSelInfo();
    void UpdateTimeFreqLabels();
    void UpdatePlaybackTimestamp();

    void SetupMapping();

    void LoadSettings();
    void SaveSettings();

    void LoadPlugins(); // load the plugins and tools
    void UpdatePluginButtons();

    void StartAudioPump();
    void StopAudioPump();
    void AudioPumpThread();
    bool m_audiopumprunning;
    pthread_t m_audiopump_thread; // playback thread


    QVector <ftmarker *> MergeVertical(QVector <ftmarker *> mrks);

private:
    Ui::MainWindow *ui;

signals:
public slots:
    void onTimer(); // display timer
    void FFTrangeChanged(const QCPRange &newRange);
    void onStartBuildIndex();
    void onEndBuildIndex();

    void onExportMarker(ftmarker *ftm);
    void onStartDataExport(bool all,QString path, double BWHz); // signal to indicate markers to export
    void onStartExport(ftmarker *ftm);
    void onEndExport();
    void onUpdateClassifyCombo();
    void onClassificationComplete(ftmarker*,QString,QMap<QString, float> );

    void onPlaybackEnded(IQDemodPlayer *player); // sent when over / cancelled
    void onPlaybackStarted(IQDemodPlayer *player);
    void onPlaybackDataReady(IQDemodPlayer *player);


    void OnMarkersSelectedWaterfall(QVector<ftmarker *> markers);
    void OnMarkerSelectedWaterfall(ftmarker *marker,bool softsel);    // single marker selection

    //signals from marker table widget
    void OnMarkerSelectedTable(ftmarker *marker);    // marker hard selected from the marker table widget
    void onMarkerHighlightTable(ftmarker *marker);
    void onAddMarkerTable();
    void OnDeleteCurrentMarker();

    void onMarkerTunerChanged(ftmarker *mrk);

    void onSetPeriodSamples(int len);

    //signals from marker manager
    void onMarkerChanged(ftmarker *mrk);
    void onMarkerAdded(ftmarker *mrk);
    void onMarkerRemoved(ftmarker *mrk);

    void onRemoveAllMarkers();
    void onMergeMarkers();

  //  void onSignalScannerCompleted(bool cancelled);
    void onPerfomRetroDF(ftmarker *mrk);// received a signal from the marker table wiget to start a DF on the indicated marker

private slots:
    void on_cmdLoad_clicked();

    void on_cmbWaterfallScheme_activated(int index);

    void on_cmdUp_clicked();
    void on_cmdDown_clicked();
    void on_cmdPageup_clicked();
    void on_cmdPageDown_clicked();

    void on_sldFFTRes_valueChanged(int value);
    void on_sldFFTTimRes_valueChanged(int value);

    void on_sldWaterRange_valuesChanged(int min, int max);
    void on_chkAutoRange_stateChanged(int arg1);

    void on_cmbWaterDir_currentIndexChanged(int index);
    void on_chkWindowFilter_clicked();

    void onFileResampEnded();
    void onFileSampleStart();

    void on_cmdUp_Small_clicked();
    void on_cmdDown_Small_clicked();

    void on_cmdSettings_clicked();

    void on_cmdClearMax_clicked();
    void on_chkShowFFT_clicked();
    void on_chkShowScope_clicked();
    void on_chkShowConstellation_clicked();
    void OnFreqHighlightFFT(double val);
    void OnTimeHighlight(double val);
    void OnPanWaterfall(double val);
    void on_cmbTool_currentIndexChanged(int index);
    void on_chkMarkers_clicked();
    void on_cmdDetect_clicked();
    void on_cmdDecode_clicked();
    void on_cmdClassify_clicked();
    void on_cmdHelp_clicked();
    void on_chkMap_stateChanged(int arg1);
    void on_chkShowWaterfall_clicked();
    void on_cmdEnergyDetect2_clicked();
    void on_cmdWorkshop_clicked();
};

#endif // MAINWINDOW_H
