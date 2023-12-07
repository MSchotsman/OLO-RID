/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eig.c
 *
 * Code generation for function 'eig'
 *
 */

/* Include files */
#include "eig.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xsyheev.h"
#include "xzgebal.h"
#include "xzlahqr.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "xzlascl.h"
#include "xztrevc3.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void eig(const creal_T A[9], creal_T V[9], creal_T D[9])
{
  creal_T b_A[9];
  creal_T tau[2];
  creal_T temp;
  double absxk;
  double s;
  int b_i;
  int i;
  int ihi;
  int j;
  int k;
  boolean_T scalea;
  scalea = true;
  for (k = 0; k < 9; k++) {
    if (scalea) {
      s = A[k].re;
      absxk = A[k].im;
      if (rtIsInf(s) || rtIsInf(absxk) || (rtIsNaN(s) || rtIsNaN(absxk))) {
        scalea = false;
      }
    } else {
      scalea = false;
    }
  }
  if (!scalea) {
    for (i = 0; i < 9; i++) {
      V[i].re = rtNaN;
      V[i].im = 0.0;
      D[i].re = 0.0;
      D[i].im = 0.0;
    }
    D[0].re = rtNaN;
    D[0].im = 0.0;
    D[4].re = rtNaN;
    D[4].im = 0.0;
    D[8].re = rtNaN;
    D[8].im = 0.0;
  } else {
    int exitg1;
    int in;
    int itau;
    boolean_T exitg2;
    scalea = true;
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j < 3)) {
      b_i = 0;
      do {
        exitg1 = 0;
        if (b_i <= j) {
          itau = j + 3 * b_i;
          in = b_i + 3 * j;
          if ((!(A[in].re == A[itau].re)) || (!(A[in].im == -A[itau].im))) {
            scalea = false;
            exitg1 = 1;
          } else {
            b_i++;
          }
        } else {
          j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);
      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
    if (scalea) {
      double scale[3];
      memcpy(&V[0], &A[0], 9U * sizeof(creal_T));
      xsyheev(V, scale);
      memset(&D[0], 0, 9U * sizeof(creal_T));
      D[0].re = scale[0];
      D[0].im = 0.0;
      D[4].re = scale[1];
      D[4].im = 0.0;
      D[8].re = scale[2];
      D[8].im = 0.0;
    } else {
      scalea = true;
      j = 0;
      exitg2 = false;
      while ((!exitg2) && (j < 3)) {
        b_i = 0;
        do {
          exitg1 = 0;
          if (b_i <= j) {
            itau = j + 3 * b_i;
            in = b_i + 3 * j;
            if ((!(A[in].re == -A[itau].re)) || (!(A[in].im == A[itau].im))) {
              scalea = false;
              exitg1 = 1;
            } else {
              b_i++;
            }
          } else {
            j++;
            exitg1 = 2;
          }
        } while (exitg1 == 0);
        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
      if (scalea) {
        for (i = 0; i < 9; i++) {
          s = A[i].im;
          absxk = A[i].re;
          V[i].re = 0.0 * absxk - s;
          V[i].im = 0.0 * s + absxk;
        }
        double scale[3];
        xsyheev(V, scale);
        memset(&D[0], 0, 9U * sizeof(creal_T));
        D[0].re = 0.0;
        D[0].im = -scale[0];
        D[4].re = 0.0;
        D[4].im = -scale[1];
        D[8].re = 0.0;
        D[8].im = -scale[2];
      } else {
        creal_T work[3];
        double anrm;
        memcpy(&b_A[0], &A[0], 9U * sizeof(creal_T));
        anrm = 0.0;
        k = 0;
        exitg2 = false;
        while ((!exitg2) && (k < 9)) {
          absxk = rt_hypotd_snf(A[k].re, A[k].im);
          if (rtIsNaN(absxk)) {
            anrm = rtNaN;
            exitg2 = true;
          } else {
            if (absxk > anrm) {
              anrm = absxk;
            }
            k++;
          }
        }
        if (rtIsInf(anrm) || rtIsNaN(anrm)) {
          work[0].re = rtNaN;
          work[0].im = 0.0;
          work[1].re = rtNaN;
          work[1].im = 0.0;
          work[2].re = rtNaN;
          work[2].im = 0.0;
          for (i = 0; i < 9; i++) {
            V[i].re = rtNaN;
            V[i].im = 0.0;
          }
        } else {
          double scale[3];
          double cscale;
          int i1;
          int ia0;
          int ilo;
          cscale = anrm;
          scalea = false;
          if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
            scalea = true;
            cscale = 6.7178761075670888E-139;
            xzlascl(anrm, cscale, b_A);
          } else if (anrm > 1.4885657073574029E+138) {
            scalea = true;
            cscale = 1.4885657073574029E+138;
            xzlascl(anrm, cscale, b_A);
          }
          ilo = xzgebal(b_A, &ihi, scale);
          i = ihi - ilo;
          if (i + 1 > 1) {
            i1 = (unsigned char)(ilo - 1);
            if (i1 - 1 >= 0) {
              memset(&tau[0], 0, (unsigned int)i1 * sizeof(creal_T));
            }
            for (b_i = ihi; b_i < 3; b_i++) {
              tau[b_i - 1].re = 0.0;
              tau[b_i - 1].im = 0.0;
            }
            work[0].re = 0.0;
            work[0].im = 0.0;
            work[1].re = 0.0;
            work[1].im = 0.0;
            work[2].re = 0.0;
            work[2].im = 0.0;
            i1 = ihi - 1;
            for (b_i = ilo; b_i <= i1; b_i++) {
              creal_T dc;
              creal_T dc1;
              itau = (b_i - 1) * 3;
              in = b_i * 3 + 1;
              j = b_i + itau;
              temp = b_A[j];
              k = ihi - b_i;
              dc = xzlarfg(k, &temp, b_A, itau + 3);
              tau[b_i - 1] = dc;
              b_A[b_i + 3 * (b_i - 1)].re = 1.0;
              b_A[b_i + 3 * (b_i - 1)].im = 0.0;
              b_xzlarf(ihi, k, j + 1, dc, b_A, in, work);
              dc1.re = dc.re;
              dc1.im = -dc.im;
              xzlarf(k, 3 - b_i, j + 1, dc1, b_A, b_i + in, work);
              b_A[j] = temp;
            }
          }
          memcpy(&V[0], &b_A[0], 9U * sizeof(creal_T));
          itau = ilo + 1;
          for (j = ihi; j >= itau; j--) {
            in = (j - 1) * 3;
            i1 = (unsigned char)(j - 1);
            memset(&V[in], 0, (unsigned int)((i1 + in) - in) * sizeof(creal_T));
            i1 = j + 1;
            for (b_i = i1; b_i <= ihi; b_i++) {
              V[in + 2] = V[in - 1];
            }
            i1 = ihi + 1;
            if (i1 <= 3) {
              memset(&V[(i1 + in) + -1], 0,
                     (unsigned int)(((in - i1) - in) + 4) * sizeof(creal_T));
            }
          }
          i1 = (unsigned char)ilo;
          for (j = 0; j < i1; j++) {
            in = j * 3;
            V[in].re = 0.0;
            V[in].im = 0.0;
            V[in + 1].re = 0.0;
            V[in + 1].im = 0.0;
            V[in + 2].re = 0.0;
            V[in + 2].im = 0.0;
            k = in + j;
            V[k].re = 1.0;
            V[k].im = 0.0;
          }
          i1 = ihi + 1;
          for (j = i1; j < 4; j++) {
            in = (j - 1) * 3;
            V[in].re = 0.0;
            V[in].im = 0.0;
            V[in + 1].re = 0.0;
            V[in + 1].im = 0.0;
            V[in + 2].re = 0.0;
            V[in + 2].im = 0.0;
            k = (in + j) - 1;
            V[k].re = 1.0;
            V[k].im = 0.0;
          }
          ia0 = ilo + ilo * 3;
          if (i >= 1) {
            k = i - 1;
            for (j = i; j <= k; j++) {
              in = ia0 + j * 3;
              memset(&V[in], 0,
                     (unsigned int)(((k + in) - in) + 1) * sizeof(creal_T));
              itau = in + j;
              V[itau].re = 1.0;
              V[itau].im = 0.0;
            }
            itau = (ilo + i) - 2;
            work[0].re = 0.0;
            work[0].im = 0.0;
            work[1].re = 0.0;
            work[1].im = 0.0;
            work[2].re = 0.0;
            work[2].im = 0.0;
            for (b_i = i; b_i >= 1; b_i--) {
              in = (ia0 + b_i) + (b_i - 1) * 3;
              if (b_i < i) {
                V[in - 1].re = 1.0;
                V[in - 1].im = 0.0;
                xzlarf(i, 1, in, tau[itau], V, in + 3, work);
                j = in + 1;
                temp.re = -tau[itau].re;
                temp.im = -tau[itau].im;
                for (k = j; k <= j; k++) {
                  absxk = V[k - 1].im;
                  s = V[k - 1].re;
                  V[k - 1].re = temp.re * s - temp.im * absxk;
                  V[k - 1].im = temp.re * absxk + temp.im * s;
                }
              }
              V[in - 1].re = 1.0 - tau[itau].re;
              V[in - 1].im = 0.0 - tau[itau].im;
              if ((unsigned char)(b_i - 1) - 1 >= 0) {
                V[in - 2].re = 0.0;
                V[in - 2].im = 0.0;
              }
              itau--;
            }
          }
          j = xzlahqr(ilo, ihi, b_A, ilo, ihi, V, work);
          if (j == 0) {
            xztrevc3(b_A, V);
            if (ilo != ihi) {
              for (b_i = ilo; b_i <= ihi; b_i++) {
                temp.re = scale[b_i - 1];
                i = b_i + 6;
                for (k = b_i; k <= i; k += 3) {
                  absxk = V[k - 1].im;
                  s = V[k - 1].re;
                  V[k - 1].re = temp.re * s - 0.0 * absxk;
                  V[k - 1].im = temp.re * absxk + 0.0 * s;
                }
              }
            }
            i = ilo - 1;
            for (b_i = i; b_i >= 1; b_i--) {
              s = scale[b_i - 1];
              if ((int)s != b_i) {
                temp = V[b_i - 1];
                V[b_i - 1] = V[(int)s - 1];
                V[(int)s - 1] = temp;
                temp = V[b_i + 2];
                V[b_i + 2] = V[(int)s + 2];
                V[(int)s + 2] = temp;
                temp = V[b_i + 5];
                V[b_i + 5] = V[(int)s + 5];
                V[(int)s + 5] = temp;
              }
            }
            for (b_i = i1; b_i < 4; b_i++) {
              s = scale[b_i - 1];
              if ((int)s != b_i) {
                temp = V[b_i - 1];
                V[b_i - 1] = V[(int)s - 1];
                V[(int)s - 1] = temp;
                temp = V[b_i + 2];
                V[b_i + 2] = V[(int)s + 2];
                V[(int)s + 2] = temp;
                temp = V[b_i + 5];
                V[b_i + 5] = V[(int)s + 5];
                V[(int)s + 5] = temp;
              }
            }
            for (b_i = 0; b_i < 3; b_i++) {
              double br;
              in = b_i * 3;
              itau = b_i * 3 + 1;
              temp.re = 1.0 / xnrm2(3, V, itau);
              i = in + 3;
              for (k = in + 1; k <= i; k++) {
                absxk = V[k - 1].im;
                s = V[k - 1].re;
                V[k - 1].re = temp.re * s - 0.0 * absxk;
                V[k - 1].im = temp.re * absxk + 0.0 * s;
              }
              absxk = V[3 * b_i].re;
              s = V[3 * b_i].im;
              scale[0] = absxk * absxk + s * s;
              absxk = V[itau].re;
              s = V[itau].im;
              scale[1] = absxk * absxk + s * s;
              itau = 3 * b_i + 2;
              absxk = V[itau].re;
              s = V[itau].im;
              scale[2] = absxk * absxk + s * s;
              k = 0;
              absxk = fabs(scale[0]);
              s = fabs(scale[1]);
              if (s > absxk) {
                k = 1;
                absxk = s;
              }
              if (fabs(scale[2]) > absxk) {
                k = 2;
              }
              itau = k + 3 * b_i;
              absxk = V[itau].re;
              s = -V[itau].im;
              br = sqrt(scale[k]);
              if (s == 0.0) {
                temp.re = absxk / br;
                temp.im = 0.0;
              } else if (absxk == 0.0) {
                temp.re = 0.0;
                temp.im = s / br;
              } else {
                temp.re = absxk / br;
                temp.im = s / br;
              }
              for (k = in + 1; k <= i; k++) {
                absxk = V[k - 1].im;
                s = V[k - 1].re;
                V[k - 1].re = temp.re * s - temp.im * absxk;
                V[k - 1].im = temp.re * absxk + temp.im * s;
              }
              V[itau].im = 0.0;
            }
          } else {
            for (i = 0; i < 9; i++) {
              V[i].re = rtNaN;
              V[i].im = 0.0;
            }
          }
          if (scalea) {
            b_xzlascl(cscale, anrm, 3 - j, work, j + 1);
            if (j != 0) {
              b_xzlascl(cscale, anrm, ilo - 1, work, 1);
            }
          }
          if (j != 0) {
            for (b_i = ilo; b_i <= j; b_i++) {
              work[b_i - 1].re = rtNaN;
              work[b_i - 1].im = 0.0;
            }
          }
        }
        memset(&D[0], 0, 9U * sizeof(creal_T));
        D[0] = work[0];
        D[4] = work[1];
        D[8] = work[2];
      }
    }
  }
}

/* End of code generation (eig.c) */
