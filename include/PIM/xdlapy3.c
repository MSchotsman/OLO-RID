/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdlapy3.c
 *
 * Code generation for function 'xdlapy3'
 *
 */

/* Include files */
#include "xdlapy3.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
double xdlapy3(double x1, double x2, double x3)
{
  double a;
  double b;
  double c;
  double y;
  a = fabs(x1);
  b = fabs(x2);
  c = fabs(x3);
  if (a > b) {
    y = a;
  } else {
    y = b;
  }
  if (c > y) {
    y = c;
  }
  if ((y > 0.0) && (!rtIsInf(y))) {
    a /= y;
    b /= y;
    c /= y;
    y *= sqrt((a * a + c * c) + b * b);
  } else {
    y = (a + b) + c;
  }
  return y;
}

/* End of code generation (xdlapy3.c) */
