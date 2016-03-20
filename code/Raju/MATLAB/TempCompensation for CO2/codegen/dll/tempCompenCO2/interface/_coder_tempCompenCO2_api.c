/*
 * File: _coder_tempCompenCO2_api.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 21-Mar-2016 01:24:47
 */

/* Include files */
#include "_coder_tempCompenCO2_api.h"

/* Function Declarations */
static double emlrt_marshallIn(const emlrtStack *sp, const mxArray *tempReading,
  const char *identifier);
static double b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *emlrt_marshallOut(const double u);
static double c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void tempCompenCO2_initialize(emlrtContext *aContext)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void tempCompenCO2_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void tempCompenCO2_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  tempCompenCO2_xil_terminate();
}

/*
 * Arguments    : const mxArray * const prhs[2]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void tempCompenCO2_api(const mxArray * const prhs[2], const mxArray *plhs[1])
{
  double tempReading;
  double CO2Reading;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  tempReading = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "tempReading");
  CO2Reading = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "CO2Reading");

  /* Invoke the target function */
  tempReading = tempCompenCO2(tempReading, CO2Reading);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(tempReading);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *tempReading
 *                const char *identifier
 * Return Type  : double
 */
static double emlrt_marshallIn(const emlrtStack *sp, const mxArray *tempReading,
  const char *identifier)
{
  double y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(tempReading), &thisId);
  emlrtDestroyArray(&tempReading);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double
 */
static double b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  double y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const double u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const double u)
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double
 */
static double c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  double ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, 0);
  ret = *(double *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * File trailer for _coder_tempCompenCO2_api.c
 *
 * [EOF]
 */
