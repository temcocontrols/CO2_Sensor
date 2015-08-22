/*
 * filterRollerEffect_initialize.c
 *
 * Code generation for function 'filterRollerEffect_initialize'
 *
 * C source code generated on: Thu Apr 09 19:31:28 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "filterRollerEffect.h"
#include "filterRollerEffect_initialize.h"
#include "filterRollerEffect_data.h"

/* Function Definitions */
void filterRollerEffect_initialize(void)
{
  int32_T i0;
  rt_InitInfAndNaN(8U);
  state_not_empty = FALSE;
  state = 1144108930U;
  for (i0 = 0; i0 < 2; i0++) {
    b_state[i0] = 362436069U + 158852560U * i0;
  }

  method = 7U;
}

/* End of code generation (filterRollerEffect_initialize.c) */
