/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * rcond.c
 *
 * Code generation for function 'rcond'
 *
 */

/* Include files */
#include "rcond.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
double rcond(const creal_T A[9], double normA)
{
  double result;
  int b_i;
  int b_j;
  int jA;
  result = 0.0;
  if (!(normA == 0.0)) {
    jA = 2;
    int exitg1;
    do {
      exitg1 = 0;
      if (jA + 1 > 0) {
        int ix;
        ix = jA + 3 * jA;
        if ((A[ix].re == 0.0) && (A[ix].im == 0.0)) {
          exitg1 = 1;
        } else {
          jA--;
        }
      } else {
        creal_T x[3];
        double ainvnm;
        int iter;
        int j;
        int jump;
        int kase;
        ainvnm = 0.0;
        iter = 2;
        kase = 1;
        jump = 1;
        j = 0;
        x[0].re = 0.33333333333333331;
        x[0].im = 0.0;
        x[1].re = 0.33333333333333331;
        x[1].im = 0.0;
        x[2].re = 0.33333333333333331;
        x[2].im = 0.0;
        int exitg2;
        do {
          double absrexk;
          double re;
          double temp;
          double temp_re_tmp;
          exitg2 = 0;
          if (kase == 1) {
            double b_temp_re_tmp;
            int ix;
            int x_re_tmp_tmp;
            for (b_j = 0; b_j < 3; b_j++) {
              int i;
              jA = b_j + b_j * 3;
              i = 1 - b_j;
              for (b_i = 0; b_i <= i; b_i++) {
                ix = (b_j + b_i) + 1;
                temp = x[b_j].re;
                x_re_tmp_tmp = (jA + b_i) + 1;
                absrexk = A[x_re_tmp_tmp].im;
                temp_re_tmp = x[b_j].im;
                b_temp_re_tmp = A[x_re_tmp_tmp].re;
                x[ix].re -= temp * b_temp_re_tmp - temp_re_tmp * absrexk;
                x[ix].im -= temp * absrexk + temp_re_tmp * b_temp_re_tmp;
              }
            }
            for (b_j = 2; b_j >= 0; b_j--) {
              double temp_im;
              double temp_re;
              jA = b_j + b_j * 3;
              temp_re = x[b_j].re;
              temp_im = x[b_j].im;
              temp_re_tmp = A[jA].re;
              b_temp_re_tmp = A[jA].im;
              if (b_temp_re_tmp == 0.0) {
                if (temp_im == 0.0) {
                  re = temp_re / temp_re_tmp;
                  temp = 0.0;
                } else if (temp_re == 0.0) {
                  re = 0.0;
                  temp = temp_im / temp_re_tmp;
                } else {
                  re = temp_re / temp_re_tmp;
                  temp = temp_im / temp_re_tmp;
                }
              } else if (temp_re_tmp == 0.0) {
                if (temp_re == 0.0) {
                  re = temp_im / b_temp_re_tmp;
                  temp = 0.0;
                } else if (temp_im == 0.0) {
                  re = 0.0;
                  temp = -(temp_re / b_temp_re_tmp);
                } else {
                  re = temp_im / b_temp_re_tmp;
                  temp = -(temp_re / b_temp_re_tmp);
                }
              } else {
                double brm;
                brm = fabs(temp_re_tmp);
                temp = fabs(b_temp_re_tmp);
                if (brm > temp) {
                  absrexk = b_temp_re_tmp / temp_re_tmp;
                  temp = temp_re_tmp + absrexk * b_temp_re_tmp;
                  re = (temp_re + absrexk * temp_im) / temp;
                  temp = (temp_im - absrexk * temp_re) / temp;
                } else if (temp == brm) {
                  if (temp_re_tmp > 0.0) {
                    absrexk = 0.5;
                  } else {
                    absrexk = -0.5;
                  }
                  if (b_temp_re_tmp > 0.0) {
                    temp = 0.5;
                  } else {
                    temp = -0.5;
                  }
                  re = (temp_re * absrexk + temp_im * temp) / brm;
                  temp = (temp_im * absrexk - temp_re * temp) / brm;
                } else {
                  absrexk = temp_re_tmp / b_temp_re_tmp;
                  temp = b_temp_re_tmp + absrexk * temp_re_tmp;
                  re = (absrexk * temp_re + temp_im) / temp;
                  temp = (absrexk * temp_im - temp_re) / temp;
                }
              }
              x[b_j].re = re;
              x[b_j].im = temp;
              for (b_i = 0; b_i < b_j; b_i++) {
                ix = (b_j - b_i) - 1;
                temp = x[b_j].re;
                x_re_tmp_tmp = (jA - b_i) - 1;
                absrexk = A[x_re_tmp_tmp].im;
                temp_re_tmp = x[b_j].im;
                b_temp_re_tmp = A[x_re_tmp_tmp].re;
                x[ix].re -= temp * b_temp_re_tmp - temp_re_tmp * absrexk;
                x[ix].im -= temp * absrexk + temp_re_tmp * b_temp_re_tmp;
              }
            }
          } else {
            double b_temp_re_tmp;
            double temp_im;
            double temp_re;
            int ix;
            for (b_j = 0; b_j < 3; b_j++) {
              jA = b_j * 3;
              temp_re = x[b_j].re;
              temp_im = x[b_j].im;
              for (b_i = 0; b_i < b_j; b_i++) {
                ix = jA + b_i;
                temp = A[ix].re;
                absrexk = A[ix].im;
                temp_re_tmp = x[b_i].im;
                b_temp_re_tmp = x[b_i].re;
                temp_re -= temp * b_temp_re_tmp + absrexk * temp_re_tmp;
                temp_im -= temp * temp_re_tmp - absrexk * b_temp_re_tmp;
              }
              ix = jA + b_j;
              temp_re_tmp = A[ix].re;
              b_temp_re_tmp = -A[ix].im;
              if (b_temp_re_tmp == 0.0) {
                if (temp_im == 0.0) {
                  x[b_j].re = temp_re / temp_re_tmp;
                  x[b_j].im = 0.0;
                } else if (temp_re == 0.0) {
                  x[b_j].re = 0.0;
                  x[b_j].im = temp_im / temp_re_tmp;
                } else {
                  x[b_j].re = temp_re / temp_re_tmp;
                  x[b_j].im = temp_im / temp_re_tmp;
                }
              } else if (temp_re_tmp == 0.0) {
                if (temp_re == 0.0) {
                  x[b_j].re = temp_im / b_temp_re_tmp;
                  x[b_j].im = 0.0;
                } else if (temp_im == 0.0) {
                  x[b_j].re = 0.0;
                  x[b_j].im = -(temp_re / b_temp_re_tmp);
                } else {
                  x[b_j].re = temp_im / b_temp_re_tmp;
                  x[b_j].im = -(temp_re / b_temp_re_tmp);
                }
              } else {
                double brm;
                brm = fabs(temp_re_tmp);
                temp = fabs(b_temp_re_tmp);
                if (brm > temp) {
                  absrexk = b_temp_re_tmp / temp_re_tmp;
                  temp = temp_re_tmp + absrexk * b_temp_re_tmp;
                  x[b_j].re = (temp_re + absrexk * temp_im) / temp;
                  x[b_j].im = (temp_im - absrexk * temp_re) / temp;
                } else if (temp == brm) {
                  if (temp_re_tmp > 0.0) {
                    absrexk = 0.5;
                  } else {
                    absrexk = -0.5;
                  }
                  if (b_temp_re_tmp > 0.0) {
                    temp = 0.5;
                  } else {
                    temp = -0.5;
                  }
                  x[b_j].re = (temp_re * absrexk + temp_im * temp) / brm;
                  x[b_j].im = (temp_im * absrexk - temp_re * temp) / brm;
                } else {
                  absrexk = temp_re_tmp / b_temp_re_tmp;
                  temp = b_temp_re_tmp + absrexk * temp_re_tmp;
                  x[b_j].re = (absrexk * temp_re + temp_im) / temp;
                  x[b_j].im = (absrexk * temp_im - temp_re) / temp;
                }
              }
            }
            for (b_j = 2; b_j >= 0; b_j--) {
              int i;
              jA = b_j * 3;
              temp_re = x[b_j].re;
              temp_im = x[b_j].im;
              i = b_j + 2;
              for (b_i = 3; b_i >= i; b_i--) {
                ix = (jA + b_i) - 1;
                temp = A[ix].re;
                absrexk = A[ix].im;
                temp_re_tmp = x[b_i - 1].im;
                b_temp_re_tmp = x[b_i - 1].re;
                temp_re -= temp * b_temp_re_tmp + absrexk * temp_re_tmp;
                temp_im -= temp * temp_re_tmp - absrexk * b_temp_re_tmp;
              }
              x[b_j].re = temp_re;
              x[b_j].im = temp_im;
            }
          }
          if (jump == 1) {
            temp = rt_hypotd_snf(x[0].re, x[0].im);
            absrexk = rt_hypotd_snf(x[1].re, x[1].im);
            temp_re_tmp = rt_hypotd_snf(x[2].re, x[2].im);
            ainvnm = (temp + absrexk) + temp_re_tmp;
            if ((!rtIsInf(ainvnm)) && (!rtIsNaN(ainvnm))) {
              if (temp > 2.2250738585072014E-308) {
                if (x[0].im == 0.0) {
                  re = x[0].re / temp;
                  temp = 0.0;
                } else if (x[0].re == 0.0) {
                  re = 0.0;
                  temp = x[0].im / temp;
                } else {
                  re = x[0].re / temp;
                  temp = x[0].im / temp;
                }
                x[0].re = re;
                x[0].im = temp;
              } else {
                x[0].re = 1.0;
                x[0].im = 0.0;
              }
              if (absrexk > 2.2250738585072014E-308) {
                if (x[1].im == 0.0) {
                  re = x[1].re / absrexk;
                  temp = 0.0;
                } else if (x[1].re == 0.0) {
                  re = 0.0;
                  temp = x[1].im / absrexk;
                } else {
                  re = x[1].re / absrexk;
                  temp = x[1].im / absrexk;
                }
                x[1].re = re;
                x[1].im = temp;
              } else {
                x[1].re = 1.0;
                x[1].im = 0.0;
              }
              if (temp_re_tmp > 2.2250738585072014E-308) {
                if (x[2].im == 0.0) {
                  re = x[2].re / temp_re_tmp;
                  temp = 0.0;
                } else if (x[2].re == 0.0) {
                  re = 0.0;
                  temp = x[2].im / temp_re_tmp;
                } else {
                  re = x[2].re / temp_re_tmp;
                  temp = x[2].im / temp_re_tmp;
                }
                x[2].re = re;
                x[2].im = temp;
              } else {
                x[2].re = 1.0;
                x[2].im = 0.0;
              }
              kase = 2;
              jump = 2;
            } else {
              exitg2 = 1;
            }
          } else if (jump == 2) {
            j = 0;
            temp = fabs(x[0].re);
            absrexk = fabs(x[1].re);
            if (!(absrexk <= temp)) {
              j = 1;
              temp = absrexk;
            }
            if (!(fabs(x[2].re) <= temp)) {
              j = 2;
            }
            iter = 2;
            x[0].re = 0.0;
            x[0].im = 0.0;
            x[1].re = 0.0;
            x[1].im = 0.0;
            x[2].re = 0.0;
            x[2].im = 0.0;
            x[j].re = 1.0;
            x[j].im = 0.0;
            kase = 1;
            jump = 3;
          } else if (jump == 3) {
            temp = rt_hypotd_snf(x[0].re, x[0].im);
            absrexk = rt_hypotd_snf(x[1].re, x[1].im);
            temp_re_tmp = rt_hypotd_snf(x[2].re, x[2].im);
            ainvnm = (temp + absrexk) + temp_re_tmp;
            if (ainvnm <= x[0].re) {
              x[0].re = 1.0;
              x[0].im = 0.0;
              x[1].re = -1.5;
              x[1].im = 0.0;
              x[2].re = 2.0;
              x[2].im = 0.0;
              kase = 1;
              jump = 5;
            } else {
              if (temp > 2.2250738585072014E-308) {
                if (x[0].im == 0.0) {
                  re = x[0].re / temp;
                  temp = 0.0;
                } else if (x[0].re == 0.0) {
                  re = 0.0;
                  temp = x[0].im / temp;
                } else {
                  re = x[0].re / temp;
                  temp = x[0].im / temp;
                }
                x[0].re = re;
                x[0].im = temp;
              } else {
                x[0].re = 1.0;
                x[0].im = 0.0;
              }
              if (absrexk > 2.2250738585072014E-308) {
                if (x[1].im == 0.0) {
                  re = x[1].re / absrexk;
                  temp = 0.0;
                } else if (x[1].re == 0.0) {
                  re = 0.0;
                  temp = x[1].im / absrexk;
                } else {
                  re = x[1].re / absrexk;
                  temp = x[1].im / absrexk;
                }
                x[1].re = re;
                x[1].im = temp;
              } else {
                x[1].re = 1.0;
                x[1].im = 0.0;
              }
              if (temp_re_tmp > 2.2250738585072014E-308) {
                if (x[2].im == 0.0) {
                  re = x[2].re / temp_re_tmp;
                  temp = 0.0;
                } else if (x[2].re == 0.0) {
                  re = 0.0;
                  temp = x[2].im / temp_re_tmp;
                } else {
                  re = x[2].re / temp_re_tmp;
                  temp = x[2].im / temp_re_tmp;
                }
                x[2].re = re;
                x[2].im = temp;
              } else {
                x[2].re = 1.0;
                x[2].im = 0.0;
              }
              kase = 2;
              jump = 4;
            }
          } else if (jump == 4) {
            jA = j;
            j = 0;
            temp = fabs(x[0].re);
            absrexk = fabs(x[1].re);
            if (!(absrexk <= temp)) {
              j = 1;
              temp = absrexk;
            }
            if (!(fabs(x[2].re) <= temp)) {
              j = 2;
            }
            if ((rt_hypotd_snf(x[jA].re, x[jA].im) !=
                 rt_hypotd_snf(x[j].re, x[j].im)) &&
                (iter <= 5)) {
              iter++;
              x[0].re = 0.0;
              x[0].im = 0.0;
              x[1].re = 0.0;
              x[1].im = 0.0;
              x[2].re = 0.0;
              x[2].im = 0.0;
              x[j].re = 1.0;
              x[j].im = 0.0;
              kase = 1;
              jump = 3;
            } else {
              x[0].re = 1.0;
              x[0].im = 0.0;
              x[1].re = -1.5;
              x[1].im = 0.0;
              x[2].re = 2.0;
              x[2].im = 0.0;
              kase = 1;
              jump = 5;
            }
          } else if (jump == 5) {
            temp = 2.0 *
                   ((rt_hypotd_snf(x[0].re, x[0].im) +
                     rt_hypotd_snf(x[1].re, x[1].im)) +
                    rt_hypotd_snf(x[2].re, x[2].im)) /
                   3.0 / 3.0;
            if (temp > ainvnm) {
              ainvnm = temp;
            }
            exitg2 = 1;
          }
        } while (exitg2 == 0);
        if (ainvnm != 0.0) {
          result = 1.0 / ainvnm / normA;
        }
        if (rtIsNaN(result)) {
          boolean_T p;
          p = false;
          for (jA = 0; jA < 9; jA++) {
            if (p || (rtIsNaN(A[jA].re) || rtIsNaN(A[jA].im))) {
              p = true;
            }
          }
          if (!p) {
            result = 0.0;
          }
        }
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return result;
}

/* End of code generation (rcond.c) */
