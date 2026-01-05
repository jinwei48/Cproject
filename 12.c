#include <stdio.h>
int main(void)
{
    int salaries[11] = {0};  
    double commission = 0.09;
    double grossSales;
    printf("Enter employee gross sales (-1 to end): ");
    scanf("%lf", &grossSales);
    while (grossSales != -1) {
        int salary = 200 + grossSales * commission;
        int index = salary / 100;
        index = (index > 10) ? 10 : index;  
        salaries[index]++;
        printf("Employee Salary is $%.2f\n", (double)salary);
        printf("Enter employee gross sales (-1 to end): ");
        scanf("%lf", &grossSales);
    }
    printf("\nEmployees in the range:\n");
    for (int i = 2; i <= 9; ++i) {
        printf("$%d00-$%d99 : %d\n", i, i, salaries[i]);
    }
    printf("Over $1000: %d\n", salaries[10]);
    return 0;
}