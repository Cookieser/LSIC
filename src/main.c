#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "lsic.h"


#include "../include/paillier.h"


           
int main(){

	const int K=1000000;
	double inputx;
	long int inputy;
	double inputtau;
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
	
	printf("The tax department inputs x(A decimal of five significant digits): ");
	
	scanf("%lf",&inputx);
	
	printf("State Grid Corporation inputs integer y: ");
	
	scanf("%ld",&inputy);
	
	printf("State Grid Corporation inputs integer tau(A decimal of five significant digits): ");
	
	scanf("%lf",&inputtau);
	
	
	inputx = inputx*K;
	
	inputtau= inputtau*K;
	
	mpz_set_si(x, (int)inputx);
	
	//gmp_printf ("x*100000:%Zd\n",x);
	
	mpz_set_si(y, inputy);
	
	mpz_set_si(tau, (int)inputtau);
	
	//gmp_printf ("tau*1000000:%Zd\n",tau); 
	
	//generate keys
	int len=2048;
	paillier_public_key pub;
	paillier_private_key priv;

	paillier_public_init(&pub);
	paillier_private_init(&priv);
	paillier_keygen(&pub, &priv, len);
	    
	    
	paillier_encrypt(cx,x,&pub);
	    
	    
	paillier_homomorphic_multc(cd,cx,y,&pub);
	    
	paillier_decrypt(d,cd,&priv);
	//gmp_printf ("x*y*1000000:%Zd\n",d);
	    
	srand((unsigned)time(NULL));
	    
	int c=rand()%100000;
	    
       //printf("c:%d\n",c);
	    
	mpz_set_si(r, c);
	    
	paillier_encrypt(cr,r,&pub);
	    
	paillier_homomorphic_add(cd,cd,cr,&pub);
		
		
	paillier_decrypt(d,cd,&priv);
	//gmp_printf ("x*y*1000000+r:%Zd\n",d); 
	    
	mpz_add(tau,tau,r);
	
	//gmp_printf ("tau*1000000+r:%Zd\n",tau); 
	printf("\n");   
	    
	LSIC(d,tau,l);
	    
	    

 	mpz_clear(x);
        mpz_clear(y);
	mpz_clear(cx);
	mpz_clear(d);
	mpz_clear(cd);
	mpz_clear(r);
	mpz_clear(cr);
	mpz_clear(tau);
	    
	    
        return 0;



}
