/*Tick Tack Toe by Jesper Franklin */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define boardsizeY
#define boardsizeX

int main(void)
{
	srand(time(NULL));
	int RNumber(void);                                                  /*Kallar på slumpnummer funktionen*/
	char GamingBoard[boardsizeY][boardsizeX];

	printf_s("Welcome, can you beat the computer in a game of Tick Tack Toe?\n");





	while (getchar() != EOF)
	(1 == 1);
	return 0;
}

int RNumber(void)
{
	int r = 1 + (rand() % 3);
	return r;
}