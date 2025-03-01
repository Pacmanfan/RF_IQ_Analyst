#ifndef DATA_EXPORTER_H
#define DATA_EXPORTER_H

#include <QObject>
#include <qvrt_tools.h>
#include <ftmarker.h>
#include <signalsource.h>
#include <file_resampler.h>
#include <resampler_arb.h>
#include <iq_16t.h>
#include <sampleindexer.h>
#include <thread>
/*
This class is used to export data from a QVRT / 16T file into short segments
of IQ data stored in .npy files. These .npy files are used as an input to the
Tensorflow ML algorithms training phase.
This data exporter will create a number of short segments and name them
random names
*/

class data_exporter : public QObject
{
    Q_OBJECT
public:
    explicit data_exporter(QObject *parent = 0);

    void StartExporting(QVRT_FileInfo *fi, ftmarker *ftm,QString inputfilenme, QString outputbasename, int StreamID, double bandwidth);
    void SingleExport(QVRT_FileInfo *fi, ftmarker *ftm,QString inputfilenme, QString outfilename, int StreamID, double bandwidth);
    void DoExport();

private :
   // pthread_t rst; // resample thread
    std::thread *rst;
    bool m_running;
    QString infile,outfile;
    file_format m_format_in; // reader format
    ftmarker *m_marker;
    double m_bandwidthHz; // in hertz
    QVRT_FileInfo *m_fi;
    int m_streamid;
    SignalSource sigsrc_resamp; // signal source for the resampler for offset tuning

signals:
    void StartExport(ftmarker *ftm);
    void ProgressExport();
    void EndExport();

public slots:
};

#endif // DATA_EXPORTER_H
