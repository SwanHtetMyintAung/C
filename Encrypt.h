#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *Encrypt(char* plainText,char* keyText,int length){
    char *encryptedText = (char*)calloc(length,sizeof(char));
    int i=0;//while loop couter
    //work until there's a null
    while(plainText[i] != '\0'){
        char currentChar = plainText[i]+3;
        for(int j=0;j<length;j++){
            //operate XOR operation
            currentChar ^= keyText[j];
        }
        //reverse the string  and add 13
        encryptedText[length-i-1] = currentChar +13;    
        i++;
    }
    return encryptedText;
}


#endif