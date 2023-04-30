# LISC-Lightweight Secure Integer Comparison

## Introduction

This is the implementation of the scheme in ["COMPARING ENCRYPTED DATA"](https://www.researchgate.net/profile/Thijs-Veugen/publication/266527434_COMPARING_ENCRYPTED_DATA/links/554086390cf2736761c27c36/COMPARING-ENCRYPTED-DATA.pdf) by the Paillier cryptosystem.

We can use this software to finish the secure integer comparison according to the schematic design.

Then, we  implement the application which is a real scenario about the Electric-tax index.

## How to use

```
make
cd build/
./Implementation 
```

## Function

**main**

```
./Implementation x y tau
return bool(x*y>=tau bool=0)(x*y<tau bool=1)
x:valueA(The ratio of corporate taxes to total industry taxes,and it's usually a decimal number)
y:valueB(Ratio of total industrial electricity to enterprise electricity consumption)
tau:The comparison threshold that we set

./Implementation 0.0023 2001 46
This means the comparison between 0.0023*20001 and 46
```

## For example

![image-20230420211215370](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20230420211215370.png)

![image-20230420211234714](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20230420211234714.png)

### LSIC

Now this had been merged in the main program in `lsic.c` and `lsic.h`

![image-20221002221905499](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20221002221905499.png)

![image-20221002222000383](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20221002222000383.png)

![image-20221002222037409](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20221002222037409.png)

![image-20230429221603016](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20230429221603016.png)

