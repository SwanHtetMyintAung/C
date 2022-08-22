#include<stdio.h>
#include<stdlib.h>
#define FILE_MAX 100

void TextOne();
void TextOnePointOne();
void FillerText();

int main(){
    int scanfOne = 0;
    int scanfOnePointOne = 0 ;
    int scanfThreePointOne = 0 ;
    int scanfThreePointTwo = 0 ;
    int count=0;
    int countTwo=0;
    int sum=0;
    int keep_going=1;
    int *ptrOne;
    int *ptrTwo;
    int *ptrThree;
    int a,b,c,d,e,f,g;

    FILE *fileptr;
    FILE *fileptrTwo;
    char filenameArrayOne[FILE_MAX];
    char filenameArrayTwo[FILE_MAX];
    char filenameArrayThree[FILE_MAX];

    printf("Yokoso kira kira doki doki  mochi mochi puyo puyo waku waku washoi no wonder stage..\n");
    while(keep_going == 1){


        TextOne();
       FillerText();
        scanf("%d",&scanfOne);

        if(scanfOne == 1){
            printf("\nHow Many Data You Want To Write:");
            scanf("%d",&count);

            ptrOne = (int*)calloc(count , sizeof(int));

            printf("\nEnter Data\n");
            for(a=0;a<count;a++){
                scanf("%d", ptrOne+a);
            }

            printf("\nData Inputting Done\n");

            TextOnePointOne();
            FillerText();
            scanf("%d",&scanfOnePointOne);

            if(scanfOnePointOne ==1){
                printf("Enter File Nam With No Space(Including  '.txt' Extension) : ");
                scanf("%s",filenameArrayOne);

                fileptr = fopen(filenameArrayOne , "w");
                for(b=0;b<count;b++){

                    if((b+1) != count){
                        fprintf(fileptr , "%d\n" , ptrOne[b]);

                    }else{
                        fprintf(fileptr , "%d" , ptrOne[b]);
                    }
                }
                printf("Inputting Data To File Done...\n");
                fclose(fileptr);
            }if(scanfOnePointOne == 2){
                continue;
            }
        }else if(scanfOne == 2){
            printf("Enter File Nam With No Space(Including  '.txt' Extension) : ");
            scanf("%s",filenameArrayTwo);

            fileptr = fopen(filenameArrayTwo ,"r");
            ptrTwo = (int*)calloc(10 , sizeof(int));


            if(fileptr == NULL){
                printf("\nFile Not Exist...\n");
                continue;
            }

            c =0;
            d=0;
            char checkchar;
            while(c==0){
                fscanf(fileptr , "%d" , ptrTwo+d);
                checkchar = getc(fileptr);
                if( checkchar == EOF ){
                    c = 1;
                }
                printf("%d\n", ptrTwo[d]);
                d++;
            }
            fclose(fileptr);

        }else if(scanfOne == 3){
            printf("Enter File Nam With No Space(Including  '.txt' Extension) : ");
            scanf("%s",filenameArrayThree);

            fileptr = fopen(filenameArrayThree ,"r+");
            ptrThree = (int*)calloc(10 , sizeof(int));

            if(fileptr == NULL){
                printf("\nFile Not Exist...\n");
                continue;
            }
            e=0;
            f=0;
            char checkchar ;
            while(e == 0){
                fscanf(fileptr , "%d" , ptrThree+f);
                printf("Index |%d| is |%d|\n", f , ptrThree[f]);
                checkchar = getc(fileptr);
                if( checkchar == EOF ){
                    e = 1;
                }else{
                    f++;
                }
            }
            fclose(fileptr);
            printf("\nIf You exit now the data will be all lost!\n");
            fileptrTwo = fopen(filenameArrayThree , "w");

            int go =1;
            while(go == 1){
                printf("\nEnter Index You Want To Edit:");
                scanf("%d" , &scanfThreePointOne);
                if(scanfThreePointOne > f){
                    printf("\nThere Is NO Index As Such...\n");

                }else{

                    go++;
                }
            }

            printf("Editing Index %d...\n" , scanfThreePointOne);
            printf("Enter New Value : ");
            scanf("%d" , ptrThree+scanfThreePointOne);
            for(g=0;g<(f+1);g++){
                if(g != f){
                    fprintf(fileptr , "%d\n" , ptrThree[g]);
                }else{
                    fprintf(fileptr , "%d" , ptrThree[g]);
                }
            }

            printf("Operation Done....\n");

            fclose(fileptr);
        }else if(scanfOne == 4){
            exit(0);
        }else{
            printf("\nThere Is No Such Option");
            exit(0);
        }
    }
    free(ptrOne);
    free(ptrTwo);
    free(ptrThree);
    return 0;
}


void TextOne(){
    printf("\nEnter 1 to Write data To File\n");
    printf("Enter 2 to Get Data From File\n");
    printf("Enter 3 to Edit Data From File\n");
    printf("Enter 4 to Exit\n");
}
void TextOnePointOne(){
    printf("\nEnter 1 to Save Data To File\n");
    printf("Enter 2 to Go Back To Main Page\n");
}
void FillerText(){
    printf("\nChoose An Option:");
}
