/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * power.c
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "power.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
creal_T b_power(const creal_T a, double b)
{
  creal_T y;
  if ((a.im == 0.0) && (a.re >= 0.0)) {
    y.re = rt_powd_snf(a.re, b);
    y.im = 0.0;
  } else if ((a.re == 0.0) && (floor(b) == b)) {
    double r;
    double ytmp;
    signed char i;
    ytmp = rt_powd_snf(a.im, b);
    if (rtIsInf(b)) {
      r = rtNaN;
    } else if (b == 0.0) {
      r = 0.0;
    } else {
      r = fmod(b, 4.0);
      if (r == 0.0) {
        r = 0.0;
      } else if (b < 0.0) {
        r += 4.0;
      }
    }
    if (r < 128.0) {
      i = (signed char)r;
    } else {
      i = 0;
    }
    if (i == 3) {
      y.re = 0.0;
      y.im = -ytmp;
    } else if (i == 2) {
      y.re = -ytmp;
      y.im = 0.0;
    } else if (i == 1) {
      y.re = 0.0;
      y.im = ytmp;
    } else {
      y.re = ytmp;
      y.im = 0.0;
    }
  } else if ((a.im == 0.0) && rtIsInf(b) && (fabs(a.re) == 1.0)) {
    y.re = 1.0;
    y.im = 0.0;
  } else {
    double b_im;
    double ytmp;
    if (a.im == 0.0) {
      if (a.re < 0.0) {
        ytmp = log(fabs(a.re));
        b_im = 3.1415926535897931;
      } else {
        ytmp = log(a.re);
        b_im = 0.0;
      }
    } else if ((fabs(a.re) > 8.9884656743115785E+307) ||
               (fabs(a.im) > 8.9884656743115785E+307)) {
      ytmp = log(rt_hypotd_snf(a.re / 2.0, a.im / 2.0)) + 0.69314718055994529;
      b_im = rt_atan2d_snf(a.im, a.re);
    } else {
      ytmp = log(rt_hypotd_snf(a.re, a.im));
      b_im = rt_atan2d_snf(a.im, a.re);
    }
    ytmp *= b;
    b_im *= b;
    if (ytmp == 0.0) {
      y.re = cos(b_im);
      y.im = sin(b_im);
    } else if (b_im == 0.0) {
      y.re = exp(ytmp);
      y.im = 0.0;
    } else if (rtIsInf(b_im) && rtIsInf(ytmp) && (ytmp < 0.0)) {
      y.re = 0.0;
      y.im = 0.0;
    } else {
      double r;
      r = exp(ytmp / 2.0);
      y.re = r * (r * cos(b_im));
      y.im = r * (r * sin(b_im));
    }
  }
  return y;
}

creal_T power(const creal_T a)
{
  creal_T y;
  if ((a.im == 0.0) && (a.re >= 0.0)) {
    y.re = rt_powd_snf(a.re, -0.5);
    y.im = 0.0;
  } else {
    double b_im;
    double r;
    if (a.im == 0.0) {
      if (a.re < 0.0) {
        r = log(fabs(a.re));
        b_im = 3.1415926535897931;
      } else {
        r = log(a.re);
        b_im = 0.0;
      }
    } else if ((fabs(a.re) > 8.9884656743115785E+307) ||
               (fabs(a.im) > 8.9884656743115785E+307)) {
      r = log(rt_hypotd_snf(a.re / 2.0, a.im / 2.0)) + 0.69314718055994529;
      b_im = rt_atan2d_snf(a.im, a.re);
    } else {
      r = log(rt_hypotd_snf(a.re, a.im));
      b_im = rt_atan2d_snf(a.im, a.re);
    }
    y.re = -0.5 * r;
    y.im = -0.5 * b_im;
    if (y.re == 0.0) {
      b_im = y.im;
      y.re = cos(b_im);
      y.im = sin(b_im);
    } else if (y.im == 0.0) {
      b_im = y.re;
      y.re = exp(b_im);
      y.im = 0.0;
    } else if (rtIsInf(y.im) && rtIsInf(y.re) && (y.re < 0.0)) {
      y.re = 0.0;
      y.im = 0.0;
    } else {
      r = exp(y.re / 2.0);
      b_im = y.im;
      y.re = r * (r * cos(b_im));
      y.im = r * (r * sin(b_im));
    }
  }
  return y;
}

/* End of code generation (power.c) */
