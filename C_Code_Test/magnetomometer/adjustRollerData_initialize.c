/*
 * adjustRollerData_initialize.c
 *
 * Code generation for function 'adjustRollerData_initialize'
 *
 * C source code generated on: Mon May 04 22:20:38 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "adjustRollerData.h"
#include "adjustRollerData_initialize.h"
#include "adjustRollerData_data.h"

/* Function Definitions */
void adjustRollerData_initialize(void)
{
  uint32_T r;
  int32_T mti;
  rt_InitInfAndNaN(8U);
  memset(&state[0], 0, 625U * sizeof(uint32_T));
  r = 5489U;
  state[0] = 5489U;
  for (mti = 0; mti < 623; mti++) {
    r = (r ^ r >> 30U) * 1812433253U + (1 + mti);
    state[1 + mti] = r;
  }

  state[624] = 624U;
}

/* End of code generation (adjustRollerData_initialize.c) */
