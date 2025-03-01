#ifndef FEATURE_DETECTOR_H
#define FEATURE_DETECTOR_H
//#include <opencv2/opencv.hpp>
#include <QString>
#include <QVector>
#include <vector>
#include <QPixmap>

#include <stdio.h>
#include <stdlib.h>
#include <fft_hist.h>

#include <ftmarker.h>

//using namespace cv;
using namespace std;

//feature detector row source
enum FD_Source
{
    eCache, // read from cache
    eAvg, // read from average
    eRaw // raw data
};

class feature_detector
{
public:
    feature_detector();

    QVector<ftmarker *> DetectFeatures(FFT_Hist *helper,bool autorange = true, float rlow = 0, float rhigh = 0, FD_Source src = eCache, bool ignoreedges = true);
    QVector<ftmarker *> DetectFeatures2(FFT_Hist *helper,int thresh = 11, FD_Source src = eCache, bool ignoreedges = true, double S_per_Line = -1);
};

//bool RectInRect(Rect *r1, Rect *r2);
#endif // BURST_DETECTOR_H
