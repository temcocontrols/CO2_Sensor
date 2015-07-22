/*
 * FFT_CO2.c
 *
 * Code generation for function 'FFT_CO2'
 *
 * C source code generated on: Wed Jul 22 12:27:56 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "FFT_CO2.h"

/* Function Declarations */
static real_T rt_hypotd_snf(real_T u0, real_T u1);

/* Function Definitions */
static real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T a;
  real_T b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

real_T FFT_CO2(const real_T sampled_data[64])
{
  real_T snrVal;
  creal_T b_y1[64];
  int32_T ix;
  int32_T ju;
  int32_T iy;
  int32_T i;
  boolean_T tst;
  real_T temp_re;
  real_T temp_im;
  int32_T iDelta;
  int32_T iDelta2;
  int32_T k;
  int32_T iheight;
  static const real_T dv0[33] = { 0.0, -0.0980171403295606, -0.19509032201612825,
    -0.29028467725446233, -0.38268343236508978, -0.47139673682599764,
    -0.55557023301960218, -0.63439328416364549, -0.70710678118654757,
    -0.773010453362737, -0.83146961230254524, -0.881921264348355,
    -0.92387953251128674, -0.95694033573220882, -0.98078528040323043,
    -0.99518472667219693, -1.0, -0.99518472667219693, -0.98078528040323043,
    -0.95694033573220882, -0.92387953251128674, -0.881921264348355,
    -0.83146961230254524, -0.773010453362737, -0.70710678118654757,
    -0.63439328416364549, -0.55557023301960218, -0.47139673682599764,
    -0.38268343236508978, -0.29028467725446233, -0.19509032201612825,
    -0.0980171403295606, -0.0 };

  static const real_T dv1[33] = { 1.0, 0.99518472667219693, 0.98078528040323043,
    0.95694033573220882, 0.92387953251128674, 0.881921264348355,
    0.83146961230254524, 0.773010453362737, 0.70710678118654757,
    0.63439328416364549, 0.55557023301960218, 0.47139673682599764,
    0.38268343236508978, 0.29028467725446233, 0.19509032201612825,
    0.0980171403295606, 0.0, -0.0980171403295606, -0.19509032201612825,
    -0.29028467725446233, -0.38268343236508978, -0.47139673682599764,
    -0.55557023301960218, -0.63439328416364549, -0.70710678118654757,
    -0.773010453362737, -0.83146961230254524, -0.881921264348355,
    -0.92387953251128674, -0.95694033573220882, -0.98078528040323043,
    -0.99518472667219693, -1.0 };

  real_T absFFT_sampled_data[64];
  creal_T FFT_sampled_data[64];
  boolean_T exitg1;
  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 63; i++) {
    b_y1[iy].re = sampled_data[ix];
    b_y1[iy].im = 0.0;
    iy = 64;
    tst = TRUE;
    while (tst) {
      if (iy >= 0) {
        iy = (int32_T)((uint32_T)iy >> 1);
      } else {
        iy = ~(int32_T)((uint32_T)~iy >> 1);
      }

      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  b_y1[iy].re = sampled_data[ix];
  b_y1[iy].im = 0.0;
  for (i = 0; i < 64; i += 2) {
    temp_re = b_y1[i + 1].re;
    temp_im = b_y1[i + 1].im;
    b_y1[i + 1].re = b_y1[i].re - b_y1[i + 1].re;
    b_y1[i + 1].im = b_y1[i].im - b_y1[i + 1].im;
    b_y1[i].re += temp_re;
    b_y1[i].im += temp_im;
  }

  iDelta = 2;
  iDelta2 = 4;
  k = 16;
  iheight = 61;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      iy = i + iDelta;
      temp_re = b_y1[iy].re;
      temp_im = b_y1[iy].im;
      b_y1[i + iDelta].re = b_y1[i].re - b_y1[iy].re;
      b_y1[i + iDelta].im = b_y1[i].im - b_y1[iy].im;
      b_y1[i].re += temp_re;
      b_y1[i].im += temp_im;
    }

    iy = 1;
    for (ju = k; ju < 32; ju += k) {
      i = iy;
      ix = iy + iheight;
      while (i < ix) {
        temp_re = dv1[ju] * b_y1[i + iDelta].re - dv0[ju] * b_y1[i + iDelta].im;
        temp_im = dv1[ju] * b_y1[i + iDelta].im + dv0[ju] * b_y1[i + iDelta].re;
        b_y1[i + iDelta].re = b_y1[i].re - temp_re;
        b_y1[i + iDelta].im = b_y1[i].im - temp_im;
        b_y1[i].re += temp_re;
        b_y1[i].im += temp_im;
        i += iDelta2;
      }

      iy++;
    }

    iy = k;
    k = (int32_T)((uint32_T)iy >> 1);
    iDelta = iDelta2;
    iDelta2 <<= 1;
    iheight -= iDelta;
  }

  for (iy = 0; iy < 64; iy++) {
    FFT_sampled_data[iy].re = 0.015625 * b_y1[iy].re;
    FFT_sampled_data[iy].im = 0.015625 * b_y1[iy].im;
    absFFT_sampled_data[iy] = rt_hypotd_snf(FFT_sampled_data[iy].re,
      FFT_sampled_data[iy].im);
  }

  iy = 1;
  temp_re = absFFT_sampled_data[0];
  if (rtIsNaN(absFFT_sampled_data[0])) {
    ix = 2;
    exitg1 = FALSE;
    while ((exitg1 == FALSE) && (ix < 65)) {
      iy = ix;
      if (!rtIsNaN(absFFT_sampled_data[ix - 1])) {
        temp_re = absFFT_sampled_data[ix - 1];
        exitg1 = TRUE;
      } else {
        ix++;
      }
    }
  }

  if (iy < 64) {
    while (iy + 1 < 65) {
      if (absFFT_sampled_data[iy] > temp_re) {
        temp_re = absFFT_sampled_data[iy];
      }

      iy++;
    }
  }

  temp_im = absFFT_sampled_data[0];
  for (k = 0; k < 63; k++) {
    temp_im += absFFT_sampled_data[k + 1];
  }

  snrVal = temp_re / ((temp_im - temp_re) / 63.0);

  /*      snrdB=10*log10(snrVal);  */
  return snrVal;
}

/* End of code generation (FFT_CO2.c) */
