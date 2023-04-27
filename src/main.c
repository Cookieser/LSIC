#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "lsic.h"


#include "../include/paillier.h"



paillier_private_key priv;
paillier_public_key pub;


char* gen_public_key(){
	mpz_t res;
	mpz_init(res);
	paillier_public_init(&pub);
	paillier_private_init(&priv);
	paillier_keygen(&pub, &priv, 2048);
	paillier_public_key *pub1=&pub;
	mpz_set(res,pub1->n);
	//gmp_printf ("%Zd\n",res);
	char *str=NULL;	
	str=mpz_get_str(str,10,res);
	mpz_clear(res);
	return str;
	
}


char* encryptX(char* input){
	mpz_t x,cx;
	mpz_init(x);
	mpz_init(cx);
	mpz_set_str(x,input,10);
	paillier_encrypt(cx,x,&pub);
	char *str=NULL;
	str=mpz_get_str(str,10,cx);
	mpz_clear(x);
	mpz_clear(cx);
	return str;
}

char* encryptCompute(char* inputcd,char* inputcr){
	mpz_t cd,cr;
	mpz_init(cd);
	mpz_init(cr);
	mpz_set_str(cd,inputcd,10);
	mpz_set_str(cr,inputcr,10);
	paillier_homomorphic_add(cd,cd,cr,&pub);
	char *str=NULL;
	str=mpz_get_str(str,10,cd);
	mpz_clear(cd);
	mpz_clear(cr);
	return str;
}


           
int main(int argc,char *argv[]){
	
	char *str=NULL;
	char *str1=NULL;
	const int K=1000000;
	double inputx = atof(argv[1]);
	long int inputy = atoi(argv[2]);
	double inputtau = atof(argv[3]);
	int l=40;
	mpz_t x, y, cx, d, cd, r, cr, tau;
	mpz_init(x);
	mpz_init(y);
	mpz_init(cx);
	mpz_init(d);
	mpz_init(cd);
	mpz_init(r);
	mpz_init(cr);
	mpz_init(tau);
	
	
	inputx = inputx*K;
	
	inputtau= inputtau*K;
	
	mpz_set_si(x, (int)inputx);
	
	
	mpz_set_si(y, inputy);
	
	mpz_set_si(tau, (int)inputtau);
	
	
	//generate keys
	str=gen_public_key();
	//printf("%s\n",str);
	str=mpz_get_str(str,10,x);
	
	
	str=encryptX(str);
	//printf("%s\n",str);
	mpz_set_str(cx,str,10);
	    
	paillier_homomorphic_multc(cd,cx,y,&pub);
	    
	paillier_decrypt(d,cd,&priv);
	//gmp_printf ("x*y*1000000:%Zd\n",d);
	    
	srand((unsigned)time(NULL));
	    
	int c=rand()%100000;
	    
	    
	mpz_set_si(r, c);
	    
	paillier_encrypt(cr,r,&pub);
	    
	//paillier_homomorphic_add(cd,cd,cr,&pub);
	str=mpz_get_str(str,10,cd);
	
	str1=mpz_get_str(str1,10,cr);
		
	str=encryptCompute(str,str1);
	mpz_set_str(cd,str,10);
	paillier_decrypt(d,cd,&priv);
	
	//gmp_printf ("x*y*1000000+r:%Zd\n",d); 
	    
	mpz_add(tau,tau,r);
	
	//gmp_printf ("tau*1000000+r:%Zd\n",tau); 
	//printf("\n");   
	    
	int res=LSIC(d,tau,l);
	printf("%d\n",res);
	    

 	mpz_clear(x);
        mpz_clear(y);
	mpz_clear(cx);
	mpz_clear(d);
	mpz_clear(cd);
	mpz_clear(r);
	mpz_clear(cr);
	mpz_clear(tau);
	    
	    
        return res;



}
