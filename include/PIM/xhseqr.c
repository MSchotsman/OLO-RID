/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xhseqr.c
 *
 * Code generation for function 'xhseqr'
 *
 */

/* Include files */
#include "xhseqr.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xzladiv.h"
#include "xzlarfg.h"
#include <math.h>

/* Function Definitions */
int xhseqr(creal_T h[9], creal_T z[9])
{
  creal_T v[2];
  creal_T sc;
  creal_T x2;
  double aa;
  double ab;
  double ar_tmp;
  double im;
  double tst;
  int b_k;
  int i;
  int info;
  int ix0;
  int ix0_tmp;
  int j;
  int k;
  int kdefl;
  int m;
  boolean_T exitg1;
  info = 0;
  h[2].re = 0.0;
  h[2].im = 0.0;
  for (i = 0; i < 2; i++) {
    m = (i + 3 * i) + 1;
    aa = h[m].im;
    if (aa != 0.0) {
      ar_tmp = h[m].re;
      tst = fabs(ar_tmp) + fabs(aa);
      if (aa == 0.0) {
        sc.re = ar_tmp / tst;
        sc.im = 0.0;
      } else if (ar_tmp == 0.0) {
        sc.re = 0.0;
        sc.im = aa / tst;
      } else {
        sc.re = ar_tmp / tst;
        sc.im = aa / tst;
      }
      tst = rt_hypotd_snf(sc.re, sc.im);
      if (-sc.im == 0.0) {
        ab = sc.re / tst;
        im = 0.0;
      } else if (sc.re == 0.0) {
        ab = 0.0;
        im = -sc.im / tst;
      } else {
        ab = sc.re / tst;
        im = -sc.im / tst;
      }
      h[m].re = rt_hypotd_snf(ar_tmp, aa);
      h[m].im = 0.0;
      ix0_tmp = (i + 1) * 3;
      ix0 = (ix0_tmp + i) + 2;
      m = ix0 + 3 * (1 - i);
      for (k = ix0; k <= m; k += 3) {
        tst = h[k - 1].im;
        aa = h[k - 1].re;
        h[k - 1].re = ab * aa - im * tst;
        h[k - 1].im = ab * tst + im * aa;
      }
      m = ix0_tmp + 3;
      for (k = ix0_tmp + 1; k <= m; k++) {
        tst = h[k - 1].im;
        aa = h[k - 1].re;
        h[k - 1].re = ab * aa - -im * tst;
        h[k - 1].im = ab * tst + -im * aa;
        tst = z[k - 1].im;
        aa = z[k - 1].re;
        z[k - 1].re = ab * aa - -im * tst;
        z[k - 1].im = ab * tst + -im * aa;
      }
    }
  }
  kdefl = 0;
  i = 2;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    int its;
    int l;
    boolean_T converged;
    boolean_T exitg2;
    l = -1;
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
      k = i;
      exitg3 = false;
      while ((!exitg3) && (k + 1 > l + 2)) {
        m = k + 3 * (k - 1);
        ab_tmp = fabs(h[m].re);
        t_re = ab_tmp + fabs(h[m].im);
        if (t_re <= 3.0062525400134592E-292) {
          exitg3 = true;
        } else {
          ix0 = k + 3 * k;
          ar_tmp = h[ix0].re;
          aa = h[ix0].im;
          tst_tmp = fabs(ar_tmp) + fabs(aa);
          im = h[m - 1].re;
          sx = h[m - 1].im;
          tst = (fabs(im) + fabs(sx)) + tst_tmp;
          if (tst == 0.0) {
            if (k - 1 >= 1) {
              tst = fabs(h[k - 1].re);
            }
            if (k + 2 <= 3) {
              tst += fabs(h[3 * k + 2].re);
            }
          }
          if (ab_tmp <= 2.2204460492503131E-16 * tst) {
            ab_tmp = fabs(h[ix0 - 1].re) + fabs(h[ix0 - 1].im);
            ab = fmax(t_re, ab_tmp);
            tst = fabs(im - ar_tmp) + fabs(sx - aa);
            aa = fmax(tst_tmp, tst);
            s = aa + ab;
            if (fmin(t_re, ab_tmp) * (ab / s) <=
                fmax(3.0062525400134592E-292,
                     2.2204460492503131E-16 *
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
      l = k - 1;
      if (k + 1 > 1) {
        m = k + 3 * (k - 1);
        h[m].re = 0.0;
        h[m].im = 0.0;
      }
      if (k + 1 >= i + 1) {
        converged = true;
        exitg2 = true;
      } else {
        double t_im;
        boolean_T foundm;
        kdefl++;
        if (kdefl - kdefl / 20 * 20 == 0) {
          ix0 = i + 3 * i;
          t_re = 0.75 * fabs(h[i + 3 * (i - 1)].re) + h[ix0].re;
          t_im = h[ix0].im;
        } else if (kdefl - kdefl / 10 * 10 == 0) {
          ix0 = k + 3 * k;
          t_re = 0.75 * fabs(h[ix0 + 1].re) + h[ix0].re;
          t_im = h[ix0].im;
        } else {
          creal_T u;
          ix0 = i + 3 * i;
          ar_tmp = h[ix0].re;
          t_re = ar_tmp;
          aa = h[ix0].im;
          t_im = aa;
          x2 = h[ix0 - 1];
          b_sqrt(&x2);
          ix0 = i + 3 * (i - 1);
          sc = h[ix0];
          b_sqrt(&sc);
          tst = x2.re * sc.re - x2.im * sc.im;
          u.re = tst;
          im = x2.re * sc.im + x2.im * sc.re;
          u.im = im;
          s = fabs(tst) + fabs(im);
          if (s != 0.0) {
            t_re = 0.5 * (h[ix0 - 1].re - ar_tmp);
            t_im = 0.5 * (h[ix0 - 1].im - aa);
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
            t_re = ar_tmp - (tst * x2.re - im * x2.im);
            t_im = aa - (tst * x2.im + im * x2.re);
          }
        }
        foundm = false;
        m = i;
        exitg3 = false;
        while ((!exitg3) && (m > k + 1)) {
          tst = h[4].re - t_re;
          ar_tmp = h[4].im - t_im;
          aa = h[5].re;
          s = (fabs(tst) + fabs(ar_tmp)) + fabs(aa);
          if (ar_tmp == 0.0) {
            ab = tst / s;
            im = 0.0;
          } else if (tst == 0.0) {
            ab = 0.0;
            im = ar_tmp / s;
          } else {
            ab = tst / s;
            im = ar_tmp / s;
          }
          sc.re = ab;
          sc.im = im;
          aa /= s;
          v[0] = sc;
          v[1].re = aa;
          v[1].im = 0.0;
          if (fabs(h[1].re) * fabs(aa) <=
              2.2204460492503131E-16 *
                  ((fabs(ab) + fabs(im)) * ((fabs(h[4].re) + fabs(h[4].im)) +
                                            (fabs(h[8].re) + fabs(h[8].im))))) {
            foundm = true;
            exitg3 = true;
          } else {
            m = 1;
          }
        }
        if (!foundm) {
          ix0 = k + 3 * k;
          tst = h[ix0].re - t_re;
          ar_tmp = h[ix0].im - t_im;
          aa = h[(k + 3 * k) + 1].re;
          s = (fabs(tst) + fabs(ar_tmp)) + fabs(aa);
          if (ar_tmp == 0.0) {
            v[0].re = tst / s;
            v[0].im = 0.0;
          } else if (tst == 0.0) {
            v[0].re = 0.0;
            v[0].im = ar_tmp / s;
          } else {
            v[0].re = tst / s;
            v[0].im = ar_tmp / s;
          }
          aa /= s;
          v[1].re = aa;
          v[1].im = 0.0;
        }
        for (b_k = m; b_k <= i; b_k++) {
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
            ix0 = b_k + 3 * (j - 1);
            ab = h[ix0 - 1].re;
            im = h[ix0 - 1].im;
            ar_tmp = h[ix0].re;
            aa = h[ix0].im;
            t_re = (sc.re * ab - -sc.im * im) + tst * ar_tmp;
            t_im = (sc.re * im + -sc.im * ab) + tst * aa;
            ab -= t_re;
            im -= t_im;
            h[ix0 - 1].re = ab;
            h[ix0 - 1].im = im;
            ar_tmp -= t_re * x2.re - t_im * x2.im;
            aa -= t_re * x2.im + t_im * x2.re;
            h[ix0].re = ar_tmp;
            h[ix0].im = aa;
          }
          for (j = 0; j <= i; j++) {
            ix0 = j + 3 * (b_k - 1);
            ab = h[ix0].re;
            im = h[ix0].im;
            ix0_tmp = j + 3 * b_k;
            ar_tmp = h[ix0_tmp].re;
            aa = h[ix0_tmp].im;
            t_re = (sc.re * ab - sc.im * im) + tst * ar_tmp;
            t_im = (sc.re * im + sc.im * ab) + tst * aa;
            ab -= t_re;
            im -= t_im;
            h[ix0].re = ab;
            h[ix0].im = im;
            ar_tmp -= t_re * x2.re - t_im * -x2.im;
            aa -= t_re * -x2.im + t_im * x2.re;
            h[ix0_tmp].re = ar_tmp;
            h[ix0_tmp].im = aa;
          }
          ix0 = 3 * (b_k - 1);
          ab = z[ix0].re;
          im = z[ix0].im;
          ar_tmp = z[3 * b_k].re;
          aa = z[3 * b_k].im;
          t_re = (sc.re * ab - sc.im * im) + tst * ar_tmp;
          t_im = (sc.re * im + sc.im * ab) + tst * aa;
          ab -= t_re;
          im -= t_im;
          z[ix0].re = ab;
          z[ix0].im = im;
          ar_tmp -= t_re * v[1].re - t_im * -v[1].im;
          aa -= t_re * -v[1].im + t_im * v[1].re;
          z[3 * b_k].re = ar_tmp;
          z[3 * b_k].im = aa;
          ab = z[ix0 + 1].re;
          im = z[ix0 + 1].im;
          ix0_tmp = 3 * b_k + 1;
          ar_tmp = z[ix0_tmp].re;
          aa = z[ix0_tmp].im;
          t_re = (sc.re * ab - sc.im * im) + tst * ar_tmp;
          t_im = (sc.re * im + sc.im * ab) + tst * aa;
          ab -= t_re;
          im -= t_im;
          z[ix0 + 1].re = ab;
          z[ix0 + 1].im = im;
          ar_tmp -= t_re * v[1].re - t_im * -v[1].im;
          aa -= t_re * -v[1].im + t_im * v[1].re;
          z[ix0_tmp].re = ar_tmp;
          z[ix0_tmp].im = aa;
          ab = z[ix0 + 2].re;
          im = z[ix0 + 2].im;
          ix0_tmp = 3 * b_k + 2;
          ar_tmp = z[ix0_tmp].re;
          aa = z[ix0_tmp].im;
          t_re = (sc.re * ab - sc.im * im) + tst * ar_tmp;
          t_im = (sc.re * im + sc.im * ab) + tst * aa;
          ab -= t_re;
          im -= t_im;
          z[ix0 + 2].re = ab;
          z[ix0 + 2].im = im;
          ar_tmp -= t_re * v[1].re - t_im * -v[1].im;
          aa -= t_re * -v[1].im + t_im * v[1].re;
          z[ix0_tmp].re = ar_tmp;
          z[ix0_tmp].im = aa;
          if ((b_k == m) && (m > k + 1)) {
            tst = rt_hypotd_snf(1.0 - sc.re, 0.0 - sc.im);
            if (0.0 - sc.im == 0.0) {
              ab = (1.0 - sc.re) / tst;
              im = 0.0;
            } else if (1.0 - sc.re == 0.0) {
              ab = 0.0;
              im = (0.0 - sc.im) / tst;
            } else {
              ab = (1.0 - sc.re) / tst;
              im = (0.0 - sc.im) / tst;
            }
            ab_tmp = h[5].re;
            t_re = h[5].im;
            aa = ab_tmp * -im + t_re * ab;
            ab_tmp = ab_tmp * ab - t_re * -im;
            h[5].re = ab_tmp;
            h[5].im = aa;
            for (j = 2; j <= i + 1; j++) {
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
                ab_tmp = z[3].im;
                t_re = z[3].re;
                aa = ab * ab_tmp + -im * t_re;
                t_re = ab * t_re - -im * ab_tmp;
                z[3].re = t_re;
                z[3].im = aa;
                ab_tmp = z[4].im;
                t_re = z[4].re;
                aa = ab * ab_tmp + -im * t_re;
                t_re = ab * t_re - -im * ab_tmp;
                z[4].re = t_re;
                z[4].im = aa;
                ab_tmp = z[5].im;
                t_re = z[5].re;
                aa = ab * ab_tmp + -im * t_re;
                t_re = ab * t_re - -im * ab_tmp;
                z[5].re = t_re;
                z[5].im = aa;
              }
            }
          }
        }
        ix0 = i + 3 * (i - 1);
        sc = h[ix0];
        if (h[ix0].im != 0.0) {
          tst = rt_hypotd_snf(h[ix0].re, h[ix0].im);
          h[ix0].re = tst;
          h[ix0].im = 0.0;
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
          if (i + 1 < 3) {
            aa = ab * h[7].im + -im * h[7].re;
            h[7].re = ab * h[7].re - -im * h[7].im;
            h[7].im = aa;
          }
          ix0_tmp = i * 3;
          m = ix0_tmp + i;
          for (k = ix0_tmp + 1; k <= m; k++) {
            tst = h[k - 1].im;
            aa = h[k - 1].re;
            h[k - 1].re = ab * aa - im * tst;
            h[k - 1].im = ab * tst + im * aa;
          }
          m = ix0_tmp + 3;
          for (k = ix0_tmp + 1; k <= m; k++) {
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
      info = i + 1;
      exitg1 = true;
    } else {
      kdefl = 0;
      i = l;
    }
  }
  h[2].re = 0.0;
  h[2].im = 0.0;
  return info;
}

/* End of code generation (xhseqr.c) */
