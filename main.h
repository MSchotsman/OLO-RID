/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.h
 *
 * Code generation for function 'main'
 *
 */

#ifndef MAIN_H
#define MAIN_H

/* Include files */
// Change the curve below and in ./main.c if neccessary
#include "./include/MiraclCore/ecdh_NIST521.h"
#include "./include/MiraclCore/core.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAXCHAR 1000

// #define FILE_PATH "./include/Traces/scenario_1_1.csv"
// #define FILE_LEN 7979
// #define FILE_PATH "./include/Traces/scenario_1_2.csv"
// #define FILE_LEN 8371
// #define FILE_PATH "./include/Traces/scenario_1_3.csv"
// #define FILE_LEN 4729
#define FILE_PATH "./include/Traces/scenario_1_4.csv"
#define FILE_LEN 5652
// #define FILE_PATH "./include/Traces/scenario_2_1.csv"
// #define FILE_LEN 11200
// #define FILE_PATH "./include/Traces/scenario_2_2.csv"
// #define FILE_LEN 12919

/* Structure declarations */

union flbyte {
    float a;
    unsigned char bytes[4];
  };

typedef struct { 
  union flbyte longitude;
  union flbyte latitude;
  union flbyte altitude;
} location;

typedef struct {
  char w[2 * EGS_NIST521 + 1];
  octet W;
} pke_W;

typedef struct {
  char s[EGS_NIST521];
  octet S;
} pke_S;

typedef struct {
  char v[2 * EFS_NIST521 + 1];
  octet V;
  char c[6 * EFS_NIST521 + 1];
  octet C;
  char t[32];
  octet T;
} cipher;

/*
  id, 4 byte for the unique id
  gcs, location of the ground control station
  obf_loc, obfuscated uav location
  time, time stamp in 4 bytes representing the epoch time
  em_status, emergency status in bytes
  cipher_out, the cipher components for the real uav location
*/
typedef struct {
  char id[4];
  location gcs;
  location obf_loc;
  unsigned char time[4];
  unsigned char em_status;
  cipher cipher_out;
} remote;

/* Function Declarations */
extern int main(int argc, char **argv);

extern void main_correlatedRelease(location uav_loc, location *obf_loc, double *Locations_orig, double *p_pos);

extern void encrypt_loc(cipher *cipher_out, pke_W TTP, location uav_loc, pke_S TTP_S);

extern void setup_uav_loc(location *loc, int i, double* trace_locations);

extern void setup_cs_loc(location *loc);

extern unsigned char get_em_status(void);

extern void get_ttp(pke_W *TTP, pke_S *TTP_S);

extern void init_p_pos(double *p_pos);

extern double* read_csv(double *csv);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (main.h) */
