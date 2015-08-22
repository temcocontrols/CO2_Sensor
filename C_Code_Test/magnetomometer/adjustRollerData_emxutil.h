/*
 * adjustRollerData_emxutil.h
 *
 * Code generation for function 'adjustRollerData_emxutil'
 *
 * C source code generated on: Mon May 04 22:20:39 2015
 *
 */

#ifndef __ADJUSTROLLERDATA_EMXUTIL_H__
#define __ADJUSTROLLERDATA_EMXUTIL_H__
/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "adjustRollerData_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int32_T oldNumel, int32_T elementSize);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int32_T numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);
#endif
/* End of code generation (adjustRollerData_emxutil.h) */
