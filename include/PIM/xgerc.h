/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgerc.h
 *
 * Code generation for function 'xgerc'
 *
 */

#ifndef XGERC_H
#define XGERC_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void xgerc(int m, int n, const creal_T alpha1, int ix0, const creal_T y[3],
           creal_T A[9], int ia0);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (xgerc.h) */
