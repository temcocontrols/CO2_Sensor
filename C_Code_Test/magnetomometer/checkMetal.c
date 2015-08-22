/*
 * checkMetal.c
 *
 * Code generation for function 'checkMetal'
 *
 * C source code generated on: Thu Apr 09 00:13:35 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkMetal.h"

/* Function Definitions */
real_T checkMetal(real_T cvVal, real_T ref_cv, real_T variation_cv)
{
  real_T metal_stat;
  if (cvVal < ref_cv + variation_cv) {
    metal_stat = 1.0;

    /* BOX present */
    /*      disp('CLEAN BOX-- NO METAL PRESENT'); */
  } else {
    metal_stat = 0.0;

    /* Noise present */
    /*      disp('CONTAMINATED BOX--METAL DETECTED'); */
  }

  return metal_stat;
}

/* End of code generation (checkMetal.c) */
