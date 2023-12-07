/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * trisolve.c
 *
 * Code generation for function 'trisolve'
 *
 */

/* Include files */
#include "trisolve.h"
#include "correlatedRelease_data.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void trisolve(const creal_T A[9], creal_T B[9])
{
  int i;
  int j;
  int k;
  for (j = 0; j < 3; j++) {
    int jBcol;
    jBcol = 3 * j;
    for (k = 2; k >= 0; k--) {
      double B_tmp_tmp_tmp;
      double b_B_tmp_tmp_tmp;
      int B_tmp_tmp;
      int kAcol;
      kAcol = 3 * k;
      B_tmp_tmp = k + jBcol;
      B_tmp_tmp_tmp = B[B_tmp_tmp].re;
      b_B_tmp_tmp_tmp = B[B_tmp_tmp].im;
      if ((B_tmp_tmp_tmp != 0.0) || (b_B_tmp_tmp_tmp != 0.0)) {
        double bi;
        double br;
        double brm;
        double im;
        double re;
        double sgnbr;
        int br_tmp;
        br_tmp = k + kAcol;
        br = A[br_tmp].re;
        bi = A[br_tmp].im;
        if (bi == 0.0) {
          if (b_B_tmp_tmp_tmp == 0.0) {
            re = B_tmp_tmp_tmp / br;
            im = 0.0;
          } else if (B_tmp_tmp_tmp == 0.0) {
            re = 0.0;
            im = b_B_tmp_tmp_tmp / br;
          } else {
            re = B_tmp_tmp_tmp / br;
            im = b_B_tmp_tmp_tmp / br;
          }
        } else if (br == 0.0) {
          if (B_tmp_tmp_tmp == 0.0) {
            re = b_B_tmp_tmp_tmp / bi;
            im = 0.0;
          } else if (b_B_tmp_tmp_tmp == 0.0) {
            re = 0.0;
            im = -(B_tmp_tmp_tmp / bi);
          } else {
            re = b_B_tmp_tmp_tmp / bi;
            im = -(B_tmp_tmp_tmp / bi);
          }
        } else {
          brm = fabs(br);
          im = fabs(bi);
          if (brm > im) {
            brm = bi / br;
            im = br + brm * bi;
            re = (B_tmp_tmp_tmp + brm * b_B_tmp_tmp_tmp) / im;
            im = (b_B_tmp_tmp_tmp - brm * B_tmp_tmp_tmp) / im;
          } else if (im == brm) {
            if (br > 0.0) {
              sgnbr = 0.5;
            } else {
              sgnbr = -0.5;
            }
            if (bi > 0.0) {
              im = 0.5;
            } else {
              im = -0.5;
            }
            re = (B_tmp_tmp_tmp * sgnbr + b_B_tmp_tmp_tmp * im) / brm;
            im = (b_B_tmp_tmp_tmp * sgnbr - B_tmp_tmp_tmp * im) / brm;
          } else {
            brm = br / bi;
            im = bi + brm * br;
            re = (brm * B_tmp_tmp_tmp + b_B_tmp_tmp_tmp) / im;
            im = (brm * b_B_tmp_tmp_tmp - B_tmp_tmp_tmp) / im;
          }
        }
        B[B_tmp_tmp].re = re;
        B[B_tmp_tmp].im = im;
        for (i = 0; i < k; i++) {
          im = B[B_tmp_tmp].re;
          br_tmp = i + kAcol;
          brm = A[br_tmp].im;
          sgnbr = B[B_tmp_tmp].im;
          br = A[br_tmp].re;
          br_tmp = i + jBcol;
          B[br_tmp].re -= im * br - sgnbr * brm;
          B[br_tmp].im -= im * brm + sgnbr * br;
        }
      }
    }
  }
}

/* End of code generation (trisolve.c) */
