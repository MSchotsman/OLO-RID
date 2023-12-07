/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * correlatedRelease_emxutil.h
 *
 * Code generation for function 'correlatedRelease_emxutil'
 *
 */

#ifndef CORRELATEDRELEASE_EMXUTIL_H
#define CORRELATEDRELEASE_EMXUTIL_H

/* Include files */
#include "correlatedRelease_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray,
                                        int oldNumel);

extern void emxEnsureCapacity_creal_T(emxArray_creal_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_int8_T(emxArray_int8_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);

extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);

extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);

extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);

extern void emxFree_int8_T(emxArray_int8_T **pEmxArray);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray);

extern void emxInit_creal_T(emxArray_creal_T **pEmxArray);

extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);

extern void emxInit_int8_T(emxArray_int8_T **pEmxArray);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (correlatedRelease_emxutil.h) */
