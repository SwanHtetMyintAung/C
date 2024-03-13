#ifndef DECRYPT_H
#define DECRYPT_H
#include <stdio.h>
#include <stdlib.h>

char *Decrypt(char* encryptedText,char* keyText,int length){
    char *plainText = (char*)calloc(length+2,sizeof(char));
    int i=0;//while loop couter
    //work until there's a null
    while(encryptedText[i] != '\0'){
        //need at subtract 13 because we added 13 AFTER the XOR and before saving into the variable
        char currentChar = encryptedText[i]-13;
        for(int j=0;j<length;j++){
            currentChar ^= keyText[j];
        }
        //minus 3 because in encryption , we forward 3 before the XOR from the plainText
        plainText[length-i-1] = currentChar-3;
        i++;
    }
    return plainText;
}

#endif