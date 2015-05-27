/*
 * abs.c
 *
 * Code generation for function 'abs'
 *
 * C source code generated on: Thu May 28 00:19:16 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "FFT_CO2.h"
#include "abs.h"

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

void b_abs(const creal_T x[256], real_T y[256])
{
  int32_T k;
  for (k = 0; k < 256; k++) {
    y[k] = rt_hypotd_snf(x[k].re, x[k].im);
  }
}

/* End of code generation (abs.c) */
