#ifndef SIGNALSTREAMSCANNER_H
#define SIGNALSTREAMSCANNER_H
#include <signaldetector.h>
#include <QObject>
#include <utils.h>
#include <qvrt_tools.h>
#include <iq_16t.h>
#include <QVector>
#include <ftmarker.h>
#include <thread>

/*
This class is used to scan through and entire stream of information
and detect signals
// this will use the signaldetector class
the main purpose of this class is to iterate throguh IQ data, perform an FFT on the data at predetermined time intervals
and to send that information to a narrow band signal detector
this will create a a new list of markers that the user can review and then export
*/

class SignalStreamScanner : public QObject
{
    Q_OBJECT
public:
    explicit SignalStreamScanner(QObject *parent = nullptr);

    void StartDetecting(ftmarker *ftm,QString inputfilenme, int StreamID, size_t fft_search_size, size_t fft_interleave);
    void ScanThread();
    //things to control
    /*
     * we can pass in an FTMarker to indicate the start/end of what to search
    */

    void CancelDetecting();
    bool Running(){return m_running;}
    QVector<ftmarker *> GetMarkers(){return m_markers;}

private:
    FFT_Hist *m_fft_hist;
    //pthread_t rst; // resample thread
    std::thread * rst;
    bool m_running;
    QString infile;
    file_format m_format_in; // reader format
    size_t m_fft_search_size;
    size_t m_fft_interleave;
    ftmarker *m_marker;
    int m_streamid;
    QVector<ftmarker *> m_markers;
signals:
    void Progress(QString Message,float percent);
    void Completed(bool cancelled);

public slots:
};

#endif // SIGNALSTREAMSCANNER_H
