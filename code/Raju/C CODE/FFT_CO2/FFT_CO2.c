/*
 * FFT_CO2.c
 *
 * Code generation for function 'FFT_CO2'
 *
 * C source code generated on: Thu May 28 00:19:16 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "FFT_CO2.h"
#include "abs.h"
#include "fft.h"

/* Function Definitions */
real_T FFT_CO2(const real_T x[250])
{
  real_T value_active;
  creal_T b[256];
  creal_T dcv0[256];
  int32_T ixstart;
  real_T Xa[256];
  int32_T ix;
  boolean_T exitg1;
  fft(x, b);
  for (ixstart = 0; ixstart < 256; ixstart++) {
    dcv0[ixstart].re = 0.004 * b[ixstart].re;
    dcv0[ixstart].im = 0.004 * b[ixstart].im;
  }

  b_abs(dcv0, Xa);
  ixstart = 1;
  value_active = Xa[0];
  if (rtIsNaN(Xa[0])) {
    ix = 2;
    exitg1 = FALSE;
    while ((exitg1 == FALSE) && (ix < 257)) {
      ixstart = ix;
      if (!rtIsNaN(Xa[ix - 1])) {
        value_active = Xa[ix - 1];
        exitg1 = TRUE;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 256) {
    while (ixstart + 1 < 257) {
      if (Xa[ixstart] > value_active) {
        value_active = Xa[ixstart];
      }

      ixstart++;
    }
  }

  return value_active;
}

/* End of code generation (FFT_CO2.c) */
