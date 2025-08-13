#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	srand(time(NULL));
	const char *dict[] = {"", "rock", "paper", "scissors"};
	int robot = rand() % 3 + 1;
	int play;
	printf("rock(1), paper(2), scissors(3) >:");
	scanf("%d", &play);
	int rps = play - robot;
	printf("robot chose %s\n", dict[robot]);
	if (rps > 0 && rps != -2) {
		printf("you won!\n");
	} else if (rps == -2) {printf("you won!\n");
	} else if (rps == -1) {printf("you lost :(\n");
	} else if (rps == 0) {printf("tie\n");
	} else {
		printf("pick one of the #'s gngy\n");
	}
}
