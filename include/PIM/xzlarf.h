/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlarf.h
 *
 * Code generation for function 'xzlarf'
 *
 */

#ifndef XZLARF_H
#define XZLARF_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_xzlarf(int m, int n, int iv0, const creal_T tau, creal_T C[9], int ic0,
              creal_T work[3]);

void xzlarf(int m, int n, int iv0, const creal_T tau, creal_T C[9], int ic0,
            creal_T work[3]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (xzlarf.h) */
