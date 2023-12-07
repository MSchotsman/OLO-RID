/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * correlatedRelease_initialize.c
 *
 * Code generation for function 'correlatedRelease_initialize'
 *
 */

/* Include files */
#include "correlatedRelease_initialize.h"
#include "correlatedRelease_data.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void correlatedRelease_initialize(void)
{
  c_eml_rand_mt19937ar_stateful_i();
  isInitialized_correlatedRelease = true;
}

/* End of code generation (correlatedRelease_initialize.c) */
