#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>
#define MAX_ARRAY_LIMIT 40
#define PASSWORD_ARRAY_LIMIT 16
#define MAX_LIMIT 1024

void FirstOperation();
void SignUp();
void fillerText();
void check_status();
int changeIsAccount(int *ptr);
int changeZeroToOne(int *ptr);


void main(){
    printf("\n ################### Welcome To Our Bank ################### \n\n");
    int IsAccount =0;
    int *pforIsAccount = &IsAccount;
    int scanfOne=0;
    int scanfTwo=0;

    char ary[MAX_LIMIT];
    char readAry[MAX_LIMIT];

    //file pointer for name
    FILE *nameFile;

    //file pointer for password
    FILE *passwordFile;

    FILE *moneyFile;


    //int IsLogin =0;

    //money stuff
    int account_money=0;
    int deposit_amount=0;
    int withdraw_amount = 0;

    // for while loop Varaiables
    int first = 1;
    int second = 1;

    //variable for signup account
    char SignUpNameArray[MAX_ARRAY_LIMIT];
    char SignUpPasswordArray[PASSWORD_ARRAY_LIMIT];

    //get name and password from file
    char NameArrayForFile[MAX_ARRAY_LIMIT];
    char PasswordArrayForFile[PASSWORD_ARRAY_LIMIT];

    //variable for login
    char LoginNameArray[MAX_ARRAY_LIMIT];
    char LoginPasswordArray[PASSWORD_ARRAY_LIMIT];


    while(first){
        FirstOperation();
        fillerText();
        scanf("%d",&scanfOne);

        //option One
        if(scanfOne == 1){
            if(IsAccount == 0){
                printf("\nYou Don't Have An Account Yet!  Please Create An Account Or LogIn\n\n");
                continue;
            }if(IsAccount == 1){
                while(second){
                    check_status();
                    fillerText();
                    scanf("%d",&scanfTwo);
                    if(scanfTwo == 1){
                        moneyFile = fopen("money.txt","r+");
                        fscanf(moneyFile , "%d" , &account_money);
                        printf("\nName:%s\n",LoginNameArray);
                        printf("Password:%s\n",LoginPasswordArray);
                        printf("Balance:%d\n",account_money);


                    }
                    if(scanfTwo == 2){

                        printf("\n How Much Do You Want To Deposit :");
                        scanf("%d",&deposit_amount);
                        account_money = account_money + deposit_amount;
                        printf("Your Balance : %d\n",account_money);
                    }
                    if(scanfTwo == 3){

                        printf("\n How Much Do You Want To Withdraw :");
                        scanf("%d",&withdraw_amount);
                        if(withdraw_amount <= account_money){
                                printf("You Have Withdraw %d ...\n" , withdraw_amount);
                            account_money = account_money - withdraw_amount;
                        }else{
                            printf("You Cant Withdraw More Than You Have...\n");
                        }
                        printf("Your Balance : %d\n",account_money);
                    }
                    if(scanfTwo == 4){
                        moneyFile = fopen("money.txt" ,"w");
                        fprintf(moneyFile, "%d" , account_money);

                        fclose(moneyFile);
                        break;
                    }
                }
            }
        }
        //option Two
        if(scanfOne == 2){
            moneyFile = fopen("money.txt","w");
            nameFile= fopen("username.txt","w");
            passwordFile = fopen("password.txt","w");

            printf("\nEnter Your Name(no space / 40 characters maximum):");

            scanf("%s",&SignUpNameArray);
            fputs(SignUpNameArray , nameFile);
            printf("Enter Your Password(no space / 16 characters maximum):");

            scanf("%s" , &SignUpPasswordArray);
            fputs(SignUpPasswordArray , passwordFile);
            fputs(account_money , moneyFile);
            //printf("%s" , SignUpNameArray);
            //printf("%s" , SignUpPasswordArray);
            printf("\nSignUp Successfull ! Plese Go Back to Main Page And Login To Access To Your Account\n");

            fclose(nameFile);
            fclose(passwordFile);

        }
        //option Three
        if(scanfOne == 3){
            nameFile= fopen("username.txt","r");
            passwordFile = fopen("password.txt","r");

            if(nameFile == NULL && passwordFile == NULL){
                printf("\nYou dont Have An Account Yet!Pls Sign Up First\n");
                continue;
            }

            printf("\nEnter Your Name(no space / 40 characters maximum):");
            scanf("%s", &LoginNameArray);
            fgets(NameArrayForFile, MAX_ARRAY_LIMIT,nameFile);


            printf("Enter Your Name(no space / 16 characters maximum):");
            scanf("%s", &LoginPasswordArray);
            fgets(PasswordArrayForFile, PASSWORD_ARRAY_LIMIT,passwordFile);


            if(strcmp(LoginNameArray ,  NameArrayForFile) == 0 && strcmp(LoginPasswordArray , PasswordArrayForFile) == 0 ){
                printf("\nLogin Successfully\n");
                changeIsAccount(&IsAccount);
            }else{
                printf("\error password are not match\n");
            }
            fclose(nameFile);
            fclose(passwordFile);
        }
        //option Four
        if(scanfOne == 4){
            exit(0);
        }
    }

}



void FirstOperation(){
    printf("\nEnter 1 to Check Your Account\n");
    printf("Enter 2 to Create Bank Account\n");
    printf("Enter 3 to Login Your Bank Account\n");
    printf("Enter 4 to Exit\n");

}

void fillerText(){
    printf("\nChoose An Option :");
}

void check_status(){
    printf("\n######## Welcome From Your Account Info ########\n");
    printf("Enter 1 to Check Name , Password And Balance\n");
    printf("Enter 2 to Deposit Money\n");
    printf("Enter 3 to Withdraw Money\n");
    printf("Enter 4 to Back to Main Page\n");
}
int changeIsAccount(int *ptr){
    *ptr = 1;
    return 0;
}

int changeZeroToOne(int *ptr){
    *ptr = 0;
    return 0;
}









