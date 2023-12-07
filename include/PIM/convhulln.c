/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * convhulln.c
 *
 * Code generation for function 'convhulln'
 *
 */

/* Include files */
#include "convhulln.h"
#include "correlatedRelease_emxutil.h"
#include "correlatedRelease_types.h"
#include "mergeDuplicatePoints.h"
#include "rt_nonfinite.h"
#include "./qhull/interface/mwQhull.h"

/* Function Definitions */
void convhulln(const emxArray_real_T *varargin_1, emxArray_real_T *k)
{
  emxArray_int32_T *hull;
  emxArray_real_T *idxmap;
  emxArray_real_T *r;
  emxArray_real_T *uniquePts;
  double v;
  double *idxmap_data;
  double *k_data;
  double *r1;
  int err;
  int i;
  int *hull_data;
  char qhullOptions_data[3];
  boolean_T dupesfound;
  emxInit_real_T(&uniquePts, 2);
  emxInit_real_T(&idxmap, 1);
  dupesfound = mergeDuplicatePoints(varargin_1, uniquePts, idxmap);
  idxmap_data = idxmap->data;
  k_data = uniquePts->data;
  qhullOptions_data[0] = 'Q';
  qhullOptions_data[1] = 't';
  qhullOptions_data[2] = '\x00';
  emxInit_real_T(&r, 2);
  i = r->size[0] * r->size[1];
  r->size[0] = 3;
  r->size[1] = uniquePts->size[0];
  emxEnsureCapacity_real_T(r, i);
  r1 = r->data;
  err = uniquePts->size[0];
  for (i = 0; i < err; i++) {
    r1[3 * i] = k_data[i];
    r1[3 * i + 1] = k_data[i + uniquePts->size[0]];
    r1[3 * i + 2] = k_data[i + uniquePts->size[0] * 2];
  }
  err =
      computeConvexhulln(&r1[0], 3, uniquePts->size[0], &qhullOptions_data[0]);
  emxFree_real_T(&r);
  emxFree_real_T(&uniquePts);
  if (err > 0) {
    char errMsg[4096];
    getQhullErrorStr(&errMsg[0]);
  }
  err = getNumConvhullTrias();
  emxInit_int32_T(&hull, 2);
  i = hull->size[0] * hull->size[1];
  hull->size[0] = err;
  hull->size[1] = 3;
  emxEnsureCapacity_int32_T(hull, i);
  hull_data = hull->data;
  produceConvexhull(&hull_data[0], err, 3, &v);
  freeQhullMemory();
  if (dupesfound) {
    i = k->size[0] * k->size[1];
    k->size[0] = hull->size[0];
    k->size[1] = 3;
    emxEnsureCapacity_real_T(k, i);
    k_data = k->data;
    err = hull->size[0] * 3;
    for (i = 0; i < err; i++) {
      k_data[i] = idxmap_data[hull_data[i] - 1];
    }
  } else {
    i = k->size[0] * k->size[1];
    k->size[0] = hull->size[0];
    k->size[1] = 3;
    emxEnsureCapacity_real_T(k, i);
    k_data = k->data;
    err = hull->size[0] * 3;
    for (i = 0; i < err; i++) {
      k_data[i] = hull_data[i];
    }
  }
  emxFree_int32_T(&hull);
  emxFree_real_T(&idxmap);
}

/* End of code generation (convhulln.c) */
