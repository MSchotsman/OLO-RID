/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mergeDuplicatePoints.c
 *
 * Code generation for function 'mergeDuplicatePoints'
 *
 */

/* Include files */
#include "mergeDuplicatePoints.h"
#include "correlatedRelease_emxutil.h"
#include "correlatedRelease_types.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sortLE.h"

/* Function Definitions */
boolean_T mergeDuplicatePoints(const emxArray_real_T *pts,
                               emxArray_real_T *uniquePts,
                               emxArray_real_T *idxmap)
{
  emxArray_int32_T *idx;
  emxArray_int32_T *iwork;
  emxArray_real_T *b;
  emxArray_real_T *ycol;
  const double *pts_data;
  double *idxmap_data;
  double *ycol_data;
  int b_i;
  int i;
  int i1;
  int j;
  int k;
  int k0;
  int khi;
  int qEnd;
  int *idx_data;
  int *iwork_data;
  boolean_T dupesfound;
  pts_data = pts->data;
  dupesfound = false;
  emxInit_int32_T(&idx, 1);
  idx_data = idx->data;
  if (pts->size[0] == 0) {
    idx->size[0] = 0;
  } else {
    int n;
    int nb;
    emxInit_real_T(&b, 2);
    i = b->size[0] * b->size[1];
    b->size[0] = pts->size[0];
    b->size[1] = 3;
    emxEnsureCapacity_real_T(b, i);
    idxmap_data = b->data;
    khi = pts->size[0] * 3;
    for (i = 0; i < khi; i++) {
      idxmap_data[i] = pts_data[i];
    }
    n = pts->size[0] + 1;
    i = idx->size[0];
    idx->size[0] = pts->size[0];
    emxEnsureCapacity_int32_T(idx, i);
    idx_data = idx->data;
    khi = pts->size[0];
    for (i = 0; i < khi; i++) {
      idx_data[i] = 0;
    }
    emxInit_int32_T(&iwork, 1);
    i = iwork->size[0];
    iwork->size[0] = pts->size[0];
    emxEnsureCapacity_int32_T(iwork, i);
    iwork_data = iwork->data;
    i = pts->size[0] - 1;
    for (k = 1; k <= i; k += 2) {
      if (sortLE(pts, k, k + 1)) {
        idx_data[k - 1] = k;
        idx_data[k] = k + 1;
      } else {
        idx_data[k - 1] = k + 1;
        idx_data[k] = k;
      }
    }
    if ((pts->size[0] & 1) != 0) {
      idx_data[pts->size[0] - 1] = pts->size[0];
    }
    b_i = 2;
    while (b_i < n - 1) {
      khi = b_i << 1;
      j = 1;
      for (k0 = b_i + 1; k0 < n; k0 = qEnd + b_i) {
        int kEnd;
        int q;
        nb = j;
        q = k0;
        qEnd = j + khi;
        if (qEnd > n) {
          qEnd = n;
        }
        k = 0;
        kEnd = qEnd - j;
        while (k + 1 <= kEnd) {
          int i2;
          i1 = idx_data[nb - 1];
          i2 = idx_data[q - 1];
          if (sortLE(pts, i1, i2)) {
            iwork_data[k] = i1;
            nb++;
            if (nb == k0) {
              while (q < qEnd) {
                k++;
                iwork_data[k] = idx_data[q - 1];
                q++;
              }
            }
          } else {
            iwork_data[k] = i2;
            q++;
            if (q == qEnd) {
              while (nb < k0) {
                k++;
                iwork_data[k] = idx_data[nb - 1];
                nb++;
              }
            }
          }
          k++;
        }
        for (k = 0; k < kEnd; k++) {
          idx_data[(j + k) - 1] = iwork_data[k];
        }
        j = qEnd;
      }
      b_i = khi;
    }
    emxFree_int32_T(&iwork);
    emxInit_real_T(&ycol, 1);
    i1 = ycol->size[0];
    ycol->size[0] = pts->size[0];
    emxEnsureCapacity_real_T(ycol, i1);
    ycol_data = ycol->data;
    for (j = 0; j < 3; j++) {
      for (b_i = 0; b_i <= i; b_i++) {
        ycol_data[b_i] = idxmap_data[(idx_data[b_i] + b->size[0] * j) - 1];
      }
      for (b_i = 0; b_i <= i; b_i++) {
        idxmap_data[b_i + b->size[0] * j] = ycol_data[b_i];
      }
    }
    i = ycol->size[0];
    ycol->size[0] = idx->size[0];
    emxEnsureCapacity_real_T(ycol, i);
    ycol_data = ycol->data;
    khi = idx->size[0];
    for (i = 0; i < khi; i++) {
      ycol_data[i] = idx_data[i];
    }
    nb = -1;
    khi = pts->size[0];
    k = 0;
    while (k + 1 <= khi) {
      k0 = k;
      int exitg1;
      do {
        exitg1 = 0;
        k++;
        if (k + 1 > khi) {
          exitg1 = 1;
        } else {
          boolean_T exitg2;
          boolean_T p;
          p = false;
          j = 0;
          exitg2 = false;
          while ((!exitg2) && (j < 3)) {
            if (idxmap_data[k0 + b->size[0] * j] !=
                idxmap_data[k + b->size[0] * j]) {
              p = true;
              exitg2 = true;
            } else {
              j++;
            }
          }
          if (p) {
            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);
      nb++;
      idxmap_data[nb] = idxmap_data[k0];
      idxmap_data[nb + b->size[0]] = idxmap_data[k0 + b->size[0]];
      idxmap_data[nb + b->size[0] * 2] = idxmap_data[k0 + b->size[0] * 2];
      ycol_data[nb] = ycol_data[k0];
    }
    emxFree_real_T(&b);
    i = idx->size[0];
    idx->size[0] = nb + 1;
    emxEnsureCapacity_int32_T(idx, i);
    idx_data = idx->data;
    for (k = 0; k <= nb; k++) {
      idx_data[k] = (int)ycol_data[k];
    }
    emxFree_real_T(&ycol);
  }
  i = idxmap->size[0];
  idxmap->size[0] = idx->size[0];
  emxEnsureCapacity_real_T(idxmap, i);
  idxmap_data = idxmap->data;
  khi = idx->size[0];
  for (i = 0; i < khi; i++) {
    idxmap_data[i] = idx_data[i];
  }
  emxFree_int32_T(&idx);
  if (pts->size[0] > idxmap->size[0]) {
    b_sort(idxmap);
    idxmap_data = idxmap->data;
    i = uniquePts->size[0] * uniquePts->size[1];
    uniquePts->size[0] = idxmap->size[0];
    uniquePts->size[1] = 3;
    emxEnsureCapacity_real_T(uniquePts, i);
    ycol_data = uniquePts->data;
    khi = idxmap->size[0];
    for (i = 0; i < 3; i++) {
      for (i1 = 0; i1 < khi; i1++) {
        ycol_data[i1 + uniquePts->size[0] * i] =
            pts_data[((int)idxmap_data[i1] + pts->size[0] * i) - 1];
      }
    }
    dupesfound = true;
  } else {
    i = uniquePts->size[0] * uniquePts->size[1];
    uniquePts->size[0] = pts->size[0];
    uniquePts->size[1] = 3;
    emxEnsureCapacity_real_T(uniquePts, i);
    ycol_data = uniquePts->data;
    khi = pts->size[0] * 3;
    for (i = 0; i < khi; i++) {
      ycol_data[i] = pts_data[i];
    }
  }
  return dupesfound;
}

/* End of code generation (mergeDuplicatePoints.c) */
