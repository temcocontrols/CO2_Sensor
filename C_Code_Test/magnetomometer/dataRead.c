/*
 * dataRead.c
 *
 * Code generation for function 'dataRead'
 *
 * C source code generated on: Sun Apr 05 23:50:22 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "dataRead.h"
#include "dataRead_emxutil.h"

/* Function Declarations */
static int32_T compute_nones(const emxArray_boolean_T *x, int32_T n);
static void eml_li_find(const emxArray_boolean_T *x, emxArray_int32_T *y);

/* Function Definitions */
static int32_T compute_nones(const emxArray_boolean_T *x, int32_T n)
{
  int32_T k;
  int32_T i;
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x->data[i - 1]) {
      k++;
    }
  }

  return k;
}

static void eml_li_find(const emxArray_boolean_T *x, emxArray_int32_T *y)
{
  int32_T n;
  int32_T k;
  int32_T i;
  n = x->size[0] * 9;
  k = compute_nones(x, n);
  i = y->size[0];
  y->size[0] = k;
  emxEnsureCapacity((emxArray__common *)y, i, (int32_T)sizeof(int32_T));
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x->data[i - 1]) {
      y->data[k] = i;
      k++;
    }
  }
}

void dataRead(emxArray_real_T *test1, real_T test_obtData[1904])
{
  emxArray_boolean_T *r0;
  int32_T i0;
  int32_T loop_ub;
  emxArray_int32_T *r1;
  real_T b_test1[1904];
  real_T c_test1[1904];
  real_T d_test1[1904];
  real_T e_test1[1904];
  real_T f_test1[1904];
  real_T g_test1[1904];
  real_T h_test1[1904];
  emxInit_boolean_T(&r0, 2);

  /* - NaN is replaced with 0 */
  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = test1->size[0];
  r0->size[1] = 9;
  emxEnsureCapacity((emxArray__common *)r0, i0, (int32_T)sizeof(boolean_T));
  loop_ub = test1->size[0] * test1->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r0->data[i0] = rtIsNaN(test1->data[i0]);
  }

  emxInit_int32_T(&r1, 1);
  eml_li_find(r0, r1);
  loop_ub = r1->size[0];
  emxFree_boolean_T(&r0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    test1->data[r1->data[i0] - 1] = 0.0;
  }

  emxFree_int32_T(&r1);
  memset(&test_obtData[0], 0, 1904U * sizeof(real_T));
  for (i0 = 0; i0 < 238; i0++) {
    test_obtData[i0] = 1.0 + (real_T)i0;
  }

  for (i0 = 0; i0 < 8; i0++) {
    for (loop_ub = 0; loop_ub < 238; loop_ub++) {
      b_test1[loop_ub + 238 * i0] = test1->data[(loop_ub + test1->size[0] * (1 +
        i0)) + 1];
    }
  }

  memcpy(&test_obtData[238], &b_test1[238], 238U * sizeof(real_T));
  for (i0 = 0; i0 < 8; i0++) {
    for (loop_ub = 0; loop_ub < 238; loop_ub++) {
      c_test1[loop_ub + 238 * i0] = test1->data[(loop_ub + test1->size[0] * (1 +
        i0)) + 1];
    }
  }

  memcpy(&test_obtData[476], &c_test1[476], 238U * sizeof(real_T));
  for (i0 = 0; i0 < 8; i0++) {
    for (loop_ub = 0; loop_ub < 238; loop_ub++) {
      d_test1[loop_ub + 238 * i0] = test1->data[(loop_ub + test1->size[0] * (1 +
        i0)) + 1];
    }
  }

  memcpy(&test_obtData[714], &d_test1[714], 238U * sizeof(real_T));
  for (i0 = 0; i0 < 8; i0++) {
    for (loop_ub = 0; loop_ub < 238; loop_ub++) {
      e_test1[loop_ub + 238 * i0] = test1->data[(loop_ub + test1->size[0] * (1 +
        i0)) + 1];
    }
  }

  memcpy(&test_obtData[952], &e_test1[952], 238U * sizeof(real_T));
  for (i0 = 0; i0 < 8; i0++) {
    for (loop_ub = 0; loop_ub < 238; loop_ub++) {
      f_test1[loop_ub + 238 * i0] = test1->data[(loop_ub + test1->size[0] * (1 +
        i0)) + 1];
    }
  }

  memcpy(&test_obtData[1190], &f_test1[1190], 238U * sizeof(real_T));
  for (i0 = 0; i0 < 8; i0++) {
    for (loop_ub = 0; loop_ub < 238; loop_ub++) {
      g_test1[loop_ub + 238 * i0] = test1->data[(loop_ub + test1->size[0] * (1 +
        i0)) + 1];
    }
  }

  memcpy(&test_obtData[1428], &g_test1[1428], 238U * sizeof(real_T));
  for (i0 = 0; i0 < 8; i0++) {
    for (loop_ub = 0; loop_ub < 238; loop_ub++) {
      h_test1[loop_ub + 238 * i0] = test1->data[(loop_ub + test1->size[0] * (1 +
        i0)) + 1];
    }
  }

  memcpy(&test_obtData[1666], &h_test1[1666], 238U * sizeof(real_T));
}

/* End of code generation (dataRead.c) */
