

#ifndef LSIC_H_
#define LSIC_H_


#include <stdio.h>
#include <gmp.h>
#include "../include/paillier.h"








#ifdef PAILLIER_DEBUG
/** Print debug message
 *
 * @ingroup Tools
 */
#define DEBUG_MSG(str) fputs(str, stderr)
#else
#define DEBUG_MSG(str)
#endif
int test(mpz_t ctest,paillier_private_key priv);
int binarybit(mpz_t r,mpz_t val,int n);
int LSIC(mpz_t a,mpz_t b, int l);

void printByte(unsigned char *str ,int byte_len);
void transfer(char *hex_string);
unsigned char* trans(const char* hex_string);
unsigned char* get_public_key();
unsigned char* get_encryptX();
unsigned char* get_encryptCompute();
int get_result();
void set(char *dst, unsigned char *src);


#endif 
