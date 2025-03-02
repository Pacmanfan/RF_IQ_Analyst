#include "analystapp.h"


AnalystApp gApp;

AnalystApp::AnalystApp() {}

void AnalystApp::Intialize()
{
    fft_hist = new FFT_Hist();
    m_builder = new FFT_Builder();
    m_builder->SetFFTHist(fft_hist);
    m_builder->SetIndexer(gApp.m_indexer);
    iqplayer = new IQDemodPlayer();
}
