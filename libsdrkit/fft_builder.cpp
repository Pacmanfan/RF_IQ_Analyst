#include "fft_builder.h"
#include "fft_hist.h"
#include "sampleindexer.h"
#include "fft_fftw.h"


FFT_Builder::FFT_Builder()
{
    //fft = make_fft_sink(MAX_FFT_SIZE);
#ifdef USE_IPP
    m_fftcalc = new fft_ipp();
#else
//    m_fftcalc = new fft_calc2();
    m_fftcalc = new fft_fftw();

#endif

    startidx = 0;
    endidx = MAX_FFT_ROWS;
    m_filter = 0;
    m_usePSD = false;
    m_updatemax = false;
}

datarange FFT_Builder::GetTimeRange()
{
    datarange rng;
    rng.high = GetBottomTimestamp();
    rng.low = GetTopTimestamp();
    return rng;
}

void FFT_Builder::PanFFT(int val)
{
    // need to convert this number of screen rows int oa change in sample index
   // datarange before,after;
    double samplesperrow = m_fft_hist->GetBWHz() / (double) FFT_UPDATE_RATE;

    sampleindex += samplesperrow * val;
    bool clipped = false;
    if(sampleindex < 0)
    {
        sampleindex = 0;
        clipped = true;
    }

    startidx =  0;
    endidx = MAX_FFT_ROWS;

    if(!clipped)
        PanCache(val);
   // after = GetTimeRange();
    Build(); // rebuild the view
}

/*
this will pan the fft_helper cache up/down by the specified number of rows
This allows us to move the data around instead of having to re-calculate everything
it also calculates the new start/end index for the remainder of the cache building
rows can be a positive or negative number of rows to move (direction)
*/
void FFT_Builder::PanCache(int rows)
{
    int absrow = abs(rows);
    if(absrow >= MAX_FFT_ROWS)
    {
        // can't re-use any of the cache, invalidate it all
        startidx = 0;
        endidx = MAX_FFT_ROWS;
        return;
    }
    int numrows;
    float *srcstart,*dststart;
    int totalsize;
    if(rows > 0)
    {
        numrows = MAX_FFT_ROWS - rows;
        totalsize = FFT_BIN_SIZE * numrows * sizeof(float);
        //data is copied down the image
        srcstart = m_fft_hist->GetCacheRow(0);
        dststart = m_fft_hist->GetCacheRow(rows);
        memmove(srcstart,dststart,totalsize);
        startidx = MAX_FFT_ROWS - rows;
        endidx = MAX_FFT_ROWS;
    }
    else // negative rows
    {
        numrows = MAX_FFT_ROWS - absrow;
        srcstart = m_fft_hist->GetCacheRow(absrow);
        dststart = m_fft_hist->GetCacheRow(0);
        totalsize = FFT_BIN_SIZE * numrows * sizeof(float);
        memmove(srcstart,dststart,totalsize);
        startidx = 0;
        endidx = absrow;
    }


}

double FFT_Builder::GetTopTimestamp()
{
    //need to convert absolute sample index to micro-second timestamp
    double tm = ((double)sampleindex) / m_fft_hist->GetBWHz();
    tm *= 1e6;
    return tm;
}

double FFT_Builder::GetBottomTimestamp()
{
    double idx = sampleindex;
    double samplesperrow = m_fft_hist->GetBWHz() / (double) FFT_UPDATE_RATE;
    idx += samplesperrow * MAX_FFT_ROWS;
    double tm = ((double)idx) / m_fft_hist->GetBWHz();
    tm *= 1e6;
    return tm;

}

void FFT_Builder::SetFFTSize(int sz)
{
    Q_UNUSED(sz);
    startidx = 0;
    endidx = MAX_FFT_ROWS;

}

void FFT_Builder::GotoTop()
{
    sampleindex = 0;
    Build();
}

void FFT_Builder::GotoTimeStamp(double timestamp)
{
    //calculate index based on timestamp
    sampleindex = (long)(timestamp * m_fft_hist->GetBWHz());;
    Build(true);
}

void FFT_Builder::GotoSampleIndex(long idx)
{
    sampleindex = idx;
    Build(true);
}

// here's where the magic happens
void FFT_Builder::Build(bool invalidate)
{
    if(invalidate)
    {
        startidx = 0;
        endidx = MAX_FFT_ROWS;
    }
    Build(m_fft_hist->GetCacheRow(0));
    m_fft_hist->m_numrows = 1; // why am I setting to 1 here?
    m_fft_hist->CalcAvg(); //calculate the average
    m_fft_hist->CalcCacheMinMax();
}

// I need a way to calculate the max FFT based on this
//We're clearly indexing directly into the rows and setting the data
// perhaps way can update the max FFT by handing it a pointer to a row


void FFT_Builder::Build(float *cache)
{
    int startrow = startidx;
    int endrow = endidx;
    long rowsampleindex;
    complex<float> IQData[MAX_FFT_SIZE]; // IQ data for this row
    complex<float> IQDataFilt[MAX_FFT_SIZE]; // IQ data for this row
    complex<float> SinWave[MAX_FFT_SIZE]; // Singal source wave
    //uS_PER_ROW
    double samplesperrow = m_fft_hist->GetBWHz() / (double) FFT_UPDATE_RATE;
    for(int c =  startrow; c < endrow; c++)
    {
        //calculate the sample index of this row
        rowsampleindex  = sampleindex + (samplesperrow * c);
        // get the IQ data for this row
        m_indexer->GetSamples(rowsampleindex,FFT_BIN_SIZE,IQData);
        float *row;
        //perform a FFT on the timeseries data
        if(m_filter != 0)
        {
            m_sigsrc->work(FFT_BIN_SIZE,SinWave);

            // Use the sine wave to shift the IQ data prior to filtering
            for(int d = 0; d < FFT_BIN_SIZE; d++)
                IQData[d] *= SinWave[d]; // address as complex numbers
            // filter this IQData
            m_filter->Filter(IQData,IQDataFilt,(unsigned int)FFT_BIN_SIZE);
            // now shift the data back in place
            for(int d = 0; d < FFT_BIN_SIZE; d++)
                IQDataFilt[d] *= (SinWave[ FFT_BIN_SIZE - d - 1] );//

            //now copy it to the row
            row = cache + ( FFT_BIN_SIZE * c);
            if(m_usePSD)
            {
               // m_fftcalc->PerformPSD(IQDataFilt,row,FFT_BIN_SIZE,m_fft_hist->GetBWHz());
            }else{
                m_fftcalc->PerformFFT(IQDataFilt,row,FFT_BIN_SIZE);
            }
        }
        else
        {
            //now copy it to the row
            row = cache + ( FFT_BIN_SIZE * c);
            if(m_usePSD)
            {
                //m_fftcalc->PerformPSD(IQData,row,FFT_BIN_SIZE,m_fft_hist->GetBWHz());
            }else{
               // m_fftcalc->PerformFFT(IQData,row,row,FFT_BIN_SIZE);
                 m_fftcalc->PerformFFT(IQData,row,FFT_BIN_SIZE);
            }
        }
        //calculate the FFT Max, keep the max till cleared
        m_fft_hist->CalcMax(row);
    }

}
