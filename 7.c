#include<stdio.h>
int gcd(int x,int y){
    while(y!=0){
        int temp=y;
        y=x%y;
        x=temp;
    }
    return x;
}
int main(){
    printf("Enter two integers:");
    int a,b;
    scanf("%d %d",&a,&b);
    printf("The greatest common divisor of %d and %d is %d\n\n",a,b,gcd(a,b));
}