/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * gamrnd.c
 *
 * Code generation for function 'gamrnd'
 *
 */

/* Include files */
#include "gamrnd.h"
#include "rand.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
double gamrnd(double b)
{
  double r;
  double u;
  double v;
  double x;
  int iter;
  u = b_rand();
  iter = 0;
  x = 0.0;
  int exitg1;
  do {
    exitg1 = 0;
    for (v = -1.0; v <= 0.0; v = 0.20412414523193154 * x + 1.0) {
      x = randn();
    }
    v *= v * v;
    x *= x;
    if ((u < 1.0 - 0.0331 * x * x) ||
        (log(u) < 0.5 * x + 2.6666666666666665 * ((1.0 - v) + log(v)))) {
      exitg1 = 1;
    } else {
      iter++;
      if (iter > 1000000) {
        exitg1 = 1;
      } else {
        u = b_rand();
      }
    }
  } while (exitg1 == 0);
  r = b * (2.6666666666666665 * v);
  if (b < 0.0) {
    r = rtNaN;
  }
  return r;
}

/* End of code generation (gamrnd.c) */
