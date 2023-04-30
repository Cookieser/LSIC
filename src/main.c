#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "lsic.h"


#include "../include/paillier.h"
#define MAX_BYTE_LEN 2048


paillier_public_key pub;
paillier_private_key priv;
char* cx_str=NULL;
char* cd_str=NULL;
int res;


void printByte(unsigned char *str ,int byte_len){
	printf("Byte array: ");
    for (int i = 0; i < byte_len; i++) {
        printf("%x ", str[i]);
    }
    printf("\n");

}
void transfer(char *hex_string){
    //char hex_string[] = "48656C6C6F20576F726C647"; // 十六进制字符串
    int len = strlen(hex_string);
    int byte_len = (len + 1) / 2;
    unsigned char byte_array[byte_len];
    int i;

    
    for (i = 0; i < len; i += 2) {
        if (i == len - 1) {
            sscanf(hex_string + i, "%1hhx", &byte_array[i / 2]);
        } else {
            sscanf(hex_string + i, "%2hhx", &byte_array[i / 2]);
        }
    }

   
    printf("Byte array: ");
    for (i = 0; i < byte_len; i++) {
        printf("%x ", byte_array[i]);
    }
    printf("\n");



}

unsigned char* trans(const char* hex_string)
{
    static unsigned char byte_array[MAX_BYTE_LEN];
    int len = strlen(hex_string);
    int i;
    for (i = 0; i < len; i += 2) {
        if (i == len - 1) {
            sscanf(hex_string + i, "%1hhx", &byte_array[i / 2]);
        } else {
            sscanf(hex_string + i, "%2hhx", &byte_array[i / 2]);
        }
    }

    return byte_array;
}







unsigned char* get_public_key(){
	char *str=NULL;
	unsigned char* byte_array=NULL;
	mpz_t res;
	mpz_init(res);
	paillier_public_key *pub1=&pub;
	mpz_set(res,pub1->n);	
	str=mpz_get_str(str,16,res);
	printf("%s\n",str);
	int len = strlen(str);
	byte_array=trans(str);
	int byte_len=(len + 1) / 2;
	printByte(byte_array,byte_len);
	
	
	mpz_clear(res);
	return byte_array;
	
}
unsigned char* get_encryptX(){
	unsigned char* byte_array=NULL;
	byte_array=trans(cx_str);
	printf("%s\n",cx_str);
	int len = strlen(cx_str);
	
	
	int byte_len=(len + 1) / 2;
	printByte(byte_array,byte_len);
	return byte_array;
	
}

unsigned char* get_encryptCompute(){
	unsigned char* byte_array=NULL;
	byte_array=trans(cd_str);
	printf("%s\n",cd_str);
	int len = strlen(cd_str);
	
	
	int byte_len=(len + 1) / 2;
	printByte(byte_array,byte_len);
	return byte_array;
	
}

int get_result(){
        printf("The result is %d\n",res);
	return res;
}

void set(char *dst, unsigned char *src) {

    size_t dst_len = strlen(dst);
    size_t src_len = strlen((char*)src);

    for (size_t i = 0; i < src_len; i++) {
        dst[dst_len + i] = (char)src[i];
    }

    dst[dst_len + src_len] = '\0';
}


        
int main(int argc,char *argv[]){
	
	
	const int K = 1000000;
	double inputx = atof(argv[1]);
	long int inputy = atof(argv[2]);
	double inputtau = atof(argv[3]);
	int l = 40;
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
	
	//gmp_printf ("x*100000:%Zd\n",x);
	
	mpz_set_si(y, inputy);
	
	mpz_set_si(tau, (int)inputtau);
	
	//gmp_printf ("tau*1000000:%Zd\n",tau); 
	
	//generate keys
	int len=2048;
	

	paillier_public_init(&pub);
	paillier_private_init(&priv);
	paillier_keygen(&pub, &priv, len);
	get_public_key();
	

	
	   
	paillier_encrypt(cx,x,&pub);
	
	cx_str = mpz_get_str(cx_str,16,cx);
	
	
	get_encryptX();
	
	paillier_homomorphic_multc(cd,cx,y,&pub);
	
	    
	paillier_decrypt(d,cd,&priv);
	//gmp_printf ("x*y*1000000:%Zd\n",d);
	    
	srand((unsigned)time(NULL));
	    
	int c=rand()%100000;
	    
       //printf("c:%d\n",c);
	    
	mpz_set_si(r, c);
	    
	paillier_encrypt(cr,r,&pub);
	    
	paillier_homomorphic_add(cd,cd,cr,&pub);
	
	cd_str=mpz_get_str(cd_str,16,cd);
	get_encryptCompute();	
		
	paillier_decrypt(d,cd,&priv);
	//gmp_printf ("x*y*1000000+r:%Zd\n",d); 
	    
	mpz_add(tau,tau,r);
	
	//gmp_printf ("tau*1000000+r:%Zd\n",tau); 
	printf("\n");   
	    
	res=LSIC(d,tau,l);
	    
	get_result();

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
