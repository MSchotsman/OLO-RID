/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * minOrMax.c
 *
 * Code generation for function 'minOrMax'
 *
 */

/* Include files */
#include "minOrMax.h"
#include "correlatedRelease_types.h"
#include "relop.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
double b_maximum(const emxArray_real_T *x)
{
  const double *x_data;
  double ex;
  int k;
  int last;
  x_data = x->data;
  last = x->size[0];
  if (x->size[0] <= 2) {
    if (x->size[0] == 1) {
      ex = x_data[0];
    } else {
      ex = x_data[x->size[0] - 1];
      if ((!(x_data[0] < ex)) && ((!rtIsNaN(x_data[0])) || rtIsNaN(ex))) {
        ex = x_data[0];
      }
    }
  } else {
    int idx;
    if (!rtIsNaN(x_data[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!rtIsNaN(x_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      ex = x_data[0];
    } else {
      ex = x_data[idx - 1];
      idx++;
      for (k = idx; k <= last; k++) {
        double d;
        d = x_data[k - 1];
        if (ex < d) {
          ex = d;
        }
      }
    }
  }
  return ex;
}

double b_minimum(const double x[3], int *idx)
{
  double ex;
  int k;
  if (!rtIsNaN(x[0])) {
    *idx = 1;
  } else {
    boolean_T exitg1;
    *idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 4)) {
      if (!rtIsNaN(x[k - 1])) {
        *idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (*idx == 0) {
    ex = x[0];
    *idx = 1;
  } else {
    int i;
    ex = x[*idx - 1];
    i = *idx + 1;
    for (k = i; k < 4; k++) {
      double d;
      d = x[k - 1];
      if (ex > d) {
        ex = d;
        *idx = k;
      }
    }
  }
  return ex;
}

double c_minimum(const emxArray_real_T *x)
{
  const double *x_data;
  double ex;
  int k;
  int last;
  x_data = x->data;
  last = x->size[0];
  if (x->size[0] <= 2) {
    if (x->size[0] == 1) {
      ex = x_data[0];
    } else {
      ex = x_data[x->size[0] - 1];
      if ((!(x_data[0] > ex)) && ((!rtIsNaN(x_data[0])) || rtIsNaN(ex))) {
        ex = x_data[0];
      }
    }
  } else {
    int idx;
    if (!rtIsNaN(x_data[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!rtIsNaN(x_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      ex = x_data[0];
    } else {
      ex = x_data[idx - 1];
      idx++;
      for (k = idx; k <= last; k++) {
        double d;
        d = x_data[k - 1];
        if (ex > d) {
          ex = d;
        }
      }
    }
  }
  return ex;
}

creal_T d_minimum(const emxArray_creal_T *x)
{
  const creal_T *x_data;
  creal_T ex;
  double y;
  int istop;
  int k;
  x_data = x->data;
  istop = x->size[1];
  ex = x_data[0];
  for (k = 2; k <= istop; k++) {
    creal_T b_x;
    boolean_T p;
    b_x = x_data[k - 1];
    if (rtIsNaN(b_x.re) || rtIsNaN(x_data[k - 1].im)) {
      p = false;
    } else if (rtIsNaN(ex.re) || rtIsNaN(ex.im)) {
      p = true;
    } else {
      double c_x;
      c_x = absRelopProxies(ex, b_x, &y);
      p = (c_x > y);
    }
    if (p) {
      ex = b_x;
    }
  }
  return ex;
}

double maximum(const double x[27])
{
  double ex;
  int idx;
  int k;
  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 27)) {
      if (!rtIsNaN(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    ex = x[0];
  } else {
    ex = x[idx - 1];
    idx++;
    for (k = idx; k < 28; k++) {
      double d;
      d = x[k - 1];
      if (ex < d) {
        ex = d;
      }
    }
  }
  return ex;
}

double minimum(const double x[27])
{
  double ex;
  int idx;
  int k;
  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 27)) {
      if (!rtIsNaN(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    ex = x[0];
  } else {
    ex = x[idx - 1];
    idx++;
    for (k = idx; k < 28; k++) {
      double d;
      d = x[k - 1];
      if (ex > d) {
        ex = d;
      }
    }
  }
  return ex;
}

/* End of code generation (minOrMax.c) */
