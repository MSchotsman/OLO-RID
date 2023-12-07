/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_correlatedRelease_api.c
 *
 * Code generation for function 'correlatedRelease'
 *
 */

/* Include files */
#include "_coder_correlatedRelease_api.h"
#include "_coder_correlatedRelease_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131642U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "correlatedRelease",                                  /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static const mxArray *b_emlrt_marshallOut(const emlrtStack *sp,
                                          const creal_T u[3]);

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *p_pos,
                                   const char_T *identifier))[27];

static const mxArray *c_emlrt_marshallOut(const real_T u[81]);

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[27];

static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *x,
                                   const char_T *identifier))[3];

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *epsilon,
                               const char_T *identifier);

static const mxArray *emlrt_marshallOut(const emxArray_real_T *u);

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3];

static real_T *g_emlrt_marshallIn(const emlrtStack *sp,
                                  const mxArray *old_locations,
                                  const char_T *identifier, int32_T y_size[2]);

static real_T *h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId,
                                  int32_T y_size[2]);

static real_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[27];

static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3];

static real_T *l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId,
                                  int32_T ret_size[2]);

/* Function Definitions */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *b_emlrt_marshallOut(const emlrtStack *sp,
                                          const creal_T u[3])
{
  static const int32_T i = 3;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxCOMPLEX);
  emlrtExportNumericArrayR2013b((emlrtConstCTX)sp, m, (const void *)&u[0], 8);
  emlrtAssign(&y, m);
  return y;
}

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *p_pos,
                                   const char_T *identifier))[27]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[27];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(p_pos), &thisId);
  emlrtDestroyArray(&p_pos);
  return y;
}

static const mxArray *c_emlrt_marshallOut(const real_T u[81])
{
  static const int32_T iv[2] = {0, 0};
  static const int32_T iv1[2] = {27, 3};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[27]
{
  real_T(*y)[27];
  y = j_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *x,
                                   const char_T *identifier))[3]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[3];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(x), &thisId);
  emlrtDestroyArray(&x);
  return y;
}

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *epsilon,
                               const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(epsilon), &thisId);
  emlrtDestroyArray(&epsilon);
  return y;
}

static const mxArray *emlrt_marshallOut(const emxArray_real_T *u)
{
  static const int32_T i = 0;
  const mxArray *m;
  const mxArray *y;
  const real_T *u_data;
  u_data = u->data;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m, &u->size[0], 1);
  emlrtAssign(&y, m);
  return y;
}

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference((emlrtCTX)sp, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  emxArray_real_T *emxArray;
  *pEmxArray = (emxArray_real_T *)emlrtMallocEmxArray(sizeof(emxArray_real_T));
  emlrtPushHeapReferenceStackEmxArray((emlrtCTX)sp, true, (void *)pEmxArray,
                                      (void *)&emxFree_real_T, NULL, NULL,
                                      NULL);
  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = 1;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  emxArray->size[0] = 0;
}

static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3]
{
  real_T(*y)[3];
  y = k_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T *g_emlrt_marshallIn(const emlrtStack *sp,
                                  const mxArray *old_locations,
                                  const char_T *identifier, int32_T y_size[2])
{
  emlrtMsgIdentifier thisId;
  real_T *y_data;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y_data = h_emlrt_marshallIn(sp, emlrtAlias(old_locations), &thisId, y_size);
  emlrtDestroyArray(&old_locations);
  return y_data;
}

static real_T *h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId,
                                  int32_T y_size[2])
{
  real_T *y_data;
  y_data = l_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y_size);
  emlrtDestroyArray(&u);
  return y_data;
}

static real_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[27]
{
  static const int32_T dims = 27;
  real_T(*ret)[27];
  int32_T i;
  boolean_T b = false;
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 1U,
                            (const void *)&dims, &b, &i);
  ret = (real_T(*)[27])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3]
{
  static const int32_T dims[2] = {1, 3};
  real_T(*ret)[3];
  int32_T iv[2];
  boolean_T bv[2] = {false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 2U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (real_T(*)[3])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T *l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId,
                                  int32_T ret_size[2])
{
  static const int32_T dims[2] = {27, 3};
  real_T *ret_data;
  int32_T iv[2];
  boolean_T bv[2] = {true, true};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 2U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret_size[0] = iv[0];
  ret_size[1] = iv[1];
  ret_data = (real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret_data;
}

void correlatedRelease_api(const mxArray *const prhs[9], int32_T nlhs,
                           const mxArray *plhs[3])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  emxArray_real_T *p_pos_res;
  const mxArray *prhs_copy_idx_4;
  creal_T z[3];
  real_T(*Locations_orig)[81];
  real_T(*old_locations_data)[81];
  real_T(*p_pos)[27];
  real_T(*x)[3];
  real_T M;
  real_T delta;
  real_T drone_speed;
  real_T epsilon;
  real_T number_of_blocks_per_dim;
  real_T shift_lat_long;
  int32_T old_locations_size[2];
  st.tls = emlrtRootTLSGlobal;
  Locations_orig = (real_T(*)[81])mxMalloc(sizeof(real_T[81]));
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  prhs_copy_idx_4 = emlrtProtectR2012b(prhs[4], 4, false, -1);
  /* Marshall function inputs */
  epsilon = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "epsilon");
  delta = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "delta");
  M = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "M");
  p_pos = c_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "p_pos");
  x = e_emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_4), "x");
  drone_speed = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "drone_speed");
  shift_lat_long =
      emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "shift_lat_long");
  *(real_T **)&old_locations_data = g_emlrt_marshallIn(
      &st, emlrtAlias(prhs[7]), "old_locations", old_locations_size);
  number_of_blocks_per_dim =
      emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "number_of_blocks_per_dim");
  /* Invoke the target function */
  emxInit_real_T(&st, &p_pos_res);
  correlatedRelease(epsilon, delta, M, *p_pos, *x, drone_speed, shift_lat_long,
                    *old_locations_data, old_locations_size,
                    number_of_blocks_per_dim, p_pos_res, z, *Locations_orig);
  /* Marshall function outputs */
  p_pos_res->canFreeData = false;
  plhs[0] = emlrt_marshallOut(p_pos_res);
  emxFree_real_T(&st, &p_pos_res);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(&st, z);
  }
  if (nlhs > 2) {
    plhs[2] = c_emlrt_marshallOut(*Locations_orig);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

void correlatedRelease_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  correlatedRelease_xil_terminate();
  correlatedRelease_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void correlatedRelease_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void correlatedRelease_terminate(void)
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_correlatedRelease_api.c) */
