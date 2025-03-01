#include "dsp_utils.h"

DSP_Utils::DSP_Utils()
{

}

/*
Unwrap phase attempts to smooth out discontinuities in phase changes in a float array
when we calculate phase using the atan2 function, the resultant values are in the range of -pi to +pi

this function will detect if the change in value from one array value to the next exceeds pi and adjusts up or down accordingly
*/
void DSP_Utils::unwrap_phase(float *inbuffer, float *outbuffer, int numsamples, float d_max, float d_min)
{
    float range = d_max - d_min;
    float threshold = range/2.0f;
    int level = 0;
    float difference;
    outbuffer[0] = inbuffer[0];
    for (int i=1; i<numsamples; ++i)
    {
        difference = inbuffer[i-1]-inbuffer[i];
        if (fabs(difference) > threshold)
        {
            if (difference > 0)
            {
                level++;
            } else {
                level--;
            }
        }
        outbuffer[i] = inbuffer[i] + range*level;
    }

}

/*
Calculates the difference in phase between the arrays : outbuffer = Phase(inbuffer1) - Phase(inbuffer2)
*/
/*
void DSP_Utils::PhaseDiff(complex<float> *inbuffer1, complex<float> *inbuffer2, float *outbuffer, int numsamples)
{
    float temp1[numsamples];
    float temp2[numsamples];
    float temp1a[numsamples];
    float temp2a[numsamples];
    Complex_To_Arg(inbuffer1,temp1,numsamples);
    Complex_To_Arg(inbuffer2,temp2,numsamples);

    unwrap_phase(temp1,temp1a,numsamples,3.14159265358979323846,-3.14159265358979323846);
    unwrap_phase(temp2,temp2a,numsamples,3.14159265358979323846,-3.14159265358979323846);

    for (long c = 0; c < numsamples; c++)
    {
        outbuffer[c] = temp1a[c] - temp2a[c];
    }
}
*/
/*
Calculates the difference in Magnitude between the arrays : outbuffer = Mag(inbuffer1) - Mag(inbuffer2)
*/
/*
void DSP_Utils::MagDiff(complex<float> *inbuffer1, complex<float> *inbuffer2, float *outbuffer, int numsamples)
{
    float temp1[numsamples];
    float temp2[numsamples];
    Magnitude(inbuffer1,temp1,numsamples);
    Magnitude(inbuffer2,temp2,numsamples);
    for (long c = 0; c < numsamples; c++)
    {
        outbuffer[c] = temp1[c] - temp2[c];
    }
}
*/
/*
Take a complex stream and output it's phase calculated from the arctangent
*/
void DSP_Utils::Complex_To_Arg(complex<float> *inbuffer, float *outbuffer, int numsamples)
{
    float *idata = (float *)inbuffer; // cast to array of interleaved floats
    for (long c = 0; c < numsamples; c++)
    {
        float Id,Qd;
        Id = idata[c * 2];
        Qd = idata[(c * 2) + 1];
        outbuffer[c] = atan2(Id,Qd);
    }
}

/*
Calculate the magnitude
*/
void DSP_Utils::Magnitude(complex<float> *inbuffer, float *outbuffer, int numsamples)
{
    float *idata = (float *)inbuffer; // cast to array of interleaved floats
    for (long c = 0; c < numsamples; c++)
    {
        float Id,Qd;
        Id = idata[c * 2];
        Qd = idata[(c * 2) + 1];
        outbuffer[c] = sqrt((Id*Id) + (Qd*Qd));
    }
}

/*
Calculates the difference between the arrays : outbuffer = (inbuffer1) - (inbuffer2)
*/

void DSP_Utils::Subtract(float *inbuffer1, float *inbuffer2, float *outbuffer, int numsamples)
{
    for (long c = 0; c < numsamples; c++)
    {
        outbuffer[c] = inbuffer1[c] - inbuffer2[c];
    }
}

void DSP_Utils::MultConst(float *in_out_buffer, float value, int numsamples)
{
    for (long c = 0; c < numsamples; c++)
    {
        in_out_buffer[c] *= value;
    }
}
