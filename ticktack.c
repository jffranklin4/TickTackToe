/*Tick Tack Toe by Jesper Franklin */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
#include <ctype.h>

#define BOARD_SIZE     3
// A is 65, B is 66 etc...
#define ASCII_OFFSET    65;

struct Actor {
    int human;
    char icon;
};

struct Cell {
    int row;
    int col;
};

int randInt(int max) //range : [min, max)
{
    static int first = 1;
    if (first) {
        srand(time(NULL)); //seeding for the first time only!
        first = 0;
    }
    return 0 + rand() % ((max + 1));
}

void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    // Print column labels (A, B, C) (TODO: only for board size 3)
    printf("\n\t  A\t  B\t  C");
    printf("\n");
    for (int rows = 0; rows < BOARD_SIZE; rows++) {
        /* Print row
         * Start with row label
         */
        printf("%d\t", rows + 1);
        for (int cols = 0; cols < BOARD_SIZE; cols++) {

            if (cols < BOARD_SIZE - 1) {
                printf(": %c ", board[rows][cols]);
            } else {
                printf(": %c :", board[rows][cols]);
            }
        }

        printf("\n");
    }
}

struct Cell *getMove(struct Actor *actor, int board[BOARD_SIZE][BOARD_SIZE]) {
    int invalidMove = 0;
    struct Cell *move = malloc(sizeof *move);

    do {
        int occupiedCell = 0;

        if (actor->human) {
            int row = 0;
            char colC = 'A';
            int col = 0;
            printf("Make your move (e.g. A1): ");
            scanf("%c%d", &colC, &row);

            // array indexing starts at 0
            row = row - 1;

            // ensure upper case
            colC = toupper(colC);
            col = (int) colC - ASCII_OFFSET;

            move->row = row;
            move->col = col;
        } else {
            move->row = randInt(BOARD_SIZE - 1);
            move->col = randInt(BOARD_SIZE - 1);

        }

        occupiedCell = board[move->row][move->col] != 0;
        invalidMove = occupiedCell || move->row >= BOARD_SIZE || move->col >= BOARD_SIZE;

        if(actor->human && invalidMove) {
            printf("Invalid move\n");
        }

    } while (invalidMove);

    return move;
}

int main(void) {
    int board[BOARD_SIZE][BOARD_SIZE] = {{0}};
    int winner, moves = 0, computerTurn;

    struct Actor player, computer;

    // Define actor props
    player.icon = 'O';
    player.human = 1;

    computer.icon = 'X';
    computer.human = 0;

    // Random start
    srand((unsigned) time(NULL));
    computerTurn = rand() % 2 - 1;        // Random number from -1 to 0, 0=Human and -1 Computer,
    // the negative number is to get complement (~) to work


    // Main game loop
    do {
        printBoard(board);

        if (computerTurn) {

            struct Cell *move = getMove(&computer, board);

            board[move->row][move->col] = computer.icon;

            printf("\nComputer made his move, your turn!\n");

        } else {

            struct Cell *move = getMove(&player, board);

            board[move->row][move->col] = player.icon;
        }

//        winner = CalculateWinner(board);
        moves++;
        computerTurn = ~computerTurn;    // Complement change from 0 -> -1 or -1 -> 0
    } while (winner == 0 && moves < BOARD_SIZE * BOARD_SIZE);

    return 0;
} // End of main