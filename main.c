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

/* Include files */
#include "main.h"
#include "./include/PIM/correlatedRelease.h"
#include "./include/PIM/correlatedRelease_data.h"
#include "./include/PIM/correlatedRelease_initialize.h"
#include "./include/PIM/correlatedRelease_emxAPI.h"
#include "./include/PIM/correlatedRelease_terminate.h"
#include "./include/MiraclCore/core.h"
#include "./include/MiraclCore/ecdh_NIST521.h"
#include "./include/MiraclCore/randapi.h"
#include "./include/PIM/rand.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include<stdbool.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  clock_t begin;
  clock_t end;

  location uav_loc;
  pke_S TTP_S;
  pke_W TTP;
  time_t time_mark;
  remote message;
  message.id[0] =  0x79;
  message.id[1] =  0x7a;
  message.id[2] =  0x61;
  message.id[3] =  0x62;
  setup_cs_loc(&message.gcs);
  get_ttp(&TTP, &TTP_S);

  double p_pos[27];
  init_p_pos(p_pos);

  double Locations_orig[81];

  double trace_locations[FILE_LEN*3];
  read_csv(trace_locations);

  int steps = FILE_LEN;
  int debug = 0;

  if (!isInitialized_correlatedRelease) {
    correlatedRelease_initialize();
  }
  for (int i = 0; i < steps; i++) {
    setup_uav_loc(&uav_loc, i, trace_locations);
    
    time_mark = time(0);
    
    unsigned char time_hex[8];
    sprintf(time_hex, "%08lx", time_mark);
    for (size_t j=0, k=0; k<4; j+=2, k++){
        message.time[k] = ((time_hex[j] % 32 + 9) % 25 * 16 + (time_hex[j+1] % 32 + 9) % 25);
    }

    message.em_status = get_em_status();
    if (debug) {
      printf("Locations orig\n");
      for (int j = 0; j < 27; j++) {
        for (int k = j; k < 81; k += 27) {
          printf("%f, ", Locations_orig[k]);
        }
        printf("\n");
      }
      printf("P pos\n");
      for (int j = 0; j < 27; j++) {
        printf("%f, ", p_pos[j]);      
      }
      printf("\n");
    }
    main_correlatedRelease(uav_loc, &message.obf_loc, Locations_orig, p_pos, debug);
    
    encrypt_loc(&message.cipher_out, TTP, uav_loc, TTP_S);  
    
    correlatedRelease_terminate();
    printf("%f\t%f\t%f\t%f\n", message.obf_loc.longitude.a, message.obf_loc.latitude.a, message.obf_loc.altitude.a);
  }
  return 0;
}

/**	@brief Obfuscate a 3D location with a Planar Isotropic Mechanism
 *
	@param uav_loc the uav location in longitude, latitude, and altitude
	@param obf_loc pointer to the eventually obfuscated location in longitude, latitude, and altitude
	@param Locations_orig pointer to a location array
  @param p_pos pointer to the probability for each position array
 */
void main_correlatedRelease(location uav_loc, location *obf_loc, double *Locations_orig, double *p_pos, int debug)
{
  // Initialize the standard values
  double epsilon = 0.1;
  double delta = 0.01;
  double number_of_blocks_per_dim = 3.0;
  double M = 1.0/(number_of_blocks_per_dim*number_of_blocks_per_dim*number_of_blocks_per_dim);
  double P_true_all[3] = {uav_loc.longitude.a, uav_loc.latitude.a, uav_loc.altitude.a};
  double drone_speed = 0.3;
  double shift_lat_long = 0.000003;
  double old_locations_data[81];
  int old_locations_size[2] = {2,2};
  emxArray_real_T *p_pos_res;
  creal_T z[3];

  emxInitArray_real_T(&p_pos_res, 1);
  correlatedRelease(epsilon, delta, M, p_pos, P_true_all, drone_speed,
                    shift_lat_long, old_locations_data, old_locations_size,
                    number_of_blocks_per_dim, p_pos_res, z, Locations_orig, debug);
  for (int i =0 ; i < 27; i++) {
    p_pos[i] = p_pos_res->data[i];
  }
  emxDestroyArray_real_T(p_pos_res);
  obf_loc->longitude.a = z[0].re;
  obf_loc->latitude.a = z[1].re;
  obf_loc->altitude.a = z[2].re;
}

// The TTP secret should later be removed, for now it is there for testing purposes
void encrypt_loc(cipher *cipher_out, pke_W TTP, location uav_loc, pke_S TTP_S) {
  // Hashtype
  int h = HASH_TYPE_NIST521;
  // Encoding parameters
  char p1[3] = {0x0, 0x1, 0x2};
  octet P1 = {3, sizeof(p1), p1};
  char p2[4] = {0x0, 0x1, 0x2, 0x3};
  octet P2 = {4, sizeof(p2), p2};
  // Create rng
  csprng R;
  char raw[100];
  octet RAW = {100, sizeof(raw), raw};
  CREATE_CSPRNG(&R,  &RAW);
  // Plaintext to be encoded
  char m[30];
  sprintf(m, "%f;%f;%f", uav_loc.longitude.a, uav_loc.latitude.a, uav_loc.altitude.a);
  octet M = {30, sizeof(m), m};
  // Length of the HMAC tag
  int len = 12;
  // Component of the output ciphertext
  cipher_out->V.len = 0;
  cipher_out->V.max = sizeof(cipher_out->v);
  cipher_out->V.val = cipher_out->v;
  // The output ciphertext
  cipher_out->C.len = 0;
  cipher_out->C.max = sizeof(cipher_out->c);
  cipher_out->C.val = cipher_out->c;
  // The output HMAC tag, part of the ciphertext
  cipher_out->T.len = 0;
  cipher_out->T.max = sizeof(cipher_out->t);
  cipher_out->T.val = cipher_out->t;
  ECP_NIST521_ECIES_ENCRYPT(h, &P1, &P2, &R, &TTP.W, &M, len, &cipher_out->V, &cipher_out->C, &cipher_out->T);
  // Test whether the program correctly encrypts/decrypts, should later be removed.
  char new_m[30];
  octet NEW_M = {30, sizeof(new_m), new_m};
  int out = ECP_NIST521_ECIES_DECRYPT(h, &P1, &P2, &cipher_out->V, &cipher_out->C, &cipher_out->T, &TTP_S.S, &NEW_M);
  // printf("M the output plaintext message\n");
  // printf("%s\n", NEW_M.val);
}

// Should have a call to the gps
void setup_uav_loc(location *loc, int i, double* trace_locations) {
  loc->longitude.a = trace_locations[i*3];
  loc->latitude.a = trace_locations[i*3+1];
  loc->altitude.a = trace_locations[i*3+2];
}

// This function can just call the uav_loc
void setup_cs_loc(location *loc) {
  loc->longitude.a = 1.0;
  loc->latitude.a = 1.0;
  loc->altitude.a = 1.0;
}

unsigned char get_em_status(void) {
  return 0;
}

void get_ttp(pke_W *TTP, pke_S *TTP_S) {
  // Setup rng
  csprng R;
  char raw[100];
  octet RAW = {100, sizeof(raw), raw};
  CREATE_CSPRNG(&R,  &RAW);
  // Setup the secret and public structures
  TTP_S->S.len = 0;
  TTP_S->S.max = sizeof(TTP_S->s);
  TTP_S->S.val = TTP_S->s;
  TTP->W.len = 0;
  TTP->W.max = sizeof(TTP->w);
  TTP->W.val = TTP->w;
  // Generate Keypair
  ECP_NIST521_KEY_PAIR_GENERATE(&R, &TTP_S->S, &TTP->W);
}

void init_p_pos(double *p_pos) {
  for (int i = 0; i < 27; i++) {
    p_pos[i] = 1.0/27.0;
  }
}


void print_hex(const char *string)
{
        unsigned char *p = (unsigned char *) string;

        for (int i=0; i < strlen(string); ++i) {
                if (! (i % 16) && i)
                        printf("\n");

                printf("%02x ", p[i]);
        }
        printf("\n\n");
}

double* read_csv(double *csv) {
    FILE *fp;
    char row[MAXCHAR];
    char *token;

    fp = fopen(FILE_PATH,"r");

    int index = 0;
    int first_line = 0;
    while (fgets(row, MAXCHAR, fp) != NULL) {
        // Skip first line because it contains headers
        if (first_line == 0) {
          first_line += 1;
          continue;
        }
        token = strtok(row, ",");

        while(token != NULL) {
            csv[index] = atof(token);
            token = strtok(NULL, ",");
            index++;
        }
    }
    return csv;
}

/* End of code generation (main.c) */
