#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "lsic.h"


#include "../include/paillier.h"






char* gen_public_key(paillier_private_key *priv,paillier_public_key *pub){
	mpz_t res;
	mpz_init(res);

	
	paillier_public_init(pub);
	paillier_private_init(priv);
	paillier_keygen(pub, priv, 2048);
	mpz_set(res,pub->n);


	//gmp_printf ("%Zd\n",res);
	char *str=NULL;	
	str=mpz_get_str(str,10,res);
	
	return str;
	
}


char* encryptX(mpz_t cx,mpz_t x,paillier_public_key *pub){

	paillier_encrypt(cx,x,pub);
	char *str=NULL;
	str=mpz_get_str(str,10,cx);
	return str;
}

char* encryptCompute(mpz_t cd,mpz_t cr,paillier_public_key *pub){

	paillier_homomorphic_add(cd,cd,cr,pub);
	char *str=NULL;
	str=mpz_get_str(str,10,cd);
	return str;
}


           
int main(int argc,char *argv[]){
	

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
	
	paillier_private_key priv;
        paillier_public_key pub;	 
	gen_public_key(&priv,&pub);
	
	
	
	encryptX(cx,x,&pub);
	  
	    
	paillier_homomorphic_multc(cd,cx,y,&pub);
	    
	paillier_decrypt(d,cd,&priv);
	//gmp_printf ("x*y*1000000:%Zd\n",d);
	    
	srand((unsigned)time(NULL));
	    
	int c=rand()%100000;
	    
	    
	mpz_set_si(r, c);
	    
	paillier_encrypt(cr,r,&pub);
	    
	//paillier_homomorphic_add(cd,cd,cr,&pub);
		
	encryptCompute(cd,cr,&pub);
	paillier_decrypt(d,cd,&priv);
	
	//gmp_printf ("x*y*1000000+r:%Zd\n",d); 
	    
	mpz_add(tau,tau,r);
	
	//gmp_printf ("tau*1000000+r:%Zd\n",tau); 
	//printf("\n");   
	    
	int res=LSIC(d,tau,l);
	//printf("%d\n",res);
	    

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
