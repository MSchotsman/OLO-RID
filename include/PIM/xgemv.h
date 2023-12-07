/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgemv.h
 *
 * Code generation for function 'xgemv'
 *
 */

#ifndef XGEMV_H
#define XGEMV_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void xgemv(int m, int n, const creal_T A[9], int ia0, const creal_T x[9],
           int ix0, creal_T y[3]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (xgemv.h) */
