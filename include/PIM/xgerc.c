/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgerc.c
 *
 * Code generation for function 'xgerc'
 *
 */

/* Include files */
#include "xgerc.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void xgerc(int m, int n, const creal_T alpha1, int ix0, const creal_T y[3],
           creal_T A[9], int ia0)
{
  int ijA;
  int j;
  if ((!(alpha1.re == 0.0)) || (!(alpha1.im == 0.0))) {
    int i;
    int jA;
    jA = ia0;
    i = (unsigned char)n;
    for (j = 0; j < i; j++) {
      double temp_im;
      double y_tmp;
      temp_im = y[j].re;
      y_tmp = y[j].im;
      if ((temp_im != 0.0) || (y_tmp != 0.0)) {
        double temp_re;
        int i1;
        temp_re = temp_im * alpha1.re + y_tmp * alpha1.im;
        temp_im = temp_im * alpha1.im - y_tmp * alpha1.re;
        i1 = m + jA;
        for (ijA = jA; ijA < i1; ijA++) {
          double A_re_tmp;
          int A_re_tmp_tmp;
          A_re_tmp_tmp = ((ix0 + ijA) - jA) - 1;
          y_tmp = A[A_re_tmp_tmp].re;
          A_re_tmp = A[A_re_tmp_tmp].im;
          A[ijA - 1].re += y_tmp * temp_re - A_re_tmp * temp_im;
          A[ijA - 1].im += y_tmp * temp_im + A_re_tmp * temp_re;
        }
      }
      jA += 3;
    }
  }
}

/* End of code generation (xgerc.c) */
