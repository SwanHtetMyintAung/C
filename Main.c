#include<stdio.h>
#include <stdlib.h>
#include"Encrypt.h"
#include "Decrypt.h"

int size_of_array(char *text){
    int size=0;
    while(text[size]!=0){
        size++;
    }
    return size;
}

void main(){
    char *plainText ="swan60953@gmail.com I am the STORM that is approaching provoking \nhello";
    int length = size_of_array(plainText);
    char *keyText = "SecretKey";

    char *enResult = (char*)malloc(sizeof(char)*length);
    enResult = Encrypt(plainText,keyText,length);
    printf("encrypted: %s\n",enResult);

    char *deResult = (char*)malloc(sizeof(char)*length);
    deResult = Decrypt(enResult,keyText,length);
    printf("Plain Text: %s\n",deResult);

}