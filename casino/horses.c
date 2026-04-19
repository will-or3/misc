#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

int main(){
    int number_of_horses = 6;
    int horses[number_of_horses + 1];
    int winner;

    for (int i=0;i<number_of_horses + 1;i++)
    {horses[i] = 1;}

    int tracklength = 24;
    int finish_line = tracklength - 1;
    int won = 0;
    while (won == 0) {
    for (int i=1; i <= number_of_horses; i++){
        if (horses[i] >= finish_line){
                won = 1;
                winner = i;
            } 
        printf("#%d:", i);
        for (int j=0; j<tracklength; j++) {
            if (j == finish_line){
                printf("|");
            }
            else if (horses[i] == j){
                printf("X");
            }
            else {printf("-");}
        }
        printf("\n");
    }
    usleep(250000);
    if (won == 0){printf("\033c");}

    uint32_t r;

    // get 4 rand bytes
    if (getrandom(&r, sizeof(r), 0) != sizeof(r)) {
        perror("getrandom");
    }
    int secret_num = (r % number_of_horses) + 1;
    horses[secret_num] += 1;

    if (horses[secret_num] > finish_line){
    horses[secret_num] = finish_line;}

    }
    
    printf("\n");
    printf("horse #%d won\n", winner);
}