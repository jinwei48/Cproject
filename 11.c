#include <stdio.h>

int main() {
    int plant[11] = {0}; 
    int choice, seatNum, i;
    char transfer;
    while (i<10) {
        printf("Please type 1 for \"first class\"\n");
        printf("Please type 2 for \"economy\"\n");
        scanf("%d", &choice);
        if (choice == 1) {
            int firstClassFull = 1;
            for (i = 0; i < 5; i++) {
                if (plant[i] == 0) {
                    firstClassFull = 0;
                    break;
                }
            }
            if (!firstClassFull) {
                for (i = 0; i < 5; i++) {
                    if (plant[i] == 0) {
                        plant[i] = 1;
                        seatNum = i + 1;
                        printf("you are in fristclass of %d\n", seatNum);
                        break;
                    }
                }
            } else {
                printf("would you like to economy?(y/n)\n");
                scanf(" %c", &transfer);
                if (transfer == 'y') {
                    for (i = 5; i < 10; i++) {
                        if (plant[i] == 0) {
                            plant[i] = 1;
                            seatNum = i + 1;
                            printf("you are in economy of %d\n", seatNum);
                            break;
                        }
                    }
                } else {
                    printf("Next flight leaves in 3 hours\n");
                }
            }
        } 
        else {
            int economyFull = 1;
            for (i = 5; i < 10; i++) {
                if (plant[i] == 0) {
                    economyFull = 0;
                    break;
                }
            }
            if (!economyFull) {
                for (i = 5; i < 10; i++) {
                    if (plant[i] == 0) {
                        plant[i] = 1;
                        seatNum = i + 1;
                        printf("you are in economy of %d\n", seatNum);
                        break;
                    }
                }
            } else {
                printf("would you want to fristclass?(y/n)\n");
                scanf(" %c", &transfer);
                if (transfer == 'y') {
                    for (i = 0; i < 5; i++) {
                        if (plant[i] == 0) {
                            plant[i] = 1;
                            seatNum = i + 1;
                            printf("you are in %d of fristclass\n", seatNum);
                            break;
                        }
                    }
                } else {
                    printf("Next flight leaves in 3 hours\n");
                }
            }
        } 
        // 检查是否所有座位都已分配
        int allFull = 1;
        for (i = 0; i < 10; i++) {
            if (plant[i] == 0) {
                allFull = 0;
                break;
            }
        }
        if (allFull) {
            printf("end!\n");
            break;
        }
    }

    return 0;
}