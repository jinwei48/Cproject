#include<stdio.h>
int toCelsius(int fTemp){
    return (fTemp-32)*5/9;
}
int toFahrenheit(int cTemp){
    return cTemp*9/5+32;
}
int main(){
    printf("Celsius to Fahrenheit:\n");
    printf("%-10d %d\n","Celsius","Fahrenheit");
    for(int c=0;c<=100;c++){
        printf("%-10d %d\n",c,toFahrenheit(c));
    }
    printf("\nFahrenheit to Celsius:\n");
    printf("%-10s %s\n","Fahrenheit","Celsius");
    for(int f=32;f<=212;f++){
        printf("%-10d %d\n",f,toCelsius(f));
    }
return 0;
}