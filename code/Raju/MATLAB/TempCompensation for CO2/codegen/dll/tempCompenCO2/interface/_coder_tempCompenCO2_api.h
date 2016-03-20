/* 
 * File: _coder_tempCompenCO2_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 21-Mar-2016 01:24:47 
 */

#ifndef ___CODER_TEMPCOMPENCO2_API_H__
#define ___CODER_TEMPCOMPENCO2_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */
extern void tempCompenCO2_initialize(emlrtContext *aContext);
extern void tempCompenCO2_terminate(void);
extern void tempCompenCO2_atexit(void);
extern void tempCompenCO2_api(const mxArray * const prhs[2], const mxArray *plhs[1]);
extern double tempCompenCO2(double tempReading, double CO2Reading);
extern void tempCompenCO2_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_tempCompenCO2_api.h 
 *  
 * [EOF] 
 */
