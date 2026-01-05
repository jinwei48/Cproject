#include <stdio.h>
int quotient(int a, int b) {
    return a / b;
}
int remainder(int a, int b) {
    return a % b;
}
void printDigits(int number) {
    int divisor = 10000;
    printf("The digits in the number are:\n");
    while (quotient(number, divisor) == 0) {
        divisor = quotient(divisor, 10);
    }
    while (divisor > 0) {
        int digit = quotient(number, divisor);
        printf("%d  ", digit);
        number = remainder(number, divisor);
        divisor = quotient(divisor, 10);
    }
}
int main() {
    printf("Enter an integer between 1 and 32767: ");
    int number;
    scanf("%d", &number);
    printDigits(number);
    return 0;
}

