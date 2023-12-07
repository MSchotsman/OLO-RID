/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_correlatedRelease_api.h
 *
 * Code generation for function 'correlatedRelease'
 *
 */

#ifndef _CODER_CORRELATEDRELEASE_API_H
#define _CODER_CORRELATEDRELEASE_API_H

/* Include files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void correlatedRelease(real_T epsilon, real_T delta, real_T M, real_T p_pos[27],
                       real_T x[3], real_T drone_speed, real_T shift_lat_long,
                       real_T old_locations_data[],
                       int32_T old_locations_size[2],
                       real_T number_of_blocks_per_dim,
                       emxArray_real_T *p_pos_res, creal_T z[3],
                       real_T Locations_orig[81]);

void correlatedRelease_api(const mxArray *const prhs[9], int32_T nlhs,
                           const mxArray *plhs[3]);

void correlatedRelease_atexit(void);

void correlatedRelease_initialize(void);

void correlatedRelease_terminate(void);

void correlatedRelease_xil_shutdown(void);

void correlatedRelease_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_correlatedRelease_api.h) */
