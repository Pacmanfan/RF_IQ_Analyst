#ifdef USE_IPP
#include "resampler_polyphase_ipp_ff.h"



/*
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 1999-2006 Intel Corporation. All Rights Reserved.
//
//     Intel(R) Integrated Performance Primitives Speech Processing Sample for Windows*
//
//  By downloading and installing this sample, you hereby agree that the
//  accompanying Materials are being provided to you under the terms and
//  conditions of the End User License Agreement for the Intel(R) Integrated
//  Performance Primitives product previously accepted by you. Please refer
//  to the file ipplic.htm located in the root directory of your Intel(R) IPP
//  product installation for more information.
//
*/

//---------------------------------------------------------------------
//                  data resampling class
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ipps.h>
//#include <ippsr.h>
//#include "resamp.h"

   /*
Resample::Resample(float rollf, float alpha)
{

   this->rollf=rollf;
   this->alpha=alpha;
   ready=false;
   ffil=NULL;
   finBuf=NULL;
   foutBuf=NULL;

}

Resample::~Resample(void)
{
   ready=false;
   if (finBuf)
       ippsFree(finBuf);
   if (foutBuf)
       ippsFree(foutBuf);
   if (ffil)
       ippsResamplePolyphaseFree_32f(ffil);
}


void Resample::Init(double factor, int length, int nStep, int bufSize)
{
    IppHintAlgorithm hint = ippAlgHintAccurate;
    IppStatus status;
    history=(((length+3)&(~3))>>1)+1;   // for time rounding
    window=(float)(2*(history-1)*IPP_MIN(1.0,factor));
    this->length=(history-1)<<1;
    this->factor=factor;
    this->nStep=nStep;
    this->bufSize=bufSize;

    status=ippsResamplePolyphaseInitAlloc_32f(&ffil,window,nStep,rollf,alpha,hint);
    finBuf=ippsMalloc_32f(bufSize+history+2);
    foutBuf=ippsMalloc_32f((int)((bufSize-history)*factor+2));
    ready=(status==ippStsNoErr)&&(finBuf!=NULL)&&(foutBuf!=NULL);

}

void Resample::Init(double factor, float window, int nStep, int bufSize)
{
    IppHintAlgorithm hint=ippAlgHintAccurate;
    IppStatus status;
    history=(int)(window*0.5*IPP_MAX(1.0,1.0/factor))+1;   // for time rounding
    length=(history-1)<<1;
    this->factor=factor;
    this->window=window;
    this->nStep=nStep;
    this->bufSize=bufSize;

    status=ippsResamplePolyphaseInitAlloc_32f(&ffil,window,nStep,rollf,alpha,hint);
    finBuf=ippsMalloc_32f(bufSize+history+2);
    foutBuf=ippsMalloc_32f((int)((bufSize-history)*factor+2));
    ready = (status==ippStsNoErr) && (finBuf!=NULL) && (foutBuf!=NULL);
}


void Resample::Do(char* inFile, char* outFile) {

   FILE *in,*out;
   int inCount=0,outCount=0;
   int inLen,outLen,lastread;
   float scale=0.98f;
   double time;
   clock_t time_start;
   clock_t time_finish;
   double rt_time;

   in = fopen(inFile,"rb");
   if (!in)
   {
      fprintf(stderr,"Could not open input file \"%s\"\n",inFile);
      exit(1);
   }

   out = fopen(outFile,"wb");
   if (!out)
   {
      fprintf(stderr,"Could not open input file \"%s\"\n",outFile);
      exit(1);
   }

         time=(double)history;
         lastread=history;
         ippsZero_32f(finBuf,history);
         while ((inLen=fread(inBuf+lastread,sizeof(short),bufSize-lastread,in))>0) {
            ippsConvert_16s32f(inBuf+lastread,finBuf+lastread,inLen);
            lastread+=inLen;
            ippsResamplePolyphase_32f(ffil,finBuf,lastread-history-(int)time,foutBuf,factor,scale,&time,&outLen);
            ippsConvert_32f16s_Sfs(foutBuf,outBuf,outLen,ippRndNear,0);
            inCount+=inLen;
            outCount+=outLen;
            fwrite(outBuf,outLen,sizeof(short),out);
            ippsMove_32f(finBuf+(int)time-history,finBuf,lastread+history-(int)time);
            lastread-=(int)time-history;
            time-=(int)time-history;
         }
         ippsZero_32f(finBuf+lastread,history);
         ippsResamplePolyphase_32f(ffil,finBuf,lastread-(int)time,foutBuf,factor,scale,&time,&outLen);
         ippsConvert_32f16s_Sfs(foutBuf,outBuf,outLen,ippRndNear,0);
         outCount+=outLen;
         fwrite(outBuf,outLen,sizeof(short),out);

}


void resampleIPP(
    int      inRate,    // input frequency
    int      outRate,   // output frequency
    FILE    *infd,      // input pcm file
    FILE    *outfd)     // output pcm file
 {
    short *inBuf,*outBuf;
    int bufsize=4096;
    int history=128;
    double time=history;
    int lastread=history;
    int inCount=0,outCount=0,inLen,outLen;
    int size,len,height;

    // state information
    IppsResamplingPolyphase_32f *state;

    //Determines the size required for the ResamplePolyphase
    ippsResamplePolyphaseGetSize_32f(inRate,outRate,2*(history-1),&size,&len, &height,ippAlgHintAccurate);

    //allocate memory for state
    state=(IppsResamlingPolyphase_32f*)ippsMalloc_8u(size);

    ippsResamplePolyphaseInit_32f(inRate,outRate,2*(history-1),0.95f,9.0f,state,           ippAlgHintAccurate);

    // allocate memory for input buffer
    inBuf=ippsMalloc_32f(bufsize+history+2);
    //allocate memory for output buffer
    outBuf=ippsMalloc_32f((int)((bufsize-history)*outRate/(float)inRate+2));
    //zero the memory in the input buffer
    ippsZero_32f(inBuf,history);

    while ((inLen=fread(inBuf+lastread,sizeof(short),bufsize-lastread,infd))>0)
    {
       inCount+=inLen;
       lastread+=inLen;
       ippsResamplePolyphase_32f(inBuf,lastread-history-(int)time,
                             outBuf,0.98f,&time,&outLen,state);
       fwrite(outBuf,outLen,sizeof(short),outfd);
       outCount+=outLen;
       ippsMove_32f(inBuf+(int)time-history,inBuf,lastread+history-(int)time);
       lastread-=(int)time-history;
       time-=(int)time-history;
    }
    ippsZero_32f(inBuf+lastread,history);

    ippsResamplePolyphase_32f(inBuf,lastread-(int)time, outBuf,0.98f,&time,&outLen,state);
    fwrite(outBuf,outLen,sizeof(short),outfd);

    outCount+=outLen;
    printf("%d inputs resampled to %d outputs\n",inCount,outCount);
    ippsFree(outBuf);
    ippsFree(inBuf);
    ippsFree (state);
 }
*/
#endif
