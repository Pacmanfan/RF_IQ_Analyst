#ifndef DSP_UTILS_H
#define DSP_UTILS_H
#include <math.h>
#include <complex>
using namespace std;

class DSP_Utils
{
public:
    DSP_Utils();
    static void unwrap_phase(float *inbuffer, float *outbuffer, int numsamples,float d_max, float d_min);
   // static void PhaseDiff(complex<float> *inbuffer1,complex<float> *inbuffer2, float *outbuffer, int numsamples);
  //  static void MagDiff(complex<float> *inbuffer1,complex<float> *inbuffer2, float *outbuffer, int numsamples);
    static void Complex_To_Arg(complex<float> *inbuffer, float *outbuffer, int numsamples);
    static void Magnitude(complex<float> *inbuffer,float *outbuffer, int numsamples);
    static void Subtract(float *inbuffer1,float *inbuffer2, float *outbuffer, int numsamples);
    static void MultConst(float *in_out_buffer, float value, int numsamples);
};

#endif // DSP_UTILS_H
