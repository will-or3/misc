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

void roulette(){
  printf("\033c");
  printf("balance: %lld\n\n", player_money);
  printf("welcome to the roulette table\nplace your bet below\n\n");

  long long bet_amount = 0;

  while (bet_amount == 0) {
    printf(">:");
    bet_amount = get_bet();
  }

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
  fgets(user_bet, sizeof(user_bet), stdin);

  size_t len = strlen(user_bet);
  if (len > 0 && user_bet[len - 1] == '\n') {
      user_bet[len - 1] = '\0';
  }

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
  // gen random num
  uint32_t r;

    // get 4 rand bytes
    if (getrandom(&r, sizeof(r), 0) != sizeof(r)) {
        perror("getrandom");
        exit(1);
    }
    int secret_num = r % 37;

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
      printf("you won!!!");
      printf("bank: %lld\n", player_money);
    }
    else if (key == 2 && black == 1){
      player_money += bet_amount * 2;
      printf("you won!!!");
      printf("bank: %lld\n", player_money);
    }
    else if (key == 5 && green == 1){
      player_money += bet_amount * 2;
      printf("you won!!!");
      printf("bank: %lld\n", player_money);
    }
    else if (secret_num % 2 == 0 && key == 4){
      player_money += bet_amount * 2;
      printf("you won!!!");
      printf("bank: %lld\n", player_money);
    }
    else if (secret_num % 2 != 0 && key == 3){
      player_money += bet_amount * 2;
      printf("you won!!!");
      printf("bank: %lld\n", player_money);
    }
    else {
      player_money = player_money - bet_amount;
      printf("\n\nyou lost...\n");
      printf(":(\n");
      printf("bank: %lld\n", player_money);
    }
  }
  else if (user_bet_single != -1){
    if (user_bet_single == secret_num){
      player_money += bet_amount * 35;
      printf("you won!!!");
      printf("bank: %lld\n", player_money);
    }
    else {
      player_money = player_money - bet_amount;
      printf("\n\nyou lost...\n");
      printf(":(\n");
      printf("bank: %lld\n", player_money);
    }
  }

}

int main(){
  roulette();
  return 0;
}
