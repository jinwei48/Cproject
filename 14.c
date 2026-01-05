#include<stdio.h>
#include<stdbool.h>
#define SIZE 50 
int main(){
    int x=0,y=0;
    int dir=0;  //0=右，1=下，2=左，3=上；
    bool pendown=false; 
    int floor[SIZE][SIZE]={0};//标记
    int cmd=0;
    int arg;
    while(cmd!=9){
        printf("Enter command (9 to end input):");
        scanf("%d",&cmd);
        switch(cmd){
            case 1:pendown=false;break;
            case 2:pendown=true;break;
            case 3:dir=(dir+1)%4;break;
            case 4:dir=(dir+3)%4;break; 
            case 5: //向前
                scanf("%d",&arg);
                for(int i=0;i<arg;i++){
                   switch(dir){
                       case 0:x++;break;
                       case 1:y++;break;
                       case 2:x--;break;
                       case 3:y--;break;
                   }
                   if(pendown){floor[y][x]=1;}
                }break;
            case 6:
                printf("The drawing is:\n");
                for(int i=0;i<SIZE;i++){
                    for(int j=0;j<SIZE;j++)
                        printf(floor[i][j] ? "*":" ");
                    printf("\n"); 
                }   
                break; 
        }
    }
    return 0;
}