#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  double sum = 0.0;

  if (argc > 1){
    for (int i = 1; i < argc; i++)
      sum += atof(argv[i]);
  } else {
    double x;
    while (scanf("%lf", &x) == 1)  // reads double from stdin
      sum += x;
  }

  printf("%g\n", sum);
  return 0;
}
