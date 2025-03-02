#ifndef ANALYSTAPP_H
#define ANALYSTAPP_H
#include <qvrt_tools.h>
#include <sampleindexer.h>
#include <fft_builder.h>
#include <ftmarker.h>
#include <freq_time_marker.h>
#include <sigtuner.h>
#include <feature_detector.h>
#include <file_resampler.h>
#include <data_exporter.h>
#include <classifier.h>
#include <pluginmanager.h>
#include <iqdemodplayer.h>
/*
This is the main 'app' object that controls most of what's going on here.
I'm trying to keep things out of mainwindow so we have separation of
GUI and business logic
*/

class AnalystApp
{
public:
    AnalystApp();
    void Intialize();

    // which streams we're importing
    QVRT_FileInfo qvrt_fileinfo;
    StreamInfo ipo;
    SampleIndexer *m_indexer = nullptr; // the indexer into the qvrt file, this provides random access to the IQ sample
    FFT_Builder *m_builder = nullptr; // this builds the historical view of the waterfall in a FFT_Hist
    FFT_Hist *fft_hist = nullptr; // An FFT wrapper class that contains the waterfall view, average, max, etc...
    freq_markers m_markers; // the marker manager
    SigTuner m_sigtuner; // the default tuner we're using
    feature_detector feat_detector;
    file_resampler *file_resamp;
    data_exporter *data_export; // for numpy files
    Classifiers m_classifiers; // machine learning classifiers
    libsdrkitplugins::PluginManager m_plugmgr; // the plugin manager
    iPluginInterface *iplgSel = nullptr; // currently selected plugin
    IQDemodPlayer *iqplayer = nullptr;

};


extern AnalystApp gApp;
#endif // ANALYSTAPP_H
