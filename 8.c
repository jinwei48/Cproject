#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void guessGame(void); 
int main() {
    srand(time(NULL));
    guessGame();
    return 0;
}
void guessGame(void) {
    char playAgain;
    do {
        int target = rand() % 1000 + 1;
        int guess;
        printf("I have a number between 1 and 1000.\n");
        printf("Can you guess my number?\n");
        printf("Please type your first guess.\n? ");
        while (1) {
            scanf("%d", &guess);
            if (guess > target) {
                printf("Too high. Try again.\n? ");
            } else if (guess < target) {
                printf("Too low. Try again.\n? ");
            } else {
                printf("Excellent! You guessed the number!\n");
                break;
            }
        }
        printf("Would you like to play again (y or n)? ");
        scanf(" %c", &playAgain); 
        printf("\n");
    } while (playAgain == 'y');
}
