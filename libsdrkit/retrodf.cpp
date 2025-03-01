#include "retrodf.h"
#include <dsp_utils.h>
#include <QFileInfo>

#define DEF_NUMSAMPLES 10000 // 10k of samples to determine DF

RetroDF::RetroDF()
{
    num_avg = 10; //average together 10 results
    m_rawdata = new retro_df_temp_data(DEF_NUMSAMPLES);
}

bool RetroDF::open(QString filename)
{
    m_indexer_stream1.setStreamid(1);
    m_indexer_stream2.setStreamid(2);
    bool op1 = m_indexer_stream1.Open(filename.toLatin1().data());
    bool op2 = m_indexer_stream2.Open(filename.toLatin1().data());

    //load the actual index files
    QFileInfo fi(filename);
    QString fidxname1 = fi.absolutePath() + "/" + fi.baseName() +"_1.idx";
    QString fidxname2 = fi.absolutePath() + "/" + fi.baseName() +"_2.idx";
    bool op4 = m_indexer_stream1.Load(fidxname1);
    bool op5 = m_indexer_stream2.Load(fidxname2);

    bool op3 = m_fi.GatherInfo(filename.toLatin1().data());
    bool success = (op1 && op2 && op3 && op4 && op5);
    StreamInfo *si1 = m_fi.GetStreamInfo(1); // get info from the first stream
    if(si1 == nullptr) // no stream info
        return false;
    //set up the tuners
    m_tuner_center.Setup(&m_indexer_stream1,si1->SampleRateHz,si1->CenterFreqHz,1);
    m_tuner_outer.Setup(&m_indexer_stream2,si1->SampleRateHz,si1->CenterFreqHz,1);
    return success;
}

void RetroDF::close()
{
    m_indexer_stream1.Close();
    m_indexer_stream2.Close();
}

void RetroDF::set_marker(ftmarker *marker)
{
    m_marker = marker;
    //copy the marker over
    m_tuner_center.Marker()->CopyFrom(marker);
    m_tuner_outer.Marker()->CopyFrom(marker);
    //set up the resampling factors
    m_tuner_center.OnMarkerChanged(marker);
    m_tuner_outer.OnMarkerChanged(marker);
}

/*
This is where the magic happens, we should probably split it up a bit
*/
retro_df_results RetroDF::get_results()
{
    retro_df_results results;
    if(m_indexer_stream1.IsOpen() == false)
        return results;

    uint64_t sampleindex = 0;
    StreamInfo *si1 = m_fi.GetStreamInfo(1);
    if(si1 == nullptr) // no stream info
        return results;

    // calculate the start time
    if(m_marker->HasStartTime())
    {
        double starttime = m_marker->StartTime_S();
        sampleindex = starttime * si1->SampleRateHz; // calculate the start index
    }
    //now, get samples from each re-sampled stream

    /* So the concern here is that when we re-sample and offset tune, the phase is not going to be preserved
     * because of the signal source starting at different places
     * How can we ensure that it is?
     * Make sure we're using the same phase by setting to 0 before the resampling
     *
    */
    m_tuner_center.setPhase(0);
    long num_samples_out1 = m_tuner_center.Produce(sampleindex,DEF_NUMSAMPLES,m_rawdata->m_IQ_1);
    m_tuner_outer.setPhase(0);
    long num_samples_out2 = m_tuner_outer.Produce(sampleindex,DEF_NUMSAMPLES,m_rawdata->m_IQ_2);

    if(num_samples_out1 != num_samples_out2)
        return results;

    //calculate the difference in phase
    DSP_Utils::PhaseDiff(m_rawdata->m_IQ_1,m_rawdata->m_IQ_2,m_rawdata->m_phasediff,num_samples_out1);

    DSP_Utils::Complex_To_Arg(m_rawdata->m_IQ_1,m_rawdata->m_phase_1,num_samples_out1);
    DSP_Utils::Complex_To_Arg(m_rawdata->m_IQ_2,m_rawdata->m_phase_2,num_samples_out1);

    //calculate the difference in magnitude
    DSP_Utils::MagDiff(m_rawdata->m_IQ_1,m_rawdata->m_IQ_2,m_rawdata->m_magdiff,num_samples_out1);
    DSP_Utils::MultConst(m_rawdata->m_magdiff,100,num_samples_out1);

    m_rawdata->m_numsamples = num_samples_out1;
    return results;
}

retro_df_results::retro_df_results()
{
    memset(this,0,sizeof(retro_df_results));
}

retro_df_temp_data::retro_df_temp_data(unsigned long sz)
{
    m_numsamples = sz;
    m_IQ_1 = new complex<float>[m_numsamples];
    m_IQ_2 = new complex<float>[m_numsamples];
    m_phasediff = new float[m_numsamples];
    m_phase_1 =  new float[m_numsamples];
    m_phase_2 =  new float[m_numsamples];
    m_magdiff = new float[m_numsamples];
}

retro_df_temp_data::~retro_df_temp_data()
{
    delete []m_IQ_1;
    delete []m_IQ_2;
    delete []m_phasediff;
    delete []m_phase_1;
    delete []m_phase_2;
    delete []m_magdiff;
    m_numsamples =0;
}
