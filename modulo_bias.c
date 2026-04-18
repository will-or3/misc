#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

#define pwd_length 16

const char charset[] =
  "abcdefghijklmnopqrstuvwxyz"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "0123456789"
  "!#$%&'()*+,-./:;<>=?@^_`~";

#define charset_size (sizeof(charset) - 1)

// generate secure random byte
unsigned char secure_random_byte(){
  unsigned char byte;
  if (getrandom(&byte, 1, 0) != 1){
    perror("getrandom");
    exit(1);
  }
  return byte;
}

// generate unbiased random index
int secure_index(int max) {
  int limit = 256 - (256 % max);
  unsigned char byte;

  // avoid modulo bias
  /*
   modulo bias is that its a fixed range of 0-255
   but if you do something like max = 10
   you want 0-9
   but:
   * 256 is not evenly divisible by 10
   * 256 / 10 = 25 remainder 6
   so:
   numbers 0-249 map cleanly to 0-9
   numbers 250-255 create imbalance if you use % 10

   so some outcomes appear more than others
  */
  do {
    byte = secure_random_byte();
  } while (byte >= limit);

  return byte % max;
  
}
int main(){
  char pwd[pwd_length];

  for (int i = 0; i < pwd_length; i++){
    int idx = secure_index(charset_size);
    pwd[i] = charset[idx];
  }

  for (int i=0; i<pwd_length; i++){
    printf("%c", pwd[i]);
  }
  printf("\n");
  
  return 0;
}
