/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_correlatedRelease_mex.c
 *
 * Code generation for function 'correlatedRelease'
 *
 */

/* Include files */
#include "_coder_correlatedRelease_mex.h"
#include "_coder_correlatedRelease_api.h"

/* Function Definitions */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&correlatedRelease_atexit);
  /* Module initialization. */
  correlatedRelease_initialize();
  /* Dispatch the entry-point. */
  unsafe_correlatedRelease_mexFunction(nlhs, plhs, nrhs, prhs);
  /* Module termination. */
  correlatedRelease_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL, "windows-1252", true);
  return emlrtRootTLSGlobal;
}

void unsafe_correlatedRelease_mexFunction(int32_T nlhs, mxArray *plhs[3],
                                          int32_T nrhs, const mxArray *prhs[9])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *b_prhs[9];
  const mxArray *outputs[3];
  int32_T i;
  int32_T i1;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 9) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 9, 4,
                        17, "correlatedRelease");
  }
  if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 17,
                        "correlatedRelease");
  }
  /* Call the function. */
  for (i = 0; i < 9; i++) {
    b_prhs[i] = prhs[i];
  }
  correlatedRelease_api(b_prhs, nlhs, outputs);
  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    i1 = 1;
  } else {
    i1 = nlhs;
  }
  emlrtReturnArrays(i1, &plhs[0], &outputs[0]);
}

/* End of code generation (_coder_correlatedRelease_mex.c) */
