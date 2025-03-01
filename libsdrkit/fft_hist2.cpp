#include "fft_hist.h"
#include "fft_hist2.h"
#include "string.h"
#include "memory.h"
#include <time.h>
#include <stdio.h>
#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions

using namespace std;
#define NOISE_FLOOR -145.0

FFT_Hist2::FFT_Hist2()
{
    m_numrows = 0;
    m_avg_min = 0;
    m_avg_max = 0;
    m_CFHz = 0;
    m_BWHz = 0;
    m_cur_row_index = 0;

    m_avgrows = DEFAULT_AVG_LEN;
    m_binsize = DEFAULT_BIN_SIZE;

    //allocate memory
    m_maxvalues = new float[MAX_FFT_SIZE]; // max values is a single row
    m_alldat = new float[MAX_FFT_SIZE * MAX_FFT_ROWS];
    m_avg = new float[MAX_FFT_SIZE* MAX_FFT_ROWS]; // another map of the averaged data

    ClearMaxValues();
}

FFT_Hist2::~FFT_Hist2()
{
    if(m_alldat !=0 )
    {
        delete []m_alldat;
        m_alldat = 0;
    }

    if(m_avg !=0 )
    {
        delete []m_avg;
        m_avg = 0;
    }

    if(m_maxvalues !=0 )
    {
        delete []m_maxvalues;
    }
}

void FFT_Hist2::ClearMaxValues()
{
    for(int c=0 ; c < m_binsize ; c++)
    {
        m_maxvalues[c] = NOISE_FLOOR;// set to noise floor
    }
}

float FFT_Hist2::GetMinAvgDBM(bool rounded)
{
    if(rounded == true)
    {
        // so, if the number is -108.78 dbm, we can
        // divide by 10 : -10.878
        // take the floor(-10.878) = -11
        // multiply by 10 = -110
        // subract 10 : -110 - 10 = -120
        float tmp = m_avg_min / 10.0;
        tmp = floor(tmp);
        tmp *= 10;
        tmp -= 15;
        if(tmp < NOISE_FLOOR)
            tmp = NOISE_FLOOR;
        return tmp;
    }
    else
    {
        return m_avg_min;
    }
}

float FFT_Hist2::GetMaxAvgDBM(bool rounded)
{
    if(rounded == true)
    {
        float tmp = m_avg_max / 10.0;
        tmp = ceil(tmp);
        tmp *= 10;
        tmp += 15;

        return tmp;
    }
    else
    {
        return m_avg_max;
    }
}

/*
This returns a pointer to a row where we can add data next;
*/
float *FFT_Hist2::GetNextAddRow()
{
    //get a point to the next row where we're going to add data
    return &m_alldat[m_cur_row_index * m_binsize];
}

float *FFT_Hist2::GetBlock1(int *num_rows)
{
    int lastidx;
    if(m_cur_row_index == 0)
    {
       lastidx =  MAX_FFT_ROWS - 1;
    }else
    {
        lastidx = m_cur_row_index - 1;
    }
    // (256  - 0 )  // first row would be 255 rows
    // 256 - 255 = 1 for last row
    *num_rows = MAX_FFT_ROWS  - lastidx;
    return &m_alldat[lastidx * m_binsize];
}

float *FFT_Hist2::GetBlock2(int *num_rows)
{
    int lastidx;
    if(m_cur_row_index == 0)
    {
       lastidx =  MAX_FFT_ROWS - 1;
    }else
    {
        lastidx = m_cur_row_index - 1;
    }
    *num_rows = lastidx;
    return m_alldat;//
}

void FFT_Hist2::AddData(int numbins, float centerfreq,float BWHz)
{
    Lock();

    if(numbins != m_binsize) // support a changing bin size if needed
    {
        m_binsize = numbins; // set the new number of bins
        m_numrows = 0;
        ClearMaxValues(); // reset the max values
        m_avg_min = m_alldat[0]; // get the first entry as a starting point
        m_avg_max = m_alldat[0];

        for(int y = 0; y < MAX_FFT_ROWS; y++)
            for(int x = 0; x < MAX_FFT_SIZE; x++)
                m_alldat[y * MAX_FFT_SIZE + x] = NOISE_FLOOR;
    }

    if(centerfreq != m_CFHz || m_BWHz != BWHz)
    {
        m_CFHz = centerfreq; // set the new CF
        m_BWHz  = BWHz;
        m_numrows = 0; // this should reset the average
        ClearMaxValues();
        m_avg_min = m_alldat[0]; // get the first entry as a starting point
        m_avg_max = m_alldat[0];
        //memcpy(m_avg,srcdat, m_binsize * sizeof(float));
    }

    m_numrows ++; // increase the number of rows of actual data
    if(m_numrows > MAX_FFT_ROWS)
    {
        m_numrows = MAX_FFT_ROWS; // limit the max number of rows to the max
    }

    // now, calculate the new average fft row from the last X samples
    CalcAvg();

    //calculate Max values
    float *row = &m_alldat[m_cur_row_index * m_binsize];
    for(int x = 0; x < m_binsize;x++)
        if(row[x] > m_maxvalues[x])
            m_maxvalues[x] = row[x];

    m_cur_row_index++;
    if(m_cur_row_index == MAX_FFT_ROWS)
        m_cur_row_index = 0; // wrap back around

    Unlock();
}

/*
This function calculates a single line (the latest) of average data
based on the last m_avgrows rows

*/
void FFT_Hist2::CalcAvg()
{
    int navrows = m_avgrows; // the number of rows to average

    if(m_numrows < navrows )
    {
        navrows = m_numrows;
    }

    //ok, a special case here.
    // if the m_avgrows is 1, there is really no averaging going on, just a copy
    int num_rows;
    float *srcdat = GetBlock1(&num_rows);
   //srcdat += navrows * m_binsize; // this is the actual current row, we haven't incremented m_cur_row_index yet from the adddata function

    if(navrows == 1 || num_rows < navrows)
    {
        // copy the single row to the average data
        memcpy(m_avg,srcdat, m_binsize * sizeof(float));
        //still have to calculate the min max averages
        for(int x = 0; x < m_binsize;x++)
        {
            if(m_avg[x] < m_avg_min) m_avg_min = m_avg[x];
            if(m_avg[x] > m_avg_max) m_avg_max = m_avg[x];
        }
        return; //and exit early
    }


    // iterate over the x column from 0 to bin size
    for(int x = 0; x < m_binsize;x++)
    {
        m_avg[x] = 0.0; //initialize the value to 0
        for(int y=0; y < navrows ; y ++ )
        {
            if(x ==0 && y==0)
            {
                m_avg_min = srcdat[0];
                m_avg_max = srcdat[0];
            }
            //should convert from log to linear here first...
            if(y==0)
            {
                m_avg[x] = Pow2Mw(srcdat[(y * m_binsize) + x]); // set the data
            }
            else
            {
                m_avg[x] += Pow2Mw(srcdat[(y * m_binsize) + x]); // add the data
            }
        }
        m_avg[x] /= (float)navrows; // calculate the average of the mw power
        m_avg[x] = Mw2Pow(m_avg[x]);

        if(m_avg[x] < m_avg_min) m_avg_min = m_avg[x];
        if(m_avg[x] > m_avg_max) m_avg_max = m_avg[x];
    }
}


/*
Return a pointer to the max rows
*/
float *FFT_Hist2::MaxValues()
{
    return m_maxvalues;
}

float FFT_Hist2::GetLowFreqHz()
{
    float val = m_CFHz;
    val -= (m_BWHz / 2.0);
    return val;
    //return m_centerfreq - (m_spanHz / 2);
}

float FFT_Hist2::GetHighFreqHz()
{
    float val = m_CFHz;
    val += (m_BWHz / 2.0);
    return val;
}
/*
 // get the time index at the given row (uS) from the uS_PER_ROW
// This is the relative row time, not the absolute row time
float FFT_Hist2::GetTime(int row)
{
    float timeuS = (float)row *uS_PER_ROW;
    return timeuS;
}
*/
// return freq in hz from 0 -> DEFAULT_BIN_SIZE-1 value
float FFT_Hist2::GetFreqHz(int binidx) // in Hz
{
    float leftfreq = GetLowFreqHz();
    float freqinc = ((float)m_BWHz) / ((float)GetBinSize());
    return leftfreq + (binidx * freqinc);
}

// return the closest bin index to the frequency or -1
int FFT_Hist2::GetBinIndex(float freqHz)
{
    //long leftfreq = m_centerfreq - (m_spanHz / 2);
    //long rightfreq = m_centerfreq + (m_spanHz / 2);
    float freqinc = m_BWHz / (float)GetBinSize();
    int binidx = 0;
    if(freqHz >= GetLowFreqHz() && freqHz <= GetHighFreqHz())
    {
        //can I calculate the index directly?
        float diff_freq = freqHz - GetLowFreqHz();
        binidx = (int)(diff_freq / freqinc);
        return binidx;
    }else
    {
        return -1;
    }
}


int FFT_Hist2::NumRows() // current number of rows of data entered
{
    return m_numrows;
}
