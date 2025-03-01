#ifndef RETRODF_H
#define RETRODF_H

#include <QObject>
#include <ftmarker.h>
#include <qvrt_tools.h>
#include <sampleindexer.h>
#include "sigtuner.h"

#define NUM_DF_ANT 5 //5 antennae elements circled around center antennae
/*
This is the main interface for the retrospective Direction finder,
In here, we want t oaccomplish several things:
Inputs:
    File name
    Stream IDs (2x - 1 for center antenna, 1 for 5-position commutating)
    Frequency Marker
        CF
        BW
        Start / Stop time

Outputs:
    GPS position at time
    LOB with % confidence interval

There is a lot to say on how to do this, so refer to the Google Document on retrospective DF AIG-129


We're going to read data from the file manually (packet by packet) basis so we can have more control over
retrieving and decoding the
*/
class retro_df_results;
class retro_df_temp_data;



class RetroDF
{
public:
    RetroDF();
    bool open(QString filename); // open a file
    void close();
    void set_marker(ftmarker *marker); //seek time right time and freq
    void set_averaging(int number);
    //should we have something here about setting averaging for lobs?
    retro_df_results get_results(); // perform the DF and retrieve results
    retro_df_temp_data *m_rawdata;
private:
    int num_avg; // how many results to average to get lob results
    ftmarker *m_marker;

    //2 readers for controlliong the streams independantly
    // We'll pull data from both, but antennae context packets from only 1

    //or should we open up and seek in the file manually?
    // can we use the sample indexer to go to the right spot for data and still
    // get the antennae context packets previous to those positions?
    SampleIndexer m_indexer_stream1;
    SampleIndexer m_indexer_stream2;
    SigTuner m_tuner_center;
    SigTuner m_tuner_outer;
    QVRT_FileInfo m_fi;

};

//this class holds the results for a single antenna pair (center - Ant(1-5))
struct lob_result
{
    float m_bearing_angle_LOB;
};

struct df_gps_info // pulled from the context packets of the QVRT file
{
    double latitude;
    double longitude;
    double altitude;
};

class retro_df_results
{
public:
    retro_df_results();
    float m_bearing_angle_LOB; // the overall averaged LOB from 0-360 degrees
    float m_confidence; // the confidence in 0-100%
    lob_result m_results[NUM_DF_ANT]; // the 5 antennae results
    df_gps_info m_gps;
};

/*
This class is so we can pass around some results to the GUI for testing
*/
class retro_df_temp_data
{
public:
    complex<float> *m_IQ_1;
    complex<float> *m_IQ_2;
    float *m_phasediff;
    float *m_magdiff;
    float *m_phase_1;
    float *m_phase_2;
    unsigned long m_numsamples;
    retro_df_temp_data(unsigned long sz);
    ~retro_df_temp_data();
};

#endif // RETRODF_H
