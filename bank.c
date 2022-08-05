#include<stdio.h>
#include<string.h>


void FirstOperation();
void SignUp();



void main(){
    int IsAccount =0;
    int scanfOne=0;
    char userName[40];


    struct User{
        char Name[40];
        int initialValue;
    };
    struct User userOne;

    int a=1;
    while( a==1){
        //FirstOperation();
        scanf("%d",&scanfOne);
        if(scanfOne == 1){
            if(IsAccount == 0){
                printf("\nYou Don't Have An Account Yet!  Please Create An Account.\n\n");
            }
        }if(scanfOne == 2){


            printf("Enter Your Name(Not More Than 40 Character):");
            scanf("%s", &userName);
            //strcpy(userOne.Name , userName);
            printf("Your Name is %s\n",userName);
        }
    }
}


void FirstOperation(){
    printf("Enter 1 to Check Your Account\n");
    printf("Enter 2 to Create Bank Account\n");
    printf("Enter 3 to Delete Your Bank Account\n");
    printf("Enter 4 to Delete Exit\n");

}

/*void SignUp(){
    char userName[40];
    struct User userOne;
    printf("Enter Your Name(Not More Than 40 Character):");
    scanf("%c",userName);
    strcpy(userOne.Name , userName);


}*/










