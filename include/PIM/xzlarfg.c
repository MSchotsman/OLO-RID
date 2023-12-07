/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlarfg.c
 *
 * Code generation for function 'xzlarfg'
 *
 */

/* Include files */
#include "xzlarfg.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_rtwutil.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "xdlapy3.h"
#include "xnrm2.h"
#include <math.h>

/* Function Definitions */
creal_T b_xzlarfg(creal_T *alpha1, creal_T *x)
{
  creal_T tau;
  double xnorm;
  int k;
  tau.re = 0.0;
  tau.im = 0.0;
  xnorm = rt_hypotd_snf(x->re, x->im);
  if ((xnorm != 0.0) || (alpha1->im != 0.0)) {
    double beta1;
    beta1 = xdlapy3(alpha1->re, alpha1->im, xnorm);
    if (alpha1->re >= 0.0) {
      beta1 = -beta1;
    }
    if (fabs(beta1) < 1.0020841800044864E-292) {
      creal_T b_alpha1;
      double ai;
      int knt;
      knt = 0;
      do {
        knt++;
        x->re *= 9.9792015476736E+291;
        x->im *= 9.9792015476736E+291;
        beta1 *= 9.9792015476736E+291;
        alpha1->re *= 9.9792015476736E+291;
        alpha1->im *= 9.9792015476736E+291;
      } while ((fabs(beta1) < 1.0020841800044864E-292) && (knt < 20));
      beta1 = xdlapy3(alpha1->re, alpha1->im, rt_hypotd_snf(x->re, x->im));
      if (alpha1->re >= 0.0) {
        beta1 = -beta1;
      }
      xnorm = beta1 - alpha1->re;
      ai = 0.0 - alpha1->im;
      if (ai == 0.0) {
        tau.re = xnorm / beta1;
        tau.im = 0.0;
      } else if (xnorm == 0.0) {
        tau.re = 0.0;
        tau.im = ai / beta1;
      } else {
        tau.re = xnorm / beta1;
        tau.im = ai / beta1;
      }
      b_alpha1.re = alpha1->re - beta1;
      b_alpha1.im = alpha1->im;
      *alpha1 = recip(b_alpha1);
      xnorm = alpha1->re * x->im + alpha1->im * x->re;
      x->re = alpha1->re * x->re - alpha1->im * x->im;
      x->im = xnorm;
      for (k = 0; k < knt; k++) {
        beta1 *= 1.0020841800044864E-292;
      }
      alpha1->re = beta1;
      alpha1->im = 0.0;
    } else {
      creal_T b_alpha1;
      double ai;
      xnorm = beta1 - alpha1->re;
      ai = 0.0 - alpha1->im;
      if (ai == 0.0) {
        tau.re = xnorm / beta1;
        tau.im = 0.0;
      } else if (xnorm == 0.0) {
        tau.re = 0.0;
        tau.im = ai / beta1;
      } else {
        tau.re = xnorm / beta1;
        tau.im = ai / beta1;
      }
      b_alpha1.re = alpha1->re - beta1;
      b_alpha1.im = alpha1->im;
      *alpha1 = recip(b_alpha1);
      xnorm = alpha1->re * x->im + alpha1->im * x->re;
      x->re = alpha1->re * x->re - alpha1->im * x->im;
      x->im = xnorm;
      alpha1->re = beta1;
      alpha1->im = 0.0;
    }
  }
  return tau;
}

creal_T xzlarfg(int n, creal_T *alpha1, creal_T x[9], int ix0)
{
  creal_T tau;
  int k;
  tau.re = 0.0;
  tau.im = 0.0;
  if (n > 0) {
    double xnorm;
    xnorm = xnrm2(n - 1, x, ix0);
    if ((xnorm != 0.0) || (alpha1->im != 0.0)) {
      double beta1;
      beta1 = xdlapy3(alpha1->re, alpha1->im, xnorm);
      if (alpha1->re >= 0.0) {
        beta1 = -beta1;
      }
      if (fabs(beta1) < 1.0020841800044864E-292) {
        creal_T b_alpha1;
        double ai;
        int i;
        int knt;
        knt = 0;
        i = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i; k++) {
            xnorm = x[k - 1].im;
            ai = x[k - 1].re;
            x[k - 1].re = 9.9792015476736E+291 * ai - 0.0 * xnorm;
            x[k - 1].im = 9.9792015476736E+291 * xnorm + 0.0 * ai;
          }
          beta1 *= 9.9792015476736E+291;
          alpha1->re *= 9.9792015476736E+291;
          alpha1->im *= 9.9792015476736E+291;
        } while ((fabs(beta1) < 1.0020841800044864E-292) && (knt < 20));
        beta1 = xdlapy3(alpha1->re, alpha1->im, xnrm2(n - 1, x, ix0));
        if (alpha1->re >= 0.0) {
          beta1 = -beta1;
        }
        xnorm = beta1 - alpha1->re;
        ai = 0.0 - alpha1->im;
        if (ai == 0.0) {
          tau.re = xnorm / beta1;
          tau.im = 0.0;
        } else if (xnorm == 0.0) {
          tau.re = 0.0;
          tau.im = ai / beta1;
        } else {
          tau.re = xnorm / beta1;
          tau.im = ai / beta1;
        }
        b_alpha1.re = alpha1->re - beta1;
        b_alpha1.im = alpha1->im;
        *alpha1 = recip(b_alpha1);
        for (k = ix0; k <= i; k++) {
          xnorm = x[k - 1].im;
          ai = x[k - 1].re;
          x[k - 1].re = alpha1->re * ai - alpha1->im * xnorm;
          x[k - 1].im = alpha1->re * xnorm + alpha1->im * ai;
        }
        for (k = 0; k < knt; k++) {
          beta1 *= 1.0020841800044864E-292;
        }
        alpha1->re = beta1;
        alpha1->im = 0.0;
      } else {
        creal_T b_alpha1;
        double ai;
        int i;
        xnorm = beta1 - alpha1->re;
        ai = 0.0 - alpha1->im;
        if (ai == 0.0) {
          tau.re = xnorm / beta1;
          tau.im = 0.0;
        } else if (xnorm == 0.0) {
          tau.re = 0.0;
          tau.im = ai / beta1;
        } else {
          tau.re = xnorm / beta1;
          tau.im = ai / beta1;
        }
        b_alpha1.re = alpha1->re - beta1;
        b_alpha1.im = alpha1->im;
        *alpha1 = recip(b_alpha1);
        i = (ix0 + n) - 2;
        for (k = ix0; k <= i; k++) {
          xnorm = x[k - 1].im;
          ai = x[k - 1].re;
          x[k - 1].re = alpha1->re * ai - alpha1->im * xnorm;
          x[k - 1].im = alpha1->re * xnorm + alpha1->im * ai;
        }
        alpha1->re = beta1;
        alpha1->im = 0.0;
      }
    }
  }
  return tau;
}

/* End of code generation (xzlarfg.c) */
