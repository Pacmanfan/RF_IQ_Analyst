#ifndef IQDEMODPLAYER_H
#define IQDEMODPLAYER_H

#include <QObject>
#include <ftmarker.h>
#include <iplugininterface.h>
#include <qvrt_tools.h>
#include <file_resampler.h>
#include <sigtuner.h>
#include <thread>

/*
The purpose of this class is to play IQ data into a demod plugin
The source is the QVRT / 16T stream file.

We have a pointer reference to a FTMarker that describes the start/stop, BW and CF
This class will:
 - Read IQ data from the file
 - Filter / Resample
 - Configure the plugin input / output rates
 - Send data to the plugin
 - Get the data back from the plugin

 For plugins that are marked as Audio plugins, it will then send the data to the audio device

 This class encapsulates an entire IQ processing chain
    This class will also have the option of throttling to the correct speed
    This class should also report it's processing speed (samples/sec)
    This can also have a circular buffer to get samples / data out of this
*/

/*
This should be changed to be a little more lightweight
We really don't need to re-implement the tuner functionality,
this was doen prior to making 'Tuner' a things of it's own
We also don't need to re-open the file
*/
class IQDemodPlayer : public QObject
{
    Q_OBJECT
private:
    SigTuner *m_tuner;
    iPluginInterface *m_decoder;
   // pthread_t playthread; // playback thread
    std::thread *playthread;
    bool m_running;
    CircBuff<float> *outbuf; // holds the float decoded data
    double actual_processing_rate; // what is the actual processing rate after resampling / filtering
    double m_starttime,m_endtime; // can be -1 for no start or stop times
public:
    explicit IQDemodPlayer(QObject *parent = 0);
    void SetTuner(SigTuner *tuner, double starttime, double endtime);//{m_tuner = tuner;m_starttime = starttime;m_endtime = endtime;}
    void SetDecoder(iPluginInterface *idecoder){m_decoder = idecoder;}
    bool Start();
    void Stop();
    void PlaybackThread();
    bool Running(){return m_running;}
    double ActualProcessingRate(){return actual_processing_rate;}
    CircBuff<float> *GetOutBuff(){return outbuf;}
signals:
    void PlaybackEnded(IQDemodPlayer *player); // sent when over / cancelled
    void PlaybackStarted(IQDemodPlayer *player);
    void DataReady(IQDemodPlayer *player);
public slots:
    void onTunerMarkerChanged(ftmarker *mrk);
};

#endif // IQDEMODPLAYER_H
