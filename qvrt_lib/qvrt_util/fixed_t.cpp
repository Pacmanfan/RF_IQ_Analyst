#include <fixed_t.h>
#include "stdio.h"
/*some utils for converting 64 bit 44:20 format to double and back*/

unsigned long long DoubleTo64Fixed(double val)
{
    unsigned long long tmp = val; // get the integer portion;
    unsigned long long retval;
    retval  = (tmp << 20) & 0xFFFFFFFFFFF00000;
    double tmpd = val - tmp; // just the fractional portion
    tmpd *= 1048575; // 2^20
    tmp = tmpd; // convert from double to unsigned long long
    retval |= tmp;
    return retval;
}

double Fixed64ToDouble(unsigned long long val)
{
    unsigned long long tmp = (val >> 20) & 0x00000FFFFFFFFFFF; // shift and mask upper 44 bits
    double retval = tmp;
    tmp = val & 0x00000000000FFFFF; // lower 20 bits is the fractional portion
    double tmpd = tmp;
    tmpd /= 1048575; // 0x000fffff
    retval += tmpd;
    return retval;
}


unsigned short DoubleToFixed16(double value, int fracbits)
{
    unsigned short retval = 0;
    unsigned short ivalue = value;// remove the decimal portion by casting
    unsigned short mask = (1 << fracbits ) - 1;
    retval |= ivalue << fracbits; // shift it into position;
    double tmpfrac = value - ivalue; // get just the decimal
    tmpfrac *= mask; // scale it
    unsigned short fvalue = tmpfrac; // should be an integer at this point
    retval |= fvalue; // or the bits in place
    return retval;
}

double Fixed16ToDouble(unsigned short value, int fracbits)
{
    double retval = 0.0;
    unsigned short mask = (1 << fracbits ) - 1;
    retval = (value >> fracbits);
    retval += ((double)(value & mask)) / ((double) mask);
    return retval;
}



unsigned int DoubleToFixed32(double value, int fracbits)
{
    unsigned int retval = 0;
    unsigned int ivalue = value;// remove the decimal portion by casting
 //   printf("DoubleToFixed32::ivalue = %u \r\n",ivalue);
    unsigned int mask = (1 << fracbits ) - 1;
//    printf("DoubleToFixed32::mask = %u \r\n",mask);
    retval |= ivalue << fracbits; // shift it into position;
//    printf("DoubleToFixed32::retval int portion = %u \r\n",retval);
    double tmpfrac = value - ivalue; // get just the decimal
//    printf("DoubleToFixed32::tmpfrac decimal portion = %f \r\n",tmpfrac);

    tmpfrac *= mask; // scale it
//    printf("DoubleToFixed32::tmpfrac scaled = %f \r\n",tmpfrac);
    unsigned int fvalue = tmpfrac; // should be an integer at this point
//    printf("DoubleToFixed32::fvalue  = %u \r\n",fvalue);
    retval |= fvalue; // or the bits in place
    if(tmpfrac == 0)
        retval -= 1;
    return retval;
}

double Fixed32ToDouble(unsigned int value , int fracbits)
{
    double retval = 0.0;
    unsigned int mask = (1 << fracbits ) - 1;
//    printf("Fixed32ToDouble:: Mask = %u\r\n",mask);
    retval = (value >> fracbits);
 //   printf("Fixed32ToDouble:: Retval1 int portion = %f\r\n",retval);
    retval += ((double)(value & mask)) / ((double) mask);
 //   printf("\r\n");
    return retval;
}
