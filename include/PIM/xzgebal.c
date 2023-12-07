/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzgebal.c
 *
 * Code generation for function 'xzgebal'
 *
 */

/* Include files */
#include "xzgebal.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
int xzgebal(creal_T A[9], int *ihi, double scale[3])
{
  double b_scale;
  double t;
  int b_ix0_tmp;
  int exitg5;
  int i;
  int ilo;
  int ira;
  int ix;
  int ix0_tmp;
  int k;
  int kend;
  int temp_re_tmp;
  boolean_T converged;
  boolean_T notdone;
  scale[0] = 1.0;
  scale[1] = 1.0;
  scale[2] = 1.0;
  ilo = 1;
  *ihi = 3;
  notdone = true;
  do {
    exitg5 = 0;
    if (notdone) {
      int exitg4;
      notdone = false;
      ix0_tmp = *ihi;
      do {
        exitg4 = 0;
        if (ix0_tmp > 0) {
          boolean_T exitg6;
          converged = false;
          i = 0;
          exitg6 = false;
          while ((!exitg6) && (i <= *ihi - 1)) {
            if (i + 1 == ix0_tmp) {
              i++;
            } else {
              kend = (ix0_tmp + 3 * i) - 1;
              if ((A[kend].re != 0.0) || (A[kend].im != 0.0)) {
                converged = true;
                exitg6 = true;
              } else {
                i++;
              }
            }
          }
          if (converged) {
            ix0_tmp--;
          } else {
            scale[*ihi - 1] = ix0_tmp;
            if (ix0_tmp != *ihi) {
              ix = (ix0_tmp - 1) * 3;
              ira = (*ihi - 1) * 3;
              for (k = 0; k < *ihi; k++) {
                temp_re_tmp = ix + k;
                t = A[temp_re_tmp].re;
                b_scale = A[temp_re_tmp].im;
                b_ix0_tmp = ira + k;
                A[temp_re_tmp] = A[b_ix0_tmp];
                A[b_ix0_tmp].re = t;
                A[b_ix0_tmp].im = b_scale;
              }
              t = A[ix0_tmp - 1].re;
              b_scale = A[ix0_tmp - 1].im;
              A[ix0_tmp - 1] = A[*ihi - 1];
              A[*ihi - 1].re = t;
              A[*ihi - 1].im = b_scale;
              t = A[ix0_tmp + 2].re;
              b_scale = A[ix0_tmp + 2].im;
              A[ix0_tmp + 2] = A[*ihi + 2];
              A[*ihi + 2].re = t;
              A[*ihi + 2].im = b_scale;
              t = A[ix0_tmp + 5].re;
              b_scale = A[ix0_tmp + 5].im;
              A[ix0_tmp + 5] = A[*ihi + 5];
              A[*ihi + 5].re = t;
              A[*ihi + 5].im = b_scale;
            }
            exitg4 = 1;
          }
        } else {
          exitg4 = 2;
        }
      } while (exitg4 == 0);
      if (exitg4 == 1) {
        if (*ihi == 1) {
          ilo = 1;
          *ihi = 1;
          exitg5 = 1;
        } else {
          (*ihi)--;
          notdone = true;
        }
      }
    } else {
      notdone = true;
      while (notdone) {
        boolean_T exitg6;
        notdone = false;
        ix0_tmp = ilo;
        exitg6 = false;
        while ((!exitg6) && (ix0_tmp <= *ihi)) {
          boolean_T exitg7;
          converged = false;
          i = ilo;
          exitg7 = false;
          while ((!exitg7) && (i <= *ihi)) {
            if (i == ix0_tmp) {
              i++;
            } else {
              kend = (i + 3 * (ix0_tmp - 1)) - 1;
              if ((A[kend].re != 0.0) || (A[kend].im != 0.0)) {
                converged = true;
                exitg7 = true;
              } else {
                i++;
              }
            }
          }
          if (converged) {
            ix0_tmp++;
          } else {
            scale[ilo - 1] = ix0_tmp;
            if (ix0_tmp != ilo) {
              ix = (ix0_tmp - 1) * 3;
              kend = (ilo - 1) * 3;
              for (k = 0; k < *ihi; k++) {
                temp_re_tmp = ix + k;
                t = A[temp_re_tmp].re;
                b_scale = A[temp_re_tmp].im;
                b_ix0_tmp = kend + k;
                A[temp_re_tmp] = A[b_ix0_tmp];
                A[b_ix0_tmp].re = t;
                A[b_ix0_tmp].im = b_scale;
              }
              ix = (kend + ix0_tmp) - 1;
              ira = (kend + ilo) - 1;
              b_ix0_tmp = (unsigned char)(4 - ilo);
              for (k = 0; k < b_ix0_tmp; k++) {
                temp_re_tmp = ix + k * 3;
                t = A[temp_re_tmp].re;
                b_scale = A[temp_re_tmp].im;
                kend = ira + k * 3;
                A[temp_re_tmp] = A[kend];
                A[kend].re = t;
                A[kend].im = b_scale;
              }
            }
            ilo++;
            notdone = true;
            exitg6 = true;
          }
        }
      }
      converged = false;
      exitg5 = 2;
    }
  } while (exitg5 == 0);
  if (exitg5 != 1) {
    boolean_T exitg3;
    exitg3 = false;
    while ((!exitg3) && (!converged)) {
      int exitg2;
      converged = true;
      i = ilo - 1;
      do {
        exitg2 = 0;
        if (i + 1 <= *ihi) {
          double absxk;
          double c;
          double ca;
          double r;
          kend = (*ihi - ilo) + 1;
          c = xnrm2(kend, A, i * 3 + ilo);
          b_ix0_tmp = (ilo - 1) * 3 + i;
          r = 0.0;
          if (kend >= 1) {
            if (kend == 1) {
              r = rt_hypotd_snf(A[b_ix0_tmp].re, A[b_ix0_tmp].im);
            } else {
              b_scale = 3.3121686421112381E-170;
              kend = (b_ix0_tmp + (kend - 1) * 3) + 1;
              for (k = b_ix0_tmp + 1; k <= kend; k += 3) {
                absxk = fabs(A[k - 1].re);
                if (absxk > b_scale) {
                  t = b_scale / absxk;
                  r = r * t * t + 1.0;
                  b_scale = absxk;
                } else {
                  t = absxk / b_scale;
                  r += t * t;
                }
                absxk = fabs(A[k - 1].im);
                if (absxk > b_scale) {
                  t = b_scale / absxk;
                  r = r * t * t + 1.0;
                  b_scale = absxk;
                } else {
                  t = absxk / b_scale;
                  r += t * t;
                }
              }
              r = b_scale * sqrt(r);
            }
          }
          ix0_tmp = i * 3;
          kend = 0;
          if (*ihi > 1) {
            b_scale = fabs(A[ix0_tmp].re) + fabs(A[ix0_tmp].im);
            for (k = 2; k <= *ihi; k++) {
              ix = (ix0_tmp + k) - 1;
              t = fabs(A[ix].re) + fabs(A[ix].im);
              if (t > b_scale) {
                kend = k - 1;
                b_scale = t;
              }
            }
          }
          kend += 3 * i;
          ca = rt_hypotd_snf(A[kend].re, A[kend].im);
          kend = 4 - ilo;
          if (4 - ilo < 1) {
            ira = 0;
          } else {
            ira = 1;
            if (4 - ilo > 1) {
              b_scale = fabs(A[b_ix0_tmp].re) + fabs(A[b_ix0_tmp].im);
              for (k = 2; k <= kend; k++) {
                ix = b_ix0_tmp + (k - 1) * 3;
                t = fabs(A[ix].re) + fabs(A[ix].im);
                if (t > b_scale) {
                  ira = k;
                  b_scale = t;
                }
              }
            }
          }
          temp_re_tmp = i + 3 * ((ira + ilo) - 2);
          b_scale = rt_hypotd_snf(A[temp_re_tmp].re, A[temp_re_tmp].im);
          if ((c == 0.0) || (r == 0.0)) {
            i++;
          } else {
            double f;
            int exitg1;
            absxk = r / 2.0;
            f = 1.0;
            t = c + r;
            do {
              exitg1 = 0;
              if ((c < absxk) &&
                  (fmax(f, fmax(c, ca)) < 4.9896007738368E+291) &&
                  (fmin(r, fmin(absxk, b_scale)) > 2.0041683600089728E-292)) {
                if (rtIsNaN(((((c + f) + ca) + r) + absxk) + b_scale)) {
                  exitg1 = 1;
                } else {
                  f *= 2.0;
                  c *= 2.0;
                  ca *= 2.0;
                  r /= 2.0;
                  absxk /= 2.0;
                  b_scale /= 2.0;
                }
              } else {
                absxk = c / 2.0;
                while ((absxk >= r) &&
                       (fmax(r, b_scale) < 4.9896007738368E+291) &&
                       (fmin(fmin(f, c), fmin(absxk, ca)) >
                        2.0041683600089728E-292)) {
                  f /= 2.0;
                  c /= 2.0;
                  absxk /= 2.0;
                  ca /= 2.0;
                  r *= 2.0;
                  b_scale *= 2.0;
                }
                if ((!(c + r >= 0.95 * t)) &&
                    ((!(f < 1.0)) || (!(scale[i] < 1.0)) ||
                     (!(f * scale[i] <= 1.0020841800044864E-292))) &&
                    ((!(f > 1.0)) || (!(scale[i] > 1.0)) ||
                     (!(scale[i] >= 9.9792015476736E+291 / f)))) {
                  scale[i] *= f;
                  kend = b_ix0_tmp + 1;
                  t = 1.0 / f;
                  b_ix0_tmp = (b_ix0_tmp + 3 * (3 - ilo)) + 1;
                  for (k = kend; k <= b_ix0_tmp; k += 3) {
                    b_scale = A[k - 1].im;
                    absxk = A[k - 1].re;
                    A[k - 1].re = t * absxk - 0.0 * b_scale;
                    A[k - 1].im = t * b_scale + 0.0 * absxk;
                  }
                  b_ix0_tmp = ix0_tmp + *ihi;
                  for (k = ix0_tmp + 1; k <= b_ix0_tmp; k++) {
                    b_scale = A[k - 1].im;
                    absxk = A[k - 1].re;
                    A[k - 1].re = f * absxk - 0.0 * b_scale;
                    A[k - 1].im = f * b_scale + 0.0 * absxk;
                  }
                  converged = false;
                }
                exitg1 = 2;
              }
            } while (exitg1 == 0);
            if (exitg1 == 1) {
              exitg2 = 2;
            } else {
              i++;
            }
          }
        } else {
          exitg2 = 1;
        }
      } while (exitg2 == 0);
      if (exitg2 != 1) {
        exitg3 = true;
      }
    }
  }
  return ilo;
}

/* End of code generation (xzgebal.c) */
