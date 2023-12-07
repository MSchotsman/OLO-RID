/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * schur.c
 *
 * Code generation for function 'schur'
 *
 */

/* Include files */
#include "schur.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "xgerc.h"
#include "xhseqr.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void schur(const creal_T A[9], creal_T V[9], creal_T T[9])
{
  creal_T alpha1;
  double b_tau_tmp;
  double tau_tmp;
  int i;
  int lastc;
  int lastv;
  boolean_T p;
  p = true;
  for (lastc = 0; lastc < 9; lastc++) {
    if (p) {
      tau_tmp = A[lastc].re;
      b_tau_tmp = A[lastc].im;
      if (rtIsInf(tau_tmp) || rtIsInf(b_tau_tmp) ||
          (rtIsNaN(tau_tmp) || rtIsNaN(b_tau_tmp))) {
        p = false;
      }
    } else {
      p = false;
    }
  }
  if (!p) {
    for (lastc = 0; lastc < 9; lastc++) {
      V[lastc].re = rtNaN;
      V[lastc].im = 0.0;
    }
    lastc = 2;
    for (lastv = 0; lastv < 2; lastv++) {
      if (lastc <= 3) {
        memset(&V[(lastv * 3 + lastc) + -1], 0,
               (unsigned int)(-lastc + 4) * sizeof(creal_T));
      }
      lastc++;
    }
    for (lastc = 0; lastc < 9; lastc++) {
      T[lastc].re = rtNaN;
      T[lastc].im = 0.0;
    }
  } else {
    creal_T work[3];
    creal_T tau[2];
    creal_T dc;
    creal_T dc1;
    int ia;
    memcpy(&T[0], &A[0], 9U * sizeof(creal_T));
    work[0].re = 0.0;
    work[0].im = 0.0;
    work[1].re = 0.0;
    work[1].im = 0.0;
    work[2].re = 0.0;
    work[2].im = 0.0;
    alpha1 = T[1];
    dc = xzlarfg(2, &alpha1, T, 3);
    tau[0] = dc;
    T[1].re = 1.0;
    T[1].im = 0.0;
    b_xzlarf(3, 2, 2, dc, T, 4, work);
    dc1.re = dc.re;
    dc1.im = -dc.im;
    xzlarf(2, 2, 2, dc1, T, 5, work);
    T[1] = alpha1;
    alpha1 = T[5];
    dc = xzlarfg(1, &alpha1, T, 6);
    tau[1] = dc;
    T[5].re = 1.0;
    T[5].im = 0.0;
    b_xzlarf(3, 1, 6, dc, T, 7, work);
    dc1.re = dc.re;
    dc1.im = -dc.im;
    xzlarf(1, 1, 6, dc1, T, 9, work);
    T[5] = alpha1;
    memcpy(&V[0], &T[0], 9U * sizeof(creal_T));
    for (lastv = 1; lastv >= 0; lastv--) {
      ia = (lastv + 1) * 3;
      for (i = 0; i <= lastv; i++) {
        lastc = ia + i;
        V[lastc].re = 0.0;
        V[lastc].im = 0.0;
      }
      lastc = lastv + 3;
      for (i = lastc; i < 4; i++) {
        V[ia + 2] = V[ia - 1];
      }
    }
    V[1].re = 0.0;
    V[1].im = 0.0;
    V[2].re = 0.0;
    V[2].im = 0.0;
    V[0].re = 1.0;
    V[0].im = 0.0;
    work[0].re = 0.0;
    work[0].im = 0.0;
    work[1].re = 0.0;
    work[1].im = 0.0;
    work[2].re = 0.0;
    work[2].im = 0.0;
    for (i = 1; i >= 0; i--) {
      int iaii;
      iaii = (i + i * 3) + 5;
      if (i + 1 < 2) {
        V[iaii - 1].re = 1.0;
        V[iaii - 1].im = 0.0;
        tau_tmp = tau[i].re;
        b_tau_tmp = tau[i].im;
        if ((tau_tmp != 0.0) || (b_tau_tmp != 0.0)) {
          lastv = 2;
          lastc = iaii;
          while ((lastv > 0) &&
                 ((V[lastc].re == 0.0) && (V[lastc].im == 0.0))) {
            lastv--;
            lastc--;
          }
          lastc = 1;
          ia = iaii + 3;
          int exitg1;
          do {
            exitg1 = 0;
            if (ia <= (iaii + lastv) + 2) {
              if ((V[ia - 1].re != 0.0) || (V[ia - 1].im != 0.0)) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc = 0;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        } else {
          lastv = 0;
          lastc = 0;
        }
        if (lastv > 0) {
          xgemv(lastv, lastc, V, iaii + 3, V, iaii, work);
          alpha1.re = -tau_tmp;
          alpha1.im = -b_tau_tmp;
          xgerc(lastv, lastc, alpha1, iaii, work, V, iaii + 3);
        }
        lastv = iaii + 1;
        for (lastc = lastv; lastc <= lastv; lastc++) {
          double b_re_tmp;
          double re_tmp;
          re_tmp = V[lastc - 1].im;
          b_re_tmp = V[lastc - 1].re;
          V[lastc - 1].re = -tau_tmp * b_re_tmp - -b_tau_tmp * re_tmp;
          V[lastc - 1].im = -tau_tmp * re_tmp + -b_tau_tmp * b_re_tmp;
        }
      }
      V[iaii - 1].re = 1.0 - tau[i].re;
      V[iaii - 1].im = 0.0 - tau[i].im;
      if (i - 1 >= 0) {
        V[iaii - 2].re = 0.0;
        V[iaii - 2].im = 0.0;
      }
    }
    xhseqr(T, V);
  }
}

/* End of code generation (schur.c) */
