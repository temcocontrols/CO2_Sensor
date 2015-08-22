/*
 * filterRollerEffect.c
 *
 * Code generation for function 'filterRollerEffect'
 *
 * C source code generated on: Thu Apr 09 19:31:28 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "filterRollerEffect.h"
#include "rand.h"

/* Function Definitions */
void filterRollerEffect(const real_T resultant[238], real_T
  roller_resultantAdjust[238], const char_T roller_type[11], real_T
  roller_removed[238])
{
  boolean_T b_bool;
  int32_T i;
  int32_T exitg3;
  static const char_T cv0[11] = { 'c', 'o', 'n', 'd', 'i', 't', 'i', 'o', 'n',
    'a', 'l' };

  int32_T exitg2;
  int32_T exitg1;
  static const char_T cv1[6] = { 'a', 'l', 'w', 'a', 'y', 's' };

  real_T b_roller_resultantAdjust;
  memset(&roller_removed[0], 0, 238U * sizeof(real_T));
  b_bool = FALSE;
  i = 0;
  do {
    exitg3 = 0;
    if (i < 11) {
      if (roller_type[i] != cv0[i]) {
        exitg3 = 1;
      } else {
        i++;
      }
    } else {
      b_bool = TRUE;
      exitg3 = 1;
    }
  } while (exitg3 == 0);

  if (b_bool == 1) {
    for (i = 0; i < 238; i++) {
      roller_removed[i] = resultant[i] - roller_resultantAdjust[i];
    }
  }

  b_bool = FALSE;
  i = 0;
  do {
    exitg2 = 0;
    if (i < 2) {
      if (1 + 10 * i != 1 + 5 * i) {
        exitg2 = 1;
      } else {
        i++;
      }
    } else {
      i = 0;
      exitg2 = 2;
    }
  } while (exitg2 == 0);

  if (exitg2 == 1) {
  } else {
    do {
      exitg1 = 0;
      if (i < 11) {
        if (roller_type[i] != cv1[i]) {
          exitg1 = 1;
        } else {
          i++;
        }
      } else {
        b_bool = TRUE;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (b_bool == 1) {
    /* Labbat Roller */
    b_rand(roller_resultantAdjust);
    for (i = 0; i < 238; i++) {
      b_roller_resultantAdjust = 80.0 + 25.0 * roller_resultantAdjust[i];
      roller_removed[i] = resultant[i] - b_roller_resultantAdjust;
      roller_resultantAdjust[i] = b_roller_resultantAdjust;
    }
  }
}

/* End of code generation (filterRollerEffect.c) */
