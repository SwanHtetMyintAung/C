#include "stdio.h"

void printNecessary();
int add(int a , int b );
int minus(int a , int b );
int multiply(int a , int b );
int divide(int a , int b );



int main(){
    int first_number =0;
    int second_number=0;
    int operation = 0; // 1-> + , 2-> - , 3-> * , 4-> /

    //warning
    printf("This Program will be able to operate only 2 integers . "
           "and the result will be only integer . no float / irrational numbers \n");

    printf("Input First Number :");
    scanf("%d",&first_number);
    printf("Input Second Number :");
    scanf("%d",&second_number);

    printNecessary();
    scanf("%d",&operation);

    printf("The Answer Is : ");


    if(operation == 1){
        //add
        printf("%d", add(first_number,second_number));
    }else if(operation == 2){
        //subtract
        printf("%d", minus(first_number,second_number));
    } else if (operation == 3){
        //multiply
        printf("%d", multiply(first_number,second_number));
    }else if(operation == 4){
        //divide
        printf("%d", divide(first_number,second_number));
    }




    return 0;
}

void printNecessary(){
    printf("\nInput 1 To Add \n");
    printf("Input 2 To Subtract \n");
    printf("Input 3 To Multiply \n");
    printf("Input 4 To Divide \n");
    printf("Choose An Operation : ");
}
int add(int a , int b ){
    return a+b;
}
int minus(int a , int b ){
    return a-b;
}
int multiply(int a , int b ){
    return a*b;
}
int divide(int a , int b ){
    return a/b;
}