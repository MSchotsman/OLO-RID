/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mergeDuplicatePoints.h
 *
 * Code generation for function 'mergeDuplicatePoints'
 *
 */

#ifndef MERGEDUPLICATEPOINTS_H
#define MERGEDUPLICATEPOINTS_H

/* Include files */
#include "correlatedRelease_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
boolean_T mergeDuplicatePoints(const emxArray_real_T *pts,
                               emxArray_real_T *uniquePts,
                               emxArray_real_T *idxmap);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (mergeDuplicatePoints.h) */
