/*Tick Tack Toe by Jesper Franklin */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
#include <ctype.h>

#define BOARD_SIZE     3
// A is 65, B is 66 etc...
#define ASCII_OFFSET    65

struct Actor {
    int human;
    char marker;
};

struct Cell {
    int row;
    int col;
};


/*
 * Get a random integer with the (board size - 1) as upper limit
 */
int getRandomInt() {
    static int first = 1;
    if (first) {
        srand(time(NULL)); //seed first time only!
        first = 0;
    }
    return 0 + rand() % ((BOARD_SIZE));
}

/*
 * Print the board to stdout
 * The board is printed as characters instead of integers
 */
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("\t  %c", (ASCII_OFFSET + i));
    }
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

/*
 * Get a pointer to a Cell struct instance containing a row and col for the board
 *
 * @return Will always return a valid row and col for a move*
 */
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

            // wipe out any '\n' from buffer
            getchar();

            // array indexing starts at 0
            row = row - 1;

            // ensure upper case for ASCII_OFFSET calculation
            col = toupper(colC) - ASCII_OFFSET;

            move->row = row;
            move->col = col;
        } else {
            // Computer is just random
            move->row = getRandomInt(BOARD_SIZE);
            move->col = getRandomInt(BOARD_SIZE);

        }

        // can we make a move at the current cell?
        occupiedCell = board[move->row][move->col] != 0;
        // is the cell within the game board bounds?
        invalidMove = occupiedCell || move->row >= BOARD_SIZE || move->col >= BOARD_SIZE;

        // the computer wouldn't listen if we complained, only show to humans
        if (actor->human && invalidMove) {
            printf("Invalid move\n");
        }

    } while (invalidMove);

    return move;
}

/* Four algorithms to check for horizontal, vertical or diagonal wins
 * A better solution would be to add scores to players during their moves
 * and keep track of the possible winning scores in a hash table (instant lookup)
 * but this is fine for now
 */
int calculateWinner(int board[BOARD_SIZE][BOARD_SIZE]) {
    int winner = 0;

    int recentMarker = 0;

    // check horizontal
    for (int rows = 0; rows < BOARD_SIZE; rows++) {
        // We check one less cell than the board size
        // a win means this value is 1
        int rowIsWon = 1 - BOARD_SIZE + 1;

        for (int cols = 1; cols < BOARD_SIZE; cols++) {
            // check current and previous column
            if (board[rows][cols] != 0 && board[rows][cols] == board[rows][cols - 1]) {
                rowIsWon++;
            }
        }

        if (rowIsWon > 0) {
            winner = 1;
        }
    }

    // check vertical
    for (int cols = 0; cols < BOARD_SIZE; cols++) {

        int colIsWon = 1 - BOARD_SIZE + 1;

        for (int rows = 1; rows < BOARD_SIZE; rows++) {
            // check current and previous row
            if (board[rows][cols] != 0 && board[rows][cols] == board[rows - 1][cols]) {
                colIsWon++;
            }
        }

        if (colIsWon > 0) {
            winner = 1;
        }
    }

    // check diagonal
    for (int rows = 1; rows < BOARD_SIZE; rows++) {

        int diagonalIsWon = 1 - BOARD_SIZE;

        for (int cols = 1; cols < BOARD_SIZE; cols++) {
            // check same and previous diagonally (up one, left one)
            if (board[rows][cols] != 0 && board[rows][cols] == board[rows - 1][cols - 1]) {
                diagonalIsWon++;
            }
        }

        if (diagonalIsWon > 0) {
            winner = 1;
        }
    }

    // check antidiagonal
    for (int rows = BOARD_SIZE - 1; rows > 0; rows--) {

        int antidiagonalIsWon = 1 - BOARD_SIZE + 1;

        for (int cols = 1; cols < BOARD_SIZE; cols++) {
            // check same and previous diagonally (down one, left one)
            if (board[rows][cols] != 0 && board[rows][cols] == board[rows + 1][cols - 1]) {
                antidiagonalIsWon++;
            }
        }

        if (antidiagonalIsWon > 0) {
            winner = 1;
        }
    }

    return winner;
}

int main(void) {
    int board[BOARD_SIZE][BOARD_SIZE] = {{0}};
    int winner, moves = 0, computerTurn;

    struct Actor player, computer;

    // Define actor props
    player.marker = 'O'; // 79
    player.human = 1;

    computer.marker = 'X'; // 88
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

            board[move->row][move->col] = computer.marker;

            printf("\nComputer made his move, your turn!\n");

        } else {

            struct Cell *move = getMove(&player, board);

            board[move->row][move->col] = player.marker;
        }

        winner = calculateWinner(board);
        moves++;
        computerTurn = ~computerTurn;    // Complement change from 0 -> -1 or -1 -> 0
    } while (winner == 0 && moves < BOARD_SIZE * BOARD_SIZE);

    printBoard(board);

    if (moves >= BOARD_SIZE * BOARD_SIZE && !winner) {
        printf("Out of moves, try again\n");
    } else {
        // if it's the computers turn now, you did the winning move
        if (computerTurn) {
            printf("Winner winner chicken dinner!!\n");
        } else {
            printf("Better luck next time!\n");
        }
    }

    return 0;
} // End of main