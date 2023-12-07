/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xztrevc3.c
 *
 * Code generation for function 'xztrevc3'
 *
 */

/* Include files */
#include "xztrevc3.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "xzladiv.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void xztrevc3(creal_T T[9], creal_T vr[9])
{
  creal_T diagonalElements[3];
  creal_T work[3];
  double rwork[3];
  double smin;
  int imax;
  int j;
  int k;
  int kend;
  int ki;
  diagonalElements[0] = T[0];
  diagonalElements[1] = T[4];
  diagonalElements[2] = T[8];
  rwork[0] = 0.0;
  for (j = 0; j < 2; j++) {
    imax = (j + 1) * 3 + 1;
    smin = 0.0;
    kend = imax + j;
    for (k = imax; k <= kend; k++) {
      smin += fabs(T[k - 1].re) + fabs(T[k - 1].im);
    }
    rwork[j + 1] = smin;
  }
  for (ki = 2; ki >= 0; ki--) {
    double temp_re;
    double tjj;
    double xbnd;
    int i;
    imax = ki + 3 * ki;
    smin = fmax(2.2204460492503131E-16 * (fabs(T[imax].re) + fabs(T[imax].im)),
                3.0062525400134592E-292);
    work[ki].re = 1.0;
    work[ki].im = 0.0;
    for (k = 0; k < ki; k++) {
      i = k + 3 * ki;
      work[k].re = -T[i].re;
      work[k].im = -T[i].im;
    }
    for (k = 0; k < ki; k++) {
      i = k + 3 * k;
      T[i].re -= T[imax].re;
      T[i].im -= T[imax].im;
      if (fabs(T[i].re) + fabs(T[i].im) < smin) {
        T[i].re = smin;
        T[i].im = 0.0;
      }
    }
    if (ki + 1 > 1) {
      double cnorm[3];
      double scale;
      double tscal;
      double xmax;
      int iy0;
      boolean_T gotoSolver;
      cnorm[0] = 0.0;
      cnorm[1] = rwork[1];
      cnorm[2] = rwork[2];
      scale = 1.0;
      imax = 0;
      if ((ki > 1) && (rwork[1] > 0.0)) {
        imax = 1;
      }
      if (rwork[imax] <= 4.9896007738368E+291) {
        tscal = 1.0;
      } else {
        tscal = 0.5 / (1.0020841800044864E-292 * rwork[imax]);
        for (k = 0; k < ki; k++) {
          cnorm[k] *= tscal;
        }
      }
      xmax = 0.0;
      for (j = 0; j < ki; j++) {
        xmax = fmax(xmax, fabs(work[j].re / 2.0) + fabs(work[j].im / 2.0));
      }
      gotoSolver = false;
      if (tscal != 1.0) {
        smin = 0.0;
      } else {
        boolean_T exitg1;
        smin = 0.5 / fmax(xmax, 1.0020841800044864E-292);
        xbnd = smin;
        j = ki - 1;
        exitg1 = false;
        while ((!exitg1) && (j + 1 > 0)) {
          if (smin <= 1.0020841800044864E-292) {
            gotoSolver = true;
            exitg1 = true;
          } else {
            imax = j + 3 * j;
            tjj = fabs(T[imax].re) + fabs(T[imax].im);
            if (tjj >= 1.0020841800044864E-292) {
              xbnd = fmin(xbnd, fmin(1.0, tjj) * smin);
            } else {
              xbnd = 0.0;
            }
            temp_re = tjj + cnorm[j];
            if (temp_re >= 1.0020841800044864E-292) {
              smin *= tjj / temp_re;
            } else {
              smin = 0.0;
            }
            j--;
          }
        }
        if (!gotoSolver) {
          smin = xbnd;
        }
      }
      if (smin * tscal > 1.0020841800044864E-292) {
        for (j = ki; j >= 1; j--) {
          xmax = work[j - 1].re;
          tscal = work[j - 1].im;
          if ((xmax != 0.0) || (tscal != 0.0)) {
            double re;
            kend = 3 * (j - 1);
            imax = (j + kend) - 1;
            xbnd = T[imax].re;
            temp_re = T[imax].im;
            if (temp_re == 0.0) {
              if (tscal == 0.0) {
                re = xmax / xbnd;
                smin = 0.0;
              } else if (xmax == 0.0) {
                re = 0.0;
                smin = tscal / xbnd;
              } else {
                re = xmax / xbnd;
                smin = tscal / xbnd;
              }
            } else if (xbnd == 0.0) {
              if (xmax == 0.0) {
                re = tscal / temp_re;
                smin = 0.0;
              } else if (tscal == 0.0) {
                re = 0.0;
                smin = -(xmax / temp_re);
              } else {
                re = tscal / temp_re;
                smin = -(xmax / temp_re);
              }
            } else {
              tjj = fabs(xbnd);
              smin = fabs(temp_re);
              if (tjj > smin) {
                tjj = temp_re / xbnd;
                smin = xbnd + tjj * temp_re;
                re = (xmax + tjj * tscal) / smin;
                smin = (tscal - tjj * xmax) / smin;
              } else if (smin == tjj) {
                if (xbnd > 0.0) {
                  xbnd = 0.5;
                } else {
                  xbnd = -0.5;
                }
                if (temp_re > 0.0) {
                  smin = 0.5;
                } else {
                  smin = -0.5;
                }
                re = (xmax * xbnd + tscal * smin) / tjj;
                smin = (tscal * xbnd - xmax * smin) / tjj;
              } else {
                tjj = xbnd / temp_re;
                smin = temp_re + tjj * xbnd;
                re = (tjj * xmax + tscal) / smin;
                smin = (tjj * tscal - xmax) / smin;
              }
            }
            work[j - 1].re = re;
            work[j - 1].im = smin;
            i = j - 1;
            for (imax = i; imax >= 1; imax--) {
              xbnd = T[kend].im;
              tjj = T[kend].re;
              work[0].re -= re * tjj - smin * xbnd;
              work[0].im -= re * xbnd + smin * tjj;
            }
          }
        }
      } else {
        if (xmax > 4.9896007738368E+291) {
          scale = 4.9896007738368E+291 / xmax;
          for (k = 0; k < ki; k++) {
            xbnd = work[k].im;
            tjj = work[k].re;
            work[k].re = scale * tjj - 0.0 * xbnd;
            work[k].im = scale * xbnd + 0.0 * tjj;
          }
          xmax = 9.9792015476736E+291;
        } else {
          xmax *= 2.0;
        }
        for (j = ki; j >= 1; j--) {
          creal_T tjjs;
          smin = fabs(work[j - 1].re) + fabs(work[j - 1].im);
          imax = (j + 3 * (j - 1)) - 1;
          tjjs.re = tscal * T[imax].re;
          tjjs.im = tscal * T[imax].im;
          tjj = fabs(tjjs.re) + fabs(tjjs.im);
          if (tjj > 1.0020841800044864E-292) {
            if ((tjj < 1.0) && (smin > tjj * 9.9792015476736E+291)) {
              smin = 1.0 / smin;
              for (k = 0; k < ki; k++) {
                xbnd = work[k].im;
                tjj = work[k].re;
                work[k].re = smin * tjj - 0.0 * xbnd;
                work[k].im = smin * xbnd + 0.0 * tjj;
              }
              scale *= smin;
              xmax *= smin;
            }
            tjjs = xzladiv(work[j - 1], tjjs);
            work[j - 1] = tjjs;
            smin = fabs(tjjs.re) + fabs(tjjs.im);
          } else if (tjj > 0.0) {
            if (smin > tjj * 9.9792015476736E+291) {
              smin = tjj * 9.9792015476736E+291 / smin;
              temp_re = cnorm[j - 1];
              if (temp_re > 1.0) {
                smin /= temp_re;
              }
              for (k = 0; k < ki; k++) {
                xbnd = work[k].im;
                tjj = work[k].re;
                work[k].re = smin * tjj - 0.0 * xbnd;
                work[k].im = smin * xbnd + 0.0 * tjj;
              }
              scale *= smin;
              xmax *= smin;
            }
            tjjs = xzladiv(work[j - 1], tjjs);
            work[j - 1] = tjjs;
            smin = fabs(tjjs.re) + fabs(tjjs.im);
          } else {
            for (imax = 0; imax < ki; imax++) {
              work[imax].re = 0.0;
              work[imax].im = 0.0;
            }
            work[j - 1].re = 1.0;
            work[j - 1].im = 0.0;
            smin = 1.0;
            scale = 0.0;
            xmax = 0.0;
          }
          if (smin > 1.0) {
            smin = 1.0 / smin;
            if (cnorm[j - 1] > (9.9792015476736E+291 - xmax) * smin) {
              smin *= 0.5;
              for (k = 0; k < ki; k++) {
                xbnd = work[k].im;
                tjj = work[k].re;
                work[k].re = smin * tjj - 0.0 * xbnd;
                work[k].im = smin * xbnd + 0.0 * tjj;
              }
              scale *= smin;
            }
          } else if (smin * cnorm[j - 1] > 9.9792015476736E+291 - xmax) {
            for (k = 0; k < ki; k++) {
              xbnd = work[k].im;
              tjj = work[k].re;
              work[k].re = 0.5 * tjj - 0.0 * xbnd;
              work[k].im = 0.5 * xbnd + 0.0 * tjj;
            }
            scale *= 0.5;
          }
          if (j > 1) {
            temp_re = tscal * -work[1].re;
            tjj = tscal * -work[1].im;
            if ((!(temp_re == 0.0)) || (!(tjj == 0.0))) {
              work[0].re += temp_re * T[3].re - tjj * T[3].im;
              work[0].im += temp_re * T[3].im + tjj * T[3].re;
            }
            xmax = fabs(work[0].re) + fabs(work[0].im);
          }
        }
        scale /= tscal;
      }
      work[ki].re = scale;
      work[ki].im = 0.0;
      iy0 = ki * 3;
      imax = iy0 + 3;
      if (scale != 1.0) {
        if (scale == 0.0) {
          if (iy0 + 1 <= imax) {
            memset(&vr[iy0], 0, (unsigned int)(imax - iy0) * sizeof(creal_T));
          }
        } else {
          for (kend = iy0 + 1; kend <= imax; kend++) {
            xbnd = vr[kend - 1].im;
            tjj = vr[kend - 1].re;
            vr[kend - 1].re = scale * tjj - 0.0 * xbnd;
            vr[kend - 1].im = scale * xbnd + 0.0 * tjj;
          }
        }
      }
      i = 3 * (ki - 1) + 1;
      for (j = 1; j <= i; j += 3) {
        imax = div_nde_s32_floor(j - 1);
        smin = work[imax].im;
        xbnd = work[imax].re;
        temp_re = xbnd - 0.0 * smin;
        tjj = smin + 0.0 * xbnd;
        imax = j + 2;
        for (k = j; k <= imax; k++) {
          smin = vr[k - 1].re;
          xbnd = vr[k - 1].im;
          kend = (iy0 + k) - j;
          vr[kend].re += smin * temp_re - xbnd * tjj;
          vr[kend].im += smin * tjj + xbnd * temp_re;
        }
      }
    }
    kend = ki * 3;
    imax = 0;
    smin = fabs(vr[kend].re) + fabs(vr[kend].im);
    tjj = fabs(vr[kend + 1].re) + fabs(vr[kend + 1].im);
    if (tjj > smin) {
      imax = 1;
      smin = tjj;
    }
    if (fabs(vr[kend + 2].re) + fabs(vr[kend + 2].im) > smin) {
      imax = 2;
    }
    imax += 3 * ki;
    temp_re = 1.0 / (fabs(vr[imax].re) + fabs(vr[imax].im));
    i = kend + 3;
    for (k = kend + 1; k <= i; k++) {
      xbnd = vr[k - 1].im;
      tjj = vr[k - 1].re;
      vr[k - 1].re = temp_re * tjj - 0.0 * xbnd;
      vr[k - 1].im = temp_re * xbnd + 0.0 * tjj;
    }
    for (k = 0; k < ki; k++) {
      T[k + 3 * k] = diagonalElements[k];
    }
  }
}

/* End of code generation (xztrevc3.c) */
