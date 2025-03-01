#include "iqdemodplayer.h"
#include <resampler_arb.h>
#include <sampleindexer.h>
#include <iq_16t.h>
#include <time.h>
#include <QFileInfo>



/*

Deprecated - use new plugin stuff!


*/




void *iqplayerthreadfn(void *param);

IQDemodPlayer::IQDemodPlayer(QObject *parent) : QObject(parent)
{
    m_running = false;
    outbuf = new CircBuff<float>(PROCESS_SIZE * 4);
}

bool IQDemodPlayer::Start()
{
    //start thread
    //make sure the plugin accepts IQ data
    ProcessSignature sig = m_decoder->Signature();
    StreamSig *ss = &sig.insigs[0];
    if(ss->_itemtype != eComplex)
        return false;
    //make sure the plugin outputs audio data
    ss = &sig.outsigs[0];
    if(ss->_itemtype != eFloat)
        return false;

    m_running = true;
    //pthread_create(&playthread, NULL, iqplayerthreadfn, this);
    playthread = new std::thread([this]{PlaybackThread();});
    return true;
}

void IQDemodPlayer::SetTuner(SigTuner *tuner, double starttime, double endtime)
{
    m_tuner = tuner;
    m_starttime = starttime;
    m_endtime = endtime;
    connect(m_tuner->Marker(),SIGNAL(MarkerChanged(ftmarker*)),this,SLOT(onTunerMarkerChanged(ftmarker*)));
}

void IQDemodPlayer::Stop()
{
    m_running = false;
    if(playthread !=nullptr )
    {
        if(playthread->joinable())
            playthread->join();
        delete playthread;
        playthread = nullptr;
    }
    //pthread_join(playthread,0);  // wait for completion
}


//for now, this will work for an audio processing chain that
// takes an IQ stream and outputs a single array of shorts
void IQDemodPlayer::PlaybackThread()
{
    /*
    clock_t start_t, now_t, diff_t;


    std::complex<float> indata[PROCESS_SIZE* 4];
    float audiodat[PROCESS_SIZE];// for audio plugins

    //define an array of input streams
   // plg_vector_const_void_star in_array;
  //  in_array.push_back((const void *) indata);

    //define the array of output streams
  //  plg_vector_void_star out_array;
 //   out_array.push_back((void *) audiodat);

    long startidx = 0;//
    long endindex = 0;//m_endtime * si.SampleRateHz; // time in seconds

    if(m_starttime != -1)
    {
        startidx = m_starttime * m_tuner->SourceSPS();// absolute position in file
    }

    if(m_endtime != -1)
    {
        endindex = m_endtime * m_tuner->SourceSPS();// absolute position in file
    }

    long cursampidx = startidx; // the current absolute sample index we're on
    long samplecount = 0;

    //set the input rate of the decoder to be the bandwidth of the marker
    m_decoder->SetInputRate(m_tuner->Marker()->BW_Hz());

    emit(PlaybackStarted(this));

    start_t = clock(); // get start time
    while(m_running)
    {
        //get some samples from the
        m_tuner->Produce(cursampidx,PROCESS_SIZE,indata); // get the filtered, resampled data into the indata array (in_array)

        cursampidx += (long)((double)PROCESS_SIZE) * (1.0 / m_tuner->ResampleRate()); // calculate the number of absolute samples we went through
        samplecount += PROCESS_SIZE;

        // now send the data through the plugin
         //long numout = m_decoder->Process(in_array,out_array,PROCESS_SIZE);
         // numout is the number of audio samples
         //send to the audio device?
         //outbuf->write(audiodat,numout); // audiodat is what out_array[0] is pointing to
         if(outbuf->size() > PROCESS_SIZE) // arbitrary size so we don't trigger the data ready flag too much
         {
            emit DataReady(this);
         }

        //check to see if we've processed enough samples
        if(cursampidx >= endindex && m_endtime != -1)
        {
            m_running = false;
        }

        //check to see if we're past the end of the file
        if(m_tuner->Indexer()->PastLength(cursampidx))
        {
            m_running = false;
        }

        //update time
        now_t = clock();
        diff_t = (double)(now_t - start_t) / CLOCKS_PER_SEC;
        if(diff_t > 1)
        {
            actual_processing_rate = samplecount; // save the processing samples / second
            start_t = now_t;
            samplecount = 0; // reset sample count
        }
    }
    emit(PlaybackEnded(this));
    */
}

void IQDemodPlayer::onTunerMarkerChanged(ftmarker *mrk)
{
    // this is so we can retune to a new BW
    static double lastbw = 0;
    if(mrk->BW_Hz() != lastbw)
    {
        lastbw = mrk->BW_Hz();
        // this crashes - usually becasue we're in the middle of using the resampler / filter
       // m_decoder->SetInputRate(m_tuner->Marker()->BW_Hz());  // may have to change the rate
    }
}


