#ifndef FFT_HIST2
#define FFT_HIST2

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdio>
#include <fstream>


class FFT_Hist2
{
public:

    FFT_Hist2();
    ~FFT_Hist2();
    int GetBinSize(){return m_binsize;}

    //functions for adding a row of data
    float *GetNextAddRow();
    void AddData(int numbins, float centerfreq,float BWHz);
    //functions for retrieving the data
    float *GetBlock1(int *num_rows);
    float *GetBlock2(int *num_rows);

    float *AvgData(){return m_avg;} // return the power averaged data
    float *MaxValues(); // return the high-water marks

    // Set and get the number of rows to average
    void SetAverageLength(int avg_rows){m_avgrows = avg_rows;}
    int GetAverageLength(){return m_avgrows;}

    int NumRows(); // current number of rows of data entered
    int MaxRows(); // returns the maxinum number of rows in this plot

    void ClearMaxValues();

    float GetFreqHz(int binidx); // in hz
//    float GetTime(int row); // get the time index at the given row (uS) from the uS_PER_ROW
    float GetLowFreqHz();
    float GetHighFreqHz();
    float GetCenterFreq(){return m_CFHz;}
    float GetMinAvgDBM(bool rounded = false); // for graphing, changes when new data is added, reset when freq or span changes
    float GetMaxAvgDBM(bool rounded = false); // for graphing, changes when new data is added, reset when freq or span changes

    float GetBWHz(){return GetHighFreqHz() - GetLowFreqHz();}
    float GetRBWHz(){return GetBWHz() / (float)m_binsize;}

    int GetBinIndex(float freqHz); // return the closest bin index to the frequency or -1

    void Lock(){m_mutex.lock();}
    void Unlock(){m_mutex.unlock();}

private:

    void CalcAvg();
    float m_avg_min; // valid until the freq / span changes
    float m_avg_max; // valid until the freq / span changes
    int m_numrows;// number of rows entered in the m_alldat table
    int m_avgrows; // how many rows to average
    int m_cur_row_index; // the index to the next row of data to add into

    int m_binsize; // number of bins (X table size)
    float *m_alldat; // a DEFAULT_BIN_SIZE * MAX_FFT_ROWS table image of values
    float *m_avg; // a single row of average data
    float *m_maxvalues; // a single row of max values (need to find some way to make them fade / remove)

    float m_CFHz; // in Hz - the center frequency
    float m_BWHz; // in Hz - also the SPS
    boost::mutex m_mutex; // for locking the tables to avoind threading issues

};

#endif // FFT_HELPER_H
