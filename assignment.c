#include"stdio.h"
#define SIZE 6


void PrintText();
int PassOrNot(int array[]);
void PrintPassOrNotResult(int student_count , int pass_or_fail);

int HasAnyDistinction(int array[]);
void PrintHasAnyDistinction(int student_count , int d_count);

int TotalMark(int array[]);
int PrintTotalMark(int student_count , int total_count);

int g_option = 0;
int main(){
    int student_one[SIZE] ={70,100,50,20,40,60} ;
    int student_two[SIZE] ={100,100,60,80,45,92} ;
    int student_three[SIZE] ={70,39,80,60,50,69} ;

    while(g_option != 10){
        PrintText();
        printf("Choose An Option:");
        scanf("%d",&g_option);

        if(g_option == 1){
            PrintPassOrNotResult(1 , PassOrNot(student_one));
            PrintPassOrNotResult(2 , PassOrNot(student_two));
            PrintPassOrNotResult(3 , PassOrNot(student_three));
        }else if(g_option == 2){
            PrintHasAnyDistinction(1, HasAnyDistinction(student_one));
            PrintHasAnyDistinction(2, HasAnyDistinction(student_two));
            PrintHasAnyDistinction(3, HasAnyDistinction(student_three));
        }else if(g_option == 3){
            PrintTotalMark(1, TotalMark(student_one));
            PrintTotalMark(2, TotalMark((student_two)));
            PrintTotalMark(3, TotalMark(student_three));
        }else{
            printf("Wrong Option!");
        }
    }


    return 0;;
}

void PrintText(){
    printf("**********************************\n");
    printf("Enter 1 to Check if the students pass the exam or NOT.\n");
    printf("Enter 2 to Check if the students got any distinctions.\n");
    printf("Enter 3 to Check the total scores of students.\n");
    printf("Enter 10 to exit the program!\n");
}


int PassOrNot(int array[]){
    int bol = 1;
    for(int i=0;i<SIZE;i++){
        if(array[i] < 40){
            bol = 0;
        }
    }
    return bol;
}
void PrintPassOrNotResult(int student_count , int pass_or_fail){

        if(student_count == 1){
            if(pass_or_fail == 1){
                printf("Student %d Pass!\n",student_count);
            }else{
                printf("Student %d Fail!\n",student_count);
            }
        }
        if(student_count == 2){
            if(pass_or_fail == 1){
                printf("Student %d Pass!\n",student_count);
            }else{
                printf("Student %d Fail!\n",student_count);
            }
        }
        if(student_count == 3){
            if(pass_or_fail == 1){
                printf("Student %d Pass!\n",student_count);
            }else{
                printf("Student %d Fail!\n",student_count);
            }
        }

}

int HasAnyDistinction(int array[]){
    int count =0;
    for(int i=0;i<SIZE;i++){
       if(array[i] > 80){
           count++;
       }
    }
    return  count;
}
void PrintHasAnyDistinction(int student_count , int d_count){
    printf("Student %d got %d Distinctions\n", student_count , d_count);
}

int TotalMark(int array[]){
    int total_mark = 0;
    for(int i=0;i< SIZE;i++){
        total_mark += array[i];
    }
    return total_mark;
}
int PrintTotalMark(int student_count , int total_mark){
    printf("Student %d's total mark is %d\n" , student_count , total_mark );
}