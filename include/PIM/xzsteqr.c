/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzsteqr.c
 *
 * Code generation for function 'xzsteqr'
 *
 */

/* Include files */
#include "xzsteqr.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "xdlaev2.h"
#include "xzlartg.h"
#include "xzlascl.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static void b_rotateRight(int n, creal_T z[9], int iz0, const double cs[4],
                          int ic0, int is0);

static void rotateRight(int n, creal_T z[9], int iz0, const double cs[4],
                        int ic0, int is0);

/* Function Definitions */
static void b_rotateRight(int n, creal_T z[9], int iz0, const double cs[4],
                          int ic0, int is0)
{
  int j;
  for (j = 0; j <= n - 2; j++) {
    double ctemp;
    double stemp;
    int offsetj;
    int offsetjp1;
    ctemp = cs[(ic0 + j) - 1];
    stemp = cs[(is0 + j) - 1];
    offsetj = (j * 3 + iz0) - 2;
    offsetjp1 = ((j + 1) * 3 + iz0) - 2;
    if ((ctemp != 1.0) || (stemp != 0.0)) {
      double d;
      double d1;
      double temp_im;
      double temp_re;
      temp_re = z[offsetjp1 + 1].re;
      temp_im = z[offsetjp1 + 1].im;
      d = z[offsetj + 1].re;
      z[offsetjp1 + 1].re = ctemp * temp_re - stemp * d;
      d1 = z[offsetj + 1].im;
      z[offsetjp1 + 1].im = ctemp * temp_im - stemp * d1;
      d = stemp * temp_re + ctemp * d;
      z[offsetj + 1].re = d;
      d1 = stemp * temp_im + ctemp * d1;
      z[offsetj + 1].im = d1;
      temp_re = z[offsetjp1 + 2].re;
      temp_im = z[offsetjp1 + 2].im;
      d = z[offsetj + 2].re;
      z[offsetjp1 + 2].re = ctemp * temp_re - stemp * d;
      d1 = z[offsetj + 2].im;
      z[offsetjp1 + 2].im = ctemp * temp_im - stemp * d1;
      d = stemp * temp_re + ctemp * d;
      z[offsetj + 2].re = d;
      d1 = stemp * temp_im + ctemp * d1;
      z[offsetj + 2].im = d1;
      temp_re = z[offsetjp1 + 3].re;
      temp_im = z[offsetjp1 + 3].im;
      d = z[offsetj + 3].re;
      z[offsetjp1 + 3].re = ctemp * temp_re - stemp * d;
      d1 = z[offsetj + 3].im;
      z[offsetjp1 + 3].im = ctemp * temp_im - stemp * d1;
      d = stemp * temp_re + ctemp * d;
      z[offsetj + 3].re = d;
      d1 = stemp * temp_im + ctemp * d1;
      z[offsetj + 3].im = d1;
    }
  }
}

static void rotateRight(int n, creal_T z[9], int iz0, const double cs[4],
                        int ic0, int is0)
{
  int i;
  int j;
  i = n - 1;
  for (j = i; j >= 1; j--) {
    double ctemp;
    double stemp;
    int offsetj;
    int offsetjp1;
    ctemp = cs[(ic0 + j) - 2];
    stemp = cs[(is0 + j) - 2];
    offsetj = ((j - 1) * 3 + iz0) - 2;
    offsetjp1 = (j * 3 + iz0) - 2;
    if ((ctemp != 1.0) || (stemp != 0.0)) {
      double d;
      double d1;
      double temp_im;
      double temp_re;
      temp_re = z[offsetjp1 + 1].re;
      temp_im = z[offsetjp1 + 1].im;
      d = z[offsetj + 1].re;
      z[offsetjp1 + 1].re = ctemp * temp_re - stemp * d;
      d1 = z[offsetj + 1].im;
      z[offsetjp1 + 1].im = ctemp * temp_im - stemp * d1;
      d = stemp * temp_re + ctemp * d;
      z[offsetj + 1].re = d;
      d1 = stemp * temp_im + ctemp * d1;
      z[offsetj + 1].im = d1;
      temp_re = z[offsetjp1 + 2].re;
      temp_im = z[offsetjp1 + 2].im;
      d = z[offsetj + 2].re;
      z[offsetjp1 + 2].re = ctemp * temp_re - stemp * d;
      d1 = z[offsetj + 2].im;
      z[offsetjp1 + 2].im = ctemp * temp_im - stemp * d1;
      d = stemp * temp_re + ctemp * d;
      z[offsetj + 2].re = d;
      d1 = stemp * temp_im + ctemp * d1;
      z[offsetj + 2].im = d1;
      temp_re = z[offsetjp1 + 3].re;
      temp_im = z[offsetjp1 + 3].im;
      d = z[offsetj + 3].re;
      z[offsetjp1 + 3].re = ctemp * temp_re - stemp * d;
      d1 = z[offsetj + 3].im;
      z[offsetjp1 + 3].im = ctemp * temp_im - stemp * d1;
      d = stemp * temp_re + ctemp * d;
      z[offsetj + 3].re = d;
      d1 = stemp * temp_im + ctemp * d1;
      z[offsetj + 3].im = d1;
    }
  }
}

int xzsteqr(double d[3], double e[2], creal_T z[9])
{
  double work[4];
  double c;
  double r;
  double s;
  double tst;
  int i;
  int info;
  int ix;
  int jtot;
  int l1;
  info = 0;
  work[0] = 0.0;
  work[1] = 0.0;
  work[2] = 0.0;
  work[3] = 0.0;
  jtot = 0;
  l1 = 1;
  int exitg1;
  do {
    exitg1 = 0;
    if (l1 > 3) {
      for (jtot = 0; jtot < 2; jtot++) {
        double p;
        int iscale;
        iscale = jtot;
        p = d[jtot];
        for (ix = jtot + 2; ix < 4; ix++) {
          c = d[ix - 1];
          if (c < p) {
            iscale = ix - 1;
            p = c;
          }
        }
        if (iscale != jtot) {
          d[iscale] = d[jtot];
          d[jtot] = p;
          ix = jtot * 3;
          iscale *= 3;
          tst = z[ix].re;
          c = z[ix].im;
          z[ix] = z[iscale];
          z[iscale].re = tst;
          z[iscale].im = c;
          tst = z[ix + 1].re;
          c = z[ix + 1].im;
          z[ix + 1] = z[iscale + 1];
          z[iscale + 1].re = tst;
          z[iscale + 1].im = c;
          tst = z[ix + 2].re;
          c = z[ix + 2].im;
          z[ix + 2] = z[iscale + 2];
          z[iscale + 2].re = tst;
          z[iscale + 2].im = c;
        }
      }
      exitg1 = 1;
    } else {
      int l;
      int lend;
      int lendsv;
      int lsv;
      int m;
      boolean_T exitg2;
      if (l1 > 1) {
        e[l1 - 2] = 0.0;
      }
      m = l1;
      exitg2 = false;
      while ((!exitg2) && (m < 3)) {
        tst = fabs(e[m - 1]);
        if (tst == 0.0) {
          exitg2 = true;
        } else if (tst <= sqrt(fabs(d[m - 1])) * sqrt(fabs(d[m])) *
                              2.2204460492503131E-16) {
          e[m - 1] = 0.0;
          exitg2 = true;
        } else {
          m++;
        }
      }
      l = l1 - 1;
      lsv = l1;
      lend = m;
      lendsv = m;
      l1 = m + 1;
      if (m != l + 1) {
        double anorm;
        int iscale;
        ix = m - l;
        if (ix <= 0) {
          anorm = 0.0;
        } else {
          anorm = fabs(d[(l + ix) - 1]);
          i = 0;
          exitg2 = false;
          while ((!exitg2) && (i <= ix - 2)) {
            iscale = l + i;
            tst = fabs(d[iscale]);
            if (rtIsNaN(tst)) {
              anorm = rtNaN;
              exitg2 = true;
            } else {
              if (tst > anorm) {
                anorm = tst;
              }
              tst = fabs(e[iscale]);
              if (rtIsNaN(tst)) {
                anorm = rtNaN;
                exitg2 = true;
              } else {
                if (tst > anorm) {
                  anorm = tst;
                }
                i++;
              }
            }
          }
        }
        iscale = 0;
        if (!(anorm == 0.0)) {
          if (rtIsInf(anorm) || rtIsNaN(anorm)) {
            d[0] = rtNaN;
            d[1] = rtNaN;
            d[2] = rtNaN;
            for (ix = 0; ix < 9; ix++) {
              z[ix].re = rtNaN;
              z[ix].im = 0.0;
            }
            exitg1 = 1;
          } else {
            if (anorm > 2.2346346549904327E+153) {
              iscale = 1;
              c_xzlascl(anorm, 2.2346346549904327E+153, ix, d, l + 1);
              d_xzlascl(anorm, 2.2346346549904327E+153, ix - 1, e, l + 1);
            } else if (anorm < 3.02546243347603E-123) {
              iscale = 2;
              c_xzlascl(anorm, 3.02546243347603E-123, ix, d, l + 1);
              d_xzlascl(anorm, 3.02546243347603E-123, ix - 1, e, l + 1);
            }
            if (fabs(d[m - 1]) < fabs(d[l])) {
              lend = lsv;
              l = m - 1;
            }
            if (lend > l + 1) {
              int exitg4;
              do {
                exitg4 = 0;
                if (l + 1 != lend) {
                  m = l + 1;
                  exitg2 = false;
                  while ((!exitg2) && (m < lend)) {
                    tst = fabs(e[m - 1]);
                    if (tst * tst <=
                        4.9303806576313238E-32 * fabs(d[m - 1]) * fabs(d[m]) +
                            2.2250738585072014E-308) {
                      exitg2 = true;
                    } else {
                      m++;
                    }
                  }
                } else {
                  m = lend;
                }
                if (m < lend) {
                  e[m - 1] = 0.0;
                }
                if (m == l + 1) {
                  l++;
                  if (l + 1 > lend) {
                    exitg4 = 1;
                  }
                } else if (m == l + 2) {
                  d[l] = xdlaev2(d[l], e[l], d[l + 1], &c, &work[l], &tst);
                  d[l + 1] = c;
                  work[l + 2] = tst;
                  rotateRight(2, z, l * 3 + 1, work, l + 1, l + 3);
                  e[l] = 0.0;
                  l += 2;
                  if (l + 1 > lend) {
                    exitg4 = 1;
                  }
                } else if (jtot == 90) {
                  exitg4 = 1;
                } else {
                  double g;
                  double p;
                  jtot++;
                  g = (d[l + 1] - d[l]) / (2.0 * e[l]);
                  c = rt_hypotd_snf(g, 1.0);
                  if (!(g >= 0.0)) {
                    c = -c;
                  }
                  g = (d[m - 1] - d[l]) + e[l] / (g + c);
                  tst = 1.0;
                  c = 1.0;
                  p = 0.0;
                  ix = m - 1;
                  for (i = ix; i >= l + 1; i--) {
                    double b;
                    double b_tmp;
                    b_tmp = e[i - 1];
                    b = c * b_tmp;
                    c = xzlartg(g, tst * b_tmp, &s, &r);
                    tst = s;
                    if (i != m - 1) {
                      e[1] = r;
                    }
                    g = d[i] - p;
                    r = (d[i - 1] - g) * s + 2.0 * c * b;
                    p = s * r;
                    d[i] = g + p;
                    g = c * r - b;
                    work[i - 1] = c;
                    work[i + 1] = -s;
                  }
                  rotateRight(m - l, z, l * 3 + 1, work, l + 1, l + 3);
                  d[l] -= p;
                  e[l] = g;
                }
              } while (exitg4 == 0);
            } else {
              int exitg3;
              do {
                exitg3 = 0;
                if (l + 1 != lend) {
                  m = l + 1;
                  exitg2 = false;
                  while ((!exitg2) && (m > lend)) {
                    tst = fabs(e[m - 2]);
                    if (tst * tst <= 4.9303806576313238E-32 * fabs(d[m - 1]) *
                                             fabs(d[m - 2]) +
                                         2.2250738585072014E-308) {
                      exitg2 = true;
                    } else {
                      m--;
                    }
                  }
                } else {
                  m = lend;
                }
                if (m > lend) {
                  e[m - 2] = 0.0;
                }
                if (m == l + 1) {
                  l--;
                  if (l + 1 < lend) {
                    exitg3 = 1;
                  }
                } else if (m == l) {
                  d[l - 1] =
                      xdlaev2(d[l - 1], e[l - 1], d[l], &c, &work[m - 1], &tst);
                  d[l] = c;
                  work[m + 1] = tst;
                  b_rotateRight(2, z, (l - 1) * 3 + 1, work, m, m + 2);
                  e[l - 1] = 0.0;
                  l -= 2;
                  if (l + 1 < lend) {
                    exitg3 = 1;
                  }
                } else if (jtot == 90) {
                  exitg3 = 1;
                } else {
                  double g;
                  double p;
                  jtot++;
                  tst = e[l - 1];
                  g = (d[l - 1] - d[l]) / (2.0 * tst);
                  c = rt_hypotd_snf(g, 1.0);
                  if (!(g >= 0.0)) {
                    c = -c;
                  }
                  g = (d[m - 1] - d[l]) + tst / (g + c);
                  tst = 1.0;
                  c = 1.0;
                  p = 0.0;
                  for (i = m; i <= l; i++) {
                    double b;
                    double b_tmp;
                    b_tmp = e[i - 1];
                    b = c * b_tmp;
                    c = xzlartg(g, tst * b_tmp, &s, &r);
                    tst = s;
                    if (i != m) {
                      e[0] = r;
                    }
                    g = d[i - 1] - p;
                    r = (d[i] - g) * s + 2.0 * c * b;
                    p = s * r;
                    d[i - 1] = g + p;
                    g = c * r - b;
                    work[i - 1] = c;
                    work[i + 1] = s;
                  }
                  b_rotateRight((l - m) + 2, z, (m - 1) * 3 + 1, work, m,
                                m + 2);
                  d[l] -= p;
                  e[l - 1] = g;
                }
              } while (exitg3 == 0);
            }
            if (iscale == 1) {
              ix = lendsv - lsv;
              c_xzlascl(2.2346346549904327E+153, anorm, ix + 1, d, lsv);
              d_xzlascl(2.2346346549904327E+153, anorm, ix, e, lsv);
            } else if (iscale == 2) {
              ix = lendsv - lsv;
              c_xzlascl(3.02546243347603E-123, anorm, ix + 1, d, lsv);
              d_xzlascl(3.02546243347603E-123, anorm, ix, e, lsv);
            }
            if (jtot >= 90) {
              if (e[0] != 0.0) {
                info = 1;
              }
              if (e[1] != 0.0) {
                info++;
              }
              exitg1 = 1;
            }
          }
        }
      }
    }
  } while (exitg1 == 0);
  return info;
}

/* End of code generation (xzsteqr.c) */
