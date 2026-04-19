#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

long long player_money = 1000;

long long get_bet(){
  char buffer[100];
  long long num;

  if (fgets(buffer, sizeof(buffer), stdin) == NULL){
    return 0;
  }

  if (sscanf(buffer, "%lld", &num) != 1) {
    return 0;
  }

  if (num < 1 || num > player_money){
    return 0;
  }

  size_t len = strlen(buffer); 
  // I have to minus 1 because my compiler warns me of OOB if I dont
  if (len > 0 && buffer[len-1] == '\n'){
  buffer[len-1] = '\0';}
  
  return num;
}

int is_red(int n){
  int red_numbers[] = {
        1,3,5,7,9,12,14,16,18,
        19,21,23,25,27,30,32,34,36
    };

    for (int i = 0; i < 18; i++) {
        if (red_numbers[i] == n) return 1;
    }
    return 0;
}

void read_line(char *buffer, size_t size){
  if (fgets(buffer, size, stdin) != NULL){
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n'){
      buffer[len - 1] = '\0';
    }
  }
}

int read_int(){
  char buffer[100];
  int num;

  if (fgets(buffer, sizeof(buffer), stdin) == NULL){
    return 0;
  }
  if (sscanf(buffer, "%d", &num) != 1) {
    return 0;
  }
  if (num < 1){
    return 0;
  }

  size_t len = strlen(buffer); 
  if (len > 0 && buffer[len-1] == '\n'){
  buffer[len-1] = '\0';}
  
  return num;
}

uint32_t gen_random(){
  uint32_t r;
  if (getrandom(&r, sizeof(r), 0) != sizeof(r)){
    perror("getrandom");
    exit(1);
  }
  return r;
}

void roulette(){
  printf("\033c");
  printf("balance: %lld\n\n", player_money);
  printf("welcome to the roulette table\nplace your bet below\n\n");

  long long bet_amount = 0;

  while (bet_amount == 0) {
    printf(">:");
    bet_amount = get_bet();
  }
  player_money = player_money - bet_amount;

  enter:
  printf("\033c");
  printf("Roulette Rules:\n");
  printf("\t you can bet on:\n");
  printf("\t* specific numbers 1-36 or 0 (if you want a single type [s])\n");
  printf("\t* (r)ed of (b)lack\n");
  printf("\t* (o)dd or (e)ven\n");
  printf("\tthats it.\n\n");

  char user_bet[100];
  printf("enter bet\n");
  printf("\n>:");
  read_line(user_bet, sizeof(user_bet));

  int key = 0;
  int user_bet_single = -1;
  if (strcmp(user_bet, "r") == 0 || strcmp(user_bet, "red") == 0){
    key = 1;
  } 
  else if (strcmp(user_bet, "b") == 0 || strcmp(user_bet, "black") == 0){
    key = 2;
  }
  else if (strcmp(user_bet, "o") == 0 || strcmp(user_bet, "odd") == 0){
    key = 3;
  }
  else if (strcmp(user_bet, "e") == 0 || strcmp(user_bet, "even") == 0){
    key = 4;
  }
  else if (strcmp(user_bet, "g") == 0 || strcmp(user_bet, "green") == 0){
    key = 5;
  }
  else if (strcmp(user_bet, "s") == 0 || strcmp(user_bet, "single") == 0){
    start_single:
    printf("enter single\n\n");
    printf(">:");
    
    char buffer[100];
    int num;
    if (fgets(buffer, sizeof(buffer), stdin) == NULL){
      goto start_single;
    }
    if (sscanf(buffer, "%d", &num) != 1) {
      goto start_single;
    }
    if (num < 0 || num > 36){
      goto start_single;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n'){
    buffer[len-1] = '\0';}

    user_bet_single = num;  
  }

  else {goto enter;}

  // game logic starts here
  int secret_num = gen_random() % 37;

    const char *frames[] = {
        "Spinning   ",
        "Spinning.  ",
        "Spinning.. ",
        "Spinning..."
    };

    int y = 0;
    
    for(int x=0; x<10; x++) {
        printf("\r%s", frames[y]);
        fflush(stdout);

        usleep(250000);
        y = (y + 1) % 4;
    }
    
    int green = 0;
    int red = 0;
    int black = 0;

    green = (secret_num == 0);
    red = is_red(secret_num);
    black = (!green && !red);
  
  if (key != 0){
    if (key == 1 && red == 1){
      player_money += bet_amount * 2;
      printf("\nyou won!!!");
      printf("bank: %lld\n", player_money);
    }
    else if (key == 2 && black == 1){
      player_money += bet_amount * 2;
      printf("\nyou won!!!");
      printf("bank: %lld\n", player_money);
    }
    else if (key == 5 && green == 1){
      player_money += bet_amount * 35;
      printf("\nyou won!!!");
      printf("bank: %lld\n", player_money);
    }
    else if (secret_num % 2 == 0 && key == 4){
      player_money += bet_amount * 2;
      printf("\nyou won!!!");
      printf("bank: %lld\n", player_money);
    }
    else if (secret_num % 2 != 0 && key == 3){
      player_money += bet_amount * 2;
      printf("\nyou won!!!");
      printf("bank: %lld\n", player_money);
    }
    else {
      printf("\n\nyou lost...\n");
      printf(":(\n");
      printf("bank: %lld\n", player_money);
    }
  }
  else if (user_bet_single != -1){
    if (user_bet_single == secret_num){
      player_money += bet_amount * 35;
      printf("\nyou won!!!");
      printf("bank: %lld\n", player_money);
    }
    else {
      printf("\n\nyou lost...\n");
      printf(":(\n");
      printf("bank: %lld\n", player_money);
    }
  }

}
void horse_races(){
    int number_of_horses = 6;
    int horses[number_of_horses + 1];
    int winner;

    for (int i=0;i<number_of_horses + 1;i++)
    {horses[i] = 1;}

    int tracklength = 24;
    int finish_line = tracklength - 1;
    int won = 0;

    //print starting track
    printf("\033c");
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
    
    printf("\nbank: %lld\n", player_money);
    printf("\nplace youre bets below people!!!\n");
    long long bet_amount = 0;
    while (bet_amount == 0) {
    printf("\n>:");
    bet_amount = get_bet();}
    player_money = player_money - bet_amount;

    ask_horse:
    printf("\nwhich horse now\v");
    printf("\n>:");
    int horse_player_chose; 
    horse_player_chose = read_int();
    if (horse_player_chose < 1 || horse_player_chose > number_of_horses){
      goto ask_horse;
    }

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

    int secret_num = (gen_random() % number_of_horses) + 1;

    horses[secret_num] += 1;

    if (horses[secret_num] > finish_line){
    horses[secret_num] = finish_line;}

    }
    
    printf("\n");
    printf("horse #%d won\n", winner);
    printf("\n");
    
    if (winner == horse_player_chose){
      player_money += bet_amount * 5;
      printf("you won!!!\n");
      printf("bank: %lld\n", player_money);
    } 
    else {
      printf("\n\nyou lost...\n");
      printf(":(\n");
      printf("bank: %lld\n", player_money);
    }
}
int main(){
  while (player_money > 0){
  printf("\033c");
  printf("bank: %lld\n\n", player_money);
  printf("!!!WELCOME!!!\n");
  printf("to my casino\n\n");
  printf("rules:\n");
  printf("\t*have fun\n");
  printf("\n");

  printf("(1) Roulette\n(2) Horse track\n\n");
  ask:
  printf(">:");
  int choice; 
  choice = read_int();

  if (choice ==  1){roulette();}
  else if (choice == 2){horse_races();}
  else {goto ask;}

  usleep(3000000);
  }
  printf("\033c");
  printf("get out bum\n");

  return 0;
}