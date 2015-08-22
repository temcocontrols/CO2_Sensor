/*
 * dataRead_emxutil.h
 *
 * Code generation for function 'dataRead_emxutil'
 *
 * C source code generated on: Sun Apr 05 23:50:22 2015
 *
 */

#ifndef __DATAREAD_EMXUTIL_H__
#define __DATAREAD_EMXUTIL_H__
/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "dataRead_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int32_T oldNumel, int32_T elementSize);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int32_T numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int32_T numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);
#endif
/* End of code generation (dataRead_emxutil.h) */
