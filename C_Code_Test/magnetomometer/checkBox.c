/*
 * checkBox.c
 *
 * Code generation for function 'checkBox'
 *
 * C source code generated on: Tue Apr 07 12:47:15 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkBox.h"

/* Function Definitions */
real_T checkBox(real_T ref_speed_box, real_T speed_box, real_T variation)
{
  real_T box_stat;

  /*  Here considered maximum opto ON (on our predifined range, min_speed to max_speed,) */
  /*  time is our desired box */
  if ((speed_box > ref_speed_box - variation) && (speed_box < ref_speed_box +
       variation)) {
    box_stat = 1.0;

    /* BOX present */
    /*      disp('BOX PRESENT'); */
  } else if (speed_box == 0.0) {
    box_stat = -1.0;

    /*  Nothing present */
    /*      disp('NO BOX PRESENT'); */
  } else {
    box_stat = 0.0;

    /* Noise present */
    /*      disp('Other Noise PRESENT'); */
  }

  return box_stat;
}

/* End of code generation (checkBox.c) */
