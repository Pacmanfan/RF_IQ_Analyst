
#ifndef FIXED_H_
#define FIXED_H_
#include <stdint.h>
#include <inttypes.h>

unsigned long long DoubleTo64Fixed(double val);
double Fixed64ToDouble(unsigned long long val);

//double Fixed_9_7_To_Double(unsigned short val);
//unsigned short DoubleTo_9_7_Fixed(double val);

double Fixed16ToDouble(unsigned short val, int fracbits);
unsigned short DoubleToFixed16(double val, int fracbits);


unsigned int DoubleToFixed32(double val, int fracbits);
double Fixed32ToDouble(unsigned int val , int fracbits);

inline uint32_t QVRTGainStageNumber (float stage_1, float stage_2)
// ---------------------------------------------------------------------------
//  Returns a VITA-49.0 VRT 32-Bit number for two gain stages given
//  floating point numbers in dB.
//  The upper 16-bits are gain stage 2, lower are stage 1.
//  The number is specified in Q8.7 2's comp format.
// ---------------------------------------------------------------------------
{
    const double scale = 128.0;     // 2^7
    if (stage_1 > 255.0f) stage_1 = 255.0f;
    if (stage_1 < -256.0f) stage_1 = -256.0f;
    if (stage_2 > 255.0f) stage_2 = 255.0f;
    if (stage_2 < -256.0f) stage_2 = -256.0f;

    uint32_t low16  = 0x0000ffff & (uint32_t) (int16_t) (stage_1 * scale);
    uint32_t high16 = ((uint32_t) (int16_t) (stage_2 * scale)) << 16;
    return high16 | low16;
}

inline uint32_t QVRTRefLevelNumber (float value)
// ---------------------------------------------------------------------------
//  Returns a VITA-49.0 VRT 32-Bit number for Reference Level given a
//  floating point number in dB. The upper 16-bits are reseved and set to 0.
//  The number is specified in Q8.7 2's comp format.
// ---------------------------------------------------------------------------
{
    const double scale = 128.0;     // 2^7
    if (value > 255.0f) value = 255.0f;
    if (value < -256.0f) value = -256.0f;
    return 0x0000ffff & (uint32_t) (int16_t) (value * scale);
}

inline double QVRTFractionalNumber (int64_t value)
// ---------------------------------------------------------------------------
//  Returns a double precision floating point number given a
//  VITA-49.0 VRT 64-Bit Fractional number.
//  The number is specified in Q44.20 2's comp format.
// ---------------------------------------------------------------------------
{
    const double scale = 1.0 / 1048576.0;     // 2^20
    return scale * (double) value;
}


inline double QVRTFractionalNumber (uint32_t hi, uint32_t lo)
// ---------------------------------------------------------------------------
//  Returns a double precision floating point number given a
//  VITA-49.0 VRT 64-Bit Fractional number stored in hi and lo.
//  The number is specified in Q44.20 2's comp format.
// ---------------------------------------------------------------------------
{
    return QVRTFractionalNumber ((int64_t) ((((uint64_t) hi) << 32) | (uint64_t) lo));
}


inline double QVRTAngleNumber (int32_t value)
// ---------------------------------------------------------------------------
//  Returns a double precision floating point number given a
//  VITA-49.0 VRT 32-Bit gepolocation angle number.
//  The number is specified in Q9.22 2's comp format.
// ---------------------------------------------------------------------------
{
    const double scale = 1.0 / 4194304.0;     // 2^22
    return scale * (double) value;
}


inline double QVRTAltitudeNumber (int32_t value)
// ---------------------------------------------------------------------------
//  Returns a double precision floating point number given a
//  VITA-49.0 VRT 32-Bit altitude number.
//  The number is specified in Q26.5 2's comp format.
// ---------------------------------------------------------------------------
{
    const double scale = 1.0 / 32.0;     // 2^5
    return scale * (double) value;
}


inline double QVRTSpeedNumber (int32_t value)
// ---------------------------------------------------------------------------
//  Returns a double precision floating point number given a
//  VITA-49.0 VRT 32-Bit speed number.
//  The number is specified in Q15.16 2's comp format.
// ---------------------------------------------------------------------------
{
    const double scale = 1.0 / 65536.0;     // 2^16
    return scale * (double) value;
}



#endif
