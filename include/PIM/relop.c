/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * relop.c
 *
 * Code generation for function 'relop'
 *
 */

/* Include files */
#include "relop.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
double absRelopProxies(const creal_T a, const creal_T b, double *y)
{
  double x;
  boolean_T SCALEA;
  boolean_T SCALEB;
  if ((fabs(a.re) > 8.9884656743115785E+307) ||
      (fabs(a.im) > 8.9884656743115785E+307)) {
    SCALEA = true;
  } else {
    SCALEA = false;
  }
  if ((fabs(b.re) > 8.9884656743115785E+307) ||
      (fabs(b.im) > 8.9884656743115785E+307)) {
    SCALEB = true;
  } else {
    SCALEB = false;
  }
  if (SCALEA || SCALEB) {
    x = rt_hypotd_snf(a.re / 2.0, a.im / 2.0);
    *y = rt_hypotd_snf(b.re / 2.0, b.im / 2.0);
  } else {
    x = rt_hypotd_snf(a.re, a.im);
    *y = rt_hypotd_snf(b.re, b.im);
  }
  if (x == *y) {
    x = rt_atan2d_snf(a.im, a.re);
    *y = rt_atan2d_snf(b.im, b.re);
    if (x == *y) {
      if (a.re != b.re) {
        if (x >= 0.0) {
          x = b.re;
          *y = a.re;
        } else {
          x = a.re;
          *y = b.re;
        }
      } else if (a.re < 0.0) {
        x = b.im;
        *y = a.im;
      } else {
        x = a.im;
        *y = b.im;
      }
      if (x == *y) {
        x = 0.0;
        *y = 0.0;
      }
    }
  }
  return x;
}

/* End of code generation (relop.c) */
