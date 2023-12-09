/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * correlatedRelease.c
 *
 * Code generation for function 'correlatedRelease'
 *
 */

/* Include files */
#include "correlatedRelease.h"
#include "convhulln.h"
#include "correlatedRelease_data.h"
#include "correlatedRelease_emxutil.h"
#include "correlatedRelease_initialize.h"
#include "correlatedRelease_rtwutil.h"
#include "correlatedRelease_types.h"
#include "find.h"
#include "gamrnd.h"
#include "mergeDuplicatePoints.h"
#include "minOrMax.h"
#include "mpower.h"
#include "norm.h"
#include "rand.h"
#include "relop.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "./qhull/interface/mwQhull.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void b_binary_expand_op(double in1[3], const double in2_data[],
                               const int in2_size[2], int in3,
                               const double in4[81], int in5);

static void binary_expand_op(emxArray_real_T *in1, const double in2[27],
                             int in3, int in4, int in5,
                             const emxArray_real_T *in6, int in7, int in8,
                             int in9);

/* Function Definitions */
static void b_binary_expand_op(double in1[3], const double in2_data[],
                               const int in2_size[2], int in3,
                               const double in4[81], int in5)
{
  int stride_0_1;
  stride_0_1 = (in2_size[1] != 1);
  in1[0] = in2_data[in3] - in4[in5];
  in1[1] = in2_data[in3 + in2_size[0] * stride_0_1] - in4[in5 + 27];
  in1[2] = in2_data[in3 + in2_size[0] * (stride_0_1 << 1)] - in4[in5 + 54];
}

static void binary_expand_op(emxArray_real_T *in1, const double in2[27],
                             int in3, int in4, int in5,
                             const emxArray_real_T *in6, int in7, int in8,
                             int in9)
{
  emxArray_real_T *b_in2;
  double in2_data[53];
  const double *in6_data;
  double *b_in2_data;
  double *in1_data;
  int i;
  int in2_size;
  int loop_ub;
  int stride_1_0;
  in6_data = in6->data;
  in2_size = ((in3 + in5) - in4) + 1;
  if (in3 >= 0) {
    memcpy(&in2_data[0], &in2[0], (unsigned int)(in3 + 1) * sizeof(double));
  }
  loop_ub = (in5 - in4) - 1;
  for (i = 0; i <= loop_ub; i++) {
    in2_data[(i + in3) + 1] = in2[(in4 + i) + 1];
  }
  i = in1->size[0];
  in1->size[0] = ((in7 + in9) - in8) + 1;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  for (i = 0; i <= in7; i++) {
    in1_data[i] = in6_data[i];
  }
  loop_ub = (in9 - in8) - 1;
  for (i = 0; i <= loop_ub; i++) {
    in1_data[(i + in7) + 1] = in6_data[(in8 + i) + 1];
  }
  emxInit_real_T(&b_in2, 1);
  if (in1->size[0] == 1) {
    loop_ub = in2_size;
  } else {
    loop_ub = in1->size[0];
  }
  i = b_in2->size[0];
  b_in2->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_in2, i);
  b_in2_data = b_in2->data;
  in2_size = (in2_size != 1);
  stride_1_0 = (in1->size[0] != 1);
  for (i = 0; i < loop_ub; i++) {
    b_in2_data[i] = in2_data[i * in2_size] * in1_data[i * stride_1_0];
  }
  i = in1->size[0];
  in1->size[0] = b_in2->size[0];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in2->size[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = b_in2_data[i];
  }
  emxFree_real_T(&b_in2);
}

void correlatedRelease(double epsilon, double delta, double M,
                       const double p_pos[27], double x[3], double drone_speed,
                       double shift_lat_long, double old_locations_data[],
                       const int old_locations_size[2],
                       double number_of_blocks_per_dim,
                       emxArray_real_T *p_pos_res, creal_T z[3],
                       double Locations_orig[81])
{
  static const signed char permutation[81] = {
      0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1, 1, 1,  1, 1,
      1,  -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  0,  0, 1, 1,  1, -1,
      -1, -1, 0,  0,  0,  1,  1,  1,  -1, -1, -1, 0,  0, 0, 1,  1, 1,
      -1, -1, -1, 0,  1,  -1, 0,  1,  -1, 0,  1,  -1, 0, 1, -1, 0, 1,
      -1, 0,  1,  -1, 0,  1,  -1, 0,  1,  -1, 0,  1,  -1};
  emxArray_boolean_T *b_Locations;
  emxArray_creal_T *K_I;
  emxArray_creal_T *b_K_I;
  emxArray_creal_T *c_K_I;
  emxArray_creal_T *c_x;
  emxArray_creal_T *d_K_I;
  emxArray_creal_T *e_K_I;
  emxArray_creal_T *f_K_I;
  emxArray_creal_T *k_idx;
  emxArray_int32_T *hull;
  emxArray_int32_T *iidx;
  emxArray_int32_T *r;
  emxArray_int8_T *selected;
  emxArray_real_T *Delta_v;
  emxArray_real_T *K_prime;
  emxArray_real_T *b_K_prime;
  emxArray_real_T *b_idx;
  emxArray_real_T *c_idx;
  emxArray_real_T *d_idx;
  emxArray_real_T *e_idx;
  emxArray_real_T *f_idx;
  emxArray_real_T *g_idx;
  emxArray_real_T *h_idx;
  emxArray_real_T *i_idx;
  emxArray_real_T *idx;
  emxArray_real_T *j_idx;
  emxArray_real_T *new_y_vals;
  emxArray_real_T *p_prior;
  creal_T T[9];
  creal_T b_T_new[9];
  creal_T b_res_part[9];
  creal_T c_Locations[3];
  creal_T b_ex;
  creal_T c_ex;
  creal_T d_x;
  creal_T ex;
  creal_T *K_I_data;
  creal_T *b_K_I_data;
  creal_T *c_K_I_data;
  creal_T *d_K_I_data;
  creal_T *e_K_I_data;
  creal_T *f_K_I_data;
  creal_T *i_idx_data;
  double Locations[81];
  double p_z_u_data[53];
  double p_z_u[27];
  double T_new[9];
  double matSums[3];
  double res_part[3];
  double T_re_tmp;
  double b_T_re_tmp;
  double b_r;
  double c_T_re_tmp;
  double d;
  double d_T_re_tmp;
  double e_T_re_tmp;
  double f_T_re_tmp;
  double g_T_re_tmp;
  double h_T_re_tmp;
  double i_T_re_tmp;
  double j_T_re_tmp;
  double scaling_fac_x;
  double scaling_fac_y;
  double sumP;
  double *Delta_v_data;
  double *K_prime_data;
  double *b_idx_data;
  double *c_idx_data;
  double *d_idx_data;
  double *e_idx_data;
  double *f_idx_data;
  double *g_idx_data;
  double *h_idx_data;
  double *idx_data;
  double *new_y_vals_data;
  double *p_pos_res_data;
  double *p_prior_data;
  int b_i;
  int hi;
  int i;
  int i1;
  int lastBlockLength;
  int loop_ub;
  int loop_ub_tmp;
  int nblocks;
  int xpageoffset;
  int *hull_data;
  char qhullOptions_data[3];
  signed char *selected_data;
  boolean_T exitg1;
  boolean_T p;
  boolean_T *Locations_data;

  // matSums = permutation.*[shift_lat_long,shift_lat_long,drone_speed];
  // Locations_orig = x + matSums;

  // Added code
  for (int i = 0; i < 81; i++) {
    old_locations_data[i] = Locations_orig[i];
  }

  matSums[0] = shift_lat_long;
  matSums[1] = shift_lat_long;
  matSums[2] = drone_speed;
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < 27; i1++) {
      xpageoffset = i1 + 27 * i;
      Locations_orig[xpageoffset] =
          x[i] + (double)permutation[xpageoffset] * matSums[i];
    }
  }
  i = p_pos_res->size[0];
  p_pos_res->size[0] = 27;
  emxEnsureCapacity_real_T(p_pos_res, i);
  p_pos_res_data = p_pos_res->data;
  for (i = 0; i < 27; i++) {
    p_pos_res_data[i] = 0.0;
  }
  emxInit_real_T(&p_prior, 1);

  


  // if isempty(old_locations)
  if ((old_locations_size[0] == 0) || (old_locations_size[1] == 0)) {
    // p_prior = M.*ones(size(p_pos,1))*p_pos;
    i = p_prior->size[0];
    p_prior->size[0] = 27;
    emxEnsureCapacity_real_T(p_prior, i);
    p_prior_data = p_prior->data;
    for (i = 0; i < 27; i++) {
      sumP = 0.0;
      for (i1 = 0; i1 < 27; i1++) {
        sumP += M * p_pos[i1];
      }
      p_prior_data[i] = sumP;
    }
  } else {
    /* [C,ia,ib] = intersect(old_locations,Locations_orig); */
    sumP = rt_powd_snf(number_of_blocks_per_dim, 3.0);
    loop_ub_tmp = (int)sumP;
    i = p_pos_res->size[0];
    p_pos_res->size[0] = (int)sumP;
    emxEnsureCapacity_real_T(p_pos_res, i);
    p_pos_res_data = p_pos_res->data;
    for (i = 0; i < loop_ub_tmp; i++) {
      p_pos_res_data[i] = 1.0 / sumP;
    }
    loop_ub = old_locations_size[1];
    for (xpageoffset = 0; xpageoffset < 27; xpageoffset++) {
      for (hi = 0; hi < 27; hi++) {
        // if (old_locations_size[1] == 3) {
        //   for (i = 0; i < loop_ub; i++) {
        //     res_part[i] =
        //         old_locations_data[xpageoffset + old_locations_size[0] * i] -
        //         Locations_orig[hi + 27 * i];
        //   }
        // } else {
        //   b_binary_expand_op(res_part, old_locations_data, old_locations_size,
        //                      xpageoffset, Locations_orig, hi);
        // }
        for (int cnt = 0; cnt < 3; cnt++) {
          res_part[cnt] = old_locations_data[xpageoffset + 27*cnt] - Locations_orig[hi + 27*cnt];
        }
        // if ((fabs(res_part[0]) + fabs(res_part[1])) + fabs(res_part[2]) <=
        //     1.0E-6) {
        if ((fabs(res_part[0]) + fabs(res_part[1])) + fabs(res_part[2]) <=
            0.00000095367431640624) {
          p_pos_res_data[hi] = p_pos[xpageoffset];
        }
        // Check for iteration 103, should be removed later TODO
        // if (((fabs(res_part[0]) + fabs(res_part[1])) + fabs(res_part[2]) <=
        //     0.00000095367431640625) && *rand_num_generated == 45389) {
        //   // printf("Trigger at: %i, %i\n", xpageoffset, hi);
        //   p_pos_res_data[hi] = p_pos[xpageoffset];
        // }
      }
    }
    /* p_pos = p_pos;%./sum(p_pos); */
    xpageoffset = p_pos_res->size[0] - 1;
    hi = p_pos_res->size[0];
    i = p_prior->size[0];
    p_prior->size[0] = p_pos_res->size[0];
    emxEnsureCapacity_real_T(p_prior, i);
    p_prior_data = p_prior->data;
    for (b_i = 0; b_i <= xpageoffset; b_i++) {
      p_prior_data[b_i] = 0.0;
    }
    for (loop_ub = 0; loop_ub < hi; loop_ub++) {
      for (b_i = 0; b_i <= xpageoffset; b_i++) {
        p_prior_data[b_i] += M * p_pos_res_data[loop_ub];
      }
    }
    /*  compute prior probability */
  }
  
  /*  difference in value scaling lat and alt */
  sumP = maximum(&Locations_orig[54]) - minimum(&Locations_orig[54]);
  scaling_fac_x =
      sumP / (maximum(&Locations_orig[0]) - minimum(&Locations_orig[0]));
  /* scaling_fac_x = 0.1; */
  x[0] *= scaling_fac_x;
  /*  difference in value scaling long and alt */
  scaling_fac_y =
      sumP / (maximum(&Locations_orig[27]) - minimum(&Locations_orig[27]));
  for (i = 0; i < 27; i++) {
    Locations[i] = Locations_orig[i] * scaling_fac_x;
    Locations[i + 27] = Locations_orig[i + 27] * scaling_fac_y;
    Locations[i + 54] = Locations_orig[i + 54];
  }
  x[1] *= scaling_fac_x;
  /*  construct delta location set */
  /*  delta-location set = minimum set such that the sum of probabilities \geq
   */
  /*  1-delta */
  /*  sort probability elements in descending order */
  emxInit_real_T(&idx, 1);
  i = idx->size[0];
  idx->size[0] = p_prior->size[0];
  emxEnsureCapacity_real_T(idx, i);
  Delta_v_data = idx->data;
  loop_ub = p_prior->size[0];
  for (i = 0; i < loop_ub; i++) {
    Delta_v_data[i] = p_prior_data[i];
  }
  emxInit_int32_T(&iidx, 1);
  sort(idx, iidx);
  Delta_v_data = idx->data;
  emxInit_int8_T(&selected);
  i = selected->size[0];
  selected->size[0] = iidx->size[0];
  emxEnsureCapacity_int8_T(selected, i);
  selected_data = selected->data;
  loop_ub = iidx->size[0];
  for (i = 0; i < loop_ub; i++) {
    selected_data[i] = 0;
  }
  /*  vector of sectors that have been selected */
  sumP = 0.0;
  xpageoffset = 0;
  exitg1 = false;
  while ((!exitg1) && (xpageoffset <= iidx->size[0] - 1)) {
    /*  scan all probability values */
    sumP += Delta_v_data[xpageoffset];
    /*  add the probability value to the overall set */
    if (sumP < 1.0 - delta) {
      /*  if the condition has been reached */
      selected_data[xpageoffset] = 1;
      /*  mark this sector as selcted */
      xpageoffset++;
    } else {
      exitg1 = true;
    }
  }
  hi = selected->size[0] - 1;
  xpageoffset = 0;
  for (b_i = 0; b_i <= hi; b_i++) {
    if (selected_data[b_i] > 0) {
      xpageoffset++;
    }
  }
  emxInit_int32_T(&r, 1);
  i = r->size[0];
  r->size[0] = xpageoffset;
  emxEnsureCapacity_int32_T(r, i);
  hull_data = r->data;
  xpageoffset = 0;
  for (b_i = 0; b_i <= hi; b_i++) {
    if (selected_data[b_i] > 0) {
      hull_data[xpageoffset] = b_i;
      xpageoffset++;
    }
  }
  emxFree_int8_T(&selected);
  /*  return the index of sectors that have been selected */
  emxInit_real_T(&K_prime, 2);
  i = K_prime->size[0] * K_prime->size[1];
  K_prime->size[0] = r->size[0];
  K_prime->size[1] = 3;
  emxEnsureCapacity_real_T(K_prime, i);
  K_prime_data = K_prime->data;

  /*  check if the true location is in Delta_x */
  emxInit_boolean_T(&b_Locations);
  i = b_Locations->size[0] * b_Locations->size[1];
  b_Locations->size[0] = r->size[0];
  b_Locations->size[1] = 3;
  emxEnsureCapacity_boolean_T(b_Locations, i);
  Locations_data = b_Locations->data;
  loop_ub = r->size[0];
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      sumP = Locations[hull_data[i1] + 27 * i];
      K_prime_data[i1 + K_prime->size[0] * i] = sumP;
      Locations_data[i1 + b_Locations->size[0] * i] = (sumP == x[i]);
    }
  }

  eml_find(b_Locations, iidx);
  emxFree_boolean_T(&b_Locations);
  if (iidx->size[0] == 0) {
    double b_x[81];
    double y[81];
    /*  if it does not */
    /* create a surrogate */
    for (i = 0; i < 3; i++) {
      for (i1 = 0; i1 < 27; i1++) {
        xpageoffset = i1 + 27 * i;
        b_x[xpageoffset] = x[i] - Locations[xpageoffset];
      }
    }
    for (loop_ub = 0; loop_ub < 81; loop_ub++) {
      y[loop_ub] = fabs(b_x[loop_ub]);
    }
    for (hi = 0; hi < 3; hi++) {
      xpageoffset = hi * 27;
      sumP = y[xpageoffset];
      for (loop_ub = 0; loop_ub < 26; loop_ub++) {
        sumP += y[(xpageoffset + loop_ub) + 1];
      }
      matSums[hi] = sumP;
    }
    b_minimum(matSums, &xpageoffset);
    x[0] = Locations[xpageoffset - 1];
    x[1] = Locations[xpageoffset + 26];
    x[2] = Locations[xpageoffset + 53];
  }

  emxFree_int32_T(&iidx);
  if (r->size[0] == 0) {
    emxInit_real_T(&b_K_prime, 2);
    convhulln(K_prime, b_K_prime);
    emxFree_real_T(&b_K_prime);
  }

  /* ----------------------------------------------------------------------------------------------------------
                                     Start of the planarIsotropic method
     ----------------------------------------------------------------------------------------------------------
  */
  /*  apply planar isotropic mechanism */
  emxInit_real_T(&b_idx, 2);
  convhulln(K_prime, b_idx);
  
  idx_data = b_idx->data;
  xpageoffset = b_idx->size[0] * 3;
  i = K_prime->size[0] * K_prime->size[1];
  K_prime->size[0] = xpageoffset;
  K_prime->size[1] = 3;
  emxEnsureCapacity_real_T(K_prime, i);
  K_prime_data = K_prime->data;
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < xpageoffset; i1++) {
      K_prime_data[i1 + K_prime->size[0] * i] =
          Locations[hull_data[(int)idx_data[i1] - 1] + 27 * i];
    }
  }

  emxFree_int32_T(&r);
  /*  compute Delta_v */
  emxInit_real_T(&Delta_v, 2);
  Delta_v_data = Delta_v->data;
  Delta_v->size[0] = 0;
  Delta_v->size[1] = 3;
  xpageoffset = b_idx->size[0] * 3;
  if (xpageoffset < 3) {
    xpageoffset = 3;
  }
  if (b_idx->size[0] * 3 == 0) {
    xpageoffset = 0;
  }
  for (b_i = 0; b_i < xpageoffset; b_i++) {
    /* for j = [1:i-1,i+1:length(K_prime)] */
    for (lastBlockLength = 0; lastBlockLength < xpageoffset;
         lastBlockLength++) {
      if ((unsigned int)lastBlockLength != (unsigned int)b_i) {
        /*  check if third dimension is below zero, if it is cut it */
        res_part[2] = K_prime_data[b_i + K_prime->size[0] * 2] -
                      K_prime_data[lastBlockLength + K_prime->size[0] * 2];
        if (!(res_part[2] < 0.0)) {
          loop_ub = Delta_v->size[0];
          i = b_idx->size[0] * b_idx->size[1];
          b_idx->size[0] = Delta_v->size[0] + 1;
          b_idx->size[1] = 3;
          emxEnsureCapacity_real_T(b_idx, i);
          idx_data = b_idx->data;
          for (i = 0; i < 3; i++) {
            for (i1 = 0; i1 < loop_ub; i1++) {
              idx_data[i1 + b_idx->size[0] * i] =
                  Delta_v_data[i1 + Delta_v->size[0] * i];
            }
          }
          idx_data[Delta_v->size[0]] =
              K_prime_data[b_i] - K_prime_data[lastBlockLength];
          idx_data[Delta_v->size[0] + b_idx->size[0]] =
              K_prime_data[b_i + K_prime->size[0]] -
              K_prime_data[lastBlockLength + K_prime->size[0]];
          idx_data[Delta_v->size[0] + b_idx->size[0] * 2] = res_part[2];
          i = Delta_v->size[0] * Delta_v->size[1];
          Delta_v->size[0] = b_idx->size[0];
          Delta_v->size[1] = 3;
          emxEnsureCapacity_real_T(Delta_v, i);
          Delta_v_data = Delta_v->data;
          loop_ub = b_idx->size[0] * 3;
          for (i = 0; i < loop_ub; i++) {
            Delta_v_data[i] = idx_data[i];
          }
        }
      }
    }
  }  

  /*  compute conv hull of delta_v */
  convhulln(Delta_v, K_prime);
  K_prime_data = K_prime->data;
  xpageoffset = K_prime->size[0] * 3;
  i = b_idx->size[0] * b_idx->size[1];
  b_idx->size[0] = xpageoffset;
  b_idx->size[1] = 3;
  emxEnsureCapacity_real_T(b_idx, i);
  idx_data = b_idx->data;
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < xpageoffset; i1++) {
      idx_data[i1 + b_idx->size[0] * i] =
          Delta_v_data[((int)K_prime_data[i1] + Delta_v->size[0] * i) - 1];
    }
  }

  emxFree_real_T(&Delta_v);
  /*  select a value ell and increase it if T is not stable */
  /* take y values uniformly at random from K */
  /* y_index = unidrnd(size(K,1),1,ell);% TODO */
  loop_ub_tmp = K_prime->size[0] * 3;
  i = idx->size[0];
  idx->size[0] = loop_ub_tmp;
  emxEnsureCapacity_real_T(idx, i);
  Delta_v_data = idx->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    Delta_v_data[i] = idx_data[i];
  }
  emxInit_real_T(&c_idx, 1);
  i = c_idx->size[0];
  c_idx->size[0] = loop_ub_tmp;
  emxEnsureCapacity_real_T(c_idx, i);
  K_prime_data = c_idx->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    K_prime_data[i] = idx_data[i];
  }
  emxInit_real_T(&d_idx, 1);
  i = d_idx->size[0];
  d_idx->size[0] = loop_ub_tmp;
  emxEnsureCapacity_real_T(d_idx, i);
  b_idx_data = d_idx->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    b_idx_data[i] = idx_data[i];
  }
  emxInit_real_T(&e_idx, 1);
  i = e_idx->size[0];
  e_idx->size[0] = loop_ub_tmp;
  emxEnsureCapacity_real_T(e_idx, i);
  c_idx_data = e_idx->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    c_idx_data[i] = idx_data[i + b_idx->size[0]];
  }
  emxInit_real_T(&f_idx, 1);
  i = f_idx->size[0];
  f_idx->size[0] = loop_ub_tmp;
  emxEnsureCapacity_real_T(f_idx, i);
  d_idx_data = f_idx->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    d_idx_data[i] = idx_data[i + b_idx->size[0]];
  }
  emxInit_real_T(&g_idx, 1);
  i = g_idx->size[0];
  g_idx->size[0] = loop_ub_tmp;
  emxEnsureCapacity_real_T(g_idx, i);
  e_idx_data = g_idx->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    e_idx_data[i] = idx_data[i + b_idx->size[0]];
  }
  emxInit_real_T(&h_idx, 1);
  i = h_idx->size[0];
  h_idx->size[0] = loop_ub_tmp;
  emxEnsureCapacity_real_T(h_idx, i);
  f_idx_data = h_idx->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    f_idx_data[i] = idx_data[i + b_idx->size[0] * 2];
  }
  emxInit_real_T(&i_idx, 1);
  i = i_idx->size[0];
  i_idx->size[0] = loop_ub_tmp;
  emxEnsureCapacity_real_T(i_idx, i);
  g_idx_data = i_idx->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    g_idx_data[i] = idx_data[i + b_idx->size[0] * 2];
  }
  emxInit_real_T(&j_idx, 1);
  i = j_idx->size[0];
  j_idx->size[0] = loop_ub_tmp;
  emxEnsureCapacity_real_T(j_idx, i);
  h_idx_data = j_idx->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    h_idx_data[i] = idx_data[i + b_idx->size[0] * 2];
  }
  // *rand_num_generated = *rand_num_generated + 3;
  sumP = b_rand();
  b_r = b_rand();
  T_re_tmp = b_rand();
  res_part[0] = c_minimum(idx) + (b_maximum(c_idx) - c_minimum(d_idx)) * sumP;
  res_part[1] = c_minimum(e_idx) + (b_maximum(f_idx) - c_minimum(g_idx)) * b_r;
  res_part[2] =
      c_minimum(h_idx) + (b_maximum(i_idx) - c_minimum(j_idx)) * T_re_tmp;
      
  /*  compute T */
  /* disp(T) */
  /* disp(size(T)) */
  for (i = 0; i < 3; i++) {
    b_res_part[3 * i].re = res_part[0] * res_part[i];
    b_res_part[3 * i].im = 0.0;
    i1 = 3 * i + 1;
    b_res_part[i1].re = res_part[1] * res_part[i];
    b_res_part[i1].im = 0.0;
    i1 = 3 * i + 2;
    b_res_part[i1].re = res_part[2] * res_part[i];
    b_res_part[i1].im = 0.0;
  }

  // This line should result in T = T^(-1/2)
  // It looks like T has no impact in the eventual results, so let's ignore this for now
  mpower(b_res_part, T);

  /* disp(T) */
  /* disp(size(T)) */
  /* disp("------------") */
  /*  check stability of T */
  /* nVals = zeros(3*size(K,1),1); */
  emxInit_real_T(&new_y_vals, 2);
  i = new_y_vals->size[0] * new_y_vals->size[1];
  new_y_vals->size[0] = 3;
  i1 = 3 * (K_prime->size[0] * 3);
  new_y_vals->size[1] = i1;
  emxEnsureCapacity_real_T(new_y_vals, i);
  new_y_vals_data = new_y_vals->data;
  loop_ub = 3 * i1;
  for (i = 0; i < loop_ub; i++) {
    new_y_vals_data[i] = 0.0;
  }
  new_y_vals_data[0] = res_part[0];
  new_y_vals_data[1] = res_part[1];
  new_y_vals_data[2] = res_part[2];
  /* disp(new_y_vals); */
  sumP = 3.0 * (double)(K_prime->size[0] * 3);
  xpageoffset = 0;
  exitg1 = false;
  int iterations = 0;
  while ((!exitg1) && (xpageoffset <= (int)(sumP - 1.0) - 1)) {
    iterations++;
    /* y_index = unidrnd(size(K,1),1,ell); */
    i = idx->size[0];
    idx->size[0] = loop_ub_tmp;
    emxEnsureCapacity_real_T(idx, i);
    Delta_v_data = idx->data;
    i = c_idx->size[0];
    c_idx->size[0] = K_prime->size[0] * 3;
    emxEnsureCapacity_real_T(c_idx, i);
    K_prime_data = c_idx->data;
    i = d_idx->size[0];
    d_idx->size[0] = K_prime->size[0] * 3;
    emxEnsureCapacity_real_T(d_idx, i);
    b_idx_data = d_idx->data;
    i = e_idx->size[0];
    e_idx->size[0] = K_prime->size[0] * 3;
    emxEnsureCapacity_real_T(e_idx, i);
    c_idx_data = e_idx->data;
    i = f_idx->size[0];
    f_idx->size[0] = K_prime->size[0] * 3;
    emxEnsureCapacity_real_T(f_idx, i);
    d_idx_data = f_idx->data;
    i = g_idx->size[0];
    g_idx->size[0] = K_prime->size[0] * 3;
    emxEnsureCapacity_real_T(g_idx, i);
    e_idx_data = g_idx->data;
    i = h_idx->size[0];
    h_idx->size[0] = K_prime->size[0] * 3;
    emxEnsureCapacity_real_T(h_idx, i);
    f_idx_data = h_idx->data;
    i = i_idx->size[0];
    i_idx->size[0] = K_prime->size[0] * 3;
    emxEnsureCapacity_real_T(i_idx, i);
    g_idx_data = i_idx->data;
    i = j_idx->size[0];
    j_idx->size[0] = K_prime->size[0] * 3;
    emxEnsureCapacity_real_T(j_idx, i);
    h_idx_data = j_idx->data;
    for (i = 0; i < loop_ub_tmp; i++) {
      b_r = idx_data[i];
      Delta_v_data[i] = b_r;
      K_prime_data[i] = b_r;
      b_idx_data[i] = b_r;
      b_r = idx_data[i + b_idx->size[0]];
      c_idx_data[i] = b_r;
      d_idx_data[i] = b_r;
      e_idx_data[i] = b_r;
      b_r = idx_data[i + b_idx->size[0] * 2];
      f_idx_data[i] = b_r;
      g_idx_data[i] = b_r;
      h_idx_data[i] = b_r;
    }
    // *rand_num_generated = *rand_num_generated + 3;
    b_r = b_rand();
    T_re_tmp = b_rand();
    e_T_re_tmp = b_rand();
    // printf("Random values 773: %f, %f, %f\n", b_r, T_re_tmp, e_T_re_tmp);
    i = 3 * (xpageoffset + 1);
    new_y_vals_data[i] =
        c_minimum(idx) + (b_maximum(c_idx) - c_minimum(d_idx)) * b_r;
    new_y_vals_data[i + 1] =
        c_minimum(e_idx) + (b_maximum(f_idx) - c_minimum(g_idx)) * T_re_tmp;
    new_y_vals_data[i + 2] =
        c_minimum(h_idx) + (b_maximum(i_idx) - c_minimum(j_idx)) * e_T_re_tmp;
    /* old_y_vals = y_vals; */
    /* y_vals = zeros(3,size(old_y_vals,2)+1); */
    /* for i = 1:size(old_y_vals,1) */
    /*     for j = 1:size(old_y_vals,2) */
    /*         y_vals(i,j) = old_y_vals(i,j); */
    /*     end */
    /* end */
    /* y_vals(:,size(y_vals,2)) = newToCon; */
    /* y_vals = [y_vals,newToCon]; */
    memset(&T_new[0], 0, 9U * sizeof(double));
    /*  compute T */
    i = xpageoffset + 1;
    b_r = 1.0 / ((double)xpageoffset + 2.0);
    for (lastBlockLength = 0; lastBlockLength <= i; lastBlockLength++) {
      for (i1 = 0; i1 < 3; i1++) {
        hi = i1 + 3 * lastBlockLength;
        T_new[3 * i1] +=
            b_r * new_y_vals_data[3 * lastBlockLength] * new_y_vals_data[hi];
        nblocks = 3 * i1 + 1;
        T_new[nblocks] += b_r * new_y_vals_data[3 * lastBlockLength + 1] *
                          new_y_vals_data[hi];
        nblocks = 3 * i1 + 2;
        T_new[nblocks] += b_r * new_y_vals_data[3 * lastBlockLength + 2] *
                          new_y_vals_data[hi];
      }
    }
    for (i = 0; i < 9; i++) {
      b_res_part[i].re = T_new[i];
      b_res_part[i].im = 0.0;
    }
    mpower(b_res_part, b_T_new);
    for (i = 0; i < 9; i++) {
      b_res_part[i].re = T[i].re - b_T_new[i].re;
      b_res_part[i].im = T[i].im - b_T_new[i].im;
    }
    if (b_norm(b_res_part) <= 0.01) {
      exitg1 = true;
    } else {
      /* nVals(ell,1) = norm(T-T_new,2); */
      memcpy(&T[0], &b_T_new[0], 9U * sizeof(creal_T));
      xpageoffset++;
    }
  }

  emxFree_real_T(&j_idx);
  emxFree_real_T(&i_idx);
  emxFree_real_T(&h_idx);
  emxFree_real_T(&g_idx);
  emxFree_real_T(&f_idx);
  emxFree_real_T(&e_idx);
  emxFree_real_T(&d_idx);
  emxFree_real_T(&c_idx);
  /*  compute K_I */
  emxInit_creal_T(&k_idx);
  i = k_idx->size[0] * k_idx->size[1];
  k_idx->size[0] = 3;
  k_idx->size[1] = b_idx->size[0];
  emxEnsureCapacity_creal_T(k_idx, i);
  i_idx_data = k_idx->data;
  loop_ub = b_idx->size[0];
  for (i = 0; i < loop_ub; i++) {
    i_idx_data[3 * i].re = idx_data[i];
    i_idx_data[3 * i].im = 0.0;
    i1 = 3 * i + 1;
    i_idx_data[i1].re = idx_data[i + b_idx->size[0]];
    i_idx_data[i1].im = 0.0;
    i1 = 3 * i + 2;
    i_idx_data[i1].re = idx_data[i + b_idx->size[0] * 2];
    i_idx_data[i1].im = 0.0;
  }
  emxInit_creal_T(&K_I);
  i = K_I->size[0] * K_I->size[1];
  K_I->size[0] = 3;
  K_I->size[1] = k_idx->size[1];
  emxEnsureCapacity_creal_T(K_I, i);
  K_I_data = K_I->data;
  loop_ub = k_idx->size[1];
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_T_re_tmp = T[i].re;
      c_T_re_tmp = i_idx_data[3 * i1].im;
      d_T_re_tmp = T[i].im;
      f_T_re_tmp = i_idx_data[3 * i1].re;
      g_T_re_tmp = T[i + 3].re;
      xpageoffset = 3 * i1 + 1;
      h_T_re_tmp = i_idx_data[xpageoffset].im;
      sumP = T[i + 3].im;
      T_re_tmp = i_idx_data[xpageoffset].re;
      e_T_re_tmp = T[i + 6].re;
      xpageoffset = 3 * i1 + 2;
      i_T_re_tmp = i_idx_data[xpageoffset].im;
      j_T_re_tmp = T[i + 6].im;
      b_r = i_idx_data[xpageoffset].re;
      xpageoffset = i + 3 * i1;
      K_I_data[xpageoffset].re =
          ((b_T_re_tmp * f_T_re_tmp - d_T_re_tmp * c_T_re_tmp) +
           (g_T_re_tmp * T_re_tmp - sumP * h_T_re_tmp)) +
          (e_T_re_tmp * b_r - j_T_re_tmp * i_T_re_tmp);
      K_I_data[xpageoffset].im =
          ((b_T_re_tmp * c_T_re_tmp + d_T_re_tmp * f_T_re_tmp) +
           (g_T_re_tmp * h_T_re_tmp + sumP * T_re_tmp)) +
          (e_T_re_tmp * i_T_re_tmp + j_T_re_tmp * b_r);
    }
  }

  emxFree_creal_T(&k_idx);
  /*  uniformly sample a value from K_I */
  /*  TODO */
  // *rand_num_generated = *rand_num_generated + 3;
  sumP = b_rand();
  T_re_tmp = b_rand();
  e_T_re_tmp = b_rand();
  /* z = [min(K_I(1,:)) + (max(K_I(1,:))+min(K_I(1,:)))*0.5;... */
  /*     min(K_I(2,:)) + (max(K_I(2,:))+min(K_I(2,:)))*0.5;... */
  /*     min(K_I(3,:)) + (max(K_I(3,:))+min(K_I(3,:)))*0.5]; */
  /*  draw a value from a Gamma distribution */
  b_r = gamrnd(1.0 / epsilon);
  /* r = gamrnd(3,5); */
  /*  TODO */
  /* r = 13.6289; */
  /*  adjust z */
  /* z = r.*z; */
  /*  release z according to */
  emxInit_creal_T(&c_x);
  i = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 1;
  c_x->size[1] = K_I->size[1];
  emxEnsureCapacity_creal_T(c_x, i);
  i_idx_data = c_x->data;
  loop_ub = K_I->size[1];
  for (i = 0; i < loop_ub; i++) {
    i_idx_data[i] = K_I_data[3 * i];
  }
  xpageoffset = K_I->size[1];
  ex = K_I_data[0];
  for (loop_ub = 2; loop_ub <= xpageoffset; loop_ub++) {
    d_x = i_idx_data[loop_ub - 1];
    if (rtIsNaN(d_x.re) || rtIsNaN(i_idx_data[loop_ub - 1].im)) {
      p = false;
    } else if (rtIsNaN(ex.re) || rtIsNaN(ex.im)) {
      p = true;
    } else {
      i_T_re_tmp = absRelopProxies(ex, d_x, &j_T_re_tmp);
      p = (i_T_re_tmp < j_T_re_tmp);
    }
    if (p) {
      ex = d_x;
    }
  }
  i = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 1;
  c_x->size[1] = K_I->size[1];
  emxEnsureCapacity_creal_T(c_x, i);
  i_idx_data = c_x->data;
  loop_ub = K_I->size[1];
  for (i = 0; i < loop_ub; i++) {
    i_idx_data[i] = K_I_data[3 * i + 1];
  }
  xpageoffset = K_I->size[1];
  b_ex = K_I_data[1];
  for (loop_ub = 2; loop_ub <= xpageoffset; loop_ub++) {
    d_x = i_idx_data[loop_ub - 1];
    if (rtIsNaN(d_x.re) || rtIsNaN(i_idx_data[loop_ub - 1].im)) {
      p = false;
    } else if (rtIsNaN(b_ex.re) || rtIsNaN(b_ex.im)) {
      p = true;
    } else {
      i_T_re_tmp = absRelopProxies(b_ex, d_x, &j_T_re_tmp);
      p = (i_T_re_tmp < j_T_re_tmp);
    }
    if (p) {
      b_ex = d_x;
    }
  }
  i = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 1;
  c_x->size[1] = K_I->size[1];
  emxEnsureCapacity_creal_T(c_x, i);
  i_idx_data = c_x->data;
  loop_ub = K_I->size[1];
  for (i = 0; i < loop_ub; i++) {
    i_idx_data[i] = K_I_data[3 * i + 2];
  }
  xpageoffset = K_I->size[1];
  c_ex = K_I_data[2];
  for (loop_ub = 2; loop_ub <= xpageoffset; loop_ub++) {
    d_x = i_idx_data[loop_ub - 1];
    if (rtIsNaN(d_x.re) || rtIsNaN(i_idx_data[loop_ub - 1].im)) {
      p = false;
    } else if (rtIsNaN(c_ex.re) || rtIsNaN(c_ex.im)) {
      p = true;
    } else {
      i_T_re_tmp = absRelopProxies(c_ex, d_x, &j_T_re_tmp);
      p = (i_T_re_tmp < j_T_re_tmp);
    }
    if (p) {
      c_ex = d_x;
    }
  }
  b_mpower(T, b_T_new);
  i = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 1;
  c_x->size[1] = K_I->size[1];
  emxEnsureCapacity_creal_T(c_x, i);
  i_idx_data = c_x->data;
  loop_ub = K_I->size[1];
  emxInit_creal_T(&b_K_I);
  i = b_K_I->size[0] * b_K_I->size[1];
  b_K_I->size[0] = 1;
  b_K_I->size[1] = K_I->size[1];
  emxEnsureCapacity_creal_T(b_K_I, i);
  b_K_I_data = b_K_I->data;
  emxInit_creal_T(&c_K_I);
  i = c_K_I->size[0] * c_K_I->size[1];
  c_K_I->size[0] = 1;
  c_K_I->size[1] = K_I->size[1];
  emxEnsureCapacity_creal_T(c_K_I, i);
  c_K_I_data = c_K_I->data;
  emxInit_creal_T(&d_K_I);
  i = d_K_I->size[0] * d_K_I->size[1];
  d_K_I->size[0] = 1;
  d_K_I->size[1] = K_I->size[1];
  emxEnsureCapacity_creal_T(d_K_I, i);
  d_K_I_data = d_K_I->data;
  emxInit_creal_T(&e_K_I);
  i = e_K_I->size[0] * e_K_I->size[1];
  e_K_I->size[0] = 1;
  e_K_I->size[1] = K_I->size[1];
  emxEnsureCapacity_creal_T(e_K_I, i);
  e_K_I_data = e_K_I->data;
  emxInit_creal_T(&f_K_I);
  i = f_K_I->size[0] * f_K_I->size[1];
  f_K_I->size[0] = 1;
  f_K_I->size[1] = K_I->size[1];
  emxEnsureCapacity_creal_T(f_K_I, i);
  f_K_I_data = f_K_I->data;
  for (i = 0; i < loop_ub; i++) {
    i_idx_data[i] = K_I_data[3 * i];
    b_K_I_data[i] = K_I_data[3 * i];
    i1 = 3 * i + 1;
    c_K_I_data[i] = K_I_data[i1];
    d_K_I_data[i] = K_I_data[i1];
    i1 = 3 * i + 2;
    e_K_I_data[i] = K_I_data[i1];
    f_K_I_data[i] = K_I_data[i1];
  }
  creal_T dc;
  // d_minimum does not take the minimum value, it takes the smallest absolute...
  // Code below has all the d_minimum changed to real_min
  // The same problem with d_minimum was also there when computing the maximum
  // Also added the max functions here because they also did not get computed correctly
  d_x = real_min(c_x);
  emxFree_creal_T(&c_x);
  ex = real_max(b_K_I);
  dc = real_min(b_K_I);
  emxFree_creal_T(&b_K_I);
  c_Locations[0].re = d_x.re + (ex.re + dc.re) * sumP;
  c_Locations[0].im = d_x.im + (ex.im + dc.im) * sumP;
  d_x = real_min(c_K_I);
  emxFree_creal_T(&c_K_I);
  b_ex = real_max(d_K_I);
  dc = real_min(d_K_I);
  emxFree_creal_T(&d_K_I);
  c_Locations[1].re = d_x.re + (b_ex.re + dc.re) * T_re_tmp;
  c_Locations[1].im = d_x.im + (b_ex.im + dc.im) * T_re_tmp;
  d_x = real_min(e_K_I);
  emxFree_creal_T(&e_K_I);
  c_ex = real_max(f_K_I);
  dc = real_min(f_K_I);
  emxFree_creal_T(&f_K_I);
  c_Locations[2].re = d_x.re + (c_ex.re + dc.re) * e_T_re_tmp;
  c_Locations[2].im = d_x.im + (c_ex.im + dc.im) * e_T_re_tmp;

  /* compute new prior distribition */
  i = b_idx->size[0] * b_idx->size[1];
  b_idx->size[0] = K_I->size[1];
  b_idx->size[1] = 3;
  emxEnsureCapacity_real_T(b_idx, i);
  idx_data = b_idx->data;
  loop_ub = K_I->size[1];
  for (i = 0; i < 3; i++) {
    e_T_re_tmp = b_r * b_T_new[i].re;
    i_T_re_tmp = b_r * b_T_new[i].im;
    sumP = e_T_re_tmp * c_Locations[0].re - i_T_re_tmp * c_Locations[0].im;
    T_re_tmp = e_T_re_tmp * c_Locations[0].im + i_T_re_tmp * c_Locations[0].re;
    e_T_re_tmp = b_r * b_T_new[i + 3].re;
    i_T_re_tmp = b_r * b_T_new[i + 3].im;
    sumP += e_T_re_tmp * c_Locations[1].re - i_T_re_tmp * c_Locations[1].im;
    T_re_tmp += e_T_re_tmp * c_Locations[1].im + i_T_re_tmp * c_Locations[1].re;
    e_T_re_tmp = b_r * b_T_new[i + 6].re;
    i_T_re_tmp = b_r * b_T_new[i + 6].im;
    sumP += e_T_re_tmp * c_Locations[2].re - i_T_re_tmp * c_Locations[2].im;
    T_re_tmp += e_T_re_tmp * c_Locations[2].im + i_T_re_tmp * c_Locations[2].re;
    z[i].re = x[i] + sumP;
    z[i].im = T_re_tmp;
    for (i1 = 0; i1 < loop_ub; i1++) {
      idx_data[i1 + b_idx->size[0] * i] = K_I_data[i + 3 * i1].re;
    }
  }

  emxFree_creal_T(&K_I);
  mergeDuplicatePoints(b_idx, K_prime, idx);
  K_prime_data = K_prime->data;
  emxFree_real_T(&b_idx);
  qhullOptions_data[0] = 'Q';
  qhullOptions_data[1] = 't';
  qhullOptions_data[2] = '\x00';
  i = new_y_vals->size[0] * new_y_vals->size[1];
  new_y_vals->size[0] = 3;
  new_y_vals->size[1] = K_prime->size[0];
  emxEnsureCapacity_real_T(new_y_vals, i);
  new_y_vals_data = new_y_vals->data;
  loop_ub = K_prime->size[0];
  for (i = 0; i < loop_ub; i++) {
    new_y_vals_data[3 * i] = K_prime_data[i];
    new_y_vals_data[3 * i + 1] = K_prime_data[i + K_prime->size[0]];
    new_y_vals_data[3 * i + 2] = K_prime_data[i + K_prime->size[0] * 2];
  }
  xpageoffset = computeConvexhulln(&new_y_vals_data[0], 3, K_prime->size[0],
                                   &qhullOptions_data[0]);
  emxFree_real_T(&new_y_vals);
  emxFree_real_T(&K_prime);
  if (xpageoffset > 0) {
    char errMsg[4096];
    getQhullErrorStr(&errMsg[0]);
  }
  xpageoffset = getNumConvhullTrias();
  emxInit_int32_T(&hull, 2);
  i = hull->size[0] * hull->size[1];
  hull->size[0] = xpageoffset;
  hull->size[1] = 3;
  emxEnsureCapacity_int32_T(hull, i);
  hull_data = hull->data;
  produceConvexhull(&hull_data[0], xpageoffset, 3, &i_T_re_tmp);
  emxFree_int32_T(&hull);
  freeQhullMemory();
  sumP = z[0].re;
  b_r = z[0].im;
  T_re_tmp = z[1].re;
  e_T_re_tmp = z[1].im;
  j_T_re_tmp = z[2].re;
  d = z[2].im;
  for (b_i = 0; b_i < 27; b_i++) {
    creal_T b_T[3];
    double d1;
    double d2;
    double d3;
    double d4;
    double d5;
    double d6;
    for (i = 0; i < 3; i++) {
      c_Locations[i].re = Locations[b_i + 27 * i];
      c_Locations[i].im = 0.0;
      b_T_re_tmp = T[i].re;
      c_T_re_tmp = T[i].im;
      d_T_re_tmp = T[i + 3].re;
      f_T_re_tmp = T[i + 3].im;
      g_T_re_tmp = T[i + 6].re;
      h_T_re_tmp = T[i + 6].im;
      b_T[i].re = ((b_T_re_tmp * sumP - c_T_re_tmp * b_r) +
                   (d_T_re_tmp * T_re_tmp - f_T_re_tmp * e_T_re_tmp)) +
                  (g_T_re_tmp * j_T_re_tmp - h_T_re_tmp * d);
      b_T[i].im = ((b_T_re_tmp * b_r + c_T_re_tmp * sumP) +
                   (d_T_re_tmp * e_T_re_tmp + f_T_re_tmp * T_re_tmp)) +
                  (g_T_re_tmp * d + h_T_re_tmp * j_T_re_tmp);
    }
    d1 = c_Locations[0].re;
    d2 = c_Locations[0].im;
    d3 = c_Locations[1].re;
    d4 = c_Locations[1].im;
    d5 = c_Locations[2].re;
    d6 = c_Locations[2].im;
    for (i = 0; i < 3; i++) {
      b_T_re_tmp = T[i].re;
      c_T_re_tmp = T[i].im;
      d_T_re_tmp = T[i + 3].re;
      f_T_re_tmp = T[i + 3].im;
      g_T_re_tmp = T[i + 6].re;
      h_T_re_tmp = T[i + 6].im;
      b_T[i].re -= ((b_T_re_tmp * d1 - c_T_re_tmp * d2) +
                    (d_T_re_tmp * d3 - f_T_re_tmp * d4)) +
                   (g_T_re_tmp * d5 - h_T_re_tmp * d6);
      b_T[i].im -= ((b_T_re_tmp * d2 + c_T_re_tmp * d1) +
                    (d_T_re_tmp * d4 + f_T_re_tmp * d3)) +
                   (g_T_re_tmp * d6 + h_T_re_tmp * d5);
    }
    d1 = epsilon * epsilon / (2.0 * i_T_re_tmp) *
         exp(-epsilon * c_norm(b_T, i_T_re_tmp));
    p_z_u[b_i] = d1;
    if (d1 == 0.0) {
      printf("%s\n", "MException: MyComponent:noSuchVariable Zero Probability");
      fflush(stdout);
      printf("%s\n", "Restart the script, this should no longer continue");
      fflush(stdout);
      /* ME = MException('MyComponent:noSuchVariable', ... */
      /*     'Zero probability',str); */
      /* throw(ME) */
    }
  }
  /*  update p_pos */
  for (b_i = 0; b_i < 27; b_i++) {
    if (b_i < 1) {
      loop_ub_tmp = 0;
    } else {
      loop_ub_tmp = b_i;
    }
    if (b_i + 2 > 27) {
      i = 0;
      i1 = 0;
    } else {
      i = b_i + 1;
      i1 = 27;
    }
    if (b_i + 2 > p_prior->size[0]) {
      xpageoffset = 0;
      hi = 0;
    } else {
      xpageoffset = b_i + 1;
      hi = p_prior->size[0];
    }
    nblocks = (loop_ub_tmp + i1) - i;
    lastBlockLength = (loop_ub_tmp + hi) - xpageoffset;
    if (nblocks == lastBlockLength) {
      if (loop_ub_tmp - 1 >= 0) {
        memcpy(&p_z_u_data[0], &p_z_u[0],
               (unsigned int)loop_ub_tmp * sizeof(double));
      }
      loop_ub = i1 - i;
      for (i1 = 0; i1 < loop_ub; i1++) {
        p_z_u_data[i1 + loop_ub_tmp] = p_z_u[i + i1];
      }
      i = idx->size[0];
      idx->size[0] = lastBlockLength;
      emxEnsureCapacity_real_T(idx, i);
      Delta_v_data = idx->data;
      for (i = 0; i < loop_ub_tmp; i++) {
        Delta_v_data[i] = p_prior_data[i];
      }
      loop_ub = hi - xpageoffset;
      for (i = 0; i < loop_ub; i++) {
        Delta_v_data[i + loop_ub_tmp] = p_prior_data[xpageoffset + i];
      }
      i = idx->size[0];
      idx->size[0] = nblocks;
      emxEnsureCapacity_real_T(idx, i);
      Delta_v_data = idx->data;
      for (i = 0; i < nblocks; i++) {
        Delta_v_data[i] *= p_z_u_data[i];
      }
    } else {
      binary_expand_op(idx, p_z_u, loop_ub_tmp - 1, i - 1, i1 - 1, p_prior,
                       loop_ub_tmp - 1, xpageoffset - 1, hi - 1);
      Delta_v_data = idx->data;
    }
    if (idx->size[0] == 0) {
      j_T_re_tmp = 0.0;
    } else {
      if (idx->size[0] <= 1024) {
        xpageoffset = idx->size[0];
        lastBlockLength = 0;
        nblocks = 1;
      } else {
        xpageoffset = 1024;
        nblocks = (int)((unsigned int)idx->size[0] >> 10);
        lastBlockLength = idx->size[0] - (nblocks << 10);
        if (lastBlockLength > 0) {
          nblocks++;
        } else {
          lastBlockLength = 1024;
        }
      }
      j_T_re_tmp = Delta_v_data[0];
      for (loop_ub = 2; loop_ub <= xpageoffset; loop_ub++) {
        j_T_re_tmp += Delta_v_data[loop_ub - 1];
      }
      for (loop_ub_tmp = 2; loop_ub_tmp <= nblocks; loop_ub_tmp++) {
        xpageoffset = (loop_ub_tmp - 1) << 10;
        sumP = Delta_v_data[xpageoffset];
        if (loop_ub_tmp == nblocks) {
          hi = lastBlockLength;
        } else {
          hi = 1024;
        }
        for (loop_ub = 2; loop_ub <= hi; loop_ub++) {
          sumP += Delta_v_data[(xpageoffset + loop_ub) - 1];
        }
        j_T_re_tmp += sumP;
      }
    }
    p_pos_res_data[b_i] = p_z_u[b_i] * p_prior_data[b_i] / j_T_re_tmp;
  }
  emxFree_real_T(&idx);
  emxFree_real_T(&p_prior);
  if (z[0].im == 0.0) {
    sumP = z[0].re / scaling_fac_x;
    T_re_tmp = 0.0;
  } else if (z[0].re == 0.0) {
    sumP = 0.0;
    T_re_tmp = z[0].im / scaling_fac_x;
  } else {
    sumP = z[0].re / scaling_fac_x;
    T_re_tmp = z[0].im / scaling_fac_x;
  }
  z[0].re = sumP;
  z[0].im = T_re_tmp;
  if (z[1].im == 0.0) {
    sumP = z[1].re / scaling_fac_y;
    T_re_tmp = 0.0;
  } else if (z[1].re == 0.0) {
    sumP = 0.0;
    T_re_tmp = z[1].im / scaling_fac_y;
  } else {
    sumP = z[1].re / scaling_fac_y;
    T_re_tmp = z[1].im / scaling_fac_y;
  }
  z[1].re = sumP;
  z[1].im = T_re_tmp;
}

/* End of code generation (correlatedRelease.c) */

creal_T real_min(const emxArray_creal_T *x)
{
  const creal_T *x_data;
  creal_T min;
  int size;
  x_data = x->data;
  min = x_data[0];
  size = x->size[1];
  for (int i = 0; i < size; i++) { 
    if (x_data[i].re < min.re) {
      min = x_data[i];
    }
  }
  return min;
}

creal_T real_max(const emxArray_creal_T *x)
{
  const creal_T *x_data;
  creal_T max;
  int size;
  x_data = x->data;
  max = x_data[0];
  size = x->size[1];
  for (int i = 0; i < size; i++) { 
    if (x_data[i].re > max.re) {
      max = x_data[i];
    }
  }
  return max;
}
