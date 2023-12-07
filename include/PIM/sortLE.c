/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sortLE.c
 *
 * Code generation for function 'sortLE'
 *
 */

/* Include files */
#include "sortLE.h"
#include "correlatedRelease_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
boolean_T sortLE(const emxArray_real_T *v, int idx1, int idx2)
{
  const double *v_data;
  int k;
  boolean_T exitg1;
  boolean_T p;
  v_data = v->data;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3)) {
    double v1;
    double v2;
    v1 = v_data[(idx1 + v->size[0] * k) - 1];
    v2 = v_data[(idx2 + v->size[0] * k) - 1];
    if ((v1 == v2) || (rtIsNaN(v1) && rtIsNaN(v2))) {
      k++;
    } else {
      if ((!(v1 <= v2)) && (!rtIsNaN(v2))) {
        p = false;
      }
      exitg1 = true;
    }
  }
  return p;
}

/* End of code generation (sortLE.c) */
