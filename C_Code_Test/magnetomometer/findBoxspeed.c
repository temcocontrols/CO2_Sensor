/*
 * findBoxspeed.c
 *
 * Code generation for function 'findBoxspeed'
 *
 * C source code generated on: Mon Apr 06 11:46:24 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "findBoxspeed.h"

/* Function Definitions */
real_T findBoxspeed(const real_T test_obtData[238])
{
  real_T speed_box;
  real_T contOne;
  real_T temp[238];
  int32_T i;

  /*  optoData= test_obtData(:,2); %#codegen */
  /*  optoON_array=findoptoON(optoData); */
  contOne = 0.0;

  /*  temp=0 */
  memset(&temp[0], 0, 238U * sizeof(real_T));
  for (i = 0; i < 237; i++) {
    if ((test_obtData[i] == 100.0) && (test_obtData[1 + i] == 100.0)) {
      /* Continous check */
      /*          disp(i) */
      if (1 + i == 237) {
        /* if last element has 100            */
        contOne += 2.0;

        /*              temp=[temp;contOne]    */
        temp[i] = contOne;
      } else {
        contOne++;
      }
    }

    if ((contOne > 0.0) && (test_obtData[i] == 100.0) && (test_obtData[1 + i] ==
         0.0)) {
      /* Ending check */
      contOne++;
    }

    if ((contOne == 0.0) && (test_obtData[i] == 100.0) && (test_obtData[1 + i] ==
         0.0)) {
      /* Just for single '1' */
      contOne = 1.0;
    }

    if ((contOne > 0.0) && (test_obtData[i] == 0.0)) {
      /*              temp=[temp;contOne] */
      temp[i] = contOne;
      contOne = 0.0;
    }
  }

  /*  disp(temp); */
  /*  if temp==0 */
  /*      optoON_array=temp */
  /*  else */
  /*      optoON_array=temp(2:end,:) */
  /*  end */
  /*  speed_box= max(optoON_array) */
  speed_box = temp[0];
  for (i = 1; i + 1 < 239; i++) {
    if (temp[i] > speed_box) {
      speed_box = temp[i];
    }
  }

  return speed_box;
}

/* End of code generation (findBoxspeed.c) */
