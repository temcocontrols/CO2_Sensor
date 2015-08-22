/*
 * adjustRollerData.c
 *
 * Code generation for function 'adjustRollerData'
 *
 * C source code generated on: Mon May 04 22:20:38 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "adjustRollerData.h"
#include "adjustRollerData_emxutil.h"
#include "rand.h"

/* Function Declarations */
static void b_eml_sort(const emxArray_real_T *x, int32_T dim, emxArray_real_T *y);
static void eml_sort(const emxArray_real_T *x, emxArray_real_T *y);

/* Function Definitions */
static void b_eml_sort(const emxArray_real_T *x, int32_T dim, emxArray_real_T *y)
{
  int32_T vlen;
  emxArray_real_T *vwork;
  int32_T ix;
  int32_T vstride;
  int32_T k;
  int32_T i1;
  int32_T j;
  emxArray_int32_T *iidx;
  emxArray_int32_T *idx0;
  uint32_T unnamed_idx_0;
  boolean_T p;
  int32_T i2;
  int32_T b_j;
  int32_T pEnd;
  int32_T b_p;
  int32_T q;
  int32_T qEnd;
  int32_T kEnd;
  if (dim <= 1) {
    vlen = x->size[0];
  } else {
    vlen = 1;
  }

  emxInit_real_T(&vwork, 1);
  ix = vwork->size[0];
  vwork->size[0] = vlen;
  emxEnsureCapacity((emxArray__common *)vwork, ix, (int32_T)sizeof(real_T));
  ix = y->size[0];
  y->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)y, ix, (int32_T)sizeof(real_T));
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x->size[0];
    k = 2;
  }

  i1 = 0;
  j = 1;
  emxInit_int32_T(&iidx, 1);
  emxInit_int32_T(&idx0, 1);
  while (j <= vstride) {
    i1++;
    ix = i1;
    for (k = 0; k < vlen; k++) {
      vwork->data[k] = x->data[ix - 1];
      ix += vstride;
    }

    unnamed_idx_0 = (uint32_T)vwork->size[0];
    ix = iidx->size[0];
    iidx->size[0] = (int32_T)unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)iidx, ix, (int32_T)sizeof(int32_T));
    if (vwork->size[0] == 0) {
    } else {
      for (k = 1; k <= vwork->size[0]; k++) {
        iidx->data[k - 1] = k;
      }

      for (k = 1; k <= vwork->size[0] - 1; k += 2) {
        if ((vwork->data[k - 1] >= vwork->data[k]) || rtIsNaN(vwork->data[k - 1]))
        {
          p = TRUE;
        } else {
          p = FALSE;
        }

        if (p) {
        } else {
          iidx->data[k - 1] = k + 1;
          iidx->data[k] = k;
        }
      }

      ix = idx0->size[0];
      idx0->size[0] = vwork->size[0];
      emxEnsureCapacity((emxArray__common *)idx0, ix, (int32_T)sizeof(int32_T));
      i2 = vwork->size[0];
      for (ix = 0; ix < i2; ix++) {
        idx0->data[ix] = 1;
      }

      ix = 2;
      while (ix < vwork->size[0]) {
        i2 = ix << 1;
        b_j = 1;
        for (pEnd = 1 + ix; pEnd < vwork->size[0] + 1; pEnd = qEnd + ix) {
          b_p = b_j - 1;
          q = pEnd;
          qEnd = b_j + i2;
          if (qEnd > vwork->size[0] + 1) {
            qEnd = vwork->size[0] + 1;
          }

          k = 0;
          kEnd = qEnd - b_j;
          while (k + 1 <= kEnd) {
            if ((vwork->data[iidx->data[b_p] - 1] >= vwork->data[iidx->data[q -
                 1] - 1]) || rtIsNaN(vwork->data[iidx->data[b_p] - 1])) {
              p = TRUE;
            } else {
              p = FALSE;
            }

            if (p) {
              idx0->data[k] = iidx->data[b_p];
              b_p++;
              if (b_p + 1 == pEnd) {
                while (q < qEnd) {
                  k++;
                  idx0->data[k] = iidx->data[q - 1];
                  q++;
                }
              }
            } else {
              idx0->data[k] = iidx->data[q - 1];
              q++;
              if (q == qEnd) {
                while (b_p + 1 < pEnd) {
                  k++;
                  idx0->data[k] = iidx->data[b_p];
                  b_p++;
                }
              }
            }

            k++;
          }

          for (k = 0; k + 1 <= kEnd; k++) {
            iidx->data[(b_j + k) - 1] = idx0->data[k];
          }

          b_j = qEnd;
        }

        ix = i2;
      }
    }

    ix = i1;
    for (k = 0; k < vlen; k++) {
      y->data[ix - 1] = vwork->data[iidx->data[k] - 1];
      ix += vstride;
    }

    j++;
  }

  emxFree_int32_T(&idx0);
  emxFree_int32_T(&iidx);
  emxFree_real_T(&vwork);
}

static void eml_sort(const emxArray_real_T *x, emxArray_real_T *y)
{
  int32_T dim;
  dim = 2;
  if (x->size[0] != 1) {
    dim = 1;
  }

  b_eml_sort(x, dim, y);
}

void adjustRollerData(const real_T roller_resultant[205], real_T n, real_T
                      roller_resultantMat_data[238], int32_T
                      roller_resultantMat_size[1])
{
  emxArray_real_T *a;
  emxArray_real_T *b_a;
  int32_T loop_ub;
  int32_T i0;
  int32_T i1;

  /*  It appends or delets the roller resultant matrix so that output matrix */
  /*  size will be equal to roller resultant pre defined data matrix  */
  /*  roller_resultantMat=zeros(size(roller_resultant)); */
  roller_resultantMat_size[0] = 238;
  memset(&roller_resultantMat_data[0], 0, 238U * sizeof(real_T));
  emxInit_real_T(&a, 1);
  emxInit_real_T(&b_a, 1);
  if ((205.0 > n) || (205.0 == n)) {
    if (1.0 > n) {
      loop_ub = 0;
    } else {
      loop_ub = (int32_T)n;
    }

    roller_resultantMat_size[0] = loop_ub;
    for (i0 = 0; i0 < loop_ub; i0++) {
      roller_resultantMat_data[i0] = roller_resultant[i0];
    }
  } else {
    if (205.0 < n) {
      memcpy(&roller_resultantMat_data[0], &roller_resultant[0], 205U * sizeof
             (real_T));
      if (206.0 > n) {
        i0 = 0;
      } else {
        i0 = 205;
      }

      b_rand(n - 205.0, a);
      i1 = b_a->size[0];
      b_a->size[0] = a->size[0];
      emxEnsureCapacity((emxArray__common *)b_a, i1, (int32_T)sizeof(real_T));
      loop_ub = a->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_a->data[i1] = a->data[i1] * roller_resultant[204];
      }

      eml_sort(b_a, a);
      loop_ub = a->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        roller_resultantMat_data[i0 + i1] = a->data[i1];
      }
    }
  }

  emxFree_real_T(&b_a);
  emxFree_real_T(&a);

  /*  disp(m); */
  /*  disp(n); */
}

/* End of code generation (adjustRollerData.c) */
