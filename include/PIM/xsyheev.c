/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xsyheev.c
 *
 * Code generation for function 'xsyheev'
 *
 */

/* Include files */
#include "xsyheev.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "xzlascl.h"
#include "xzsteqr.h"
#include "rt_nonfinite.h"

/* Function Definitions */
int xsyheev(creal_T A[9], double W[3])
{
  creal_T temp1;
  double absx;
  double anrm;
  int b_i;
  int i;
  int ii;
  int info;
  int j;
  int jj;
  int temp1_tmp_tmp_tmp;
  boolean_T exitg2;
  info = 0;
  anrm = 0.0;
  j = 0;
  exitg2 = false;
  while ((!exitg2) && (j < 3)) {
    int exitg1;
    i = 0;
    do {
      exitg1 = 0;
      if (i <= j) {
        temp1 = A[i + 3 * j];
        absx = rt_hypotd_snf(temp1.re, temp1.im);
        if (rtIsNaN(absx)) {
          anrm = rtNaN;
          exitg1 = 1;
        } else {
          if (absx > anrm) {
            anrm = absx;
          }
          i++;
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
  if (rtIsInf(anrm) || rtIsNaN(anrm)) {
    W[0] = rtNaN;
    W[1] = rtNaN;
    W[2] = rtNaN;
    for (b_i = 0; b_i < 9; b_i++) {
      A[b_i].re = rtNaN;
      A[b_i].im = 0.0;
    }
  } else {
    creal_T work[3];
    creal_T tau[2];
    double e[2];
    double temp2_re;
    int i1;
    int iaii;
    boolean_T iscale;
    iscale = false;
    if ((anrm > 0.0) && (anrm < 1.0010415475915505E-146)) {
      iscale = true;
      anrm = 1.0010415475915505E-146 / anrm;
      xzlascl(1.0, anrm, A);
    } else if (anrm > 9.9895953610111751E+145) {
      iscale = true;
      anrm = 9.9895953610111751E+145 / anrm;
      xzlascl(1.0, anrm, A);
    }
    A[0].im = 0.0;
    for (i = 0; i < 2; i++) {
      creal_T taui;
      int temp1_tmp_tmp;
      temp1_tmp_tmp = i + 3 * i;
      temp1 = A[temp1_tmp_tmp + 1];
      taui = xzlarfg(2 - i, &temp1, A, i * 3 + 3);
      e[i] = temp1.re;
      if ((taui.re != 0.0) || (taui.im != 0.0)) {
        double A_re_tmp;
        double b_A_re_tmp;
        double temp1_tmp;
        double temp2_im;
        int i2;
        A[(i + 3 * i) + 1].re = 1.0;
        A[(i + 3 * i) + 1].im = 0.0;
        for (j = i + 1; j < 3; j++) {
          tau[j - 1].re = 0.0;
          tau[j - 1].im = 0.0;
        }
        b_i = 1 - i;
        i1 = 2 - i;
        for (jj = 0; jj <= b_i; jj++) {
          temp1_tmp_tmp_tmp = i + jj;
          j = (temp1_tmp_tmp_tmp + 3 * i) + 1;
          temp1_tmp = A[j].im;
          absx = A[j].re;
          temp1.re = taui.re * absx - taui.im * temp1_tmp;
          temp1.im = taui.re * temp1_tmp + taui.im * absx;
          temp2_re = 0.0;
          temp2_im = 0.0;
          i2 = 3 * (temp1_tmp_tmp_tmp + 1);
          absx = A[(temp1_tmp_tmp_tmp + i2) + 1].re;
          tau[temp1_tmp_tmp_tmp].re += temp1.re * absx;
          tau[temp1_tmp_tmp_tmp].im += temp1.im * absx;
          iaii = jj + 2;
          for (ii = iaii; ii <= i1; ii++) {
            absx = A[i2 + 2].im;
            temp1_tmp = A[i2 + 2].re;
            tau[1].re += temp1.re * temp1_tmp - temp1.im * absx;
            tau[1].im += temp1.re * absx + temp1.im * temp1_tmp;
            j = 3 * i + 2;
            A_re_tmp = A[j].im;
            b_A_re_tmp = A[j].re;
            temp2_re += temp1_tmp * b_A_re_tmp - -absx * A_re_tmp;
            temp2_im += temp1_tmp * A_re_tmp + -absx * b_A_re_tmp;
          }
          tau[temp1_tmp_tmp_tmp].re += taui.re * temp2_re - taui.im * temp2_im;
          tau[temp1_tmp_tmp_tmp].im += taui.re * temp2_im + taui.im * temp2_re;
        }
        temp1.re = 0.0;
        temp1.im = 0.0;
        for (temp1_tmp_tmp_tmp = 0; temp1_tmp_tmp_tmp <= b_i;
             temp1_tmp_tmp_tmp++) {
          j = i + temp1_tmp_tmp_tmp;
          temp1_tmp = tau[j].re;
          iaii = (temp1_tmp_tmp + temp1_tmp_tmp_tmp) + 1;
          absx = A[iaii].im;
          temp2_re = tau[j].im;
          temp2_im = A[iaii].re;
          temp1.re += temp1_tmp * temp2_im + temp2_re * absx;
          temp1.im += temp1_tmp * absx - temp2_re * temp2_im;
        }
        absx = -0.5 * taui.re;
        temp2_re = -0.5 * taui.im;
        temp2_im = absx * temp1.re - temp2_re * temp1.im;
        temp2_re = absx * temp1.im + temp2_re * temp1.re;
        if ((!(temp2_im == 0.0)) || (!(temp2_re == 0.0))) {
          for (temp1_tmp_tmp_tmp = 0; temp1_tmp_tmp_tmp <= b_i;
               temp1_tmp_tmp_tmp++) {
            j = (temp1_tmp_tmp + temp1_tmp_tmp_tmp) + 1;
            absx = A[j].im;
            temp1_tmp = A[j].re;
            i2 = i + temp1_tmp_tmp_tmp;
            tau[i2].re += temp2_im * temp1_tmp - temp2_re * absx;
            tau[i2].im += temp2_im * absx + temp2_re * temp1_tmp;
          }
        }
        for (jj = 0; jj <= b_i; jj++) {
          j = i + jj;
          iaii = (j + 3 * i) + 1;
          temp1.re = A[iaii].re;
          temp1_tmp = A[iaii].im;
          temp2_re = tau[j].re;
          temp2_im = tau[j].im;
          absx = temp2_re * temp1.re;
          i2 = 3 * (j + 1);
          iaii = (j + i2) + 1;
          A[iaii].re = (A[iaii].re - (absx - temp2_im * -temp1_tmp)) -
                       (absx - temp1_tmp * -temp2_im);
          A[iaii].im = 0.0;
          iaii = jj + 2;
          for (ii = iaii; ii <= i1; ii++) {
            j = 3 * i + 2;
            A_re_tmp = A[j].re;
            b_A_re_tmp = A[j].im;
            A[i2 + 2].re = (A[i2 + 2].re -
                            (tau[1].re * temp1.re - tau[1].im * -temp1_tmp)) -
                           (A_re_tmp * temp2_re - b_A_re_tmp * -temp2_im);
            A[i2 + 2].im = (A[i2 + 2].im -
                            (tau[1].re * -temp1_tmp + tau[1].im * temp1.re)) -
                           (A_re_tmp * -temp2_im + b_A_re_tmp * temp2_re);
          }
        }
      } else {
        A[(i + 3 * (i + 1)) + 1].im = 0.0;
      }
      A[(i + 3 * i) + 1].re = e[i];
      A[(i + 3 * i) + 1].im = 0.0;
      W[i] = A[temp1_tmp_tmp].re;
      tau[i] = taui;
    }
    W[2] = A[8].re;
    for (j = 1; j >= 0; j--) {
      b_i = 3 * (j + 1);
      A[b_i].re = 0.0;
      A[b_i].im = 0.0;
      i1 = j + 3;
      for (i = i1; i < 4; i++) {
        A[b_i + 2] = A[3 * j + 2];
      }
    }
    A[0].re = 1.0;
    A[0].im = 0.0;
    A[1].re = 0.0;
    A[1].im = 0.0;
    A[2].re = 0.0;
    A[2].im = 0.0;
    work[0].re = 0.0;
    work[0].im = 0.0;
    work[1].re = 0.0;
    work[1].im = 0.0;
    work[2].re = 0.0;
    work[2].im = 0.0;
    for (i = 1; i >= 0; i--) {
      iaii = (i + i * 3) + 4;
      if (i + 1 < 2) {
        A[iaii].re = 1.0;
        A[iaii].im = 0.0;
        xzlarf(2, 1, iaii + 1, tau[i], A, iaii + 4, work);
        j = iaii + 2;
        temp1.re = -tau[i].re;
        temp1.im = -tau[i].im;
        for (temp1_tmp_tmp_tmp = j; temp1_tmp_tmp_tmp <= j;
             temp1_tmp_tmp_tmp++) {
          absx = A[temp1_tmp_tmp_tmp - 1].im;
          temp2_re = A[temp1_tmp_tmp_tmp - 1].re;
          A[temp1_tmp_tmp_tmp - 1].re = temp1.re * temp2_re - temp1.im * absx;
          A[temp1_tmp_tmp_tmp - 1].im = temp1.re * absx + temp1.im * temp2_re;
        }
      }
      A[iaii].re = 1.0 - tau[i].re;
      A[iaii].im = 0.0 - tau[i].im;
      for (j = 0; j < i; j++) {
        A[iaii - 1].re = 0.0;
        A[iaii - 1].im = 0.0;
      }
    }
    info = xzsteqr(W, e, A);
    if (info != 0) {
      W[0] = rtNaN;
      W[1] = rtNaN;
      W[2] = rtNaN;
      for (b_i = 0; b_i < 9; b_i++) {
        A[b_i].re = rtNaN;
        A[b_i].im = 0.0;
      }
    } else if (iscale) {
      absx = 1.0 / anrm;
      W[0] *= absx;
      W[1] *= absx;
      W[2] *= absx;
    }
  }
  return info;
}

/* End of code generation (xsyheev.c) */
