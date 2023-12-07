/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgemv.c
 *
 * Code generation for function 'xgemv'
 *
 */

/* Include files */
#include "xgemv.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void xgemv(int m, int n, const creal_T A[9], int ia0, const creal_T x[9],
           int ix0, creal_T y[3])
{
  int ia;
  int iac;
  if (n != 0) {
    int i;
    i = (unsigned char)n;
    memset(&y[0], 0, (unsigned int)i * sizeof(creal_T));
    i = ia0 + 3 * (n - 1);
    for (iac = ia0; iac <= i; iac += 3) {
      double c_im;
      double c_re;
      int i1;
      c_re = 0.0;
      c_im = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        double b_c_re_tmp;
        double c_c_re_tmp;
        double c_re_tmp;
        double d_c_re_tmp;
        int c_re_tmp_tmp;
        c_re_tmp = A[ia - 1].re;
        c_re_tmp_tmp = ((ix0 + ia) - iac) - 1;
        b_c_re_tmp = x[c_re_tmp_tmp].im;
        c_c_re_tmp = A[ia - 1].im;
        d_c_re_tmp = x[c_re_tmp_tmp].re;
        c_re += c_re_tmp * d_c_re_tmp + c_c_re_tmp * b_c_re_tmp;
        c_im += c_re_tmp * b_c_re_tmp - c_c_re_tmp * d_c_re_tmp;
      }
      i1 = div_nde_s32_floor(iac - ia0);
      y[i1].re += c_re - 0.0 * c_im;
      y[i1].im += c_im + 0.0 * c_re;
    }
  }
}

/* End of code generation (xgemv.c) */
