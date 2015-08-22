/*
 * checkLargeNoiseMetal.c
 *
 * Code generation for function 'checkLargeNoiseMetal'
 *
 * C source code generated on: Thu Apr 09 00:16:37 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkLargeNoiseMetal.h"

/* Function Definitions */
real_T checkLargeNoiseMetal(real_T cvVal, real_T max_cv)
{
  real_T largenoisemetal_stat;
  if (cvVal > max_cv) {
    largenoisemetal_stat = 1.0;
  } else {
    largenoisemetal_stat = 0.0;
  }

  return largenoisemetal_stat;
}

/* End of code generation (checkLargeNoiseMetal.c) */
