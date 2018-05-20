/*Tick Tack Toe by Jesper Franklin */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>

#define BOARD_SIZE     3

struct Actor {
    char icon;
};

void printBoard(int board[][BOARD_SIZE]) {
    // Print column labels (A, B, C) (TODO: only for board size 3)
    printf("\t  A\t  B\t  C");
    printf("\n");
    for (int rows = 0; rows < BOARD_SIZE; rows++) {
        /* Print row
         * Start with row label
         */
        printf("%d\t", rows + 1);
        for (int cols = 0; cols < BOARD_SIZE; cols++) {

            if (cols < BOARD_SIZE - 1) {
                printf(": %d ", board[rows][cols]);
            } else {
                printf(": %d :", board[rows][cols]);
            }
        }

        printf("\n");
    }
}

int main(void) {
    int board[BOARD_SIZE][BOARD_SIZE] = {{0}};
    int winner, moves = 0, computerTurn;

    struct Actor player, computer;

    // Random start
    srand((unsigned) time(NULL));
    computerTurn = rand() % 2 - 1;        // Random number from -1 to 0, 0=Human and -1 Computer,
    // the negative number is to get complement (~) to work
    // Main game loop
    do {
        printBoard(board);
        if (computerTurn) {
//            Computer(board);
        } else {
            int d;
            scanf("%d", &d);
            printf("%d", d);
//            Player(board);
        }

//        winner = CalculateWinner(board);
        moves++;
        computerTurn = ~computerTurn;    // Complement change from 0 -> -1 or -1 -> 0
    } while (winner == 0 && moves < BOARD_SIZE * BOARD_SIZE);

    return 0;
} // End of main