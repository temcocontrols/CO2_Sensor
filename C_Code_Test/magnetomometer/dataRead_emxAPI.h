/*
 * dataRead_emxAPI.h
 *
 * Code generation for function 'dataRead_emxAPI'
 *
 * C source code generated on: Sun Apr 05 23:50:22 2015
 *
 */

#ifndef __DATAREAD_EMXAPI_H__
#define __DATAREAD_EMXAPI_H__
/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "dataRead_types.h"

/* Function Declarations */
extern emxArray_real_T *emxCreateND_real_T(int32_T numDimensions, int32_T *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(real_T *data, int32_T numDimensions, int32_T *size);
extern emxArray_real_T *emxCreateWrapper_real_T(real_T *data, int32_T rows, int32_T cols);
extern emxArray_real_T *emxCreate_real_T(int32_T rows, int32_T cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
#endif
/* End of code generation (dataRead_emxAPI.h) */
