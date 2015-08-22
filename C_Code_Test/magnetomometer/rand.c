/*
 * rand.c
 *
 * Code generation for function 'rand'
 *
 * C source code generated on: Mon May 04 22:20:39 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "adjustRollerData.h"
#include "rand.h"
#include "adjustRollerData_emxutil.h"
#include "adjustRollerData_data.h"

/* Function Definitions */
void b_rand(real_T varargin_1, emxArray_real_T *r)
{
  int32_T i;
  int32_T k;
  int32_T exitg1;
  uint32_T u[2];
  uint32_T b_r;
  int32_T kk;
  uint32_T y;
  uint32_T b_y;
  uint32_T c_y;
  uint32_T d_y;
  real_T c_r;
  boolean_T isvalid;
  boolean_T exitg2;
  i = r->size[0];
  r->size[0] = (int32_T)varargin_1;
  emxEnsureCapacity((emxArray__common *)r, i, (int32_T)sizeof(real_T));
  for (k = 0; k < (int32_T)varargin_1; k++) {
    /* <LEGAL>   This is a uniform (0,1) pseudorandom number generator based on: */
    /* <LEGAL> */
    /* <LEGAL>    A C-program for MT19937, with initialization improved 2002/1/26. */
    /* <LEGAL>    Coded by Takuji Nishimura and Makoto Matsumoto. */
    /* <LEGAL> */
    /* <LEGAL>    Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura, */
    /* <LEGAL>    All rights reserved. */
    /* <LEGAL> */
    /* <LEGAL>    Redistribution and use in source and binary forms, with or without */
    /* <LEGAL>    modification, are permitted provided that the following conditions */
    /* <LEGAL>    are met: */
    /* <LEGAL> */
    /* <LEGAL>      1. Redistributions of source code must retain the above copyright */
    /* <LEGAL>         notice, this list of conditions and the following disclaimer. */
    /* <LEGAL> */
    /* <LEGAL>      2. Redistributions in binary form must reproduce the above copyright */
    /* <LEGAL>         notice, this list of conditions and the following disclaimer in the */
    /* <LEGAL>         documentation and/or other materials provided with the distribution. */
    /* <LEGAL> */
    /* <LEGAL>      3. The names of its contributors may not be used to endorse or promote */
    /* <LEGAL>         products derived from this software without specific prior written */
    /* <LEGAL>         permission. */
    /* <LEGAL> */
    /* <LEGAL>    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS */
    /* <LEGAL>    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT */
    /* <LEGAL>    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR */
    /* <LEGAL>    A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR */
    /* <LEGAL>    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, */
    /* <LEGAL>    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, */
    /* <LEGAL>    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR */
    /* <LEGAL>    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF */
    /* <LEGAL>    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING */
    /* <LEGAL>    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS */
    /* <LEGAL>    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
    do {
      exitg1 = 0;
      for (i = 0; i < 2; i++) {
        u[i] = 0U;
      }

      for (i = 0; i < 2; i++) {
        b_r = state[624] + 1U;
        if (b_r >= 625U) {
          for (kk = 0; kk < 227; kk++) {
            y = (state[kk] & 2147483648U) | (state[1 + kk] & 2147483647U);
            if ((int32_T)(y & 1U) == 0) {
              b_y = y >> 1U;
            } else {
              b_y = y >> 1U ^ 2567483615U;
            }

            state[kk] = state[397 + kk] ^ b_y;
          }

          for (kk = 0; kk < 396; kk++) {
            y = (state[227 + kk] & 2147483648U) | (state[228 + kk] & 2147483647U);
            if ((int32_T)(y & 1U) == 0) {
              c_y = y >> 1U;
            } else {
              c_y = y >> 1U ^ 2567483615U;
            }

            state[227 + kk] = state[kk] ^ c_y;
          }

          y = (state[623] & 2147483648U) | (state[0] & 2147483647U);
          if ((int32_T)(y & 1U) == 0) {
            d_y = y >> 1U;
          } else {
            d_y = y >> 1U ^ 2567483615U;
          }

          state[623] = state[396] ^ d_y;
          b_r = 1U;
        }

        y = state[(int32_T)b_r - 1];
        state[624] = b_r;
        y ^= y >> 11U;
        y ^= y << 7U & 2636928640U;
        y ^= y << 15U & 4022730752U;
        y ^= y >> 18U;
        u[i] = y;
      }

      c_r = 1.1102230246251565E-16 * ((real_T)(u[0] >> 5U) * 6.7108864E+7 +
        (real_T)(u[1] >> 6U));
      if (c_r == 0.0) {
        if ((state[624] >= 1U) && (state[624] < 625U)) {
          isvalid = TRUE;
        } else {
          isvalid = FALSE;
        }

        if (isvalid) {
          isvalid = FALSE;
          i = 1;
          exitg2 = FALSE;
          while ((exitg2 == FALSE) && (i < 625)) {
            if (state[i - 1] == 0U) {
              i++;
            } else {
              isvalid = TRUE;
              exitg2 = TRUE;
            }
          }
        }

        if (!isvalid) {
          b_r = 5489U;
          state[0] = 5489U;
          for (i = 0; i < 623; i++) {
            b_r = (b_r ^ b_r >> 30U) * 1812433253U + (1 + i);
            state[1 + i] = b_r;
          }

          state[624] = 624U;
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    r->data[k] = c_r;
  }
}

/* End of code generation (rand.c) */
