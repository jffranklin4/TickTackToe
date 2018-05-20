/* Tick-tack-toe for grade 3
Student Name */
#include <stdio.h>

#define BOARD_SIZE     3

void PrintBoard(int Board[][BOARD_SIZE]);

int main(void)
{
	int Board[BOARD_SIZE][BOARD_SIZE] = { { 0 } };
	int Winner, Moves = 0, YourTurn;

	// Random start
	srand((unsigned)time(NULL));
	YourTurn = rand() % 2 - 1; 		// Random number from -1 to 0, 0=Human and -1 Computer,
									// the negative number is to get complement (~) to work
									// Main game loop
	do
	{
		PrintBoard(Board);
		if (YourTurn)
		{
			Player(Board);
		}
		else
		{
			Computer(Board);
		}

		Winner = CalculateWinner(Board);
		Moves++;
		YourTurn = ~YourTurn;  	// Complement change from 0 -> -1 or -1 -> 0
	} while (Winner == 0 && Moves<BOARD_SIZE*BOARD_SIZE);

	return 0;
} // End of main
