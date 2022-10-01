#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>


#include "../include/paillier.h"


           
 
 /*
 
 LSIC
 
 */
 
 
 
int binarybit(mpz_t r,mpz_t val,int n){
	mpz_t q, d;
	mpz_init(q);
        mpz_init(r);
        mpz_init(d);
        mpz_set_si(d, 2);
	for(int i=0;i<n+1;i++){


		mpz_fdiv_qr(q,r, val, d);
		val=q;
				}


       gmp_printf ("%Zd\n",r);


       mpz_clear(q);
       mpz_clear(d);
       return 0;

}  
 

int main() {
	
	
	


	//generate keys
	int len=2048;
	paillier_public_key pub;
	paillier_private_key priv;

	paillier_public_init(&pub);
	paillier_private_init(&priv);
	paillier_keygen(&pub, &priv, len);
	
	
	
	
	
	
	//1-6

 
	//int l=6;
	
	mpz_t a,b,a0,b0,cb0,ct,zero,czero,one,cone;
	mpz_t test;
	mpz_init(test);
	
	mpz_init(a);
	mpz_init(a0);
	mpz_init(zero);
	mpz_init(czero);
	
	mpz_init(one);
	
	mpz_init(b);
	mpz_init(b0);
	mpz_init(cb0);
	mpz_init(ct);
	mpz_set_si(a, 20);
	mpz_set_si(b, 21);
	mpz_set_si(zero, 0);
	mpz_set_si(one, 1);

	
   	binarybit(b0,b,0);
   	paillier_encrypt(cb0,b0,&pub);
   	paillier_encrypt(czero,zero,&pub);
   	paillier_encrypt(cone,one,&pub);
   
   	
   	binarybit(a0,a,0);
   	
   	if(mpz_cmp_si(a0,0)) mpz_set(ct,czero);
   	else mpz_set(ct,cb0);
   	



	//7-19
	 /*
	mpz_t negativeone;
	mpz_init(negativeone);
	mpz_set_si(negativeone, 20);
	
	//mpz_init_set_si(negativeone,-1);
	gmp_printf ("\n here is test:  %Zd\n",negativeone);
	*/
	
	
	
	/*
	int c=rand()%2;
	if(c) mpz_set(ctau,ct);
	else 
	
	{
	
	paillier_homomorphic_multc(ctau,ct,negativeone,&pub);
	paillier_homomorphic_add(ctau,ctau,cone,&pub);
	
	}
	*/
	/*	   	
   	paillier_decrypt(test,ctau,&priv);
	gmp_printf ("\n here is test:  %Zd\n",test);
	
	*/
	

	
	/*
	

	//encrypt
	
	paillier_encrypt(cb,b,&pub);
	
	//add
	paillier_homomorphic_add(cr,ca,cb,&pub);
	paillier_homomorphic_multc(mpz_t ciphertext2, mpz_t ciphertext1, mpz_t constant, paillier_public_key *pub)
	//decrypt
	paillier_decrypt(r,cr,&priv);
	
	
	
	*/
	
	
	return 0;
}
