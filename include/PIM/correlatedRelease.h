/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * correlatedRelease.h
 *
 * Code generation for function 'correlatedRelease'
 *
 */

#ifndef CORRELATEDRELEASE_H
#define CORRELATEDRELEASE_H

/* Include files */
#include "correlatedRelease_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void correlatedRelease(double epsilon, double delta, double M,
                              const double p_pos[27], double x[3],
                              double drone_speed, double shift_lat_long,
                              double old_locations_data[],
                              const int old_locations_size[2],
                              double number_of_blocks_per_dim,
                              emxArray_real_T *p_pos_res, creal_T z[3],
                              double Locations_orig[81], int debug);

creal_T real_min(const emxArray_creal_T *x);

creal_T real_max(const emxArray_creal_T *x);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (correlatedRelease.h) */
