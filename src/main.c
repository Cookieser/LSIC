#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>


#include "../include/paillier.h"


           
 
 /*
 
 LSIC:Lightweight Secure Integer Comparison
 
 */
 
int test(mpz_t ctest,paillier_private_key priv){
	    mpz_t test;
	    mpz_init(test);

	    paillier_decrypt(test,ctest,&priv);

	    gmp_printf ("The result of this comparison:%Zd \n",test);
	    printf("\n");

	    mpz_clear(test);

	    return 0;

}
 

int binarybit(mpz_t r,mpz_t val,int n){
	    mpz_t q, d;
	    mpz_init(q);
        mpz_init(r);
        mpz_init(d);
        mpz_set_si(d, 2);

	    for(int i=0;i<n+1;i++)
        {
		    mpz_fdiv_qr(q,r, val, d);
		    val=q;
        }

        gmp_printf ("The %d-bit of this value is %Zd\n",n,r);

        mpz_clear(q);
        mpz_clear(d);
        return 0;

}  
 

int main(int argc, char *argv[]) {

	//generate keys
	    int len=2048;
	    paillier_public_key pub;
	    paillier_private_key priv;

	    paillier_public_init(&pub);
	    paillier_private_init(&priv);
	    paillier_keygen(&pub, &priv, len);
	

	//1-6

	    int l=atoi(argv[3]);
	    long int inputa=atoi(argv[1]);
	    long int inputb=atoi(argv[2]);
	
	    mpz_t a,b,a0,b0,cb0,ct,t,zero,czero,one,cone,negativeone,ctau,ai,bi,cbi,tb,ctb;

	    mpz_init(a);
	    mpz_init(b);
	    mpz_init(a0);
	    mpz_init(b0);
	    mpz_init(cb0);
	    mpz_init(t);
	    mpz_init(ct);
	    mpz_init(ctb);
	    mpz_init(cbi);
	    mpz_init(ctau);
	    mpz_init(zero);
	    mpz_init(czero);
	    mpz_init(one);
	    mpz_init(cone);
	    mpz_init(negativeone);
	    mpz_init(ai);
	    mpz_init(bi);
	    mpz_init(tb);

	    mpz_set_si(a, inputa);
	    mpz_set_si(b, inputb);
	    mpz_set_si(zero, 0);
	    mpz_set_si(one, 1);
	    mpz_set_si(negativeone, -1);
	
	    printf("B:");
    	binarybit(b0,b,0);
   	    paillier_encrypt(cb0,b0,&pub);
    	paillier_encrypt(czero,zero,&pub);
    	paillier_encrypt(cone,one,&pub);
   
     	printf("A:");
    	binarybit(a0,a,0);
   	
      	if(mpz_cmp_si(a0,0)) mpz_set(ct,czero);
     	else mpz_set(ct,cb0);
   	

    	paillier_decrypt(t,ct,&priv);
	
     	gmp_printf ("Finish the comparison between the least significant bits, we can get the result t = %Zd \n",t);
    	printf("\n");



	    //7-13
	    srand((unsigned)time(NULL));
	    for(int i=1;i<l;i++)
        {

	        int c=rand()%2;
	        if(!c) mpz_set(ctau,ct);
	        else{
                    paillier_homomorphic_multc(ctau,ct,negativeone,&pub);
		            paillier_homomorphic_add(ctau,ctau,cone,&pub);
		        }

	
	
	        //15-24
	        printf("B:");
	        binarybit(bi,b,i);

	        if(mpz_cmp_si(bi,0)) mpz_set(ctb,ctau);
	        else mpz_set(ctb,czero);

	        paillier_encrypt(cbi,bi,&pub);
	        if(c==1)
	        {
	            paillier_homomorphic_multc(ctb,ctb,negativeone,&pub);
	            paillier_homomorphic_add(ctb,ctb,cbi,&pub);
	
	         }
	
	
	
	        //25-30
	        printf("A:");
	        binarybit(ai,a,i);
	        if(mpz_cmp_si(ai,0)) mpz_set(ct,ctb);
	        else
	            {
		            paillier_homomorphic_multc(ctb,ctb,negativeone,&pub);
		            paillier_homomorphic_add(ctb,ctb,cbi,&pub);
		            paillier_homomorphic_add(ct,ctb,ct,&pub);
	            }
	
            test(ct,priv);
	    }
	
	    paillier_decrypt(t,ct,&priv);
	
	    if(mpz_cmp_si(t,0)) printf("The answer is A<B\n");
	    else printf("The answer is A>=B\n");
	
	
	    printf("-------------------------------------------------\n");

	    gmp_printf ("Proof:The inputA=%Zd, inputB=%Zd\n",a,b);
	

	
	

	
	
	    mpz_clear(a);
	    mpz_clear(b);
	    mpz_clear(a0);
	    mpz_clear(b0);
	    mpz_clear(cb0);
	    mpz_clear(ct);
	    mpz_clear(zero);
	    mpz_clear(czero);
	    mpz_clear(one);
	    mpz_clear(cone);
	    mpz_clear(negativeone);
	    mpz_clear(ctau);
	    mpz_clear(ai);
	    mpz_clear(bi);
	    mpz_clear(tb);
	    mpz_clear(ctb);
	    mpz_clear(cbi);
	    mpz_clear(t);
	
	
	
	    return 0;
}
