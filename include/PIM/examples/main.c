/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include files */
#include "main.h"
#include "correlatedRelease.h"
#include "correlatedRelease_emxAPI.h"
#include "correlatedRelease_terminate.h"
#include "correlatedRelease_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void argInit_1x3_real_T(double result[3]);

static void argInit_27x1_real_T(double result[27]);

static void argInit_d27xd3_real_T(double result_data[], int result_size[2]);

static double argInit_real_T(void);

/* Function Definitions */
static void argInit_1x3_real_T(double result[3])
{
  int idx1;
  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 3; idx1++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx1] = argInit_real_T();
  }
}

static void argInit_27x1_real_T(double result[27])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 27; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static void argInit_d27xd3_real_T(double result_data[], int result_size[2])
{
  int i;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result_size[0] = 2;
  result_size[1] = 2;
  /* Loop over the array to initialize each element. */
  for (i = 0; i < 4; i++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result_data[i] = argInit_real_T();
  }
}

static double argInit_real_T(void)
{
  return 0.0;
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_correlatedRelease();
  /* Terminate the application.
You do not need to do this more than one time. */
  correlatedRelease_terminate();
  return 0;
}

void main_correlatedRelease(void)
{
  emxArray_real_T *p_pos_res;
  creal_T z[3];
  double Locations_orig[81];
  double old_locations_data[81];
  double dv[27];
  double dv1[3];
  double epsilon_tmp;
  int old_locations_size[2];
  /* Initialize function 'correlatedRelease' input arguments. */
  epsilon_tmp = argInit_real_T();
  /* Initialize function input argument 'p_pos'. */
  /* Initialize function input argument 'x'. */
  /* Initialize function input argument 'old_locations'. */
  argInit_d27xd3_real_T(old_locations_data, old_locations_size);
  /* Call the entry-point 'correlatedRelease'. */
  emxInitArray_real_T(&p_pos_res, 1);
  argInit_27x1_real_T(dv);
  argInit_1x3_real_T(dv1);
  correlatedRelease(epsilon_tmp, epsilon_tmp, epsilon_tmp, dv, dv1, epsilon_tmp,
                    epsilon_tmp, old_locations_data, old_locations_size,
                    epsilon_tmp, p_pos_res, z, Locations_orig);
  emxDestroyArray_real_T(p_pos_res);
}

/* End of code generation (main.c) */
