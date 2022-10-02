# LISC-Lightweight Secure Integer Comparison

## Introduction

This is the implementation of the scheme in ["COMPARING ENCRYPTED DATA"](https://www.researchgate.net/profile/Thijs-Veugen/publication/266527434_COMPARING_ENCRYPTED_DATA/links/554086390cf2736761c27c36/COMPARING-ENCRYPTED-DATA.pdf) by the Paillier cryptosystem.

We can use this software to finish the secure integer comparison according to the schematic design.

## How to use

```
make
cd build/

# ./LSIC A B length
# We should input A and B, and the max bit-length of them  
./LSIC 200 34 8
```

## For example

![image-20221002221905499](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20221002221905499.png)

![image-20221002222000383](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20221002222000383.png)

![image-20221002222037409](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20221002222037409.png)