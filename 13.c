#include<stdio.h>
int main(){
    double sales[4][5]={0.0};
    double productsales[5]={0.0};
    double personsales[4]={0.0};
    puts("Enter the salesperson(0-3),product(0-4),and total sales.");
    puts("Enter -1 for the salesperson to end input.");
    unsigned int salesperson=0;
    unsigned int product;
    double amount;
    while(salesperson!=-1){
        scanf("%u",&salesperson);
        scanf("%u %1f",&product,&amount);
        sales[salesperson][product]+=amount;
        for(int i=0;i<5;i++){
            for(int j=0;j<4;j++){
                productsales[i]+=sales[j][i];
            }
        }
        for(int i=0;i<4;i++){
            for(int j=0;j<5;j++){
                personsales[i]+=sales[i][j];
            }
        }
        printf("\n      0    1    2    3    4    \n");
        for(int i=0;i<4;i++){
            printf("salesperson%d ",i);
            for(int j=0;j<5;j++){
               printf("%1f  ",sales[i][j]);
            }
        }
    }
}