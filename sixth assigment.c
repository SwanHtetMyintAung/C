#include "stdio.h"
#include "stdlib.h"
#define STR_LEN 50
#define PAS_LEN 20
#define MAX_USER 7
#define MAX_RECORD 10
#define DEFAULT_TOKEN 500

const char input_format[] = "id:%d,token:%d,name:%[^,],email:%[^,],password:%[^,],trasition_record:";
const char output_format[] = "id:%d,token:%d,name:%s,email:%s,password:%s,trasition_record:";

struct transition_record{
    int record_id;
    char record[50];
};
typedef struct user{
    int id;
    int token;
    char name[STR_LEN];
    char email[STR_LEN];
    char password[PAS_LEN];
    struct transition_record transition_db[MAX_RECORD];
}user;
static const struct user ResetUser;
struct user database[MAX_USER];
//utilities
void make_int_array(int* ptr,int user_id);
int get_biggest_int(int array[MAX_RECORD]);
int get_smallest_int(int array[MAX_RECORD] ,int initial);
int check_str(char destination[STR_LEN],char target[STR_LEN]);
void copy_str(char destination[STR_LEN],char target[STR_LEN]);
int size_of_array(char array[STR_LEN]);
int check_unique_email(char email[STR_LEN]);
int validate_password(char password[PAS_LEN]);
int validate_email(char email[STR_LEN]);
//file
int retrieve_data_from_file();
int save_data_to_file();
void save_transition_record(int token_amount , struct user *sender , struct user *receiver);
//main function for program
void register_user_data();
void login_handler(char email[STR_LEN],char password[PAS_LEN]);
void login();
void print_stars(int length);
int check_admin(int id);
void dashboard(int id);
int transfer_token();
int logout();
//just print function
void print_main_menu();

//global variabes
int g_total_user = 0;
int g_is_login = 0;//default is logout

int main(){
    retrieve_data_from_file();        

    while(1){
        
        int option = 0;
        print_main_menu();
        scanf("%d",&option);

        //to register
        if(option == 1){
            if(g_is_login == -1){
                system("clear");
                register_user_data();
            }else if(g_total_user == MAX_USER){
                printf("Our DataBase is Full For The Moment!\n");
            }else{
                printf("You already have an account!\n");
            }
        //to login
        }else if(option == 2){
            if(g_is_login == -1){
                system("clear");
                login();
            }else{
                system("clear");
                dashboard(g_is_login);
            };
        //to logout
        }else if(option == 3){
            int result = logout();
            if(result ==1){
                system("clear");
                printf("You Have Logout Successfully!\n");
            }
        //to exit
        }else if(option == 4){
            FILE *file_clear = fopen("user_data.txt","w");
            if(file_clear == NULL){
                printf("Something Wrong In clearing the File!\n");
                return -1;
            }
            fclose(file_clear);
            int result = save_data_to_file();
            if(result != 1){
                printf("Something went wrong while saving data!\n");
            }
            exit(1);
        }
    }
    return 0;
}
//this is a function to print option as main menu
void print_main_menu(){
    printf("****WELCOME TO MY SYSTEM****\n");
    printf("Enter 1 to Register.\n");
    printf("Enter 2 to Login.\n");
    printf("Enter 3 to Logout.\n");
    printf("Enter 4 to Exit.\n");
    printf("Enter an Option:");
}
//register user for the first time
void register_user_data(){
    //creat temp variable for convenient sake when storing data
    char reg_name[STR_LEN];
    char reg_email[STR_LEN];
    char reg_password[PAS_LEN];

    printf("Your Are Now Registering to My System! Your ID would be : %d\n" , g_total_user);
    printf("Name:");
    scanf("%s", reg_name);
    printf("Email:");
    scanf("%s", reg_email);
    printf("Password:");
    scanf("%s", reg_password);

    //get 1 or 0 depending on the input email
    int is_unique = check_unique_email(reg_email);


    //proceed the program if only the email is unique
    if(is_unique == 1 ){
        //get 1 or 0 depending on if the password is strong or not!
        int password_is_valid = validate_password(reg_password);
        if(password_is_valid == 1){
            //set the id automatically according to total user count
            database[g_total_user].id = g_total_user;

            //set original token
            database[g_total_user].token = DEFAULT_TOKEN;
            //this function basically copy the string from second argument to first argument
            copy_str(database[g_total_user].name , reg_name);
            copy_str(database[g_total_user].email , reg_email);
            copy_str(database[g_total_user].password , reg_password);

            g_total_user++;
        }

    }else{
        printf("Already Existing Email\n");
    }
    //if everything goes well , plus one in total user

}
//main function that operates the login section
void login(){
    //same as register , temp array for convenient sake
    char l_email[STR_LEN];
    char l_password[PAS_LEN];

    printf("Your Are Now Logging In to My System!\n");
    printf("Email:");
    scanf("%s", l_email);
    printf("Password:");
    scanf("%s", l_password);

    //this function allowed us to check if the password and email match with the database
    login_handler(l_email , l_password);
    if(g_is_login != -1){
        printf("Login Successfully! Your Id is : %d\n", g_is_login);
        //a function to show the user its data
        system("clear");
        dashboard(g_is_login);
    }else{
        printf("The Data Of your Input did not match with the one we had!\n");
    }

}
//this function mainly focus on logic behind login
void login_handler(char email[STR_LEN],char password[PAS_LEN]){
    int i=0;
    //basically loop through every user
    for(i=0;i<g_total_user;i++){
        //this function return 1 or 0 depending on the string are same or not
        int check_email = check_str(database[i].email , email);
        //if only we find a matched email(which means there's account with the email) ,we will proceed to check the password
        if(check_email == 1){
            int check_password = check_str(database[i].password, password);
            if(check_password == 1){
                //if both email and password are checked and same , the program update this global variable which will be used as a global id
                g_is_login = database[i].id;
                break;
                //dev code
                //printf("The global variable g_is_login has changed!\n");
            }else{
                printf("Wrong Password!\n");
                break;
            }
            //if we don't find the email and the current index(i) is the same as the last account on the list , the program print the line
            //the reason why "g_total_user-1" is , g_total_user is always 1 ahead and the condition on "loop" is i<g_total_user
        }else if(check_email == 0 && i == g_total_user -1){

            printf("Couldn't Find The Matching Email!\n");
        }
    }
};
//return 1 if the id is admin account . returns 0 if not
int check_admin(int id){
    if(id < 4){
        return 1;
    }else{
        return 0;
    }
}



//this function is used to replace the password with "*"
void print_stars(int length){
    for(int i=0;i<length;i++){
        printf("*");
    }
}
//show the user its info for now
void dashboard(int id){
    //get the length of the password ; so, we can replace it with "*"
    int l_option = 0;
    int is_admin = check_admin(id);

    while(1){
        //system("clear");
        printf("********This Is Your DashBoard Page.************\n");
        printf("Enter 1 to check Your Account Info\n");
        printf("Enter 2 to Transfer Token\n");
        printf("Enter 3 to Check Your Transition Data\n");
        printf("Enter 4 to Back\n");
        if(is_admin == 1){
            printf("Admin Privillage\n");
            printf("Enter 5 to See All User and Their Passwords\n");
            printf("Enter 6 To Delete A User(you can't delete other admin admin account)\n");
        }
        printf("Choose An Option :");
        scanf("%d",&l_option);

        if(l_option == 1){
            system("clear");
            int length = size_of_array(database[id].password);
            printf("Name : %s \n",database[id].name);
            printf("Email : %s \n",database[id].email);
            printf("Your Total Token : %d \n" ,database[id].token);
            printf("Password : ");
            print_stars(length);
            printf("\n");
            
        }else if(l_option == 2){
            system("clear");
            int result = transfer_token();
            if(result == 1){
                printf("Transfer Completed!\n");
            }else{
                printf("Transfer Failed!\n");
            }
        }else if(l_option == 3){
            int record_exist =0;//this is used to check if the user have at least one transition
            for(int i=0;i<=MAX_RECORD;i++){
                 
                if(database[g_is_login].transition_db[i].record[0] == '\0'){
                    if(record_exist == 0){
                        printf("No Record Available!\n");
                    }
                    break;
                }else{
                    record_exist = 1;
                    printf("%d.%s\n",database[g_is_login].transition_db[i].record_id,
                                    database[g_is_login].transition_db[i].record);
                }
            }
        }else if(l_option == 4){
            break;
        }else if(l_option == 5 && is_admin == 1){
            system("clear");
            printf("UserName \t Email \t \t Password\n");
            for(int i=0;i<g_total_user;i++){
                printf("%d.%s \t %s \t %s\n",i,database[i].name,database[i].email , database[i].password);
            }
        }else if(l_option == 6 && is_admin == 1){
            int id_to_delete = -1;
            printf("Enter The ID number Of An Account You Want To Dispose Of:");
            scanf("%d",&id_to_delete);
            //not 1 means it is not admin account.
            if(check_admin(id_to_delete) != 1){
                database[id_to_delete] = ResetUser ;
            }else{
                printf("can't delete the account for some reasons!\n");
            }
        }
    }


}
//main function that handle the logout
int logout(){
    //a variable to check the conditions are met
    int has_logout = 0;
    //if g_is_login is not default , change the g_is_login to default(-1) and has_logout to 1 which mean the logout operation is a success!
    if(g_is_login != -1 ){
        g_is_login = -1;
        has_logout = 1;
    //on the contrary , if the g_is_login is default, the program will show the message.
    }else if(g_is_login == -1){
        printf("You Haven't Login Yet!\n");
    }

    return has_logout;
}


//utilities
//make integer array 
void make_int_array(int* ptr,int user_id){
    if(g_is_login == -1){
        return -1;
    }
    for(int i=0;i<MAX_RECORD;i++){
        ptr = database[user_id].transition_db[i].record_id;
        ptr++;
    }
}
//to get the biggest integer from the array
int get_biggest_int(int array[MAX_RECORD]){
    int return_id = -1;//to hold the biggest integer
    for(int i=0;i<MAX_RECORD;i++){
        //if current index value is greater than "return_id" , that will be the new value
        (array[i] > return_id) &&(return_id = array[i]);
    }
    return return_id;
}
//to get the smallest integer from the array
int get_smallest_int(int array[MAX_RECORD] ,int initial){
    int return_id = initial;//to hold the biggest integer
    for(int i=0;i<MAX_RECORD;i++){
        //if current index value is smaller than "return_id" , that will be the new value
        (array[i] < return_id) && (return_id = array[i]);
    }
    return return_id;
}
//check if two strings are the same , the order of argument doesn't really matter for now.
int check_str(char destination[STR_LEN],char target[STR_LEN]){
    //a variable to determine that all the conditions are met!
    int is_same = -1;

    //get the size of both array/
    int first = size_of_array(destination);
    int second = size_of_array(target);

    //if the size of both array don't match ,  we don't need to do any logic anymore
    if(first != second){
        is_same =0;
        return is_same;
    }else{
        //but if they do , loop through them and check every element is the same!
        for(int i=0;i<=first;i++){
            if(target[i] != destination[i]){
                is_same=0;
                break;
            }else{
                is_same =1;
            }
        }
    }

    return is_same;
}
//copy the string from target to destination
void copy_str(char destination[STR_LEN],char target[STR_LEN]){
    int i=0;
    for(i=0;i<STR_LEN;i++){
        //"\0" means its blank and no elements at all
        if(target[i] == "\0"){
            break;
        }else{
            destination[i] = target[i];
        }
    }
}
//get the actual length of the array
int size_of_array(char array[STR_LEN]) {
    int size =0;
    //loop through the array until it see "\0"
    for(int i=0;i<STR_LEN;i++){
        if(array[i]=='\0'){
            break;
        }else{
            size++;
        }
    }


    return size;
}
//this function check if there's a string same as the input one
int check_unique_email(char email[STR_LEN]){
    // a variable to check whether all conditions are met!
    int is_unique=0;
    int is_valid = validate_email(email);
    if(is_valid != 1){
        printf("The Email Isn't Valid.\n");
        return 0;
    }else if(is_valid == 1){

        //loop through every user
        for(int i=0;i<=g_total_user;i++){
            //and use the check_str function for every user until it find the user or the  is finish
            int check_email = check_str(database[i].email , email);
            if(check_email != 1){
                is_unique = 1;
            }else{
                is_unique =0;
                break;
            }
        }
    }
    return is_unique;
}
//a function is to validate the password
int validate_password(char password[PAS_LEN]){
    //small letter-> 97-122 , capital letter -> 65-90
    //special character -> 33-46 ,58-64 , 91-96 , 123 ,126

    //variable to check EACH requirements for validation
    int is_valid = 0;
    int has_small_letter =0;
    int has_capital_letter =0;
    int has_number =0;
    int has_special_character =0;

    //get the length of the array
    int length_of_pass = size_of_array(password);
    // if it's less than six , the passsword is weak
    if(length_of_pass >= 6){
        //loop through every element in array
        for(int i=0;i<length_of_pass;i++){
            //check their respective ascii value
            if(password[i] > 96 && password[i] < 123){
                has_small_letter = 1;
            }else if(password[i] > 64 && password[i] < 91){
                has_capital_letter = 1;
            }else if(password[i] > 47 && password[i] < 58){
                has_number = 1;
            }else{
                has_special_character =1;
            }
        }
    }else{
        printf("Password Must Be At Least 6 characters Long\n");
    }
    //if only all requirements are fulfilled , this code will work
    if(has_capital_letter && has_small_letter && has_number && has_capital_letter && has_special_character){
        printf("your password is strong!\n");
        //printf("%d ; %d ; %d ; %d \n", has_capital_letter ,has_small_letter , has_number, has_special_character);
        is_valid=1;
    //if the requirements aren't fulfilled , the warning message and requirements to strong password will show up
    }else{
        printf("Password Must Be Have At Least 1 small letter , 1 CAPITAL LETTER , 1 Number And 1 Special Character Such As : !@#$%^&*\n");
    }
    return is_valid;
}
//to validate email
int validate_email(char email[STR_LEN]){
    //get the total length of the array
    int size = size_of_array(email);
    //temp variable for conditions
    int at_sign = 0;
    int dot_sign = 0;
    for(int i=0;i<=size;i++){
        if(email[i] == '@'){
            //at sign can't be at last or near it "example@google.com"
            if(i < size - 3){
                at_sign = i;
            }
        }else if(email[i] == '.'){
            //dot can't be at the last place and can't be next to at sign
            if(i != size && at_sign < i && !(i == at_sign+1)){
                dot_sign = i;
            }
        }
    }
    if(at_sign && dot_sign){
        return 1;
    }else{
        return 0;
    }
}

//a function add transition record 
//take three parameters 1.amount of the token the transition make , the address of sender and the address of receiver
void save_transition_record(int token_amount , struct user *sender , struct user *receiver){
    //loop through the transition record of the sender to check which spot are available
    for(int i=0;i<MAX_RECORD;i++){
        //get the first character of the record array in transition_db of sender
        char first_cha = sender->transition_db[i].record[0];
        int done_written = 0;
        int latest_id = 0;//to find the biggest/latest id
        int first_id = 0;//to find the smallest/earliest id
        //check if the first character is '\0' which means it is blank
        if(first_cha == '\0'){
            //assign transition record id
            sender->transition_db[i].record_id = i;
            //write data to the array 
            sprintf(sender->transition_db[i].record ,"You Sent %s A Total Of %d",receiver->name ,token_amount);
            done_written = 1;
            break;
            
        //checking if the looping has reach maximum value which is MAX_RECORD , AND if data has not been written. the two condition basically means , the record database is full .
        }else if(i == (MAX_RECORD -1) && done_written == 0){
            sprintf(sender->transition_db[MAX_RECORD].record ,"You Sent %s A Total Of %d",receiver->name ,token_amount);
            done_written = 1;
            //code in process
            // int id_array[MAX_RECORD];
            // int *p_id_array = &id_array;
            // make_int_array(p_id_array , g_is_login);
            // int biggest_id = get_biggest_int(id_array);
            // int smallest_id = get_smallest_int(id_array , biggest_id);
            // if(smallest_id != -1){
            //     int current_id = biggest_id - MAX_RECORD;
            //     sender->transition_db[current_id].record_id = (current_id);
            //     sprintf(sender->transition_db[current_id].record ,"You Sent %s A Total Of %d",receiver->name ,token_amount);
            // }
        }
    }
    //everything is the same , and this is for the receiver
    for(int i=0;i<MAX_RECORD;i++){
        char first_cha = receiver->transition_db[i].record[0];
        int done_written = 0;
        if(first_cha == '\0'){
            receiver->transition_db[i].record_id = i;
            sprintf(receiver->transition_db[i].record ,"You Received A Total Of %d From %s",token_amount  , sender->name);
            break;
        }else if(i == (MAX_RECORD -1) && done_written == 0){
            int id_array[MAX_RECORD];
            int *p_id_array = &id_array;
            make_int_array(p_id_array , i);
            int biggest_id = get_biggest_int(id_array);
            int smallest_id = get_smallest_int(id_array , biggest_id);
            if(smallest_id != -1){
                int current_id = biggest_id - MAX_RECORD;
                sender->transition_db[current_id].record_id = (current_id);
                sprintf(sender->transition_db[current_id].record ,"You Received A Total Of %d From %s",token_amount,sender->name);
            }
        }
    }
}

// a function to handle the trasnfer of tokens
//0 means failed dn 1 means success
int transfer_token() {
    //to store the token amount you want to transfer
    int l_amount = 0;
    printf("Your Balance Is : %d \n", database[g_is_login].token);
    printf("How Much Do you Want To Transfer :");
    scanf("%d", &l_amount);
    //check if the amount of token is valid . more than 0 which means no negative values and less than your current token
    if (l_amount  > 0 && l_amount <= database[g_is_login].token) {
        char l_email[STR_LEN];//store target email
        //get email from user
        printf("Enter an Email You Want to Send:");
        scanf("%s", &l_email);
        //loop through all the user and check the email exist!
        for (int i = 0; i < g_total_user; i++) {
            //return 1 if they are the same
            int check_email = check_str(database[i].email, l_email);
            //if only the emails are matched , we will proceed.
            if (check_email == 1) {
                //check the condition where the input email is the same with the user currently login
                if(i == g_is_login){
                    printf("You can not send the tokens to yourself!\n");
                    return 0;
                    //after checking every other possible bug . the code will add the token to target user and deduce from current user
                }else{
                    //receiver
                    database[i].token = database[i].token + l_amount;
                    //sender / current user
                    database[g_is_login].token = database[g_is_login].token - l_amount;
                    save_transition_record(l_amount, &database[g_is_login] , &database[i]);
                    return 1;
                }

            } else if (check_email != 1 && i == g_total_user ) {
                printf("User Not Found!\n");
            }
        }
        return 1;
    }else{
        printf("You Do Not Have Enough Tokens!\n");
        return 0;
    }
}

//save data to file
int save_data_to_file(){
    FILE *file_write = fopen("user_data.txt","a");

    if(file_write == NULL){
        printf("Couldn't Open File!\n");
        return -1;
    }
    for(int i=0;i<g_total_user;i++){
        if(database[i].name[0] != '\0'){
            fprintf(file_write,output_format,
            i,//this is to sort the id automatically 
            database[i].token,
            database[i].name,
            database[i].email,
            database[i].password);
            for(int j=0;j<MAX_RECORD;j++){
                char first_cha = database[i].transition_db[j].record[0];
                if(first_cha != '\0'){
                    fprintf(file_write,"%s,",
                    //database[i].transition_db[j].record_id,
                    database[i].transition_db[j].record);
                }
                if(j==MAX_RECORD-1){
                    fputc('\n',file_write);
                }
            }
        }
        //loop through all transition data , maxium is 10;

        if(i == g_total_user){
            printf("Data Saved Successfully!\n");
        }
    }
    
    return 1;
}
int retrieve_data_from_file() {
    FILE *file_read ;
    file_read = fopen("user_data.txt", "r");

    if (file_read == NULL) {
        printf("Couldn't find the file!\n");
        return -1;
    }
    
    int total_field=0;
    int users_from_file = 0;

    while((total_field = fscanf(file_read,input_format,
                            &database[users_from_file].id,
                            &database[users_from_file].token,
                            database[users_from_file].name,
                            database[users_from_file].email,
                            database[users_from_file].password)) == 5){
            int record_counter =0;
            //to get transition record data/
            int debug =-1;
            while((fscanf(file_read,"%[^\n,],",
                    //database[users_from_file].transition_db[record_counter].record_id,
                    database[users_from_file].transition_db[record_counter].record))){
                database[users_from_file].transition_db[record_counter].record_id = record_counter;
                record_counter++;
            }
            //to get '\n' new line character out of the way
            char c= fgetc(file_read);
            users_from_file++;
    }

    g_total_user = users_from_file;
    fclose(file_read);
    return 1;
}
