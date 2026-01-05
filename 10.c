#include <stdbool.h>
#include <stdio.h>
#define MAX 20
int main(void)
{
    unsigned int a[MAX] = {0};  
    unsigned int k = 0;        
    unsigned int i, j;
    bool duplicate;
    printf("Enter 20 integers between 10 and 100:\n");
    for (i = 0; i < MAX; ++i) {
        unsigned int input;
        scanf("%u", &input);
        duplicate = false;
        for (j = 0; j < k; ++j) {
            if (a[j] == input) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            a[k++] = input;
        }
    }
    printf("The nonduplicate values are:\n");
    for (i = 0; i < k; ++i) {
        printf("%u ", a[i]);
    }
    printf("\n");

    return 0;
}