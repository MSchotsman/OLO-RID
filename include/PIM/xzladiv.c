/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzladiv.c
 *
 * Code generation for function 'xzladiv'
 *
 */

/* Include files */
#include "xzladiv.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
creal_T xzladiv(const creal_T x, const creal_T y)
{
  creal_T z;
  double aa;
  double ab;
  double bb;
  double cc;
  double cd;
  double cd_tmp;
  double dd;
  double p;
  double r;
  double s;
  aa = x.re;
  bb = x.im;
  cc = y.re;
  dd = y.im;
  ab = fmax(fabs(x.re), fabs(x.im));
  cd_tmp = fabs(y.im);
  r = fabs(y.re);
  cd = fmax(r, cd_tmp);
  s = 1.0;
  if (ab >= 8.9884656743115785E+307) {
    aa = 0.5 * x.re;
    bb = 0.5 * x.im;
    s = 2.0;
  }
  if (cd >= 8.9884656743115785E+307) {
    cc = 0.5 * y.re;
    dd = 0.5 * y.im;
    s *= 0.5;
  }
  if (ab <= 2.0041683600089728E-292) {
    aa *= 4.0564819207303341E+31;
    bb *= 4.0564819207303341E+31;
    s /= 4.0564819207303341E+31;
  }
  if (cd <= 2.0041683600089728E-292) {
    cc *= 4.0564819207303341E+31;
    dd *= 4.0564819207303341E+31;
    s *= 4.0564819207303341E+31;
  }
  if (cd_tmp <= r) {
    r = dd / cc;
    cd = 1.0 / (cc + dd * r);
    if (r != 0.0) {
      ab = bb * r;
      cd_tmp = bb * cd;
      if (ab != 0.0) {
        p = (aa + ab) * cd;
      } else {
        p = aa * cd + cd_tmp * r;
      }
      ab = -aa * r;
      if (ab != 0.0) {
        ab = (bb + ab) * cd;
      } else {
        ab = cd_tmp + -aa * cd * r;
      }
    } else {
      p = (aa + dd * (bb / cc)) * cd;
      ab = (bb + dd * (-aa / cc)) * cd;
    }
  } else {
    r = cc / dd;
    cd = 1.0 / (dd + cc * r);
    if (r != 0.0) {
      ab = aa * r;
      cd_tmp = aa * cd;
      if (ab != 0.0) {
        p = (bb + ab) * cd;
      } else {
        p = bb * cd + cd_tmp * r;
      }
      ab = -bb * r;
      if (ab != 0.0) {
        ab = (aa + ab) * cd;
      } else {
        ab = cd_tmp + -bb * cd * r;
      }
    } else {
      p = (bb + cc * (aa / dd)) * cd;
      ab = (aa + cc * (-bb / dd)) * cd;
    }
    ab = -ab;
  }
  p *= s;
  ab *= s;
  z.re = p;
  z.im = ab;
  return z;
}

/* End of code generation (xzladiv.c) */
