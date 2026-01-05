#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int flip(){
   return rand()%2;
}
int main(){
   srand(time(NULL));
   int heads=0,tails=0;
   for(int i=1;i<=100;i++){
      int result=flip();
      if(result==1){
        printf("Heads");
        heads++;
    }else {
        printf("Tails");
        tails++;
    }if(i%10==0){printf("\n");}
   }
   printf("\nThe total number of Heads was %d\n",heads);
   printf("The total number of Tails was %d\n",tails);
   return 0;
}