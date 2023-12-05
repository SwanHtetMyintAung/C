
#include <stdio.h>

int main()
{
    int i =0;//outermost loop , for rows
    int j=0;//first space " "
    int k=0;//first star pyramid
    int p=0;//second space " "
    int r=0;//second star pyramid
    int size=10;//pyramid size
    printf("size of the pyramids :");
    scanf("%d",&size);
    
    for(i=0;i<size;i++){
        //first space
        for(j=0;j<size-i;j++){
            printf(" ");
        }
        //first star pyramid
        for(k=0;k<=i*2;k++){
            printf("*");
        }
        //second space
        for(p=0;p<(size-i)*2-1;p++){
            printf(" ");
        }
        //second star pyramid
        for(r=0;r<=i*2;r++){
            printf("*");
        }
        
        
        printf("\n");
    }

    return 0;
}
