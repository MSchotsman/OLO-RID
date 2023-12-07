/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * norm.c
 *
 * Code generation for function 'norm'
 *
 */

/* Include files */
#include "norm.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xrotg.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
double b_norm(const creal_T x[9])
{
  creal_T A[9];
  double absx;
  double f;
  double sqds;
  double y;
  double ztest;
  int ix;
  int iy;
  int jj;
  int k;
  int q;
  y = 0.0;
  for (ix = 0; ix < 3; ix++) {
    absx = rt_hypotd_snf(x[3 * ix].re, x[3 * ix].im);
    if (rtIsNaN(absx) || (absx > y)) {
      y = absx;
    }
    iy = 3 * ix + 1;
    absx = rt_hypotd_snf(x[iy].re, x[iy].im);
    if (rtIsNaN(absx) || (absx > y)) {
      y = absx;
    }
    iy = 3 * ix + 2;
    absx = rt_hypotd_snf(x[iy].re, x[iy].im);
    if (rtIsNaN(absx) || (absx > y)) {
      y = absx;
    }
  }
  if ((!rtIsInf(y)) && (!rtIsNaN(y))) {
    creal_T e[3];
    creal_T s[3];
    creal_T work[3];
    double brm;
    double d;
    double nrm;
    double re;
    double scale;
    double snorm;
    double t_im;
    double t_re;
    int iter;
    int nmqp1_tmp;
    int qjj;
    int qp1;
    memcpy(&A[0], &x[0], 9U * sizeof(creal_T));
    s[0].re = 0.0;
    s[0].im = 0.0;
    e[0].re = 0.0;
    e[0].im = 0.0;
    work[0].re = 0.0;
    work[0].im = 0.0;
    s[1].re = 0.0;
    s[1].im = 0.0;
    e[1].re = 0.0;
    e[1].im = 0.0;
    work[1].re = 0.0;
    work[1].im = 0.0;
    s[2].re = 0.0;
    s[2].im = 0.0;
    e[2].re = 0.0;
    e[2].im = 0.0;
    work[2].re = 0.0;
    work[2].im = 0.0;
    for (q = 0; q < 2; q++) {
      boolean_T apply_transform;
      qp1 = q + 2;
      iter = q + 3 * q;
      nmqp1_tmp = 2 - q;
      apply_transform = false;
      nrm = xnrm2(3 - q, A, iter + 1);
      if (nrm > 0.0) {
        apply_transform = true;
        absx = A[iter].re;
        ztest = A[iter].im;
        if ((absx == 0.0) && (ztest == 0.0)) {
          scale = 0.0;
          s[q].re = nrm;
          s[q].im = 0.0;
        } else {
          sqds = nrm / rt_hypotd_snf(absx, ztest);
          nrm = sqds * absx;
          scale = sqds * ztest;
          s[q].re = nrm;
          s[q].im = scale;
        }
        if (rt_hypotd_snf(nrm, scale) >= 1.0020841800044864E-292) {
          if (scale == 0.0) {
            t_re = 1.0 / nrm;
            t_im = 0.0;
          } else if (nrm == 0.0) {
            t_re = 0.0;
            t_im = -(1.0 / scale);
          } else {
            brm = fabs(nrm);
            f = fabs(scale);
            if (brm > f) {
              brm = scale / nrm;
              d = nrm + brm * scale;
              t_re = (brm * 0.0 + 1.0) / d;
              t_im = (0.0 - brm) / d;
            } else if (f == brm) {
              if (nrm > 0.0) {
                d = 0.5;
              } else {
                d = -0.5;
              }
              if (scale > 0.0) {
                scale = 0.5;
              } else {
                scale = -0.5;
              }
              t_re = (d + 0.0 * scale) / brm;
              t_im = (0.0 * d - scale) / brm;
            } else {
              brm = nrm / scale;
              d = scale + brm * nrm;
              t_re = brm / d;
              t_im = (brm * 0.0 - 1.0) / d;
            }
          }
          ix = (iter - q) + 3;
          for (k = iter + 1; k <= ix; k++) {
            sqds = A[k - 1].im;
            absx = A[k - 1].re;
            A[k - 1].re = t_re * absx - t_im * sqds;
            A[k - 1].im = t_re * sqds + t_im * absx;
          }
        } else {
          ix = (iter - q) + 3;
          for (k = iter + 1; k <= ix; k++) {
            nrm = A[k - 1].re;
            sqds = A[k - 1].im;
            absx = s[q].re;
            ztest = s[q].im;
            if (ztest == 0.0) {
              if (sqds == 0.0) {
                re = nrm / absx;
                scale = 0.0;
              } else if (nrm == 0.0) {
                re = 0.0;
                scale = sqds / absx;
              } else {
                re = nrm / absx;
                scale = sqds / absx;
              }
            } else if (absx == 0.0) {
              if (nrm == 0.0) {
                re = sqds / ztest;
                scale = 0.0;
              } else if (sqds == 0.0) {
                re = 0.0;
                scale = -(nrm / ztest);
              } else {
                re = sqds / ztest;
                scale = -(nrm / ztest);
              }
            } else {
              brm = fabs(absx);
              f = fabs(ztest);
              if (brm > f) {
                brm = ztest / absx;
                d = absx + brm * ztest;
                re = (nrm + brm * sqds) / d;
                scale = (sqds - brm * nrm) / d;
              } else if (f == brm) {
                if (absx > 0.0) {
                  d = 0.5;
                } else {
                  d = -0.5;
                }
                if (ztest > 0.0) {
                  scale = 0.5;
                } else {
                  scale = -0.5;
                }
                re = (nrm * d + sqds * scale) / brm;
                scale = (sqds * d - nrm * scale) / brm;
              } else {
                brm = absx / ztest;
                d = ztest + brm * absx;
                re = (brm * nrm + sqds) / d;
                scale = (brm * sqds - nrm) / d;
              }
            }
            A[k - 1].re = re;
            A[k - 1].im = scale;
          }
        }
        A[iter].re++;
        s[q].re = -s[q].re;
        s[q].im = -s[q].im;
      } else {
        s[q].re = 0.0;
        s[q].im = 0.0;
      }
      for (jj = qp1; jj < 4; jj++) {
        qjj = q + 3 * (jj - 1);
        if (apply_transform) {
          t_re = 0.0;
          t_im = 0.0;
          for (k = 0; k <= nmqp1_tmp; k++) {
            ix = iter + k;
            sqds = A[ix].re;
            iy = qjj + k;
            nrm = A[iy].im;
            absx = A[ix].im;
            ztest = A[iy].re;
            t_re += sqds * ztest + absx * nrm;
            t_im += sqds * nrm - absx * ztest;
          }
          absx = A[iter].re;
          ztest = A[iter].im;
          if (ztest == 0.0) {
            if (t_im == 0.0) {
              f = t_re / absx;
              t_im = 0.0;
            } else if (t_re == 0.0) {
              f = 0.0;
              t_im /= absx;
            } else {
              f = t_re / absx;
              t_im /= absx;
            }
          } else if (absx == 0.0) {
            if (t_re == 0.0) {
              f = t_im / ztest;
              t_im = 0.0;
            } else if (t_im == 0.0) {
              f = 0.0;
              t_im = -(t_re / ztest);
            } else {
              f = t_im / ztest;
              t_im = -(t_re / ztest);
            }
          } else {
            brm = fabs(absx);
            f = fabs(ztest);
            if (brm > f) {
              brm = ztest / absx;
              d = absx + brm * ztest;
              f = (t_re + brm * t_im) / d;
              t_im = (t_im - brm * t_re) / d;
            } else if (f == brm) {
              if (absx > 0.0) {
                d = 0.5;
              } else {
                d = -0.5;
              }
              if (ztest > 0.0) {
                scale = 0.5;
              } else {
                scale = -0.5;
              }
              f = (t_re * d + t_im * scale) / brm;
              t_im = (t_im * d - t_re * scale) / brm;
            } else {
              brm = absx / ztest;
              d = ztest + brm * absx;
              f = (brm * t_re + t_im) / d;
              t_im = (brm * t_im - t_re) / d;
            }
          }
          if ((!(-f == 0.0)) || (!(-t_im == 0.0))) {
            for (k = 0; k <= nmqp1_tmp; k++) {
              ix = iter + k;
              sqds = A[ix].im;
              nrm = A[ix].re;
              ix = qjj + k;
              A[ix].re += -f * nrm - -t_im * sqds;
              A[ix].im += -f * sqds + -t_im * nrm;
            }
          }
        }
        e[jj - 1].re = A[qjj].re;
        e[jj - 1].im = -A[qjj].im;
      }
      if (q + 1 <= 1) {
        nrm = b_xnrm2(e);
        if (nrm == 0.0) {
          e[0].re = 0.0;
          e[0].im = 0.0;
        } else {
          if ((e[1].re == 0.0) && (e[1].im == 0.0)) {
            e[0].re = nrm;
            e[0].im = 0.0;
          } else {
            absx = nrm / rt_hypotd_snf(e[1].re, e[1].im);
            e[0].re = absx * e[1].re;
            e[0].im = absx * e[1].im;
          }
          absx = e[0].re;
          ztest = e[0].im;
          if (rt_hypotd_snf(e[0].re, e[0].im) >= 1.0020841800044864E-292) {
            if (e[0].im == 0.0) {
              t_re = 1.0 / e[0].re;
              t_im = 0.0;
            } else if (e[0].re == 0.0) {
              t_re = 0.0;
              t_im = -(1.0 / e[0].im);
            } else {
              brm = fabs(e[0].re);
              f = fabs(e[0].im);
              if (brm > f) {
                brm = e[0].im / e[0].re;
                d = e[0].re + brm * e[0].im;
                t_re = (brm * 0.0 + 1.0) / d;
                t_im = (0.0 - brm) / d;
              } else if (f == brm) {
                if (e[0].re > 0.0) {
                  d = 0.5;
                } else {
                  d = -0.5;
                }
                if (e[0].im > 0.0) {
                  scale = 0.5;
                } else {
                  scale = -0.5;
                }
                t_re = (d + 0.0 * scale) / brm;
                t_im = (0.0 * d - scale) / brm;
              } else {
                brm = e[0].re / e[0].im;
                d = e[0].im + brm * e[0].re;
                t_re = brm / d;
                t_im = (brm * 0.0 - 1.0) / d;
              }
            }
            for (k = qp1; k < 4; k++) {
              sqds = e[k - 1].im;
              absx = e[k - 1].re;
              e[k - 1].re = t_re * absx - t_im * sqds;
              e[k - 1].im = t_re * sqds + t_im * absx;
            }
          } else {
            for (k = qp1; k < 4; k++) {
              nrm = e[k - 1].re;
              sqds = e[k - 1].im;
              if (ztest == 0.0) {
                if (sqds == 0.0) {
                  re = nrm / absx;
                  scale = 0.0;
                } else if (nrm == 0.0) {
                  re = 0.0;
                  scale = sqds / absx;
                } else {
                  re = nrm / absx;
                  scale = sqds / absx;
                }
              } else if (absx == 0.0) {
                if (nrm == 0.0) {
                  re = sqds / ztest;
                  scale = 0.0;
                } else if (sqds == 0.0) {
                  re = 0.0;
                  scale = -(nrm / ztest);
                } else {
                  re = sqds / ztest;
                  scale = -(nrm / ztest);
                }
              } else {
                brm = fabs(absx);
                f = fabs(ztest);
                if (brm > f) {
                  brm = ztest / absx;
                  d = absx + brm * ztest;
                  re = (nrm + brm * sqds) / d;
                  scale = (sqds - brm * nrm) / d;
                } else if (f == brm) {
                  if (absx > 0.0) {
                    d = 0.5;
                  } else {
                    d = -0.5;
                  }
                  if (ztest > 0.0) {
                    scale = 0.5;
                  } else {
                    scale = -0.5;
                  }
                  re = (nrm * d + sqds * scale) / brm;
                  scale = (sqds * d - nrm * scale) / brm;
                } else {
                  brm = absx / ztest;
                  d = ztest + brm * absx;
                  re = (brm * nrm + sqds) / d;
                  scale = (brm * sqds - nrm) / d;
                }
              }
              e[k - 1].re = re;
              e[k - 1].im = scale;
            }
          }
          t_re = e[1].re + 1.0;
          e[1].re++;
          e[0].re = -e[0].re;
          for (jj = qp1; jj < 4; jj++) {
            work[jj - 1].re = 0.0;
            work[jj - 1].im = 0.0;
          }
          for (jj = qp1; jj < 4; jj++) {
            absx = e[jj - 1].re;
            ztest = e[jj - 1].im;
            if ((!(absx == 0.0)) || (!(ztest == 0.0))) {
              ix = q + 3 * (jj - 1);
              sqds = A[ix + 1].im;
              nrm = A[ix + 1].re;
              work[q + 1].re += absx * nrm - ztest * sqds;
              work[q + 1].im += absx * sqds + ztest * nrm;
              sqds = A[ix + 2].im;
              nrm = A[ix + 2].re;
              work[q + 2].re += absx * nrm - ztest * sqds;
              work[q + 2].im += absx * sqds + ztest * nrm;
            }
          }
          for (jj = qp1; jj < 4; jj++) {
            nrm = -e[jj - 1].re;
            sqds = -e[jj - 1].im;
            if (e[1].im == 0.0) {
              if (sqds == 0.0) {
                ztest = nrm / t_re;
                absx = 0.0;
              } else if (nrm == 0.0) {
                ztest = 0.0;
                absx = sqds / t_re;
              } else {
                ztest = nrm / t_re;
                absx = sqds / t_re;
              }
            } else if (t_re == 0.0) {
              if (nrm == 0.0) {
                ztest = sqds / e[1].im;
                absx = 0.0;
              } else if (sqds == 0.0) {
                ztest = 0.0;
                absx = -(nrm / e[1].im);
              } else {
                ztest = sqds / e[1].im;
                absx = -(nrm / e[1].im);
              }
            } else {
              brm = fabs(t_re);
              f = fabs(e[1].im);
              if (brm > f) {
                brm = e[1].im / t_re;
                d = t_re + brm * e[1].im;
                ztest = (nrm + brm * sqds) / d;
                absx = (sqds - brm * nrm) / d;
              } else if (f == brm) {
                if (t_re > 0.0) {
                  d = 0.5;
                } else {
                  d = -0.5;
                }
                if (e[1].im > 0.0) {
                  scale = 0.5;
                } else {
                  scale = -0.5;
                }
                ztest = (nrm * d + sqds * scale) / brm;
                absx = (sqds * d - nrm * scale) / brm;
              } else {
                brm = t_re / e[1].im;
                d = e[1].im + brm * t_re;
                ztest = (brm * nrm + sqds) / d;
                absx = (brm * sqds - nrm) / d;
              }
            }
            if ((!(ztest == 0.0)) || (!(-absx == 0.0))) {
              iy = (q + 3 * (jj - 1)) + 1;
              sqds = work[q + 1].im;
              nrm = work[q + 1].re;
              A[iy].re += ztest * nrm - -absx * sqds;
              A[iy].im += ztest * sqds + -absx * nrm;
              sqds = work[q + 2].im;
              nrm = work[q + 2].re;
              A[iy + 1].re += ztest * nrm - -absx * sqds;
              A[iy + 1].im += ztest * sqds + -absx * nrm;
            }
          }
        }
      }
    }
    qjj = 1;
    s[2] = A[8];
    e[1] = A[7];
    e[2].re = 0.0;
    e[2].im = 0.0;
    iter = 0;
    absx = s[0].re;
    re = s[0].re;
    if ((s[0].re != 0.0) || (s[0].im != 0.0)) {
      nrm = rt_hypotd_snf(s[0].re, s[0].im);
      t_im = s[0].im;
      re = nrm;
      s[0].re = nrm;
      s[0].im = 0.0;
      if (t_im == 0.0) {
        t_re = absx / nrm;
        t_im = 0.0;
      } else if (absx == 0.0) {
        t_re = 0.0;
        t_im /= nrm;
      } else {
        t_re = absx / nrm;
        t_im /= nrm;
      }
      if (t_im == 0.0) {
        if (e[0].im == 0.0) {
          absx = e[0].re / t_re;
          scale = 0.0;
        } else if (e[0].re == 0.0) {
          absx = 0.0;
          scale = e[0].im / t_re;
        } else {
          absx = e[0].re / t_re;
          scale = e[0].im / t_re;
        }
      } else if (t_re == 0.0) {
        if (e[0].re == 0.0) {
          absx = e[0].im / t_im;
          scale = 0.0;
        } else if (e[0].im == 0.0) {
          absx = 0.0;
          scale = -(e[0].re / t_im);
        } else {
          absx = e[0].im / t_im;
          scale = -(e[0].re / t_im);
        }
      } else {
        brm = fabs(t_re);
        f = fabs(t_im);
        if (brm > f) {
          brm = t_im / t_re;
          d = t_re + brm * t_im;
          absx = (e[0].re + brm * e[0].im) / d;
          scale = (e[0].im - brm * e[0].re) / d;
        } else if (f == brm) {
          if (t_re > 0.0) {
            d = 0.5;
          } else {
            d = -0.5;
          }
          if (t_im > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }
          absx = (e[0].re * d + e[0].im * scale) / brm;
          scale = (e[0].im * d - e[0].re * scale) / brm;
        } else {
          brm = t_re / t_im;
          d = t_im + brm * t_re;
          absx = (brm * e[0].re + e[0].im) / d;
          scale = (brm * e[0].im - e[0].re) / d;
        }
      }
      e[0].re = absx;
      e[0].im = scale;
    }
    if ((e[0].re != 0.0) || (e[0].im != 0.0)) {
      nrm = rt_hypotd_snf(e[0].re, e[0].im);
      t_re = e[0].re;
      t_im = e[0].im;
      e[0].re = nrm;
      e[0].im = 0.0;
      if (t_im == 0.0) {
        ztest = nrm / t_re;
        absx = 0.0;
      } else if (t_re == 0.0) {
        if (nrm == 0.0) {
          ztest = 0.0 / t_im;
          absx = 0.0;
        } else {
          ztest = 0.0;
          absx = -(nrm / t_im);
        }
      } else {
        brm = fabs(t_re);
        f = fabs(t_im);
        if (brm > f) {
          brm = t_im / t_re;
          d = t_re + brm * t_im;
          ztest = (nrm + brm * 0.0) / d;
          absx = (0.0 - brm * nrm) / d;
        } else if (f == brm) {
          if (t_re > 0.0) {
            d = 0.5;
          } else {
            d = -0.5;
          }
          if (t_im > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }
          ztest = (nrm * d + 0.0 * scale) / brm;
          absx = (0.0 * d - nrm * scale) / brm;
        } else {
          brm = t_re / t_im;
          d = t_im + brm * t_re;
          ztest = brm * nrm / d;
          absx = (brm * 0.0 - nrm) / d;
        }
      }
      scale = s[1].re * absx + s[1].im * ztest;
      s[1].re = s[1].re * ztest - s[1].im * absx;
      s[1].im = scale;
    }
    snorm = fmax(0.0, fmax(fabs(re), fabs(e[0].re)));
    absx = s[1].re;
    re = s[1].re;
    if ((s[1].re != 0.0) || (s[1].im != 0.0)) {
      nrm = rt_hypotd_snf(s[1].re, s[1].im);
      t_im = s[1].im;
      re = nrm;
      s[1].re = nrm;
      s[1].im = 0.0;
      if (t_im == 0.0) {
        t_re = absx / nrm;
        t_im = 0.0;
      } else if (absx == 0.0) {
        t_re = 0.0;
        t_im /= nrm;
      } else {
        t_re = absx / nrm;
        t_im /= nrm;
      }
      if (t_im == 0.0) {
        if (A[7].im == 0.0) {
          absx = A[7].re / t_re;
          scale = 0.0;
        } else if (A[7].re == 0.0) {
          absx = 0.0;
          scale = A[7].im / t_re;
        } else {
          absx = A[7].re / t_re;
          scale = A[7].im / t_re;
        }
      } else if (t_re == 0.0) {
        if (A[7].re == 0.0) {
          absx = A[7].im / t_im;
          scale = 0.0;
        } else if (A[7].im == 0.0) {
          absx = 0.0;
          scale = -(A[7].re / t_im);
        } else {
          absx = A[7].im / t_im;
          scale = -(A[7].re / t_im);
        }
      } else {
        brm = fabs(t_re);
        f = fabs(t_im);
        if (brm > f) {
          brm = t_im / t_re;
          d = t_re + brm * t_im;
          absx = (A[7].re + brm * A[7].im) / d;
          scale = (A[7].im - brm * A[7].re) / d;
        } else if (f == brm) {
          if (t_re > 0.0) {
            d = 0.5;
          } else {
            d = -0.5;
          }
          if (t_im > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }
          absx = (A[7].re * d + A[7].im * scale) / brm;
          scale = (A[7].im * d - A[7].re * scale) / brm;
        } else {
          brm = t_re / t_im;
          d = t_im + brm * t_re;
          absx = (brm * A[7].re + A[7].im) / d;
          scale = (brm * A[7].im - A[7].re) / d;
        }
      }
      e[1].re = absx;
      e[1].im = scale;
    }
    if ((e[1].re != 0.0) || (e[1].im != 0.0)) {
      nrm = rt_hypotd_snf(e[1].re, e[1].im);
      t_re = e[1].re;
      t_im = e[1].im;
      e[1].re = nrm;
      e[1].im = 0.0;
      if (t_im == 0.0) {
        ztest = nrm / t_re;
        absx = 0.0;
      } else if (t_re == 0.0) {
        if (nrm == 0.0) {
          ztest = 0.0 / t_im;
          absx = 0.0;
        } else {
          ztest = 0.0;
          absx = -(nrm / t_im);
        }
      } else {
        brm = fabs(t_re);
        f = fabs(t_im);
        if (brm > f) {
          brm = t_im / t_re;
          d = t_re + brm * t_im;
          ztest = (nrm + brm * 0.0) / d;
          absx = (0.0 - brm * nrm) / d;
        } else if (f == brm) {
          if (t_re > 0.0) {
            d = 0.5;
          } else {
            d = -0.5;
          }
          if (t_im > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }
          ztest = (nrm * d + 0.0 * scale) / brm;
          absx = (0.0 * d - nrm * scale) / brm;
        } else {
          brm = t_re / t_im;
          d = t_im + brm * t_re;
          ztest = brm * nrm / d;
          absx = (brm * 0.0 - nrm) / d;
        }
      }
      s[2].re = A[8].re * ztest - A[8].im * absx;
      s[2].im = A[8].re * absx + A[8].im * ztest;
    }
    snorm = fmax(snorm, fmax(fabs(re), fabs(e[1].re)));
    re = s[2].re;
    if ((s[2].re != 0.0) || (s[2].im != 0.0)) {
      nrm = rt_hypotd_snf(s[2].re, s[2].im);
      re = nrm;
      s[2].re = nrm;
      s[2].im = 0.0;
    }
    snorm = fmax(snorm, fmax(fabs(re), 0.0));
    while ((qjj + 2 > 0) && (iter < 75)) {
      boolean_T exitg1;
      nmqp1_tmp = qjj + 1;
      jj = qjj + 1;
      exitg1 = false;
      while (!(exitg1 || (jj == 0))) {
        absx = fabs(e[jj - 1].re);
        if ((absx <=
             2.2204460492503131E-16 * (fabs(s[jj - 1].re) + fabs(s[jj].re))) ||
            (absx <= 1.0020841800044864E-292) ||
            ((iter > 20) && (absx <= 2.2204460492503131E-16 * snorm))) {
          e[jj - 1].re = 0.0;
          e[jj - 1].im = 0.0;
          exitg1 = true;
        } else {
          jj--;
        }
      }
      if (jj == qjj + 1) {
        ix = 4;
      } else {
        iy = qjj + 2;
        ix = qjj + 2;
        exitg1 = false;
        while ((!exitg1) && (ix >= jj)) {
          iy = ix;
          if (ix == jj) {
            exitg1 = true;
          } else {
            absx = 0.0;
            if (ix < qjj + 2) {
              absx = fabs(e[ix - 1].re);
            }
            if (ix > jj + 1) {
              absx += fabs(e[ix - 2].re);
            }
            ztest = fabs(s[ix - 1].re);
            if ((ztest <= 2.2204460492503131E-16 * absx) ||
                (ztest <= 1.0020841800044864E-292)) {
              s[ix - 1].re = 0.0;
              s[ix - 1].im = 0.0;
              exitg1 = true;
            } else {
              ix--;
            }
          }
        }
        if (iy == jj) {
          ix = 3;
        } else if (iy == qjj + 2) {
          ix = 1;
        } else {
          ix = 2;
          jj = iy;
        }
      }
      switch (ix) {
      case 1:
        f = e[qjj].re;
        e[qjj].re = 0.0;
        e[qjj].im = 0.0;
        for (k = nmqp1_tmp; k >= jj + 1; k--) {
          absx = s[k - 1].re;
          nrm = xrotg(&absx, &f, &sqds);
          s[k - 1].re = absx;
          s[k - 1].im = 0.0;
          if (k > jj + 1) {
            f = -sqds * e[0].re;
            e[0].re *= nrm;
            e[0].im *= nrm;
          }
        }
        break;
      case 2:
        f = e[jj - 1].re;
        e[jj - 1].re = 0.0;
        e[jj - 1].im = 0.0;
        for (k = jj + 1; k <= qjj + 2; k++) {
          absx = s[k - 1].re;
          nrm = xrotg(&absx, &f, &sqds);
          s[k - 1].re = absx;
          s[k - 1].im = 0.0;
          ztest = e[k - 1].re;
          f = -sqds * ztest;
          e[k - 1].re = nrm * ztest;
          e[k - 1].im *= nrm;
        }
        break;
      case 3:
        absx = s[qjj + 1].re;
        ztest = s[qjj].re;
        sqds = e[qjj].re;
        nrm = s[jj].re;
        d = e[jj].re;
        scale = fmax(
            fmax(fmax(fmax(fabs(absx), fabs(ztest)), fabs(sqds)), fabs(nrm)),
            fabs(d));
        f = absx / scale;
        absx = ztest / scale;
        ztest = sqds / scale;
        sqds = nrm / scale;
        nrm = ((absx + f) * (absx - f) + ztest * ztest) / 2.0;
        absx = f * ztest;
        absx *= absx;
        if ((nrm != 0.0) || (absx != 0.0)) {
          ztest = sqrt(nrm * nrm + absx);
          if (nrm < 0.0) {
            ztest = -ztest;
          }
          ztest = absx / (nrm + ztest);
        } else {
          ztest = 0.0;
        }
        f = (sqds + f) * (sqds - f) + ztest;
        absx = sqds * (d / scale);
        for (k = jj + 1; k <= nmqp1_tmp; k++) {
          nrm = xrotg(&f, &absx, &sqds);
          if (k > jj + 1) {
            e[0].re = f;
            e[0].im = 0.0;
          }
          absx = e[k - 1].re;
          ztest = s[k - 1].re;
          f = nrm * ztest + sqds * absx;
          e[k - 1].re = nrm * absx - sqds * ztest;
          e[k - 1].im = nrm * e[k - 1].im - sqds * s[k - 1].im;
          absx = s[k].re;
          ztest = sqds * absx;
          re = nrm * absx;
          scale = nrm * s[k].im;
          nrm = xrotg(&f, &ztest, &sqds);
          s[k - 1].re = f;
          s[k - 1].im = 0.0;
          ztest = e[k - 1].re;
          f = nrm * ztest + sqds * re;
          re = -sqds * ztest + nrm * re;
          scale = -sqds * e[k - 1].im + nrm * scale;
          s[k].re = re;
          s[k].im = scale;
          ztest = e[k].re;
          absx = sqds * ztest;
          e[k].re = nrm * ztest;
          e[k].im *= nrm;
        }
        e[qjj].re = f;
        e[qjj].im = 0.0;
        iter++;
        break;
      default:
        if (s[jj].re < 0.0) {
          s[jj].re = -s[jj].re;
          s[jj].im = 0.0;
        }
        qp1 = jj + 1;
        while ((jj + 1 < 3) && (s[jj].re < s[qp1].re)) {
          nrm = s[jj].re;
          s[jj].re = s[qp1].re;
          s[jj].im = 0.0;
          s[qp1].re = nrm;
          s[qp1].im = 0.0;
          jj = qp1;
          qp1++;
        }
        iter = 0;
        qjj--;
        break;
      }
    }
    y = s[0].re;
  }
  return y;
}

double c_norm(const creal_T x[3], double P)
{
  double absx;
  double y;
  int j;
  boolean_T VECTOR_INPUT_AND_P_IS_NUMERIC;
  boolean_T VECTOR_INPUT_AND_P_IS_ZERO;
  boolean_T guard1 = false;
  VECTOR_INPUT_AND_P_IS_ZERO = false;
  VECTOR_INPUT_AND_P_IS_NUMERIC = false;
  guard1 = false;
  if (!rtIsNaN(P)) {
    if ((P > 0.0) && rtIsInf(P)) {
      y = 0.0;
      absx = rt_hypotd_snf(x[0].re, x[0].im);
      if (rtIsNaN(absx) || (absx > 0.0)) {
        y = absx;
      }
      absx = rt_hypotd_snf(x[1].re, x[1].im);
      if (rtIsNaN(absx) || (absx > y)) {
        y = absx;
      }
      absx = rt_hypotd_snf(x[2].re, x[2].im);
      if (rtIsNaN(absx) || (absx > y)) {
        y = absx;
      }
    } else {
      if (P == 0.0) {
        VECTOR_INPUT_AND_P_IS_ZERO = true;
      } else {
        VECTOR_INPUT_AND_P_IS_NUMERIC = true;
      }
      guard1 = true;
    }
  } else {
    guard1 = true;
  }
  if (guard1) {
    if (VECTOR_INPUT_AND_P_IS_ZERO) {
      y = rt_powd_snf((rt_powd_snf(rt_hypotd_snf(x[0].re, x[0].im), P) +
                       rt_powd_snf(rt_hypotd_snf(x[1].re, x[1].im), P)) +
                          rt_powd_snf(rt_hypotd_snf(x[2].re, x[2].im), P),
                      1.0 / P);
    } else if (VECTOR_INPUT_AND_P_IS_NUMERIC) {
      if (P == 2.0) {
        double scale;
        double t;
        scale = 3.3121686421112381E-170;
        absx = fabs(x[0].re);
        if (absx > 3.3121686421112381E-170) {
          y = 1.0;
          scale = absx;
        } else {
          t = absx / 3.3121686421112381E-170;
          y = t * t;
        }
        absx = fabs(x[0].im);
        if (absx > scale) {
          t = scale / absx;
          y = y * t * t + 1.0;
          scale = absx;
        } else {
          t = absx / scale;
          y += t * t;
        }
        absx = fabs(x[1].re);
        if (absx > scale) {
          t = scale / absx;
          y = y * t * t + 1.0;
          scale = absx;
        } else {
          t = absx / scale;
          y += t * t;
        }
        absx = fabs(x[1].im);
        if (absx > scale) {
          t = scale / absx;
          y = y * t * t + 1.0;
          scale = absx;
        } else {
          t = absx / scale;
          y += t * t;
        }
        absx = fabs(x[2].re);
        if (absx > scale) {
          t = scale / absx;
          y = y * t * t + 1.0;
          scale = absx;
        } else {
          t = absx / scale;
          y += t * t;
        }
        absx = fabs(x[2].im);
        if (absx > scale) {
          t = scale / absx;
          y = y * t * t + 1.0;
          scale = absx;
        } else {
          t = absx / scale;
          y += t * t;
        }
        y = scale * sqrt(y);
      } else if (rtIsInf(P)) {
        if (P > 0.0) {
          y = 0.0;
          absx = rt_hypotd_snf(x[0].re, x[0].im);
          if (rtIsNaN(absx) || (absx > 0.0)) {
            y = absx;
          }
          absx = rt_hypotd_snf(x[1].re, x[1].im);
          if (rtIsNaN(absx) || (absx > y)) {
            y = absx;
          }
          absx = rt_hypotd_snf(x[2].re, x[2].im);
          if (rtIsNaN(absx) || (absx > y)) {
            y = absx;
          }
        } else {
          y = rtInf;
          absx = rt_hypotd_snf(x[0].re, x[0].im);
          if (rtIsNaN(absx) || (absx < rtInf)) {
            y = absx;
          }
          absx = rt_hypotd_snf(x[1].re, x[1].im);
          if (rtIsNaN(absx) || (absx < y)) {
            y = absx;
          }
          absx = rt_hypotd_snf(x[2].re, x[2].im);
          if (rtIsNaN(absx) || (absx < y)) {
            y = absx;
          }
        }
      } else if (P == 1.0) {
        y = (rt_hypotd_snf(x[0].re, x[0].im) +
             rt_hypotd_snf(x[1].re, x[1].im)) +
            rt_hypotd_snf(x[2].re, x[2].im);
      } else if (P > 0.0) {
        double scale;
        int exitg4;
        int k;
        y = 0.0;
        scale = 0.0;
        k = 0;
        do {
          exitg4 = 0;
          if (k < 3) {
            absx = rt_hypotd_snf(x[k].re, x[k].im);
            if (rtIsNaN(absx)) {
              y = rtNaN;
              exitg4 = 2;
            } else if (rtIsInf(absx)) {
              y = rtInf;
              j = 0;
              exitg4 = 1;
            } else {
              if (absx > 0.0) {
                if (scale < absx) {
                  y = y * rt_powd_snf(scale / absx, P) + 1.0;
                  scale = absx;
                } else {
                  y += rt_powd_snf(absx / scale, P);
                }
              }
              k++;
            }
          } else {
            if ((y > 0.0) && (!rtIsInf(y))) {
              y = scale * rt_powd_snf(y, 1.0 / P);
            }
            exitg4 = 2;
          }
        } while (exitg4 == 0);
        if (exitg4 == 1) {
          boolean_T exitg3;
          exitg3 = false;
          while ((!exitg3) && (j <= 1 - k)) {
            int b_j;
            b_j = (k + j) + 1;
            if (rtIsNaN(x[b_j].re) || rtIsNaN(x[b_j].im)) {
              y = rtNaN;
              exitg3 = true;
            } else {
              j++;
            }
          }
        }
      } else if (P < 0.0) {
        double scale;
        int exitg2;
        int k;
        y = 0.0;
        scale = rtInf;
        k = 0;
        do {
          exitg2 = 0;
          if (k < 3) {
            absx = rt_hypotd_snf(x[k].re, x[k].im);
            if (rtIsNaN(absx)) {
              y = rtNaN;
              exitg2 = 2;
            } else if (absx == 0.0) {
              y = 0.0;
              j = 0;
              exitg2 = 1;
            } else {
              if (absx < scale) {
                y = y * rt_powd_snf(scale / absx, P) + 1.0;
                scale = absx;
              } else if (!rtIsInf(absx)) {
                y += rt_powd_snf(absx / scale, P);
              }
              k++;
            }
          } else {
            if ((y > 0.0) && (!rtIsInf(y))) {
              y = scale * rt_powd_snf(y, 1.0 / P);
            }
            exitg2 = 2;
          }
        } while (exitg2 == 0);
        if (exitg2 == 1) {
          boolean_T exitg1;
          exitg1 = false;
          while ((!exitg1) && (j <= 1 - k)) {
            int b_j;
            b_j = (k + j) + 1;
            if (rtIsNaN(x[b_j].re) || rtIsNaN(x[b_j].im)) {
              y = rtNaN;
              exitg1 = true;
            } else {
              j++;
            }
          }
        }
      } else {
        y = rtNaN;
      }
    } else {
      y = rtNaN;
    }
  }
  return y;
}

/* End of code generation (norm.c) */
