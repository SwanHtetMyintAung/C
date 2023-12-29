#include "stdio.h"
#include "stdlib.h"
#define STR_LEN 50
#define PAS_LEN 20
#define MAX_USER 7

struct user{
    int id;
    char name[STR_LEN];
    char email[STR_LEN];
    char password[PAS_LEN];
};
struct user database[MAX_USER];

void print_main_menu();
void register_user_data();
void copy_str(char destination[STR_LEN],char target[STR_LEN]);
void login();
int check_str(char destination[STR_LEN],char target[STR_LEN]);
int size_of_array(char array[STR_LEN]);
void login_handler(char email[STR_LEN],char password[PAS_LEN]);
void print_stars(int length);
void dashboard();
int logout();

int g_total_user = 0;
int g_is_login =-1;//default is logout

int main(){


    while(1){
        int option = 0;
        print_main_menu();
        scanf("%d",&option);

        //to register
        if(option == 1){
            if(g_is_login == -1){
                register_user_data();
            }else{
                printf("You already have an account!\n");
            };

        }else if(option == 2){
            if(g_is_login == -1){
                login();
            }else{
                printf("You have already login!\n");
            };
        }else if(option == 3){
            int result = logout();

            if(result ==1){
                printf("You Have Logout Successfully!")
;            }
        }else if(option == 4){
            exit(1);
        }
    }



    return 0;
}

void print_main_menu(){
    printf("****WELCOME TO MY SYSTEM****\n");
    printf("Enter 1 to Register.\n");
    printf("Enter 2 to Login.\n");
    printf("Enter 3 to Logout.\n");
    printf("Enter 4 to Exit.\n");
    printf("Enter an Option:");
}

void register_user_data(){
    char reg_name[STR_LEN];
    char reg_email[STR_LEN];
    char reg_password[PAS_LEN];

    printf("Your Are Now Registering to My System!\n");
    printf("Name:");
    scanf(" %[^\n]" , &reg_name);
    printf("Email:");
    scanf(" %[^\n]" , &reg_email);
    printf("Password:");
    scanf(" %[^\n]" , &reg_password);

    database[g_total_user].id = g_total_user;
    copy_str(database[g_total_user].name , reg_name);
    copy_str(database[g_total_user].email , reg_email);
    copy_str(database[g_total_user].password , reg_password);

    g_total_user++;
}

void copy_str(char destination[STR_LEN],char target[STR_LEN]){

    int i=0;
    for(i=0;i<STR_LEN;i++){
        if(target[i] == "\0"){
            break;
        }else{
            destination[i] = target[i];
        }

    }
}

void login(){
    char l_name[STR_LEN];
    char l_email[STR_LEN];
    char l_password[PAS_LEN];

    printf("Your Are Now Logging In to My System!\n");
    printf("Email:");
    scanf(" %[^\n]" , &l_email);
    printf("Password:");
    scanf(" %[^\n]" , &l_password);

    login_handler(l_email , l_password);
    if(g_is_login != -1){
        printf("Login Successfully! Your Id is : %d\n", g_is_login);
    }
    dashboard();

}

void login_handler(char email[STR_LEN],char password[PAS_LEN]){
    int i=0;
    int check_email =0;
    for(i=0;i<g_total_user;i++){
        int check_email = check_str(database[i].email , email);

        if(check_email == 1){
            int check_password = check_str(database[i].password, password);
            if(check_password == 1){
                g_is_login = database[i].id;
            }
        }
        if(check_email == 0 && i == g_total_user -1){
            printf("Wrong Email!\n");
        }
    }
};

int check_str(char destination[STR_LEN],char target[STR_LEN]){
    int is_same = -1;

    int first = size_of_array(destination);
    int second = size_of_array(target);

    if(first == second){
        int i=0;
        for(i=0;i<first;i++){
            if(target[i] != destination[i]){
                is_same =0;
            }else{
                is_same=1;
            }
        }

    }else{
        is_same =0;
    }

   return is_same;
}

int size_of_array(char array[STR_LEN]) {
    int size =0;

    for(int i=0;i<STR_LEN;i++){
        if(array[i]=='\0'){
            break;
        }else{
            size++;
        }
    }


    return size;
}

void print_stars(int length){
    int i=0;
    for(i=0;i<length;i++){
        printf("*");
    }
}
void dashboard(){
    int length = size_of_array(database[g_is_login].password);
    printf("Name : %s \n",database[g_is_login].name);
    printf("Email : %s \n",database[g_is_login].email);
    printf("Password : ");
    print_stars(length);
    printf("\n");
}

int logout(){
    int has_logout = 0;
    if(g_is_login != -1 ){
        g_is_login = -1;
        has_logout = 1;
    }else if(g_is_login == -1){
        printf("You Haven't Login Yet!\n");
    }

    return has_logout;
}



