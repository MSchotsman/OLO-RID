/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * minOrMax.h
 *
 * Code generation for function 'minOrMax'
 *
 */

#ifndef MINORMAX_H
#define MINORMAX_H

/* Include files */
#include "correlatedRelease_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double b_maximum(const emxArray_real_T *x);

double b_minimum(const double x[3], int *idx);

double c_minimum(const emxArray_real_T *x);

creal_T d_minimum(const emxArray_creal_T *x);

double maximum(const double x[27]);

double minimum(const double x[27]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (minOrMax.h) */
