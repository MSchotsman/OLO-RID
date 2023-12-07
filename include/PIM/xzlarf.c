/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlarf.c
 *
 * Code generation for function 'xzlarf'
 *
 */

/* Include files */
#include "xzlarf.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "xgerc.h"
#include <string.h>

/* Function Definitions */
void b_xzlarf(int m, int n, int iv0, const creal_T tau, creal_T C[9], int ic0,
              creal_T work[3])
{
  int i;
  int iac;
  int jA;
  int lastc;
  int lastv;
  if ((tau.re != 0.0) || (tau.im != 0.0)) {
    boolean_T exitg2;
    lastv = n;
    i = iv0 + n;
    while ((lastv > 0) && ((C[i - 2].re == 0.0) && (C[i - 2].im == 0.0))) {
      lastv--;
      i--;
    }
    lastc = m;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      int exitg1;
      i = (ic0 + lastc) - 1;
      jA = i;
      do {
        exitg1 = 0;
        if (jA <= i + (lastv - 1) * 3) {
          if ((C[jA - 1].re != 0.0) || (C[jA - 1].im != 0.0)) {
            exitg1 = 1;
          } else {
            jA += 3;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);
      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }
  if (lastv > 0) {
    double c_im;
    double c_re;
    double c_re_tmp;
    double temp_im;
    int b_i;
    int i1;
    if (lastc != 0) {
      b_i = (unsigned char)lastc;
      memset(&work[0], 0, (unsigned int)b_i * sizeof(creal_T));
      b_i = ic0 + 3 * (lastv - 1);
      for (iac = ic0; iac <= b_i; iac += 3) {
        i = (iv0 + div_nde_s32_floor(iac - ic0)) - 1;
        temp_im = C[i].im;
        c_re_tmp = C[i].re;
        c_re = c_re_tmp - 0.0 * temp_im;
        c_im = temp_im + 0.0 * c_re_tmp;
        i1 = (iac + lastc) - 1;
        for (jA = iac; jA <= i1; jA++) {
          temp_im = C[jA - 1].re;
          c_re_tmp = C[jA - 1].im;
          i = jA - iac;
          work[i].re += temp_im * c_re - c_re_tmp * c_im;
          work[i].im += temp_im * c_im + c_re_tmp * c_re;
        }
      }
    }
    c_re = -tau.re;
    c_im = -tau.im;
    if ((!(-tau.re == 0.0)) || (!(-tau.im == 0.0))) {
      jA = ic0;
      b_i = (unsigned char)lastv;
      for (lastv = 0; lastv < b_i; lastv++) {
        i = (iv0 + lastv) - 1;
        temp_im = C[i].re;
        c_re_tmp = C[i].im;
        if ((temp_im != 0.0) || (c_re_tmp != 0.0)) {
          double temp_re;
          temp_re = temp_im * c_re + c_re_tmp * c_im;
          temp_im = temp_im * c_im - c_re_tmp * c_re;
          i1 = lastc + jA;
          for (iac = jA; iac < i1; iac++) {
            double work_re_tmp;
            i = iac - jA;
            c_re_tmp = work[i].re;
            work_re_tmp = work[i].im;
            C[iac - 1].re += c_re_tmp * temp_re - work_re_tmp * temp_im;
            C[iac - 1].im += c_re_tmp * temp_im + work_re_tmp * temp_re;
          }
        }
        jA += 3;
      }
    }
  }
}

void xzlarf(int m, int n, int iv0, const creal_T tau, creal_T C[9], int ic0,
            creal_T work[3])
{
  int lastc;
  int lastv;
  if ((tau.re != 0.0) || (tau.im != 0.0)) {
    boolean_T exitg2;
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) &&
           ((C[lastc - 2].re == 0.0) && (C[lastc - 2].im == 0.0))) {
      lastv--;
      lastc--;
    }
    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      int coltop;
      int exitg1;
      int ia;
      coltop = ic0 + (lastc - 1) * 3;
      ia = coltop;
      do {
        exitg1 = 0;
        if (ia <= (coltop + lastv) - 1) {
          if ((C[ia - 1].re != 0.0) || (C[ia - 1].im != 0.0)) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);
      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }
  if (lastv > 0) {
    creal_T b_tau;
    xgemv(lastv, lastc, C, ic0, C, iv0, work);
    b_tau.re = -tau.re;
    b_tau.im = -tau.im;
    xgerc(lastv, lastc, b_tau, iv0, work, C, ic0);
  }
}

/* End of code generation (xzlarf.c) */
