/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mpower.c
 *
 * Code generation for function 'mpower'
 *
 */

/* Include files */
#include "mpower.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_rtwutil.h"
#include "eig.h"
#include "mpower_schur.h"
#include "power.h"
#include "rcond.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void b_mpower(const creal_T a[9], creal_T c[9])
{
  creal_T x[9];
  double absx11;
  double absx21;
  double absx31;
  double brm;
  double d;
  double im;
  double re;
  double t1_im;
  double t1_re;
  double t2_im;
  double t2_re;
  int p1;
  int p2;
  int p3;
  memcpy(&x[0], &a[0], 9U * sizeof(creal_T));
  p1 = 0;
  p2 = 3;
  p3 = 6;
  absx11 = rt_hypotd_snf(a[0].re, a[0].im);
  absx21 = rt_hypotd_snf(a[1].re, a[1].im);
  absx31 = rt_hypotd_snf(a[2].re, a[2].im);
  if ((absx21 > absx11) && (absx21 > absx31)) {
    p1 = 3;
    p2 = 0;
    x[0] = a[1];
    x[1] = a[0];
    x[3] = a[4];
    x[4] = a[3];
    x[6] = a[7];
    x[7] = a[6];
  } else if (absx31 > absx11) {
    p1 = 6;
    p3 = 0;
    x[0] = a[2];
    x[2] = a[0];
    x[3] = a[5];
    x[5] = a[3];
    x[6] = a[8];
    x[8] = a[6];
  }
  if (x[0].im == 0.0) {
    if (x[1].im == 0.0) {
      re = x[1].re / x[0].re;
      im = 0.0;
    } else if (x[1].re == 0.0) {
      re = 0.0;
      im = x[1].im / x[0].re;
    } else {
      re = x[1].re / x[0].re;
      im = x[1].im / x[0].re;
    }
  } else if (x[0].re == 0.0) {
    if (x[1].re == 0.0) {
      re = x[1].im / x[0].im;
      im = 0.0;
    } else if (x[1].im == 0.0) {
      re = 0.0;
      im = -(x[1].re / x[0].im);
    } else {
      re = x[1].im / x[0].im;
      im = -(x[1].re / x[0].im);
    }
  } else {
    brm = fabs(x[0].re);
    absx31 = fabs(x[0].im);
    if (brm > absx31) {
      absx31 = x[0].im / x[0].re;
      d = x[0].re + absx31 * x[0].im;
      re = (x[1].re + absx31 * x[1].im) / d;
      im = (x[1].im - absx31 * x[1].re) / d;
    } else if (absx31 == brm) {
      if (x[0].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[0].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      re = (x[1].re * absx31 + x[1].im * d) / brm;
      im = (x[1].im * absx31 - x[1].re * d) / brm;
    } else {
      absx31 = x[0].re / x[0].im;
      d = x[0].im + absx31 * x[0].re;
      re = (absx31 * x[1].re + x[1].im) / d;
      im = (absx31 * x[1].im - x[1].re) / d;
    }
  }
  x[1].re = re;
  x[1].im = im;
  if (x[0].im == 0.0) {
    if (x[2].im == 0.0) {
      absx21 = x[2].re / x[0].re;
      absx11 = 0.0;
    } else if (x[2].re == 0.0) {
      absx21 = 0.0;
      absx11 = x[2].im / x[0].re;
    } else {
      absx21 = x[2].re / x[0].re;
      absx11 = x[2].im / x[0].re;
    }
  } else if (x[0].re == 0.0) {
    if (x[2].re == 0.0) {
      absx21 = x[2].im / x[0].im;
      absx11 = 0.0;
    } else if (x[2].im == 0.0) {
      absx21 = 0.0;
      absx11 = -(x[2].re / x[0].im);
    } else {
      absx21 = x[2].im / x[0].im;
      absx11 = -(x[2].re / x[0].im);
    }
  } else {
    brm = fabs(x[0].re);
    absx31 = fabs(x[0].im);
    if (brm > absx31) {
      absx31 = x[0].im / x[0].re;
      d = x[0].re + absx31 * x[0].im;
      absx21 = (x[2].re + absx31 * x[2].im) / d;
      absx11 = (x[2].im - absx31 * x[2].re) / d;
    } else if (absx31 == brm) {
      if (x[0].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[0].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      absx21 = (x[2].re * absx31 + x[2].im * d) / brm;
      absx11 = (x[2].im * absx31 - x[2].re * d) / brm;
    } else {
      absx31 = x[0].re / x[0].im;
      d = x[0].im + absx31 * x[0].re;
      absx21 = (absx31 * x[2].re + x[2].im) / d;
      absx11 = (absx31 * x[2].im - x[2].re) / d;
    }
  }
  x[2].re = absx21;
  x[2].im = absx11;
  x[4].re -= re * x[3].re - im * x[3].im;
  x[4].im -= re * x[3].im + im * x[3].re;
  x[5].re -= absx21 * x[3].re - absx11 * x[3].im;
  x[5].im -= absx21 * x[3].im + absx11 * x[3].re;
  x[7].re -= re * x[6].re - im * x[6].im;
  x[7].im -= re * x[6].im + im * x[6].re;
  x[8].re -= absx21 * x[6].re - absx11 * x[6].im;
  x[8].im -= absx21 * x[6].im + absx11 * x[6].re;
  if (rt_hypotd_snf(x[5].re, x[5].im) > rt_hypotd_snf(x[4].re, x[4].im)) {
    int itmp;
    itmp = p2;
    p2 = p3;
    p3 = itmp;
    x[1] = x[2];
    x[2].re = re;
    x[2].im = im;
    t1_re = x[4].re;
    t1_im = x[4].im;
    x[4] = x[5];
    x[5].re = t1_re;
    x[5].im = t1_im;
    t1_re = x[7].re;
    t1_im = x[7].im;
    x[7] = x[8];
    x[8].re = t1_re;
    x[8].im = t1_im;
  }
  if (x[4].im == 0.0) {
    if (x[5].im == 0.0) {
      re = x[5].re / x[4].re;
      im = 0.0;
    } else if (x[5].re == 0.0) {
      re = 0.0;
      im = x[5].im / x[4].re;
    } else {
      re = x[5].re / x[4].re;
      im = x[5].im / x[4].re;
    }
  } else if (x[4].re == 0.0) {
    if (x[5].re == 0.0) {
      re = x[5].im / x[4].im;
      im = 0.0;
    } else if (x[5].im == 0.0) {
      re = 0.0;
      im = -(x[5].re / x[4].im);
    } else {
      re = x[5].im / x[4].im;
      im = -(x[5].re / x[4].im);
    }
  } else {
    brm = fabs(x[4].re);
    absx31 = fabs(x[4].im);
    if (brm > absx31) {
      absx31 = x[4].im / x[4].re;
      d = x[4].re + absx31 * x[4].im;
      re = (x[5].re + absx31 * x[5].im) / d;
      im = (x[5].im - absx31 * x[5].re) / d;
    } else if (absx31 == brm) {
      if (x[4].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[4].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      re = (x[5].re * absx31 + x[5].im * d) / brm;
      im = (x[5].im * absx31 - x[5].re * d) / brm;
    } else {
      absx31 = x[4].re / x[4].im;
      d = x[4].im + absx31 * x[4].re;
      re = (absx31 * x[5].re + x[5].im) / d;
      im = (absx31 * x[5].im - x[5].re) / d;
    }
  }
  x[8].re -= re * x[7].re - im * x[7].im;
  x[8].im -= re * x[7].im + im * x[7].re;
  absx11 = (x[1].re * re - x[1].im * im) - x[2].re;
  absx21 = (x[1].re * im + x[1].im * re) - x[2].im;
  if (x[8].im == 0.0) {
    if (absx21 == 0.0) {
      t1_re = absx11 / x[8].re;
      t1_im = 0.0;
    } else if (absx11 == 0.0) {
      t1_re = 0.0;
      t1_im = absx21 / x[8].re;
    } else {
      t1_re = absx11 / x[8].re;
      t1_im = absx21 / x[8].re;
    }
  } else if (x[8].re == 0.0) {
    if (absx11 == 0.0) {
      t1_re = absx21 / x[8].im;
      t1_im = 0.0;
    } else if (absx21 == 0.0) {
      t1_re = 0.0;
      t1_im = -(absx11 / x[8].im);
    } else {
      t1_re = absx21 / x[8].im;
      t1_im = -(absx11 / x[8].im);
    }
  } else {
    brm = fabs(x[8].re);
    absx31 = fabs(x[8].im);
    if (brm > absx31) {
      absx31 = x[8].im / x[8].re;
      d = x[8].re + absx31 * x[8].im;
      t1_re = (absx11 + absx31 * absx21) / d;
      t1_im = (absx21 - absx31 * absx11) / d;
    } else if (absx31 == brm) {
      if (x[8].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[8].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      t1_re = (absx11 * absx31 + absx21 * d) / brm;
      t1_im = (absx21 * absx31 - absx11 * d) / brm;
    } else {
      absx31 = x[8].re / x[8].im;
      d = x[8].im + absx31 * x[8].re;
      t1_re = (absx31 * absx11 + absx21) / d;
      t1_im = (absx31 * absx21 - absx11) / d;
    }
  }
  absx11 = -(x[1].re + (x[7].re * t1_re - x[7].im * t1_im));
  absx21 = -(x[1].im + (x[7].re * t1_im + x[7].im * t1_re));
  if (x[4].im == 0.0) {
    if (absx21 == 0.0) {
      t2_re = absx11 / x[4].re;
      t2_im = 0.0;
    } else if (absx11 == 0.0) {
      t2_re = 0.0;
      t2_im = absx21 / x[4].re;
    } else {
      t2_re = absx11 / x[4].re;
      t2_im = absx21 / x[4].re;
    }
  } else if (x[4].re == 0.0) {
    if (absx11 == 0.0) {
      t2_re = absx21 / x[4].im;
      t2_im = 0.0;
    } else if (absx21 == 0.0) {
      t2_re = 0.0;
      t2_im = -(absx11 / x[4].im);
    } else {
      t2_re = absx21 / x[4].im;
      t2_im = -(absx11 / x[4].im);
    }
  } else {
    brm = fabs(x[4].re);
    absx31 = fabs(x[4].im);
    if (brm > absx31) {
      absx31 = x[4].im / x[4].re;
      d = x[4].re + absx31 * x[4].im;
      t2_re = (absx11 + absx31 * absx21) / d;
      t2_im = (absx21 - absx31 * absx11) / d;
    } else if (absx31 == brm) {
      if (x[4].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[4].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      t2_re = (absx11 * absx31 + absx21 * d) / brm;
      t2_im = (absx21 * absx31 - absx11 * d) / brm;
    } else {
      absx31 = x[4].re / x[4].im;
      d = x[4].im + absx31 * x[4].re;
      t2_re = (absx31 * absx11 + absx21) / d;
      t2_im = (absx31 * absx21 - absx11) / d;
    }
  }
  absx11 = (1.0 - (x[3].re * t2_re - x[3].im * t2_im)) -
           (x[6].re * t1_re - x[6].im * t1_im);
  absx21 = (0.0 - (x[3].re * t2_im + x[3].im * t2_re)) -
           (x[6].re * t1_im + x[6].im * t1_re);
  if (x[0].im == 0.0) {
    if (absx21 == 0.0) {
      c[p1].re = absx11 / x[0].re;
      c[p1].im = 0.0;
    } else if (absx11 == 0.0) {
      c[p1].re = 0.0;
      c[p1].im = absx21 / x[0].re;
    } else {
      c[p1].re = absx11 / x[0].re;
      c[p1].im = absx21 / x[0].re;
    }
  } else if (x[0].re == 0.0) {
    if (absx11 == 0.0) {
      c[p1].re = absx21 / x[0].im;
      c[p1].im = 0.0;
    } else if (absx21 == 0.0) {
      c[p1].re = 0.0;
      c[p1].im = -(absx11 / x[0].im);
    } else {
      c[p1].re = absx21 / x[0].im;
      c[p1].im = -(absx11 / x[0].im);
    }
  } else {
    brm = fabs(x[0].re);
    absx31 = fabs(x[0].im);
    if (brm > absx31) {
      absx31 = x[0].im / x[0].re;
      d = x[0].re + absx31 * x[0].im;
      c[p1].re = (absx11 + absx31 * absx21) / d;
      c[p1].im = (absx21 - absx31 * absx11) / d;
    } else if (absx31 == brm) {
      if (x[0].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[0].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      c[p1].re = (absx11 * absx31 + absx21 * d) / brm;
      c[p1].im = (absx21 * absx31 - absx11 * d) / brm;
    } else {
      absx31 = x[0].re / x[0].im;
      d = x[0].im + absx31 * x[0].re;
      c[p1].re = (absx31 * absx11 + absx21) / d;
      c[p1].im = (absx31 * absx21 - absx11) / d;
    }
  }
  c[p1 + 1].re = t2_re;
  c[p1 + 1].im = t2_im;
  c[p1 + 2].re = t1_re;
  c[p1 + 2].im = t1_im;
  if (x[8].im == 0.0) {
    if (-im == 0.0) {
      t1_re = -re / x[8].re;
      t1_im = 0.0;
    } else if (-re == 0.0) {
      t1_re = 0.0;
      t1_im = -im / x[8].re;
    } else {
      t1_re = -re / x[8].re;
      t1_im = -im / x[8].re;
    }
  } else if (x[8].re == 0.0) {
    if (-re == 0.0) {
      t1_re = -im / x[8].im;
      t1_im = 0.0;
    } else if (-im == 0.0) {
      t1_re = 0.0;
      t1_im = -(-re / x[8].im);
    } else {
      t1_re = -im / x[8].im;
      t1_im = -(-re / x[8].im);
    }
  } else {
    brm = fabs(x[8].re);
    absx31 = fabs(x[8].im);
    if (brm > absx31) {
      absx31 = x[8].im / x[8].re;
      d = x[8].re + absx31 * x[8].im;
      t1_re = (-re + absx31 * -im) / d;
      t1_im = (-im - absx31 * -re) / d;
    } else if (absx31 == brm) {
      if (x[8].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[8].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      t1_re = (-re * absx31 + -im * d) / brm;
      t1_im = (-im * absx31 - -re * d) / brm;
    } else {
      absx31 = x[8].re / x[8].im;
      d = x[8].im + absx31 * x[8].re;
      t1_re = (absx31 * -re - im) / d;
      t1_im = (absx31 * -im - (-re)) / d;
    }
  }
  absx11 = x[7].re * t1_re - x[7].im * t1_im;
  absx21 = x[7].re * t1_im + x[7].im * t1_re;
  if (x[4].im == 0.0) {
    if (0.0 - absx21 == 0.0) {
      t2_re = (1.0 - absx11) / x[4].re;
      t2_im = 0.0;
    } else if (1.0 - absx11 == 0.0) {
      t2_re = 0.0;
      t2_im = (0.0 - absx21) / x[4].re;
    } else {
      t2_re = (1.0 - absx11) / x[4].re;
      t2_im = (0.0 - absx21) / x[4].re;
    }
  } else if (x[4].re == 0.0) {
    if (1.0 - absx11 == 0.0) {
      t2_re = (0.0 - absx21) / x[4].im;
      t2_im = 0.0;
    } else if (0.0 - absx21 == 0.0) {
      t2_re = 0.0;
      t2_im = -((1.0 - absx11) / x[4].im);
    } else {
      t2_re = (0.0 - absx21) / x[4].im;
      t2_im = -((1.0 - absx11) / x[4].im);
    }
  } else {
    brm = fabs(x[4].re);
    absx31 = fabs(x[4].im);
    if (brm > absx31) {
      absx31 = x[4].im / x[4].re;
      d = x[4].re + absx31 * x[4].im;
      t2_re = ((1.0 - absx11) + absx31 * (0.0 - absx21)) / d;
      t2_im = ((0.0 - absx21) - absx31 * (1.0 - absx11)) / d;
    } else if (absx31 == brm) {
      if (x[4].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[4].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      t2_re = ((1.0 - absx11) * absx31 + (0.0 - absx21) * d) / brm;
      t2_im = ((0.0 - absx21) * absx31 - (1.0 - absx11) * d) / brm;
    } else {
      absx31 = x[4].re / x[4].im;
      d = x[4].im + absx31 * x[4].re;
      t2_re = (absx31 * (1.0 - absx11) + (0.0 - absx21)) / d;
      t2_im = (absx31 * (0.0 - absx21) - (1.0 - absx11)) / d;
    }
  }
  absx11 = -((x[3].re * t2_re - x[3].im * t2_im) +
             (x[6].re * t1_re - x[6].im * t1_im));
  absx21 = -((x[3].re * t2_im + x[3].im * t2_re) +
             (x[6].re * t1_im + x[6].im * t1_re));
  if (x[0].im == 0.0) {
    if (absx21 == 0.0) {
      c[p2].re = absx11 / x[0].re;
      c[p2].im = 0.0;
    } else if (absx11 == 0.0) {
      c[p2].re = 0.0;
      c[p2].im = absx21 / x[0].re;
    } else {
      c[p2].re = absx11 / x[0].re;
      c[p2].im = absx21 / x[0].re;
    }
  } else if (x[0].re == 0.0) {
    if (absx11 == 0.0) {
      c[p2].re = absx21 / x[0].im;
      c[p2].im = 0.0;
    } else if (absx21 == 0.0) {
      c[p2].re = 0.0;
      c[p2].im = -(absx11 / x[0].im);
    } else {
      c[p2].re = absx21 / x[0].im;
      c[p2].im = -(absx11 / x[0].im);
    }
  } else {
    brm = fabs(x[0].re);
    absx31 = fabs(x[0].im);
    if (brm > absx31) {
      absx31 = x[0].im / x[0].re;
      d = x[0].re + absx31 * x[0].im;
      c[p2].re = (absx11 + absx31 * absx21) / d;
      c[p2].im = (absx21 - absx31 * absx11) / d;
    } else if (absx31 == brm) {
      if (x[0].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[0].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      c[p2].re = (absx11 * absx31 + absx21 * d) / brm;
      c[p2].im = (absx21 * absx31 - absx11 * d) / brm;
    } else {
      absx31 = x[0].re / x[0].im;
      d = x[0].im + absx31 * x[0].re;
      c[p2].re = (absx31 * absx11 + absx21) / d;
      c[p2].im = (absx31 * absx21 - absx11) / d;
    }
  }
  c[p2 + 1].re = t2_re;
  c[p2 + 1].im = t2_im;
  c[p2 + 2].re = t1_re;
  c[p2 + 2].im = t1_im;
  if (x[8].im == 0.0) {
    t1_re = 1.0 / x[8].re;
    t1_im = 0.0;
  } else if (x[8].re == 0.0) {
    t1_re = 0.0;
    t1_im = -(1.0 / x[8].im);
  } else {
    brm = fabs(x[8].re);
    absx31 = fabs(x[8].im);
    if (brm > absx31) {
      absx31 = x[8].im / x[8].re;
      d = x[8].re + absx31 * x[8].im;
      t1_re = (absx31 * 0.0 + 1.0) / d;
      t1_im = (0.0 - absx31) / d;
    } else if (absx31 == brm) {
      if (x[8].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[8].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      t1_re = (absx31 + 0.0 * d) / brm;
      t1_im = (0.0 * absx31 - d) / brm;
    } else {
      absx31 = x[8].re / x[8].im;
      d = x[8].im + absx31 * x[8].re;
      t1_re = absx31 / d;
      t1_im = (absx31 * 0.0 - 1.0) / d;
    }
  }
  absx11 = -x[7].re * t1_re - -x[7].im * t1_im;
  absx21 = -x[7].re * t1_im + -x[7].im * t1_re;
  if (x[4].im == 0.0) {
    if (absx21 == 0.0) {
      t2_re = absx11 / x[4].re;
      t2_im = 0.0;
    } else if (absx11 == 0.0) {
      t2_re = 0.0;
      t2_im = absx21 / x[4].re;
    } else {
      t2_re = absx11 / x[4].re;
      t2_im = absx21 / x[4].re;
    }
  } else if (x[4].re == 0.0) {
    if (absx11 == 0.0) {
      t2_re = absx21 / x[4].im;
      t2_im = 0.0;
    } else if (absx21 == 0.0) {
      t2_re = 0.0;
      t2_im = -(absx11 / x[4].im);
    } else {
      t2_re = absx21 / x[4].im;
      t2_im = -(absx11 / x[4].im);
    }
  } else {
    brm = fabs(x[4].re);
    absx31 = fabs(x[4].im);
    if (brm > absx31) {
      absx31 = x[4].im / x[4].re;
      d = x[4].re + absx31 * x[4].im;
      t2_re = (absx11 + absx31 * absx21) / d;
      t2_im = (absx21 - absx31 * absx11) / d;
    } else if (absx31 == brm) {
      if (x[4].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[4].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      t2_re = (absx11 * absx31 + absx21 * d) / brm;
      t2_im = (absx21 * absx31 - absx11 * d) / brm;
    } else {
      absx31 = x[4].re / x[4].im;
      d = x[4].im + absx31 * x[4].re;
      t2_re = (absx31 * absx11 + absx21) / d;
      t2_im = (absx31 * absx21 - absx11) / d;
    }
  }
  absx11 = -((x[3].re * t2_re - x[3].im * t2_im) +
             (x[6].re * t1_re - x[6].im * t1_im));
  absx21 = -((x[3].re * t2_im + x[3].im * t2_re) +
             (x[6].re * t1_im + x[6].im * t1_re));
  if (x[0].im == 0.0) {
    if (absx21 == 0.0) {
      c[p3].re = absx11 / x[0].re;
      c[p3].im = 0.0;
    } else if (absx11 == 0.0) {
      c[p3].re = 0.0;
      c[p3].im = absx21 / x[0].re;
    } else {
      c[p3].re = absx11 / x[0].re;
      c[p3].im = absx21 / x[0].re;
    }
  } else if (x[0].re == 0.0) {
    if (absx11 == 0.0) {
      c[p3].re = absx21 / x[0].im;
      c[p3].im = 0.0;
    } else if (absx21 == 0.0) {
      c[p3].re = 0.0;
      c[p3].im = -(absx11 / x[0].im);
    } else {
      c[p3].re = absx21 / x[0].im;
      c[p3].im = -(absx11 / x[0].im);
    }
  } else {
    brm = fabs(x[0].re);
    absx31 = fabs(x[0].im);
    if (brm > absx31) {
      absx31 = x[0].im / x[0].re;
      d = x[0].re + absx31 * x[0].im;
      c[p3].re = (absx11 + absx31 * absx21) / d;
      c[p3].im = (absx21 - absx31 * absx11) / d;
    } else if (absx31 == brm) {
      if (x[0].re > 0.0) {
        absx31 = 0.5;
      } else {
        absx31 = -0.5;
      }
      if (x[0].im > 0.0) {
        d = 0.5;
      } else {
        d = -0.5;
      }
      c[p3].re = (absx11 * absx31 + absx21 * d) / brm;
      c[p3].im = (absx21 * absx31 - absx11 * d) / brm;
    } else {
      absx31 = x[0].re / x[0].im;
      d = x[0].im + absx31 * x[0].re;
      c[p3].re = (absx31 * absx11 + absx21) / d;
      c[p3].im = (absx31 * absx21 - absx11) / d;
    }
  }
  c[p3 + 1].re = t2_re;
  c[p3 + 1].im = t2_im;
  c[p3 + 2].re = t1_re;
  c[p3 + 2].im = t1_im;
}

void mpower(const creal_T a[9], creal_T c[9])
{
  creal_T V[9];
  creal_T Vfact[9];
  creal_T temp;
  double ai;
  double ar;
  double bi;
  double br;
  double re;
  double s;
  double sgnbr;
  double smax;
  int Vfact_tmp_tmp;
  int exitg1;
  int i;
  int j;
  int jA;
  int jAcol;
  int jBcol;
  int jp1j;
  int k;
  boolean_T exitg2;
  boolean_T guard1 = false;
  boolean_T p;
  eig(a, V, c);
  p = true;
  j = 0;
  exitg2 = false;
  while ((!exitg2) && (j < 3)) {
    jA = 0;
    do {
      exitg1 = 0;
      if (jA <= j) {
        jBcol = j + 3 * jA;
        jAcol = jA + 3 * j;
        if ((!(a[jAcol].re == a[jBcol].re)) ||
            (!(a[jAcol].im == -a[jBcol].im))) {
          p = false;
          exitg1 = 1;
        } else {
          jA++;
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
  guard1 = false;
  if (p) {
    guard1 = true;
  } else {
    p = true;
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j < 3)) {
      jA = 0;
      do {
        exitg1 = 0;
        if (jA <= j) {
          jBcol = j + 3 * jA;
          jAcol = jA + 3 * j;
          if ((!(a[jAcol].re == -a[jBcol].re)) ||
              (!(a[jAcol].im == a[jBcol].im))) {
            p = false;
            exitg1 = 1;
          } else {
            jA++;
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
    if (p) {
      guard1 = true;
    } else {
      signed char ipiv[3];
      memcpy(&Vfact[0], &V[0], 9U * sizeof(creal_T));
      ipiv[0] = 1;
      ipiv[1] = 2;
      ipiv[2] = 3;
      for (j = 0; j < 2; j++) {
        int b_tmp;
        int mmj_tmp;
        mmj_tmp = 1 - j;
        b_tmp = j << 2;
        jp1j = b_tmp + 2;
        jBcol = 3 - j;
        jAcol = 0;
        smax = fabs(Vfact[b_tmp].re) + fabs(Vfact[b_tmp].im);
        for (k = 2; k <= jBcol; k++) {
          jA = (b_tmp + k) - 1;
          s = fabs(Vfact[jA].re) + fabs(Vfact[jA].im);
          if (s > smax) {
            jAcol = k - 1;
            smax = s;
          }
        }
        jBcol = b_tmp + jAcol;
        if ((Vfact[jBcol].re != 0.0) || (Vfact[jBcol].im != 0.0)) {
          if (jAcol != 0) {
            jBcol = j + jAcol;
            ipiv[j] = (signed char)(jBcol + 1);
            temp = Vfact[j];
            Vfact[j] = Vfact[jBcol];
            Vfact[jBcol] = temp;
            temp = Vfact[j + 3];
            Vfact[j + 3] = Vfact[jBcol + 3];
            Vfact[jBcol + 3] = temp;
            temp = Vfact[j + 6];
            Vfact[j + 6] = Vfact[jBcol + 6];
            Vfact[jBcol + 6] = temp;
          }
          i = (b_tmp - j) + 3;
          for (jA = jp1j; jA <= i; jA++) {
            ar = Vfact[jA - 1].re;
            ai = Vfact[jA - 1].im;
            br = Vfact[b_tmp].re;
            bi = Vfact[b_tmp].im;
            if (bi == 0.0) {
              if (ai == 0.0) {
                re = ar / br;
                smax = 0.0;
              } else if (ar == 0.0) {
                re = 0.0;
                smax = ai / br;
              } else {
                re = ar / br;
                smax = ai / br;
              }
            } else if (br == 0.0) {
              if (ar == 0.0) {
                re = ai / bi;
                smax = 0.0;
              } else if (ai == 0.0) {
                re = 0.0;
                smax = -(ar / bi);
              } else {
                re = ai / bi;
                smax = -(ar / bi);
              }
            } else {
              s = fabs(br);
              smax = fabs(bi);
              if (s > smax) {
                s = bi / br;
                smax = br + s * bi;
                re = (ar + s * ai) / smax;
                smax = (ai - s * ar) / smax;
              } else if (smax == s) {
                if (br > 0.0) {
                  sgnbr = 0.5;
                } else {
                  sgnbr = -0.5;
                }
                if (bi > 0.0) {
                  smax = 0.5;
                } else {
                  smax = -0.5;
                }
                re = (ar * sgnbr + ai * smax) / s;
                smax = (ai * sgnbr - ar * smax) / s;
              } else {
                s = br / bi;
                smax = bi + s * br;
                re = (s * ar + ai) / smax;
                smax = (s * ai - ar) / smax;
              }
            }
            Vfact[jA - 1].re = re;
            Vfact[jA - 1].im = smax;
          }
        }
        jA = b_tmp;
        for (jp1j = 0; jp1j <= mmj_tmp; jp1j++) {
          Vfact_tmp_tmp = (b_tmp + jp1j * 3) + 3;
          smax = Vfact[Vfact_tmp_tmp].re;
          sgnbr = Vfact[Vfact_tmp_tmp].im;
          if ((smax != 0.0) || (sgnbr != 0.0)) {
            temp.re = -smax - sgnbr * 0.0;
            temp.im = smax * 0.0 - sgnbr;
            i = jA + 5;
            Vfact_tmp_tmp = (jA - j) + 6;
            for (jBcol = i; jBcol <= Vfact_tmp_tmp; jBcol++) {
              jAcol = ((b_tmp + jBcol) - jA) - 4;
              br = Vfact[jAcol].re;
              s = Vfact[jAcol].im;
              Vfact[jBcol - 1].re += br * temp.re - s * temp.im;
              Vfact[jBcol - 1].im += br * temp.im + s * temp.re;
            }
          }
          jA += 3;
        }
      }
      smax = 0.0;
      j = 0;
      exitg2 = false;
      while ((!exitg2) && (j < 3)) {
        jA = 3 * j + 1;
        jBcol = 3 * j + 2;
        s = (rt_hypotd_snf(V[3 * j].re, V[3 * j].im) +
             rt_hypotd_snf(V[jA].re, V[jA].im)) +
            rt_hypotd_snf(V[jBcol].re, V[jBcol].im);
        if (rtIsNaN(s)) {
          smax = rtNaN;
          exitg2 = true;
        } else {
          if (s > smax) {
            smax = s;
          }
          j++;
        }
      }
      if (rcond(Vfact, smax) < 0.01) {
        mpower_schur(a, c);
      } else {
        for (j = 0; j < 3; j++) {
          temp = power(c[j + 3 * j]);
          smax = V[3 * j].re;
          sgnbr = V[3 * j].im;
          c[3 * j].re = smax * temp.re - sgnbr * temp.im;
          c[3 * j].im = smax * temp.im + sgnbr * temp.re;
          i = 3 * j + 1;
          smax = V[i].re;
          sgnbr = V[i].im;
          c[i].re = smax * temp.re - sgnbr * temp.im;
          c[i].im = smax * temp.im + sgnbr * temp.re;
          i = 3 * j + 2;
          smax = V[i].re;
          sgnbr = V[i].im;
          c[i].re = smax * temp.re - sgnbr * temp.im;
          c[i].im = smax * temp.im + sgnbr * temp.re;
        }
        for (j = 0; j < 3; j++) {
          jBcol = 3 * j - 1;
          jAcol = 3 * j;
          for (k = 0; k < j; k++) {
            jA = 3 * k;
            Vfact_tmp_tmp = k + jAcol;
            smax = Vfact[Vfact_tmp_tmp].re;
            sgnbr = Vfact[Vfact_tmp_tmp].im;
            if ((smax != 0.0) || (sgnbr != 0.0)) {
              br = c[jA].im;
              s = c[jA].re;
              c[jBcol + 1].re -= smax * s - sgnbr * br;
              c[jBcol + 1].im -= smax * br + sgnbr * s;
              br = c[jA + 1].im;
              s = c[jA + 1].re;
              c[jBcol + 2].re -= smax * s - sgnbr * br;
              c[jBcol + 2].im -= smax * br + sgnbr * s;
              br = c[jA + 2].im;
              s = c[jA + 2].re;
              c[jBcol + 3].re -= smax * s - sgnbr * br;
              c[jBcol + 3].im -= smax * br + sgnbr * s;
            }
          }
          temp = recip(Vfact[j + jAcol]);
          smax = c[jBcol + 1].im;
          sgnbr = c[jBcol + 1].re;
          c[jBcol + 1].re = temp.re * sgnbr - temp.im * smax;
          c[jBcol + 1].im = temp.re * smax + temp.im * sgnbr;
          smax = c[jBcol + 2].im;
          sgnbr = c[jBcol + 2].re;
          c[jBcol + 2].re = temp.re * sgnbr - temp.im * smax;
          c[jBcol + 2].im = temp.re * smax + temp.im * sgnbr;
          smax = c[jBcol + 3].im;
          sgnbr = c[jBcol + 3].re;
          c[jBcol + 3].re = temp.re * sgnbr - temp.im * smax;
          c[jBcol + 3].im = temp.re * smax + temp.im * sgnbr;
        }
        for (j = 2; j >= 0; j--) {
          jBcol = 3 * j - 1;
          i = j + 2;
          for (k = i; k < 4; k++) {
            jA = 3 * (k - 1);
            Vfact_tmp_tmp = k + jBcol;
            smax = Vfact[Vfact_tmp_tmp].re;
            sgnbr = Vfact[Vfact_tmp_tmp].im;
            if ((smax != 0.0) || (sgnbr != 0.0)) {
              br = c[jA].im;
              s = c[jA].re;
              c[jBcol + 1].re -= smax * s - sgnbr * br;
              c[jBcol + 1].im -= smax * br + sgnbr * s;
              br = c[jA + 1].im;
              s = c[jA + 1].re;
              c[jBcol + 2].re -= smax * s - sgnbr * br;
              c[jBcol + 2].im -= smax * br + sgnbr * s;
              br = c[jA + 2].im;
              s = c[jA + 2].re;
              c[jBcol + 3].re -= smax * s - sgnbr * br;
              c[jBcol + 3].im -= smax * br + sgnbr * s;
            }
          }
        }
        for (j = 1; j >= 0; j--) {
          signed char i1;
          i1 = ipiv[j];
          if (i1 != j + 1) {
            temp = c[3 * j];
            jBcol = 3 * (i1 - 1);
            c[3 * j] = c[jBcol];
            c[jBcol] = temp;
            jAcol = 3 * j + 1;
            temp = c[jAcol];
            c[jAcol] = c[jBcol + 1];
            c[jBcol + 1] = temp;
            jAcol = 3 * j + 2;
            temp = c[jAcol];
            c[jAcol] = c[jBcol + 2];
            c[jBcol + 2] = temp;
          }
        }
      }
    }
  }
  if (guard1) {
    for (j = 0; j < 3; j++) {
      temp = power(c[j + 3 * j]);
      smax = V[3 * j].re;
      sgnbr = V[3 * j].im;
      c[3 * j].re = smax * temp.re - sgnbr * temp.im;
      c[3 * j].im = smax * temp.im + sgnbr * temp.re;
      i = 3 * j + 1;
      smax = V[i].re;
      sgnbr = V[i].im;
      c[i].re = smax * temp.re - sgnbr * temp.im;
      c[i].im = smax * temp.im + sgnbr * temp.re;
      i = 3 * j + 2;
      smax = V[i].re;
      sgnbr = V[i].im;
      c[i].re = smax * temp.re - sgnbr * temp.im;
      c[i].im = smax * temp.im + sgnbr * temp.re;
    }
    for (i = 0; i < 3; i++) {
      double b_c_re_tmp;
      double c_re_tmp;
      s = c[i].re;
      bi = c[i].im;
      ar = c[i + 3].re;
      ai = c[i + 3].im;
      c_re_tmp = c[i + 6].re;
      b_c_re_tmp = c[i + 6].im;
      for (Vfact_tmp_tmp = 0; Vfact_tmp_tmp < 3; Vfact_tmp_tmp++) {
        sgnbr = V[Vfact_tmp_tmp].re;
        br = -V[Vfact_tmp_tmp].im;
        re = s * sgnbr - bi * br;
        smax = s * br + bi * sgnbr;
        sgnbr = V[Vfact_tmp_tmp + 3].re;
        br = -V[Vfact_tmp_tmp + 3].im;
        re += ar * sgnbr - ai * br;
        smax += ar * br + ai * sgnbr;
        sgnbr = V[Vfact_tmp_tmp + 6].re;
        br = -V[Vfact_tmp_tmp + 6].im;
        re += c_re_tmp * sgnbr - b_c_re_tmp * br;
        smax += c_re_tmp * br + b_c_re_tmp * sgnbr;
        jBcol = i + 3 * Vfact_tmp_tmp;
        Vfact[jBcol].re = re;
        Vfact[jBcol].im = smax;
      }
    }
    memcpy(&c[0], &Vfact[0], 9U * sizeof(creal_T));
  }
}

/* End of code generation (mpower.c) */
