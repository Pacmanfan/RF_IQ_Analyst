#include "feature_detector.h"


//we're going to make an image from the waterfall data
// and feed it into the burst detector


int idx = 0;
#define MIN_FEATURE_SIZE_DEFAULT_X 4
#define MIN_FEATURE_SIZE_DEFAULT_Y 4
#define MIN_FEATURE_AREA_SIZE_DEFAULT_Y 16

feature_detector::feature_detector()
{

}

/*
return true if r2 is inside r1
*/
/*
bool RectInRect(Rect *r1, Rect *r2)
{
    if(r1->contains(r2->tl()) && r1->contains(r2->br()))
        return true;

    return false;
}
*/

float mapVal(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void CalcMinMax(uint8_t *dat, int sz,int *mmin, int *mmax)
{
    int val;
    for(int c =0 ; c < sz; c++)
    {
        val = dat[c];
        if(c == 0)
        {
            *mmin = val;
            *mmax = val;
        }else
        {
            if(val < *mmin) *mmin = val;
            if(val > *mmax) *mmax = val;
        }
    }
    printf("Min %d : Max %d \r\n",*mmin,*mmax);

}
/*
void MarkContours(Mat *image, QString fn)
{
    vector<vector<Point> > contours;
    findContours(*image,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);

  //  findContours(image_denoise_threshold,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE); // new

    vector<Rect> boundRect( contours.size() );
    vector<vector<Point> > contours_poly( contours.size() );

    for(unsigned  int i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        //minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
        rectangle( *image, boundRect[i].tl(), boundRect[i].br(), Scalar(255,255,255), 2, 8, 0 );
    }
   // imwrite(fn.toLatin1().data(),*image);
}
*/

float LocalNoiseFloorFD(int idx,int binwidth,int imwidth, float *stddev, float *tdat)
{
    int lowidx = idx - binwidth;
    int highidx = idx + binwidth;

    if(lowidx < 0 )lowidx = 0;
    if(highidx > imwidth)
        highidx = imwidth;

  //  printf("************FFT_Helper::LocalNoiseFloor\r\n");
    float   mean = 0;
    float   sum_of_sq = 0;

    int range = highidx - lowidx;

    for (int i = lowidx; i < highidx; i++) //calculate the mean of the FFT and the sum of squares
    {
        mean += tdat[i];
        sum_of_sq += tdat[i] * tdat[i];
    }
    mean /= range;
    // now calculate the standard deviation
    *stddev = sqrt( sum_of_sq/range-mean*mean );
    return mean;
}



/*
This will look for burst in the cache table
could be modified in the futre for average or alldat tables
*/
QVector<ftmarker *> feature_detector::DetectFeatures2(FFT_Hist *helper, int thresh, FD_Source src, bool ignoreedges,double S_per_Line  )
{
    Q_UNUSED(thresh)
    Q_UNUSED(ignoreedges)
    Q_UNUSED(S_per_Line)
    helper->Lock();
    int xsz = helper->GetBinSize();
    int ysz = helper->MaxRows();
    uint8_t *waterfallimage = new uint8_t[xsz*ysz];
   // uint8_t *waterfallfloor = new uint8_t[xsz*ysz]; // adjusted local noise floor

    float minV,maxV; // get min and max of the waterfall image
    float *fp;


    fp = helper->GetCacheRow(0); // using the cache data
    if(src == eAvg)
    {
        fp = helper->GetAvgRow(0); // using the average data
    }
    if(src == eRaw)
    {
        fp = helper->GetRow(0); // using the average data
    }

/*
Here, we're creating an image of the noise floor by iterating over each row
for each row Ry, create a filter gaussian filter N pixels long
The filter is created such that only values that do NOT exceed the standard deivation are used

so an example row:
11,10,11,12,10,11,18,19,11,

for each pixel in row Ry
*/

    //find the low / high values in the waterfall image
    for(int c = 0; c< xsz*ysz; c++)
    {
        if(c == 0)
        {
            minV = *fp;
            maxV = *fp;
        }
        if(*fp < minV) minV = *fp;
        if(*fp > maxV) maxV = *fp;
        fp++; // next pointer position
    }


    //tweak the levels
    //calculate range
    float range =  (maxV - minV);
    float scale = 255.0f / range;//(maxV - minV) ; // create a scalar value
    printf("Min %f : Max %f : scaler %f\r\n",minV,maxV,scale);


    uint8_t *ip = waterfallimage; // pointer to the image data
    fp = helper->GetCacheRow(0);//GetAvgRow(0); // reset pointer to beginning
    if(src == eAvg)
    {
        fp = helper->GetAvgRow(0); // using the average data
    }

    if(src == eRaw)
    {
        fp = helper->GetRow(0); //
    }

    uint8_t tvi;
    int temp_1,temp_h;
    float fv;
    for(int c = 0; c < xsz*ysz; c++)
    {
        fv = *fp;        
        if(fv < minV) // if the current pixel is less than the minimum (shouldn't happen)
        {
            fv = 0; // set it to 0
        }else
        {
            fv -= minV; // else subtract the minimum value from this
        }
        tvi = (fv * scale);
        *ip = tvi;
        fp++; // next pointer position
        ip++;

        if(c == 0)
        {
            temp_1 = tvi;
            temp_h = tvi;
        }
        if(tvi < temp_1) temp_1 = tvi;
        if(tvi > temp_h) temp_h = tvi;
    }

    printf("Min Col %d : Max Col %d \r\n",temp_1,temp_h);
    helper->Unlock();

    //**********************************************

/*


    //declare some images
    Mat image(ysz,xsz,CV_8U ,waterfallimage); // waterfall image converted into Mat
    Mat image_denoise(ysz,xsz,CV_8U);
    Mat image_denoise_threshold(ysz,xsz,CV_8U);
    vector<vector<Point> > contours;
    fastNlMeansDenoising(image, image_denoise, thresh, 7, 21);
    threshold( image_denoise, image_denoise_threshold,0,255,THRESH_BINARY | THRESH_OTSU );
    findContours(image_denoise_threshold,contours,CV_RETR_EXTERNAL ,CV_CHAIN_APPROX_SIMPLE);
//    imwrite("waterfallimage.png",image);
//    imwrite("image_denoise.png",image_denoise);
//    imwrite("image_denoise_threshold.png",image_denoise_threshold);

    vector<Rect> boundRect( contours.size() );
    vector<vector<Point> > contours_poly( contours.size() );

    for(unsigned  int i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
    }

    QVector <ftmarker *>qvec;
    //convert these pixel based rectangles to time / frequency based markers
    for(unsigned  int i = 0; i < boundRect.size(); i++ )
    {

        Rect rct = boundRect[i];
        if(ignoreedges)
        {
            // get rid of rectangles that start at the x/y origin, because they are probably clipped
            if(rct.x == 0)continue;
            if(rct.y == 0)continue;
            // get rid of rects that end on the edge
            if(rct.br().x >= xsz-1) continue;
            if(rct.br().y >= ysz-1) continue;
        }
        ftmarker *mrk = new ftmarker();

        //remove small spot features
        if(rct.width < MIN_FEATURE_SIZE_DEFAULT_X)continue;
        if(rct.height < MIN_FEATURE_SIZE_DEFAULT_Y)continue;
        if(rct.area() < MIN_FEATURE_AREA_SIZE_DEFAULT_Y) continue;

        qvec.append(mrk);


        mrk->setFreqLowHz(helper->GetFreqHz(rct.x));
        mrk->setFreqHighHz(helper->GetFreqHz(rct.x + rct.width));

        if(S_per_Line != -1)
        {
            mrk->setStartTime_S(S_per_Line * rct.y);
            mrk->setEndTime_S(S_per_Line * (rct.y + rct.height));

        }else{
            mrk->setStartTime_S(helper->GetTime(rct.y));
            mrk->setEndTime_S(helper->GetTime(rct.y + rct.height));
        }
        //check to see if this is unbounded in the + or - time axis

    }
    */
    QVector <ftmarker *>qvec;
    delete []waterfallimage;
    return qvec;
}


QVector<ftmarker *> feature_detector::DetectFeatures(FFT_Hist *helper, bool autorange , float rlow , float rhigh , FD_Source src, bool ignoreedges  )
{
Q_UNUSED(ignoreedges)
    helper->Lock();
    int xsz = helper->GetBinSize();
    int ysz = helper->MaxRows();
    uint8_t *waterfallimage = new uint8_t[xsz*ysz];

    float minV,maxV; // get min and max of the waterfall image
    float *fp;
    if(autorange == true)
    {

        fp = helper->GetCacheRow(0); // using the cache data
        if(src == eAvg)
        {
            fp = helper->GetAvgRow(0); // using the average data
        }

        for(int c = 0; c< xsz*ysz; c++)
        {
            if(c == 0)
            {
                minV = *fp;
                maxV = *fp;
            }
            if(*fp < minV) minV = *fp;
            if(*fp > maxV) maxV = *fp;
            fp++; // next pointer position
        }
    }
    else
    {
        minV = rlow;
        maxV = rhigh;
    }

    //tweak the levels
    //calculate range
    float range =  (maxV - minV);
   // range /= 2.0 ;//range / 2;
   // minV += (range * .4); // add to the bottom

    float scale = 255.0f / range;//(maxV - minV) ; // create a scalar value
   // printf("Min %f : Max %f : scaler %f\r\n",minV,maxV,scale);

    uint8_t *ip = waterfallimage; // pointer to the image data
    fp = helper->GetCacheRow(0);//GetAvgRow(0); // reset pointer to beginning
    if(src == eAvg)
    {
        fp = helper->GetAvgRow(0); // using the average data
    }
    uint8_t tvi;
    int temp_1,temp_h;
    float fv;
    for(int c = 0; c < xsz*ysz; c++)
    {
        fv = *fp;
        //if(fv < (minV + (range / 2)))
        if(fv < minV)
        {
            fv = 0;
        }else
        {
            fv -= minV;
        }
        tvi = (fv * scale);
        *ip = tvi;
        fp++; // next pointer position
        ip++;

        if(c == 0)
        {
            temp_1 = tvi;
            temp_h = tvi;
        }
        if(tvi < temp_1) temp_1 = tvi;
        if(tvi > temp_h) temp_h = tvi;

    }
    /*
    Mat image(ysz,xsz,CV_8U ,waterfallimage);
    Mat imageout(ysz,xsz,CV_8U ,waterfallimage);
  //  imwrite("input.png",image);
    helper->Unlock();
    char fn[127];

    Mat blur_gauss; // blurred image
   // Mat blur_gauss2; // blurred image
    Mat th; // thresholded image
  //  Mat eq1;
  //  Mat laplace,sobelX,sobelY;


    vector<vector<Point> > contours;

    GaussianBlur(image, blur_gauss, Size(5, 5), 0);
  //  imwrite("gaussian.png",blur_gauss);

  //  GaussianBlur(image, blur_gauss2, Size(7, 7), 0);
   // imwrite("gaussian7x7.png",blur_gauss2);

    // equalize the image after blurring
   // equalizeHist(blur_gauss,eq1);
   // imwrite("blur_eq_gauss.png",eq1);
    int sigma = 3;



    threshold( blur_gauss, th,0,255,THRESH_BINARY | THRESH_OTSU );

    Mat th_n;

    //findContours(sobelX,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
    findContours(th,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
    //findContours(blur_gauss,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);

    vector<Rect> boundRect( contours.size() );
    vector<vector<Point> > contours_poly( contours.size() );

    for(unsigned  int i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        //minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
        //don't neewd to draw the rectangle
       // rectangle( imageout, boundRect[i].tl(), boundRect[i].br(), Scalar(255,255,255), 2, 8, 0 );
    }
   // imwrite("image_out.png",imageout);

    QVector <ftmarker *>qvec;
    //convert these pixel based rectangles to time / frequency based markers
    for(unsigned  int i = 0; i < boundRect.size(); i++ )
    {

        bool cntflg = false;
        Rect rct = boundRect[i];
        for(unsigned  int j = 0; j < boundRect.size(); j++ )
        {
            Rect r2 = boundRect[j];
            if(rct != r2)
            {
                if(RectInRect(&r2,&rct))
                {
                    cntflg = true;
                    break;
                }
            }
        }
        if(cntflg)continue;

        if(ignoreedges)
        {
            // get rid of rectangles that start at the x/y origin, because they are probably clipped
            if(rct.x == 0)continue;
            if(rct.y == 0)continue;
            // get rid of rects that end on the edge
            if(rct.br().x >= xsz-1) continue;
            if(rct.br().y >= ysz-1) continue;
        }
        ftmarker *mrk = new ftmarker();

        //remove small spot features
        if(rct.width < MIN_FEATURE_SIZE_DEFAULT_X)continue;
        if(rct.height < MIN_FEATURE_SIZE_DEFAULT_Y)continue;
        if(rct.area() < MIN_FEATURE_AREA_SIZE_DEFAULT_Y) continue;

        qvec.append(mrk);

        mrk->setFreqLowHz(helper->GetFreqHz(rct.x));
        mrk->setFreqHighHz(helper->GetFreqHz(rct.x + rct.width));

        mrk->setStartTime_S(helper->GetTime(rct.y));
        mrk->setEndTime_S(helper->GetTime(rct.y + rct.height));
        //check to see if this is unbounded in the + or - time axis

    }
    */
    QVector <ftmarker *>qvec;
    delete []waterfallimage;
    return qvec;
}
