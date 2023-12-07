/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mpower_schur.c
 *
 * Code generation for function 'mpower_schur'
 *
 */

/* Include files */
#include "mpower_schur.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_rtwutil.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "schur.h"
#include "sqrt.h"
#include "trisolve.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static void powerm2by2(const creal_T A[4], double p, creal_T X[4]);

/* Function Definitions */
static void powerm2by2(const creal_T A[4], double p, creal_T X[4])
{
  creal_T a1p;
  creal_T a2p;
  a1p = b_power(A[0], p);
  a2p = b_power(A[3], p);
  X[1].re = 0.0;
  X[1].im = 0.0;
  X[0] = a1p;
  X[3] = a2p;
  if ((A[0].re == A[3].re) && (A[0].im == A[3].im)) {
    double absz;
    double t;
    a1p = b_power(A[0], p - 1.0);
    t = p * A[2].re;
    absz = p * A[2].im;
    X[2].re = t * a1p.re - absz * a1p.im;
    X[2].im = t * a1p.im + absz * a1p.re;
  } else {
    double absz;
    double ai_tmp;
    double ar_tmp;
    double brm;
    double t;
    double xr;
    double z_im;
    double z_re;
    ar_tmp = A[3].re - A[0].re;
    ai_tmp = A[3].im - A[0].im;
    absz = A[0].re + A[3].re;
    t = A[0].im + A[3].im;
    if (t == 0.0) {
      if (ai_tmp == 0.0) {
        z_re = ar_tmp / absz;
        z_im = 0.0;
      } else if (ar_tmp == 0.0) {
        z_re = 0.0;
        z_im = ai_tmp / absz;
      } else {
        z_re = ar_tmp / absz;
        z_im = ai_tmp / absz;
      }
    } else if (absz == 0.0) {
      if (ar_tmp == 0.0) {
        z_re = ai_tmp / t;
        z_im = 0.0;
      } else if (ai_tmp == 0.0) {
        z_re = 0.0;
        z_im = -(ar_tmp / t);
      } else {
        z_re = ai_tmp / t;
        z_im = -(ar_tmp / t);
      }
    } else {
      brm = fabs(absz);
      xr = fabs(t);
      if (brm > xr) {
        brm = t / absz;
        absz += brm * t;
        z_re = (ar_tmp + brm * ai_tmp) / absz;
        z_im = (ai_tmp - brm * ar_tmp) / absz;
      } else if (xr == brm) {
        if (absz > 0.0) {
          xr = 0.5;
        } else {
          xr = -0.5;
        }
        if (t > 0.0) {
          absz = 0.5;
        } else {
          absz = -0.5;
        }
        z_re = (ar_tmp * xr + ai_tmp * absz) / brm;
        z_im = (ai_tmp * xr - ar_tmp * absz) / brm;
      } else {
        brm = absz / t;
        absz = t + brm * absz;
        z_re = (brm * ar_tmp + ai_tmp) / absz;
        z_im = (brm * ai_tmp - ar_tmp) / absz;
      }
    }
    if (((A[0].im == 0.0) && (A[3].im == 0.0)) ||
        (rt_hypotd_snf(z_re, z_im) > 90.509667991878089) ||
        (rt_hypotd_snf(z_re - 1.0, z_im) < 0.011048543456039804) ||
        (rt_hypotd_snf(z_re + 1.0, z_im) < 0.011048543456039804)) {
      double xi;
      t = a2p.re - a1p.re;
      absz = a2p.im - a1p.im;
      xi = A[2].re * t - A[2].im * absz;
      t = A[2].re * absz + A[2].im * t;
      if (ai_tmp == 0.0) {
        if (t == 0.0) {
          X[2].re = xi / ar_tmp;
          X[2].im = 0.0;
        } else if (xi == 0.0) {
          X[2].re = 0.0;
          X[2].im = t / ar_tmp;
        } else {
          X[2].re = xi / ar_tmp;
          X[2].im = t / ar_tmp;
        }
      } else if (ar_tmp == 0.0) {
        if (xi == 0.0) {
          X[2].re = t / ai_tmp;
          X[2].im = 0.0;
        } else if (t == 0.0) {
          X[2].re = 0.0;
          X[2].im = -(xi / ai_tmp);
        } else {
          X[2].re = t / ai_tmp;
          X[2].im = -(xi / ai_tmp);
        }
      } else {
        brm = fabs(ar_tmp);
        xr = fabs(ai_tmp);
        if (brm > xr) {
          brm = ai_tmp / ar_tmp;
          absz = ar_tmp + brm * ai_tmp;
          X[2].re = (xi + brm * t) / absz;
          X[2].im = (t - brm * xi) / absz;
        } else if (xr == brm) {
          if (ar_tmp > 0.0) {
            xr = 0.5;
          } else {
            xr = -0.5;
          }
          if (ai_tmp > 0.0) {
            absz = 0.5;
          } else {
            absz = -0.5;
          }
          X[2].re = (xi * xr + t * absz) / brm;
          X[2].im = (t * xr - xi * absz) / brm;
        } else {
          brm = ar_tmp / ai_tmp;
          absz = ai_tmp + brm * ar_tmp;
          X[2].re = (brm * xi + t) / absz;
          X[2].im = (brm * t - xi) / absz;
        }
      }
    } else {
      double xi;
      if (A[0].im == 0.0) {
        if (A[0].re < 0.0) {
          a1p.re = log(fabs(A[0].re));
          a1p.im = 3.1415926535897931;
        } else {
          a1p.re = log(fabs(A[0].re));
          a1p.im = 0.0;
        }
      } else if ((fabs(A[0].re) > 8.9884656743115785E+307) ||
                 (fabs(A[0].im) > 8.9884656743115785E+307)) {
        a1p.re = log(rt_hypotd_snf(A[0].re / 2.0, A[0].im / 2.0)) +
                 0.69314718055994529;
        a1p.im = rt_atan2d_snf(A[0].im, A[0].re);
      } else {
        a1p.re = log(rt_hypotd_snf(A[0].re, A[0].im));
        a1p.im = rt_atan2d_snf(A[0].im, A[0].re);
      }
      if (A[3].im == 0.0) {
        if (A[3].re < 0.0) {
          a2p.re = log(fabs(A[3].re));
          a2p.im = 3.1415926535897931;
        } else {
          a2p.re = log(fabs(A[3].re));
          a2p.im = 0.0;
        }
      } else if ((fabs(A[3].re) > 8.9884656743115785E+307) ||
                 (fabs(A[3].im) > 8.9884656743115785E+307)) {
        a2p.re = log(rt_hypotd_snf(A[3].re / 2.0, A[3].im / 2.0)) +
                 0.69314718055994529;
        a2p.im = rt_atan2d_snf(A[3].im, A[3].re);
      } else {
        a2p.re = log(rt_hypotd_snf(A[3].re, A[3].im));
        a2p.im = rt_atan2d_snf(A[3].im, A[3].re);
      }
      xr = fabs(z_re);
      xi = fabs(z_im);
      if ((xr > 3.3519519824856489E+153) || (xi > 3.3519519824856489E+153)) {
        if (xi == 0.0) {
          xr = 1.0 / xr;
        } else if (xr == 0.0) {
          xr = 0.0;
        } else if (xr > xi) {
          brm = xi / xr;
          xr = (brm * 0.0 + 1.0) / (xr + brm * xi);
        } else if (xi == xr) {
          xr = 0.5 / xr;
        } else {
          brm = xr / xi;
          xr = brm / (xi + brm * xr);
        }
        xi = 1.5707963267948966;
      } else if ((xr == 1.0) && (xi == 0.0)) {
        xr = rtInf;
      } else if (xr == 1.0) {
        xr =
            log(sqrt(sqrt(xi * xi + 4.0)) / sqrt(xi + 2.9833362924800834E-154));
        xi = (atan((xi + 2.9833362924800834E-154) / 2.0) + 1.5707963267948966) /
             2.0;
      } else if ((xi == 0.0) && (!(xr > 1.0))) {
        if (xr < 0.5) {
          t = xr + xr;
          t += t * (xr / (1.0 - xr));
          if (!(t < 2.2204460492503131E-16)) {
            t = log(t + 1.0) * (t / ((t + 1.0) - 1.0));
          }
          xr = t / 2.0;
        } else if (xr == 1.0) {
          xr = rtInf;
        } else {
          t = (xr + xr) / (1.0 - xr);
          if ((t > 4.503599627370496E+15) || rtIsNaN(t)) {
            t++;
            t = log(t);
          } else {
            t = log(t + 1.0) * (t / ((t + 1.0) - 1.0));
          }
          xr = t / 2.0;
        }
      } else {
        absz = (xi + 2.9833362924800834E-154) * (xi + 2.9833362924800834E-154);
        xi = rt_atan2d_snf(2.0 * xi, (1.0 - xr) * (xr + 1.0) - absz) / 2.0;
        t = 4.0 * (xr / ((1.0 - xr) * (1.0 - xr) + absz));
        absz = fabs(t);
        if ((absz > 4.503599627370496E+15) || (rtIsInf(t) || rtIsNaN(t))) {
          t++;
          t = log(t);
        } else if (!(absz < 2.2204460492503131E-16)) {
          t = log(t + 1.0) * (t / ((t + 1.0) - 1.0));
        }
        xr = t / 4.0;
      }
      if (z_re < 0.0) {
        xr = -xr;
      }
      if ((z_im < 0.0) || ((z_im == 0.0) && (z_re < -1.0))) {
        xi = -xi;
      }
      t = p * (a1p.re + a2p.re);
      absz = p * (a1p.im + a2p.im);
      if (absz == 0.0) {
        z_re = t / 2.0;
        z_im = 0.0;
      } else if (t == 0.0) {
        z_re = 0.0;
        z_im = absz / 2.0;
      } else {
        z_re = t / 2.0;
        z_im = absz / 2.0;
      }
      if (z_re == 0.0) {
        z_re = cos(z_im);
        z_im = sin(z_im);
      } else if (z_im == 0.0) {
        z_re = exp(z_re);
        z_im = 0.0;
      } else if (rtIsInf(z_im) && rtIsInf(z_re) && (z_re < 0.0)) {
        z_re = 0.0;
        z_im = 0.0;
      } else {
        absz = exp(z_re / 2.0);
        z_re = absz * (absz * cos(z_im));
        z_im = absz * (absz * sin(z_im));
      }
      absz =
          ceil(((a2p.im - a1p.im) - 3.1415926535897931) / 6.2831853071795862);
      xr = p * (xr + 0.0 * absz);
      t = p * (xi + 3.1415926535897931 * absz);
      if (t == 0.0) {
        xr = sinh(xr);
        t = 0.0;
      } else {
        absz = xr;
        xr = sinh(xr) * cos(t);
        t = cosh(absz) * sin(t);
      }
      xi = 2.0 * z_re;
      z_im *= 2.0;
      z_re = xi * xr - z_im * t;
      z_im = xi * t + z_im * xr;
      if (ai_tmp == 0.0) {
        if (z_im == 0.0) {
          xi = z_re / ar_tmp;
          z_im = 0.0;
        } else if (z_re == 0.0) {
          xi = 0.0;
          z_im /= ar_tmp;
        } else {
          xi = z_re / ar_tmp;
          z_im /= ar_tmp;
        }
      } else if (ar_tmp == 0.0) {
        if (z_re == 0.0) {
          xi = z_im / ai_tmp;
          z_im = 0.0;
        } else if (z_im == 0.0) {
          xi = 0.0;
          z_im = -(z_re / ai_tmp);
        } else {
          xi = z_im / ai_tmp;
          z_im = -(z_re / ai_tmp);
        }
      } else {
        brm = fabs(ar_tmp);
        xr = fabs(ai_tmp);
        if (brm > xr) {
          brm = ai_tmp / ar_tmp;
          absz = ar_tmp + brm * ai_tmp;
          xi = (z_re + brm * z_im) / absz;
          z_im = (z_im - brm * z_re) / absz;
        } else if (xr == brm) {
          if (ar_tmp > 0.0) {
            xr = 0.5;
          } else {
            xr = -0.5;
          }
          if (ai_tmp > 0.0) {
            absz = 0.5;
          } else {
            absz = -0.5;
          }
          xi = (z_re * xr + z_im * absz) / brm;
          z_im = (z_im * xr - z_re * absz) / brm;
        } else {
          brm = ar_tmp / ai_tmp;
          absz = ai_tmp + brm * ar_tmp;
          xi = (brm * z_re + z_im) / absz;
          z_im = (brm * z_im - z_re) / absz;
        }
      }
      X[2].re = A[2].re * xi - A[2].im * z_im;
      X[2].im = A[2].re * z_im + A[2].im * xi;
    }
  }
}

void mpower_schur(const creal_T a[9], creal_T X[9])
{
  static const double xvals[7] = {1.51266667212246E-5, 0.0022365507825297779,
                                  0.01882832775783885, 0.060361006930897639,
                                  0.1239372725584911,  0.19980306906042711,
                                  0.27876299308620989};
  creal_T Q[9];
  creal_T R[9];
  creal_T T[9];
  creal_T T_old[9];
  creal_T TmI[9];
  creal_T b_T[9];
  creal_T b_T_old[4];
  creal_T dcv[4];
  creal_T d[3];
  creal_T diagT[3];
  creal_T s;
  double T_re_tmp;
  double TmI_re_tmp;
  double absx;
  double b_T_re_tmp;
  double b_TmI_re_tmp;
  double brm;
  double c_T_re_tmp;
  double d3;
  double d4;
  double d_T_re_tmp;
  double im;
  double r_im;
  double z0_im;
  double z0_re;
  int T_re_tmp_tmp;
  int T_tmp_tmp;
  int b;
  int b_i;
  int exitg1;
  int i;
  int ind;
  int j;
  int nsq;
  int q;
  int s0;
  signed char T_tmp[2];
  boolean_T exitg2;
  boolean_T foundm;
  boolean_T schurA;
  b = 0;
  schurA = true;
  j = 0;
  exitg2 = false;
  while ((!exitg2) && (j < 3)) {
    i = j + 1;
    do {
      exitg1 = 0;
      if (i + 1 < 4) {
        ind = i + 3 * j;
        if ((!(a[ind].re == 0.0)) || (!(a[ind].im == 0.0))) {
          schurA = false;
          exitg1 = 1;
        } else {
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
  if (schurA) {
    memcpy(&T[0], &a[0], 9U * sizeof(creal_T));
  } else {
    schur(a, Q, T);
  }
  memcpy(&T_old[0], &T[0], 9U * sizeof(creal_T));
  s0 = 0;
  diagT[0].re = T[0].re;
  diagT[0].im = T[0].im;
  d[0].re = T[0].re;
  d[0].im = T[0].im;
  diagT[1].re = T[4].re;
  diagT[1].im = T[4].im;
  d[1].re = T[4].re;
  d[1].im = T[4].im;
  diagT[2].re = T[8].re;
  diagT[2].im = T[8].im;
  d[2].re = T[8].re;
  d[2].im = T[8].im;
  if ((rt_hypotd_snf(T[0].re, T[0].im) + rt_hypotd_snf(T[4].re, T[4].im)) +
          rt_hypotd_snf(T[8].re, T[8].im) !=
      0.0) {
    do {
      exitg1 = 0;
      r_im = 0.0;
      absx = rt_hypotd_snf(d[0].re - 1.0, d[0].im);
      if (rtIsNaN(absx) || (absx > 0.0)) {
        r_im = absx;
      }
      absx = rt_hypotd_snf(d[1].re - 1.0, d[1].im);
      if (rtIsNaN(absx) || (absx > r_im)) {
        r_im = absx;
      }
      absx = rt_hypotd_snf(d[2].re - 1.0, d[2].im);
      if (rtIsNaN(absx) || (absx > r_im)) {
        r_im = absx;
      }
      if ((r_im > 0.27876299308620989) && (s0 < 100)) {
        b_sqrt(&d[0]);
        b_sqrt(&d[1]);
        b_sqrt(&d[2]);
        s0++;
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  nsq = s0;
  for (q = 0; q < s0; q++) {
    for (b_i = 0; b_i < 9; b_i++) {
      b_T[b_i] = T[b_i];
      T[b_i].re = 0.0;
      T[b_i].im = 0.0;
    }
    for (j = 0; j < 3; j++) {
      T_tmp_tmp = j + 3 * j;
      T[T_tmp_tmp] = b_T[T_tmp_tmp];
      b_sqrt(&T[T_tmp_tmp]);
      for (i = j; i >= 1; i--) {
        s.re = 0.0;
        s.im = 0.0;
        b_i = i + 1;
        for (ind = b_i; ind <= j; ind++) {
          T_re_tmp = T[i + 2].re;
          T_re_tmp_tmp = 3 * j + 1;
          b_T_re_tmp = T[T_re_tmp_tmp].im;
          c_T_re_tmp = T[i + 2].im;
          d_T_re_tmp = T[T_re_tmp_tmp].re;
          s.re += T_re_tmp * d_T_re_tmp - c_T_re_tmp * b_T_re_tmp;
          s.im += T_re_tmp * b_T_re_tmp + c_T_re_tmp * d_T_re_tmp;
        }
        ind = (i + 3 * j) - 1;
        z0_re = b_T[ind].re - s.re;
        z0_im = b_T[ind].im - s.im;
        T_re_tmp_tmp = (i + 3 * (i - 1)) - 1;
        absx = T[T_re_tmp_tmp].re + T[T_tmp_tmp].re;
        r_im = T[T_re_tmp_tmp].im + T[T_tmp_tmp].im;
        if (r_im == 0.0) {
          if (z0_im == 0.0) {
            d4 = z0_re / absx;
            im = 0.0;
          } else if (z0_re == 0.0) {
            d4 = 0.0;
            im = z0_im / absx;
          } else {
            d4 = z0_re / absx;
            im = z0_im / absx;
          }
        } else if (absx == 0.0) {
          if (z0_re == 0.0) {
            d4 = z0_im / r_im;
            im = 0.0;
          } else if (z0_im == 0.0) {
            d4 = 0.0;
            im = -(z0_re / r_im);
          } else {
            d4 = z0_im / r_im;
            im = -(z0_re / r_im);
          }
        } else {
          brm = fabs(absx);
          im = fabs(r_im);
          if (brm > im) {
            im = r_im / absx;
            absx += im * r_im;
            d4 = (z0_re + im * z0_im) / absx;
            im = (z0_im - im * z0_re) / absx;
          } else if (im == brm) {
            if (absx > 0.0) {
              im = 0.5;
            } else {
              im = -0.5;
            }
            if (r_im > 0.0) {
              absx = 0.5;
            } else {
              absx = -0.5;
            }
            d4 = (z0_re * im + z0_im * absx) / brm;
            im = (z0_im * im - z0_re * absx) / brm;
          } else {
            im = absx / r_im;
            absx = r_im + im * absx;
            d4 = (im * z0_re + z0_im) / absx;
            im = (im * z0_im - z0_re) / absx;
          }
        }
        T[ind].re = d4;
        T[ind].im = im;
      }
    }
  }
  memset(&TmI[0], 0, 9U * sizeof(creal_T));
  for (j = 0; j < 3; j++) {
    for (i = 0; i < j; i++) {
      ind = i + 3 * j;
      TmI[ind] = T[ind];
    }
    b_i = j + 3 * j;
    TmI[b_i].re = T[b_i].re - 1.0;
    TmI[b_i].im = T[b_i].im;
  }
  for (b_i = 0; b_i < 3; b_i++) {
    absx = TmI[b_i].re;
    r_im = TmI[b_i].im;
    im = TmI[b_i + 3].re;
    z0_re = TmI[b_i + 3].im;
    z0_im = TmI[b_i + 6].re;
    T_re_tmp = TmI[b_i + 6].im;
    for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
      b_T_re_tmp = TmI[3 * T_tmp_tmp].im;
      c_T_re_tmp = TmI[3 * T_tmp_tmp].re;
      ind = 3 * T_tmp_tmp + 1;
      d_T_re_tmp = TmI[ind].im;
      TmI_re_tmp = TmI[ind].re;
      ind = 3 * T_tmp_tmp + 2;
      b_TmI_re_tmp = TmI[ind].im;
      brm = TmI[ind].re;
      ind = b_i + 3 * T_tmp_tmp;
      b_T[ind].re = ((absx * c_T_re_tmp - r_im * b_T_re_tmp) +
                     (im * TmI_re_tmp - z0_re * d_T_re_tmp)) +
                    (z0_im * brm - T_re_tmp * b_TmI_re_tmp);
      b_T[ind].im = ((absx * b_T_re_tmp + r_im * c_T_re_tmp) +
                     (im * d_T_re_tmp + z0_re * TmI_re_tmp)) +
                    (z0_im * b_TmI_re_tmp + T_re_tmp * brm);
    }
  }
  for (b_i = 0; b_i < 3; b_i++) {
    absx = TmI[b_i].re;
    r_im = TmI[b_i].im;
    im = TmI[b_i + 3].re;
    z0_re = TmI[b_i + 3].im;
    z0_im = TmI[b_i + 6].re;
    T_re_tmp = TmI[b_i + 6].im;
    for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
      b_T_re_tmp = b_T[3 * T_tmp_tmp].im;
      c_T_re_tmp = b_T[3 * T_tmp_tmp].re;
      ind = 3 * T_tmp_tmp + 1;
      d_T_re_tmp = b_T[ind].im;
      TmI_re_tmp = b_T[ind].re;
      ind = 3 * T_tmp_tmp + 2;
      b_TmI_re_tmp = b_T[ind].im;
      brm = b_T[ind].re;
      ind = b_i + 3 * T_tmp_tmp;
      R[ind].re = ((absx * c_T_re_tmp - r_im * b_T_re_tmp) +
                   (im * TmI_re_tmp - z0_re * d_T_re_tmp)) +
                  (z0_im * brm - T_re_tmp * b_TmI_re_tmp);
      R[ind].im = ((absx * b_T_re_tmp + r_im * c_T_re_tmp) +
                   (im * d_T_re_tmp + z0_re * TmI_re_tmp)) +
                  (z0_im * b_TmI_re_tmp + T_re_tmp * brm);
    }
  }
  r_im = 0.0;
  j = 0;
  exitg2 = false;
  while ((!exitg2) && (j < 3)) {
    ind = 3 * j + 1;
    T_re_tmp_tmp = 3 * j + 2;
    im = (rt_hypotd_snf(R[3 * j].re, R[3 * j].im) +
          rt_hypotd_snf(R[ind].re, R[ind].im)) +
         rt_hypotd_snf(R[T_re_tmp_tmp].re, R[T_re_tmp_tmp].im);
    if (rtIsNaN(im)) {
      r_im = rtNaN;
      exitg2 = true;
    } else {
      if (im > r_im) {
        r_im = im;
      }
      j++;
    }
  }
  d3 = rt_powd_snf(r_im, 0.33333333333333331);
  r_im = 0.0;
  j = 0;
  exitg2 = false;
  while ((!exitg2) && (j < 3)) {
    ind = 3 * j + 1;
    T_re_tmp_tmp = 3 * j + 2;
    im = (rt_hypotd_snf(b_T[3 * j].re, b_T[3 * j].im) +
          rt_hypotd_snf(b_T[ind].re, b_T[ind].im)) +
         rt_hypotd_snf(b_T[T_re_tmp_tmp].re, b_T[T_re_tmp_tmp].im);
    if (rtIsNaN(im)) {
      r_im = rtNaN;
      exitg2 = true;
    } else {
      if (im > r_im) {
        r_im = im;
      }
      j++;
    }
  }
  absx = fmax(sqrt(r_im), d3);
  if (absx <= 1.51266667212246E-5) {
    b = 1;
    foundm = true;
  } else if (absx <= 0.0022365507825297779) {
    b = 2;
    foundm = true;
  } else {
    foundm = false;
  }
  q = 0;
  exitg2 = false;
  while ((!exitg2) && (!foundm)) {
    double alpha3;
    boolean_T exitg3;
    boolean_T guard1 = false;
    boolean_T guard2 = false;
    boolean_T more;
    more = false;
    if (nsq > s0) {
      for (b_i = 0; b_i < 3; b_i++) {
        absx = TmI[b_i].re;
        r_im = TmI[b_i].im;
        im = TmI[b_i + 3].re;
        z0_re = TmI[b_i + 3].im;
        z0_im = TmI[b_i + 6].re;
        T_re_tmp = TmI[b_i + 6].im;
        for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
          b_T_re_tmp = TmI[3 * T_tmp_tmp].im;
          c_T_re_tmp = TmI[3 * T_tmp_tmp].re;
          ind = 3 * T_tmp_tmp + 1;
          d_T_re_tmp = TmI[ind].im;
          TmI_re_tmp = TmI[ind].re;
          ind = 3 * T_tmp_tmp + 2;
          b_TmI_re_tmp = TmI[ind].im;
          brm = TmI[ind].re;
          ind = b_i + 3 * T_tmp_tmp;
          b_T[ind].re = ((absx * c_T_re_tmp - r_im * b_T_re_tmp) +
                         (im * TmI_re_tmp - z0_re * d_T_re_tmp)) +
                        (z0_im * brm - T_re_tmp * b_TmI_re_tmp);
          b_T[ind].im = ((absx * b_T_re_tmp + r_im * c_T_re_tmp) +
                         (im * d_T_re_tmp + z0_re * TmI_re_tmp)) +
                        (z0_im * b_TmI_re_tmp + T_re_tmp * brm);
        }
      }
      for (b_i = 0; b_i < 3; b_i++) {
        absx = TmI[b_i].re;
        r_im = TmI[b_i].im;
        im = TmI[b_i + 3].re;
        z0_re = TmI[b_i + 3].im;
        z0_im = TmI[b_i + 6].re;
        T_re_tmp = TmI[b_i + 6].im;
        for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
          b_T_re_tmp = b_T[3 * T_tmp_tmp].im;
          c_T_re_tmp = b_T[3 * T_tmp_tmp].re;
          ind = 3 * T_tmp_tmp + 1;
          d_T_re_tmp = b_T[ind].im;
          TmI_re_tmp = b_T[ind].re;
          ind = 3 * T_tmp_tmp + 2;
          b_TmI_re_tmp = b_T[ind].im;
          brm = b_T[ind].re;
          ind = b_i + 3 * T_tmp_tmp;
          R[ind].re = ((absx * c_T_re_tmp - r_im * b_T_re_tmp) +
                       (im * TmI_re_tmp - z0_re * d_T_re_tmp)) +
                      (z0_im * brm - T_re_tmp * b_TmI_re_tmp);
          R[ind].im = ((absx * b_T_re_tmp + r_im * c_T_re_tmp) +
                       (im * d_T_re_tmp + z0_re * TmI_re_tmp)) +
                      (z0_im * b_TmI_re_tmp + T_re_tmp * brm);
        }
      }
      r_im = 0.0;
      j = 0;
      exitg3 = false;
      while ((!exitg3) && (j < 3)) {
        ind = 3 * j + 1;
        T_re_tmp_tmp = 3 * j + 2;
        im = (rt_hypotd_snf(R[3 * j].re, R[3 * j].im) +
              rt_hypotd_snf(R[ind].re, R[ind].im)) +
             rt_hypotd_snf(R[T_re_tmp_tmp].re, R[T_re_tmp_tmp].im);
        if (rtIsNaN(im)) {
          r_im = rtNaN;
          exitg3 = true;
        } else {
          if (im > r_im) {
            r_im = im;
          }
          j++;
        }
      }
      d3 = rt_powd_snf(r_im, 0.33333333333333331);
    }
    for (b_i = 0; b_i < 3; b_i++) {
      absx = TmI[b_i].re;
      r_im = TmI[b_i].im;
      im = TmI[b_i + 3].re;
      z0_re = TmI[b_i + 3].im;
      z0_im = TmI[b_i + 6].re;
      T_re_tmp = TmI[b_i + 6].im;
      for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
        b_T_re_tmp = TmI[3 * T_tmp_tmp].im;
        c_T_re_tmp = TmI[3 * T_tmp_tmp].re;
        ind = 3 * T_tmp_tmp + 1;
        d_T_re_tmp = TmI[ind].im;
        TmI_re_tmp = TmI[ind].re;
        ind = 3 * T_tmp_tmp + 2;
        b_TmI_re_tmp = TmI[ind].im;
        brm = TmI[ind].re;
        ind = b_i + 3 * T_tmp_tmp;
        b_T[ind].re = ((absx * c_T_re_tmp - r_im * b_T_re_tmp) +
                       (im * TmI_re_tmp - z0_re * d_T_re_tmp)) +
                      (z0_im * brm - T_re_tmp * b_TmI_re_tmp);
        b_T[ind].im = ((absx * b_T_re_tmp + r_im * c_T_re_tmp) +
                       (im * d_T_re_tmp + z0_re * TmI_re_tmp)) +
                      (z0_im * b_TmI_re_tmp + T_re_tmp * brm);
      }
    }
    for (b_i = 0; b_i < 3; b_i++) {
      T_re_tmp = b_T[b_i].re;
      b_T_re_tmp = b_T[b_i].im;
      c_T_re_tmp = b_T[b_i + 3].re;
      d_T_re_tmp = b_T[b_i + 3].im;
      TmI_re_tmp = b_T[b_i + 6].re;
      b_TmI_re_tmp = b_T[b_i + 6].im;
      for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
        absx = b_T[3 * T_tmp_tmp].im;
        r_im = b_T[3 * T_tmp_tmp].re;
        T_re_tmp_tmp = 3 * T_tmp_tmp + 1;
        im = b_T[T_re_tmp_tmp].im;
        z0_re = b_T[T_re_tmp_tmp].re;
        T_re_tmp_tmp = 3 * T_tmp_tmp + 2;
        z0_im = b_T[T_re_tmp_tmp].im;
        brm = b_T[T_re_tmp_tmp].re;
        ind = b_i + 3 * T_tmp_tmp;
        R[ind].re = ((T_re_tmp * r_im - b_T_re_tmp * absx) +
                     (c_T_re_tmp * z0_re - d_T_re_tmp * im)) +
                    (TmI_re_tmp * brm - b_TmI_re_tmp * z0_im);
        R[ind].im = ((T_re_tmp * absx + b_T_re_tmp * r_im) +
                     (c_T_re_tmp * im + d_T_re_tmp * z0_re)) +
                    (TmI_re_tmp * z0_im + b_TmI_re_tmp * brm);
      }
    }
    r_im = 0.0;
    j = 0;
    exitg3 = false;
    while ((!exitg3) && (j < 3)) {
      ind = 3 * j + 1;
      T_re_tmp_tmp = 3 * j + 2;
      im = (rt_hypotd_snf(R[3 * j].re, R[3 * j].im) +
            rt_hypotd_snf(R[ind].re, R[ind].im)) +
           rt_hypotd_snf(R[T_re_tmp_tmp].re, R[T_re_tmp_tmp].im);
      if (rtIsNaN(im)) {
        r_im = rtNaN;
        exitg3 = true;
      } else {
        if (im > r_im) {
          r_im = im;
        }
        j++;
      }
    }
    d4 = rt_powd_snf(r_im, 0.25);
    alpha3 = fmax(d3, d4);
    guard1 = false;
    guard2 = false;
    if (alpha3 <= 0.27876299308620989) {
      ind = 0;
      j = 3;
      exitg3 = false;
      while ((!exitg3) && (j < 8)) {
        if (alpha3 <= xvals[j - 1]) {
          ind = j;
          exitg3 = true;
        } else {
          j++;
        }
      }
      if (ind <= 6) {
        b = ind;
        exitg2 = true;
      } else {
        if ((alpha3 / 2.0 <= 0.1239372725584911) && (q < 2)) {
          more = true;
          q++;
        }
        guard2 = true;
      }
    } else {
      guard2 = true;
    }
    if (guard2) {
      if (!more) {
        creal_T c_T[9];
        for (b_i = 0; b_i < 3; b_i++) {
          absx = TmI[b_i].re;
          r_im = TmI[b_i].im;
          im = TmI[b_i + 3].re;
          z0_re = TmI[b_i + 3].im;
          z0_im = TmI[b_i + 6].re;
          T_re_tmp = TmI[b_i + 6].im;
          for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
            b_T_re_tmp = TmI[3 * T_tmp_tmp].im;
            c_T_re_tmp = TmI[3 * T_tmp_tmp].re;
            ind = 3 * T_tmp_tmp + 1;
            d_T_re_tmp = TmI[ind].im;
            TmI_re_tmp = TmI[ind].re;
            ind = 3 * T_tmp_tmp + 2;
            b_TmI_re_tmp = TmI[ind].im;
            brm = TmI[ind].re;
            ind = b_i + 3 * T_tmp_tmp;
            b_T[ind].re = ((absx * c_T_re_tmp - r_im * b_T_re_tmp) +
                           (im * TmI_re_tmp - z0_re * d_T_re_tmp)) +
                          (z0_im * brm - T_re_tmp * b_TmI_re_tmp);
            b_T[ind].im = ((absx * b_T_re_tmp + r_im * c_T_re_tmp) +
                           (im * d_T_re_tmp + z0_re * TmI_re_tmp)) +
                          (z0_im * b_TmI_re_tmp + T_re_tmp * brm);
          }
        }
        for (b_i = 0; b_i < 3; b_i++) {
          T_re_tmp = b_T[b_i].re;
          b_T_re_tmp = b_T[b_i].im;
          c_T_re_tmp = b_T[b_i + 3].re;
          d_T_re_tmp = b_T[b_i + 3].im;
          TmI_re_tmp = b_T[b_i + 6].re;
          b_TmI_re_tmp = b_T[b_i + 6].im;
          for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
            absx = b_T[3 * T_tmp_tmp].im;
            r_im = b_T[3 * T_tmp_tmp].re;
            T_re_tmp_tmp = 3 * T_tmp_tmp + 1;
            im = b_T[T_re_tmp_tmp].im;
            z0_re = b_T[T_re_tmp_tmp].re;
            T_re_tmp_tmp = 3 * T_tmp_tmp + 2;
            z0_im = b_T[T_re_tmp_tmp].im;
            brm = b_T[T_re_tmp_tmp].re;
            ind = b_i + 3 * T_tmp_tmp;
            c_T[ind].re = ((T_re_tmp * r_im - b_T_re_tmp * absx) +
                           (c_T_re_tmp * z0_re - d_T_re_tmp * im)) +
                          (TmI_re_tmp * brm - b_TmI_re_tmp * z0_im);
            c_T[ind].im = ((T_re_tmp * absx + b_T_re_tmp * r_im) +
                           (c_T_re_tmp * im + d_T_re_tmp * z0_re)) +
                          (TmI_re_tmp * z0_im + b_TmI_re_tmp * brm);
          }
        }
        for (b_i = 0; b_i < 3; b_i++) {
          absx = TmI[b_i].re;
          r_im = TmI[b_i].im;
          im = TmI[b_i + 3].re;
          z0_re = TmI[b_i + 3].im;
          z0_im = TmI[b_i + 6].re;
          T_re_tmp = TmI[b_i + 6].im;
          for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
            b_T_re_tmp = c_T[3 * T_tmp_tmp].im;
            c_T_re_tmp = c_T[3 * T_tmp_tmp].re;
            ind = 3 * T_tmp_tmp + 1;
            d_T_re_tmp = c_T[ind].im;
            TmI_re_tmp = c_T[ind].re;
            ind = 3 * T_tmp_tmp + 2;
            b_TmI_re_tmp = c_T[ind].im;
            brm = c_T[ind].re;
            ind = b_i + 3 * T_tmp_tmp;
            R[ind].re = ((absx * c_T_re_tmp - r_im * b_T_re_tmp) +
                         (im * TmI_re_tmp - z0_re * d_T_re_tmp)) +
                        (z0_im * brm - T_re_tmp * b_TmI_re_tmp);
            R[ind].im = ((absx * b_T_re_tmp + r_im * c_T_re_tmp) +
                         (im * d_T_re_tmp + z0_re * TmI_re_tmp)) +
                        (z0_im * b_TmI_re_tmp + T_re_tmp * brm);
          }
        }
        r_im = 0.0;
        j = 0;
        exitg3 = false;
        while ((!exitg3) && (j < 3)) {
          ind = 3 * j + 1;
          T_re_tmp_tmp = 3 * j + 2;
          im = (rt_hypotd_snf(R[3 * j].re, R[3 * j].im) +
                rt_hypotd_snf(R[ind].re, R[ind].im)) +
               rt_hypotd_snf(R[T_re_tmp_tmp].re, R[T_re_tmp_tmp].im);
          if (rtIsNaN(im)) {
            r_im = rtNaN;
            exitg3 = true;
          } else {
            if (im > r_im) {
              r_im = im;
            }
            j++;
          }
        }
        absx = fmin(alpha3, fmax(d4, rt_powd_snf(r_im, 0.2)));
        if (absx <= 0.27876299308620989) {
          b = 7;
          if (absx <= 0.19980306906042711) {
            b = 6;
          }
          exitg2 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    }
    if (guard1) {
      if (nsq == 100) {
        b = 13;
        exitg2 = true;
      } else {
        for (b_i = 0; b_i < 9; b_i++) {
          b_T[b_i] = T[b_i];
          T[b_i].re = 0.0;
          T[b_i].im = 0.0;
        }
        for (j = 0; j < 3; j++) {
          T_tmp_tmp = j + 3 * j;
          T[T_tmp_tmp] = b_T[T_tmp_tmp];
          b_sqrt(&T[T_tmp_tmp]);
          for (i = j; i >= 1; i--) {
            s.re = 0.0;
            s.im = 0.0;
            b_i = i + 1;
            for (ind = b_i; ind <= j; ind++) {
              T_re_tmp = T[i + 2].re;
              T_re_tmp_tmp = 3 * j + 1;
              b_T_re_tmp = T[T_re_tmp_tmp].im;
              c_T_re_tmp = T[i + 2].im;
              d_T_re_tmp = T[T_re_tmp_tmp].re;
              s.re += T_re_tmp * d_T_re_tmp - c_T_re_tmp * b_T_re_tmp;
              s.im += T_re_tmp * b_T_re_tmp + c_T_re_tmp * d_T_re_tmp;
            }
            ind = (i + 3 * j) - 1;
            z0_re = b_T[ind].re - s.re;
            z0_im = b_T[ind].im - s.im;
            T_re_tmp_tmp = (i + 3 * (i - 1)) - 1;
            absx = T[T_re_tmp_tmp].re + T[T_tmp_tmp].re;
            r_im = T[T_re_tmp_tmp].im + T[T_tmp_tmp].im;
            if (r_im == 0.0) {
              if (z0_im == 0.0) {
                d4 = z0_re / absx;
                im = 0.0;
              } else if (z0_re == 0.0) {
                d4 = 0.0;
                im = z0_im / absx;
              } else {
                d4 = z0_re / absx;
                im = z0_im / absx;
              }
            } else if (absx == 0.0) {
              if (z0_re == 0.0) {
                d4 = z0_im / r_im;
                im = 0.0;
              } else if (z0_im == 0.0) {
                d4 = 0.0;
                im = -(z0_re / r_im);
              } else {
                d4 = z0_im / r_im;
                im = -(z0_re / r_im);
              }
            } else {
              brm = fabs(absx);
              im = fabs(r_im);
              if (brm > im) {
                im = r_im / absx;
                absx += im * r_im;
                d4 = (z0_re + im * z0_im) / absx;
                im = (z0_im - im * z0_re) / absx;
              } else if (im == brm) {
                if (absx > 0.0) {
                  im = 0.5;
                } else {
                  im = -0.5;
                }
                if (r_im > 0.0) {
                  absx = 0.5;
                } else {
                  absx = -0.5;
                }
                d4 = (z0_re * im + z0_im * absx) / brm;
                im = (z0_im * im - z0_re * absx) / brm;
              } else {
                im = absx / r_im;
                absx = r_im + im * absx;
                d4 = (im * z0_re + z0_im) / absx;
                im = (im * z0_im - z0_re) / absx;
              }
            }
            T[ind].re = d4;
            T[ind].im = im;
          }
        }
        for (j = 0; j < 3; j++) {
          for (i = 0; i < j; i++) {
            ind = i + 3 * j;
            TmI[ind] = T[ind];
          }
          b_i = j + 3 * j;
          TmI[b_i].re = T[b_i].re - 1.0;
          TmI[b_i].im = T[b_i].im;
        }
        nsq++;
      }
    }
  }
  for (i = 0; i < 2; i++) {
    for (b_i = 0; b_i < 2; b_i++) {
      T_tmp[b_i] = (signed char)((i + b_i) + 1);
    }
    ind = 3 * (T_tmp[0] - 1);
    b_T_old[0] = T_old[(T_tmp[0] + ind) - 1];
    b_T_old[1] = T_old[(T_tmp[1] + ind) - 1];
    ind = 3 * (T_tmp[1] - 1);
    b_T_old[2] = T_old[(T_tmp[0] + ind) - 1];
    b_T_old[3] = T_old[(T_tmp[1] + ind) - 1];
    powerm2by2(b_T_old, 1.0 / rt_powd_snf(2.0, nsq), dcv);
    ind = i + 3 * i;
    T[ind] = dcv[0];
    T[ind + 1] = dcv[1];
    ind = i + 3 * (i + 1);
    T[ind] = dcv[2];
    T[ind + 1] = dcv[3];
  }
  memset(&R[0], 0, 9U * sizeof(creal_T));
  for (j = 0; j < 3; j++) {
    for (i = 0; i < j; i++) {
      b_i = i + 3 * j;
      R[b_i].re = -T[b_i].re;
      R[b_i].im = -T[b_i].im;
    }
    s = diagT[j];
    if (nsq == 0) {
      s.re = diagT[j].re - 1.0;
      s.im = diagT[j].im;
    } else {
      ind = nsq - 2;
      if (rt_atan2d_snf(diagT[j].im, diagT[j].re) >= 1.5707963267948966) {
        b_sqrt(&s);
        ind = nsq - 3;
      }
      z0_re = s.re - 1.0;
      z0_im = s.im;
      b_sqrt(&s);
      absx = s.re + 1.0;
      r_im = s.im;
      for (i = 0; i <= ind; i++) {
        b_sqrt(&s);
        d4 = absx * (s.re + 1.0) - r_im * s.im;
        r_im = absx * s.im + r_im * (s.re + 1.0);
        absx = d4;
      }
      if (r_im == 0.0) {
        if (z0_im == 0.0) {
          s.re = z0_re / absx;
          s.im = 0.0;
        } else if (z0_re == 0.0) {
          s.re = 0.0;
          s.im = z0_im / absx;
        } else {
          s.re = z0_re / absx;
          s.im = z0_im / absx;
        }
      } else if (absx == 0.0) {
        if (z0_re == 0.0) {
          s.re = z0_im / r_im;
          s.im = 0.0;
        } else if (z0_im == 0.0) {
          s.re = 0.0;
          s.im = -(z0_re / r_im);
        } else {
          s.re = z0_im / r_im;
          s.im = -(z0_re / r_im);
        }
      } else {
        brm = fabs(absx);
        im = fabs(r_im);
        if (brm > im) {
          im = r_im / absx;
          absx += im * r_im;
          s.re = (z0_re + im * z0_im) / absx;
          s.im = (z0_im - im * z0_re) / absx;
        } else if (im == brm) {
          if (absx > 0.0) {
            im = 0.5;
          } else {
            im = -0.5;
          }
          if (r_im > 0.0) {
            absx = 0.5;
          } else {
            absx = -0.5;
          }
          s.re = (z0_re * im + z0_im * absx) / brm;
          s.im = (z0_im * im - z0_re * absx) / brm;
        } else {
          im = absx / r_im;
          absx = r_im + im * absx;
          s.re = (im * z0_re + z0_im) / absx;
          s.im = (im * z0_im - z0_re) / absx;
        }
      }
    }
    b_i = j + 3 * j;
    R[b_i].re = -s.re;
    R[b_i].im = -s.im;
  }
  ind = b << 1;
  if (ind == 1) {
    absx = 0.5;
  } else {
    absx = (double)ind / 2.0;
    if ((ind & 1) == 0) {
      absx = (-absx - 0.5) / (2.0 * (2.0 * absx - 1.0));
    } else {
      absx = floor(absx);
      absx = (-absx - -0.5) / (2.0 * (2.0 * absx + 1.0));
    }
  }
  for (b_i = 0; b_i < 9; b_i++) {
    TmI[b_i].re = absx * R[b_i].re;
    TmI[b_i].im = absx * R[b_i].im;
  }
  b_i = ind - 1;
  for (j = b_i; j >= 1; j--) {
    if (j == 1) {
      absx = 0.5;
    } else {
      absx = (double)j / 2.0;
      if ((j & 1) == 0) {
        absx = (-absx - 0.5) / (2.0 * (2.0 * absx - 1.0));
      } else {
        absx = floor(absx);
        absx = (-absx - -0.5) / (2.0 * (2.0 * absx + 1.0));
      }
    }
    TmI[0].re++;
    TmI[4].re++;
    TmI[8].re++;
    memcpy(&b_T[0], &R[0], 9U * sizeof(creal_T));
    trisolve(TmI, b_T);
    for (T_tmp_tmp = 0; T_tmp_tmp < 9; T_tmp_tmp++) {
      TmI[T_tmp_tmp].re = absx * b_T[T_tmp_tmp].re;
      TmI[T_tmp_tmp].im = absx * b_T[T_tmp_tmp].im;
    }
  }
  memset(&X[0], 0, 9U * sizeof(creal_T));
  for (j = 0; j < 3; j++) {
    X[3 * j] = TmI[3 * j];
    ind = 3 * j + 1;
    X[ind] = TmI[ind];
    b_i = j + 3 * j;
    X[b_i].re = TmI[b_i].re + 1.0;
    X[b_i].im = TmI[b_i].im;
  }
  for (q = 0; q <= nsq; q++) {
    if (q != 0) {
      for (b_i = 0; b_i < 3; b_i++) {
        absx = X[b_i].re;
        r_im = X[b_i].im;
        im = X[b_i + 3].re;
        z0_re = X[b_i + 3].im;
        z0_im = X[b_i + 6].re;
        brm = X[b_i + 6].im;
        for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
          T_re_tmp = X[3 * T_tmp_tmp].im;
          b_T_re_tmp = X[3 * T_tmp_tmp].re;
          ind = 3 * T_tmp_tmp + 1;
          c_T_re_tmp = X[ind].im;
          d_T_re_tmp = X[ind].re;
          ind = 3 * T_tmp_tmp + 2;
          TmI_re_tmp = X[ind].im;
          b_TmI_re_tmp = X[ind].re;
          ind = b_i + 3 * T_tmp_tmp;
          b_T[ind].re = ((absx * b_T_re_tmp - r_im * T_re_tmp) +
                         (im * d_T_re_tmp - z0_re * c_T_re_tmp)) +
                        (z0_im * b_TmI_re_tmp - brm * TmI_re_tmp);
          b_T[ind].im = ((absx * T_re_tmp + r_im * b_T_re_tmp) +
                         (im * c_T_re_tmp + z0_re * d_T_re_tmp)) +
                        (z0_im * TmI_re_tmp + brm * b_TmI_re_tmp);
        }
      }
      memcpy(&X[0], &b_T[0], 9U * sizeof(creal_T));
    }
    for (i = 0; i < 2; i++) {
      for (b_i = 0; b_i < 2; b_i++) {
        T_tmp[b_i] = (signed char)((i + b_i) + 1);
      }
      ind = 3 * (T_tmp[0] - 1);
      b_T_old[0] = T_old[(T_tmp[0] + ind) - 1];
      b_T_old[1] = T_old[(T_tmp[1] + ind) - 1];
      ind = 3 * (T_tmp[1] - 1);
      b_T_old[2] = T_old[(T_tmp[0] + ind) - 1];
      b_T_old[3] = T_old[(T_tmp[1] + ind) - 1];
      powerm2by2(b_T_old, -0.5 / rt_powd_snf(2.0, nsq - q), dcv);
      ind = i + 3 * i;
      X[ind] = dcv[0];
      X[ind + 1] = dcv[1];
      ind = i + 3 * (i + 1);
      X[ind] = dcv[2];
      X[ind + 1] = dcv[3];
    }
  }
  if (!schurA) {
    for (b_i = 0; b_i < 3; b_i++) {
      absx = Q[b_i].re;
      r_im = Q[b_i].im;
      im = Q[b_i + 3].re;
      z0_re = Q[b_i + 3].im;
      z0_im = Q[b_i + 6].re;
      brm = Q[b_i + 6].im;
      for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
        T_re_tmp = X[3 * T_tmp_tmp].im;
        b_T_re_tmp = X[3 * T_tmp_tmp].re;
        ind = 3 * T_tmp_tmp + 1;
        c_T_re_tmp = X[ind].im;
        d_T_re_tmp = X[ind].re;
        ind = 3 * T_tmp_tmp + 2;
        TmI_re_tmp = X[ind].im;
        b_TmI_re_tmp = X[ind].re;
        ind = b_i + 3 * T_tmp_tmp;
        b_T[ind].re = ((absx * b_T_re_tmp - r_im * T_re_tmp) +
                       (im * d_T_re_tmp - z0_re * c_T_re_tmp)) +
                      (z0_im * b_TmI_re_tmp - brm * TmI_re_tmp);
        b_T[ind].im = ((absx * T_re_tmp + r_im * b_T_re_tmp) +
                       (im * c_T_re_tmp + z0_re * d_T_re_tmp)) +
                      (z0_im * TmI_re_tmp + brm * b_TmI_re_tmp);
      }
    }
    for (b_i = 0; b_i < 3; b_i++) {
      T_re_tmp = b_T[b_i].re;
      b_T_re_tmp = b_T[b_i].im;
      c_T_re_tmp = b_T[b_i + 3].re;
      d_T_re_tmp = b_T[b_i + 3].im;
      TmI_re_tmp = b_T[b_i + 6].re;
      b_TmI_re_tmp = b_T[b_i + 6].im;
      for (T_tmp_tmp = 0; T_tmp_tmp < 3; T_tmp_tmp++) {
        absx = Q[T_tmp_tmp].re;
        r_im = -Q[T_tmp_tmp].im;
        d4 = T_re_tmp * absx - b_T_re_tmp * r_im;
        im = T_re_tmp * r_im + b_T_re_tmp * absx;
        absx = Q[T_tmp_tmp + 3].re;
        r_im = -Q[T_tmp_tmp + 3].im;
        d4 += c_T_re_tmp * absx - d_T_re_tmp * r_im;
        im += c_T_re_tmp * r_im + d_T_re_tmp * absx;
        absx = Q[T_tmp_tmp + 6].re;
        r_im = -Q[T_tmp_tmp + 6].im;
        d4 += TmI_re_tmp * absx - b_TmI_re_tmp * r_im;
        im += TmI_re_tmp * r_im + b_TmI_re_tmp * absx;
        ind = b_i + 3 * T_tmp_tmp;
        X[ind].re = d4;
        X[ind].im = im;
      }
    }
  }
}

/* End of code generation (mpower_schur.c) */
