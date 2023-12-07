/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlahqr.c
 *
 * Code generation for function 'xzlahqr'
 *
 */

/* Include files */
#include "xzlahqr.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xzladiv.h"
#include "xzlarfg.h"
#include <math.h>

/* Function Definitions */
int xzlahqr(int ilo, int ihi, creal_T h[9], int iloz, int ihiz, creal_T z[9],
            creal_T w[3])
{
  creal_T v[2];
  creal_T sc;
  creal_T x2;
  int b_i;
  int b_k;
  int i;
  int i1;
  int info;
  int ix0_tmp;
  int j;
  int k;
  info = 0;
  i = (unsigned char)(ilo - 1);
  for (b_i = 0; b_i < i; b_i++) {
    w[b_i] = h[b_i + 3 * b_i];
  }
  i = ihi + 1;
  for (b_i = i; b_i < 4; b_i++) {
    w[b_i - 1] = h[(b_i + 3 * (b_i - 1)) - 1];
  }
  if (ilo == ihi) {
    w[ilo - 1] = h[(ilo + 3 * (ilo - 1)) - 1];
  } else {
    double aa;
    double ab;
    double br;
    double im;
    double smlnum;
    double tst;
    int ix0;
    int kdefl;
    int nz;
    int t_re_tmp_tmp;
    boolean_T exitg1;
    if (ilo <= ihi - 2) {
      h[ihi - 1].re = 0.0;
      h[ihi - 1].im = 0.0;
    }
    i = ilo + 1;
    for (b_i = i; b_i <= ihi; b_i++) {
      t_re_tmp_tmp = (b_i + 3 * (b_i - 2)) - 1;
      tst = h[t_re_tmp_tmp].im;
      if (tst != 0.0) {
        aa = h[t_re_tmp_tmp].re;
        br = fabs(aa) + fabs(tst);
        if (tst == 0.0) {
          sc.re = aa / br;
          sc.im = 0.0;
        } else if (aa == 0.0) {
          sc.re = 0.0;
          sc.im = tst / br;
        } else {
          sc.re = aa / br;
          sc.im = tst / br;
        }
        br = rt_hypotd_snf(sc.re, sc.im);
        if (-sc.im == 0.0) {
          ab = sc.re / br;
          im = 0.0;
        } else if (sc.re == 0.0) {
          ab = 0.0;
          im = -sc.im / br;
        } else {
          ab = sc.re / br;
          im = -sc.im / br;
        }
        h[t_re_tmp_tmp].re = rt_hypotd_snf(aa, tst);
        h[t_re_tmp_tmp].im = 0.0;
        ix0_tmp = (b_i - 1) * 3;
        ix0 = ix0_tmp + b_i;
        t_re_tmp_tmp = ix0 + 3 * (3 - b_i);
        for (k = ix0; k <= t_re_tmp_tmp; k += 3) {
          tst = h[k - 1].im;
          aa = h[k - 1].re;
          h[k - 1].re = ab * aa - im * tst;
          h[k - 1].im = ab * tst + im * aa;
        }
        t_re_tmp_tmp = ix0_tmp + 3;
        for (k = ix0_tmp + 1; k <= t_re_tmp_tmp; k++) {
          tst = h[k - 1].im;
          aa = h[k - 1].re;
          h[k - 1].re = ab * aa - -im * tst;
          h[k - 1].im = ab * tst + -im * aa;
        }
        ix0 = ix0_tmp + iloz;
        t_re_tmp_tmp = (ix0 + ihiz) - iloz;
        for (k = ix0; k <= t_re_tmp_tmp; k++) {
          tst = z[k - 1].im;
          aa = z[k - 1].re;
          z[k - 1].re = ab * aa - -im * tst;
          z[k - 1].im = ab * tst + -im * aa;
        }
      }
    }
    nz = ihiz - iloz;
    smlnum = 2.2250738585072014E-308 *
             ((double)((ihi - ilo) + 1) / 2.2204460492503131E-16);
    kdefl = 0;
    b_i = ihi - 1;
    exitg1 = false;
    while ((!exitg1) && (b_i + 1 >= ilo)) {
      int its;
      int l;
      boolean_T converged;
      boolean_T exitg2;
      l = ilo;
      converged = false;
      its = 0;
      exitg2 = false;
      while ((!exitg2) && (its < 301)) {
        double ab_tmp;
        double s;
        double sx;
        double t_re;
        double tst_tmp;
        boolean_T exitg3;
        k = b_i;
        exitg3 = false;
        while ((!exitg3) && (k + 1 > l)) {
          i = k + 3 * (k - 1);
          ab_tmp = fabs(h[i].re);
          t_re = ab_tmp + fabs(h[i].im);
          if (t_re <= smlnum) {
            exitg3 = true;
          } else {
            ix0_tmp = k + 3 * k;
            br = h[ix0_tmp].re;
            aa = h[ix0_tmp].im;
            tst_tmp = fabs(br) + fabs(aa);
            im = h[i - 1].re;
            sx = h[i - 1].im;
            tst = (fabs(im) + fabs(sx)) + tst_tmp;
            if (tst == 0.0) {
              if (k - 1 >= ilo) {
                tst = fabs(h[k - 1].re);
              }
              if (k + 2 <= ihi) {
                tst += fabs(h[3 * k + 2].re);
              }
            }
            if (ab_tmp <= 2.2204460492503131E-16 * tst) {
              ab_tmp = fabs(h[ix0_tmp - 1].re) + fabs(h[ix0_tmp - 1].im);
              ab = fmax(t_re, ab_tmp);
              tst = fabs(im - br) + fabs(sx - aa);
              aa = fmax(tst_tmp, tst);
              s = aa + ab;
              if (fmin(t_re, ab_tmp) * (ab / s) <=
                  fmax(smlnum, 2.2204460492503131E-16 *
                                   (fmin(tst_tmp, tst) * (aa / s)))) {
                exitg3 = true;
              } else {
                k--;
              }
            } else {
              k--;
            }
          }
        }
        l = k + 1;
        if (k + 1 > ilo) {
          i = k + 3 * (k - 1);
          h[i].re = 0.0;
          h[i].im = 0.0;
        }
        if (k + 1 >= b_i + 1) {
          converged = true;
          exitg2 = true;
        } else {
          double t_im;
          int m;
          boolean_T foundm;
          kdefl++;
          if (kdefl - kdefl / 20 * 20 == 0) {
            ix0_tmp = b_i + 3 * b_i;
            t_re = 0.75 * fabs(h[b_i + 3 * (b_i - 1)].re) + h[ix0_tmp].re;
            t_im = h[ix0_tmp].im;
          } else if (kdefl - kdefl / 10 * 10 == 0) {
            ix0_tmp = k + 3 * k;
            t_re = 0.75 * fabs(h[ix0_tmp + 1].re) + h[ix0_tmp].re;
            t_im = h[ix0_tmp].im;
          } else {
            creal_T u;
            t_re_tmp_tmp = b_i + 3 * b_i;
            br = h[t_re_tmp_tmp].re;
            t_re = br;
            aa = h[t_re_tmp_tmp].im;
            t_im = aa;
            x2 = h[t_re_tmp_tmp - 1];
            b_sqrt(&x2);
            ix0_tmp = b_i + 3 * (b_i - 1);
            sc = h[ix0_tmp];
            b_sqrt(&sc);
            tst = x2.re * sc.re - x2.im * sc.im;
            u.re = tst;
            im = x2.re * sc.im + x2.im * sc.re;
            u.im = im;
            s = fabs(tst) + fabs(im);
            if (s != 0.0) {
              t_re = 0.5 * (h[ix0_tmp - 1].re - br);
              t_im = 0.5 * (h[ix0_tmp - 1].im - aa);
              sx = fabs(t_re) + fabs(t_im);
              s = fmax(s, sx);
              if (t_im == 0.0) {
                sc.re = t_re / s;
                sc.im = 0.0;
              } else if (t_re == 0.0) {
                sc.re = 0.0;
                sc.im = t_im / s;
              } else {
                sc.re = t_re / s;
                sc.im = t_im / s;
              }
              if (im == 0.0) {
                x2.re = tst / s;
                x2.im = 0.0;
              } else if (tst == 0.0) {
                x2.re = 0.0;
                x2.im = im / s;
              } else {
                x2.re = tst / s;
                x2.im = im / s;
              }
              ab_tmp = sc.re * sc.im;
              ab = x2.re * x2.re - x2.im * x2.im;
              tst_tmp = x2.re * x2.im;
              x2.re = (sc.re * sc.re - sc.im * sc.im) + ab;
              x2.im = (ab_tmp + ab_tmp) + (tst_tmp + tst_tmp);
              b_sqrt(&x2);
              sc.re = s * x2.re;
              sc.im = s * x2.im;
              if (sx > 0.0) {
                if (t_im == 0.0) {
                  x2.re = t_re / sx;
                  x2.im = 0.0;
                } else if (t_re == 0.0) {
                  x2.re = 0.0;
                  x2.im = t_im / sx;
                } else {
                  x2.re = t_re / sx;
                  x2.im = t_im / sx;
                }
                if (x2.re * sc.re + x2.im * sc.im < 0.0) {
                  sc.re = -sc.re;
                  sc.im = -sc.im;
                }
              }
              x2.re = t_re + sc.re;
              x2.im = t_im + sc.im;
              x2 = xzladiv(u, x2);
              t_re = br - (tst * x2.re - im * x2.im);
              t_im = aa - (tst * x2.im + im * x2.re);
            }
          }
          foundm = false;
          m = b_i;
          exitg3 = false;
          while ((!exitg3) && (m > k + 1)) {
            tst = h[4].re - t_re;
            br = h[4].im - t_im;
            aa = h[5].re;
            s = (fabs(tst) + fabs(br)) + fabs(aa);
            if (br == 0.0) {
              ab = tst / s;
              im = 0.0;
            } else if (tst == 0.0) {
              ab = 0.0;
              im = br / s;
            } else {
              ab = tst / s;
              im = br / s;
            }
            sc.re = ab;
            sc.im = im;
            aa /= s;
            v[0] = sc;
            v[1].re = aa;
            v[1].im = 0.0;
            if (fabs(h[1].re) * fabs(aa) <=
                2.2204460492503131E-16 * ((fabs(ab) + fabs(im)) *
                                          ((fabs(h[4].re) + fabs(h[4].im)) +
                                           (fabs(h[8].re) + fabs(h[8].im))))) {
              foundm = true;
              exitg3 = true;
            } else {
              m = 1;
            }
          }
          if (!foundm) {
            ix0_tmp = k + 3 * k;
            tst = h[ix0_tmp].re - t_re;
            br = h[ix0_tmp].im - t_im;
            aa = h[(k + 3 * k) + 1].re;
            s = (fabs(tst) + fabs(br)) + fabs(aa);
            if (br == 0.0) {
              v[0].re = tst / s;
              v[0].im = 0.0;
            } else if (tst == 0.0) {
              v[0].re = 0.0;
              v[0].im = br / s;
            } else {
              v[0].re = tst / s;
              v[0].im = br / s;
            }
            aa /= s;
            v[1].re = aa;
            v[1].im = 0.0;
          }
          if (m <= b_i) {
            i1 = (unsigned char)(b_i + 1);
          }
          for (b_k = m; b_k <= b_i; b_k++) {
            if (b_k > m) {
              v[0] = h[1];
              v[1] = h[2];
            }
            sc = b_xzlarfg(&v[0], &v[1]);
            if (b_k > m) {
              h[1] = v[0];
              h[2].re = 0.0;
              h[2].im = 0.0;
            }
            x2 = v[1];
            tst = sc.re * v[1].re - sc.im * v[1].im;
            for (j = b_k; j < 4; j++) {
              ix0_tmp = b_k + 3 * (j - 1);
              ab = h[ix0_tmp - 1].re;
              im = h[ix0_tmp - 1].im;
              br = h[ix0_tmp].re;
              aa = h[ix0_tmp].im;
              t_re = (sc.re * ab - -sc.im * im) + tst * br;
              t_im = (sc.re * im + -sc.im * ab) + tst * aa;
              ab -= t_re;
              im -= t_im;
              h[ix0_tmp - 1].re = ab;
              h[ix0_tmp - 1].im = im;
              br -= t_re * x2.re - t_im * x2.im;
              aa -= t_re * x2.im + t_im * x2.re;
              h[ix0_tmp].re = br;
              h[ix0_tmp].im = aa;
            }
            for (j = 0; j < i1; j++) {
              ix0_tmp = j + 3 * (b_k - 1);
              ab = h[ix0_tmp].re;
              im = h[ix0_tmp].im;
              t_re_tmp_tmp = j + 3 * b_k;
              br = h[t_re_tmp_tmp].re;
              aa = h[t_re_tmp_tmp].im;
              t_re = (sc.re * ab - sc.im * im) + tst * br;
              t_im = (sc.re * im + sc.im * ab) + tst * aa;
              ab -= t_re;
              im -= t_im;
              h[ix0_tmp].re = ab;
              h[ix0_tmp].im = im;
              br -= t_re * x2.re - t_im * -x2.im;
              aa -= t_re * -x2.im + t_im * x2.re;
              h[t_re_tmp_tmp].re = br;
              h[t_re_tmp_tmp].im = aa;
            }
            for (j = iloz; j <= ihiz; j++) {
              ix0_tmp = (j + 3 * (b_k - 1)) - 1;
              ab = z[ix0_tmp].re;
              im = z[ix0_tmp].im;
              t_re_tmp_tmp = (j + 3 * b_k) - 1;
              br = z[t_re_tmp_tmp].re;
              aa = z[t_re_tmp_tmp].im;
              t_re = (sc.re * ab - sc.im * im) + tst * br;
              t_im = (sc.re * im + sc.im * ab) + tst * aa;
              ab -= t_re;
              im -= t_im;
              z[ix0_tmp].re = ab;
              z[ix0_tmp].im = im;
              br -= t_re * x2.re - t_im * -x2.im;
              aa -= t_re * -x2.im + t_im * x2.re;
              z[t_re_tmp_tmp].re = br;
              z[t_re_tmp_tmp].im = aa;
            }
            if ((b_k == m) && (m > k + 1)) {
              br = rt_hypotd_snf(1.0 - sc.re, 0.0 - sc.im);
              if (0.0 - sc.im == 0.0) {
                ab = (1.0 - sc.re) / br;
                im = 0.0;
              } else if (1.0 - sc.re == 0.0) {
                ab = 0.0;
                im = (0.0 - sc.im) / br;
              } else {
                ab = (1.0 - sc.re) / br;
                im = (0.0 - sc.im) / br;
              }
              ab_tmp = h[5].re;
              t_re = h[5].im;
              aa = ab_tmp * -im + t_re * ab;
              ab_tmp = ab_tmp * ab - t_re * -im;
              h[5].re = ab_tmp;
              h[5].im = aa;
              for (j = 2; j <= b_i + 1; j++) {
                if (j != 3) {
                  ab_tmp = h[7].im;
                  t_re = h[7].re;
                  aa = ab * ab_tmp + im * t_re;
                  t_re = ab * t_re - im * ab_tmp;
                  h[7].re = t_re;
                  h[7].im = aa;
                  ab_tmp = h[3].im;
                  t_re = h[3].re;
                  aa = ab * ab_tmp + -im * t_re;
                  t_re = ab * t_re - -im * ab_tmp;
                  h[3].re = t_re;
                  h[3].im = aa;
                  ix0 = iloz + 3;
                  i = (iloz + nz) + 3;
                  for (ix0_tmp = ix0; ix0_tmp <= i; ix0_tmp++) {
                    tst = z[ix0_tmp - 1].im;
                    aa = z[ix0_tmp - 1].re;
                    z[ix0_tmp - 1].re = ab * aa - -im * tst;
                    z[ix0_tmp - 1].im = ab * tst + -im * aa;
                  }
                }
              }
            }
          }
          ix0_tmp = b_i + 3 * (b_i - 1);
          sc = h[ix0_tmp];
          if (h[ix0_tmp].im != 0.0) {
            tst = rt_hypotd_snf(h[ix0_tmp].re, h[ix0_tmp].im);
            h[ix0_tmp].re = tst;
            h[ix0_tmp].im = 0.0;
            if (sc.im == 0.0) {
              ab = sc.re / tst;
              im = 0.0;
            } else if (sc.re == 0.0) {
              ab = 0.0;
              im = sc.im / tst;
            } else {
              ab = sc.re / tst;
              im = sc.im / tst;
            }
            if (b_i + 1 < 3) {
              aa = ab * h[7].im + -im * h[7].re;
              h[7].re = ab * h[7].re - -im * h[7].im;
              h[7].im = aa;
            }
            ix0 = b_i * 3;
            i = ix0 + b_i;
            for (k = ix0 + 1; k <= i; k++) {
              tst = h[k - 1].im;
              aa = h[k - 1].re;
              h[k - 1].re = ab * aa - im * tst;
              h[k - 1].im = ab * tst + im * aa;
            }
            ix0 = b_i * 3 + iloz;
            i = ix0 + nz;
            for (k = ix0; k <= i; k++) {
              tst = z[k - 1].im;
              aa = z[k - 1].re;
              z[k - 1].re = ab * aa - im * tst;
              z[k - 1].im = ab * tst + im * aa;
            }
          }
          its++;
        }
      }
      if (!converged) {
        info = b_i + 1;
        exitg1 = true;
      } else {
        w[b_i] = h[b_i + 3 * b_i];
        kdefl = 0;
        b_i = l - 2;
      }
    }
    h[2].re = 0.0;
    h[2].im = 0.0;
  }
  return info;
}

/* End of code generation (xzlahqr.c) */
