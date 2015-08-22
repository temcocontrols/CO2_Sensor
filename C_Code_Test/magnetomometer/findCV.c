/*
 * findCV.c
 *
 * Code generation for function 'findCV'
 *
 * C source code generated on: Tue Apr 07 14:00:19 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "findCV.h"

/* Function Definitions */
real_T findCV(const real_T resultant[238])
{
  real_T y;
  int32_T ix;
  real_T xbar;
  int32_T k;
  real_T r;
  real_T b_y;
  y = resultant[0];

  /*  varVal = std2(resultant); */
  ix = 0;
  xbar = resultant[0];
  for (k = 0; k < 237; k++) {
    y += resultant[k + 1];
    ix++;
    xbar += resultant[ix];
  }

  xbar /= 238.0;
  ix = 0;
  r = resultant[0] - xbar;
  b_y = r * r;
  for (k = 0; k < 237; k++) {
    ix++;
    r = resultant[ix] - xbar;
    b_y += r * r;
  }

  b_y /= 237.0;
  return sqrt(b_y) / (y / 238.0);
}

/* End of code generation (findCV.c) */
