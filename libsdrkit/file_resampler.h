#ifndef FILE_RESAMPLER_H
#define FILE_RESAMPLER_H
#include <liquid/liquid.h>
#include <QObject>
#include <ftmarker.h>
#include <qvrt_tools.h>
#include <signalsource.h>
#ifdef WIN32
#define HAVE_STRUCT_TIMESPEC
#endif
//#include <pthread.h>
#include <thread>
#include <utils.h>

using namespace std;
file_format DetermineFormat(QString filename);

class file_resampler : public QObject
{
    Q_OBJECT
public:

    explicit file_resampler(QObject *parent = 0);
    void StartResampling(QVRT_FileInfo *fi, ftmarker *ftm,QString inputfilenme, QString outputfilename, int StreamID);
    void DoResample();

private :
    //pthread_t rst; // resample thread
    std::thread *rst;
    bool m_running;
    QString infile,outfile;
    file_format m_format_in; // reader format
    file_format m_format_out; // writer format
    ftmarker *m_marker;
    QVRT_FileInfo *m_fi;
    int m_streamid;
    SignalSource sigsrc_resamp; // signal source for the resampler for offset tuning



signals:
    void StartResample();
    void ProgressResample();
    void EndResample();

public slots:
};

#endif // FILE_RESAMPLER_H
