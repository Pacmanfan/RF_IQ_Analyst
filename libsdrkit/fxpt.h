#ifndef FXPT_H
#define FXPT_H


#include <stdint.h>
#include <cmath>


  /*!
   * \brief fixed point sine and cosine and friends.
   * \ingroup misc
   *
   *   fixed pt	radians
   *  ---------	--------
   *   -2**31       -pi
   *        0         0
   *  2**31-1        pi - epsilon
   */
  class fxpt
  {
    static const int WORDBITS = 32;
    static const int NBITS = 10;
    static const float s_sine_table[1 << NBITS][2];
    static const float PI;
    static const float TAU;
    static const float TWO_TO_THE_31;

  public:
    static int32_t float_to_fixed(float x)
    {
      // Fold x into -PI to PI.
      int d = (int)std::floor(x/TAU+0.5);
      x -= d*TAU;
      // And convert to an integer.
      return (int32_t) ((float) x * TWO_TO_THE_31 / PI);
    }

    static float fixed_to_float (int32_t x)
    {
      return x * (PI / TWO_TO_THE_31);
    }

    /*!
     * \brief Given a fixed point angle x, return float sine (x)
     */
    static float fxpt_sin(int32_t x)
    {
      uint32_t ux = x;
      int index = ux >> (WORDBITS - NBITS);
      return s_sine_table[index][0] * (ux >> 1) + s_sine_table[index][1];
    }

    /*
     * \brief Given a fixed point angle x, return float cosine (x)
     */
    static float fxpt_cos (int32_t x)
    {
      uint32_t ux = x + 0x40000000;
      int index = ux >> (WORDBITS - NBITS);
      return s_sine_table[index][0] * (ux >> 1) + s_sine_table[index][1];
    }

    /*
     * \brief Given a fixedpoint angle x, return float cos(x) and sin (x)
     */
    static void fxpt_sincos(int32_t x, float *s, float *c)
    {
      uint32_t ux = x;
      int sin_index = ux >> (WORDBITS - NBITS);
      *s = s_sine_table[sin_index][0] * (ux >> 1) + s_sine_table[sin_index][1];

      ux = x + 0x40000000;
      int cos_index = ux >> (WORDBITS - NBITS);
      *c = s_sine_table[cos_index][0] * (ux >> 1) + s_sine_table[cos_index][1];

      return;
    }

  };

#endif // FXPT_H
