#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define SHIP_COUNT 5
#define EMPTY 0
#define SHIP 1
#define HIT 2
#define MISS 3

// Declare the game boards
int playerBoard[SIZE][SIZE];
int computerBoard[SIZE][SIZE];
int computerHitBoard[SIZE][SIZE];

// Function to initialize the boards
void initializeBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Function to print the game board
void printBoard(int board[SIZE][SIZE], int showShips) {
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%2d", i + 1);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (showShips == 1 && board[i][j] == SHIP) {
                printf(" S"); // Hide ships
            } else if (board[i][j] == HIT) {
                printf(" X");
            } else if (board[i][j] == MISS) {
                printf(" O");
            } else {
                printf(" .");
            }
        }
        printf("\n");
    }
}

// Function to place ships randomly on the board
void placeShips(int board[SIZE][SIZE], int shipCount) {
    int shipsPlaced = 0;
    srand(time(NULL));

    while (shipsPlaced < shipCount) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (board[row][col] == EMPTY) {
            board[row][col] = SHIP;
            shipsPlaced++;
        }
    }
}

// Function to take the player's shot
int takeShot(int board[SIZE][SIZE], int row, int col) {
    if (board[row][col] == SHIP) {
        board[row][col] = HIT;
        return 1; // Hit
    } else if (board[row][col] == EMPTY) {
        board[row][col] = MISS;
        return 0; // Miss
    }
    return -1; // Already shot there
}

// Function for the computer to take a shot
int computerShot(int board[SIZE][SIZE]) {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (board[row][col] == HIT || board[row][col] == MISS);

    if (board[row][col] == SHIP) {
        board[row][col] = HIT;
        return 1; // Hit
    } else {
        board[row][col] = MISS;
        return 0; // Miss
    }
}

// Function to check if the game is over
int checkGameOver(int board[SIZE][SIZE], int shipCount) {
    int shipsRemaining = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == SHIP) {
                shipsRemaining++;
            }
        }
    }
    return shipsRemaining == 0;
}

// Function to play a single game round
void playGame() {
    int playerRow, playerCol;
    int playerScore = 0;
    int computerScore = 0;

    // Initialize both boards
    initializeBoard(playerBoard);
    initializeBoard(computerBoard);
    initializeBoard(computerHitBoard);

    // Place ships on both boards
    placeShips(playerBoard, SHIP_COUNT);
    placeShips(computerBoard, SHIP_COUNT);

    printf("Welcome to Battleship!\n");

    // Game loop
    while (1) {
        // Print both boards (hide player's ships)
        printf("\nYour Board:\n");
        printBoard(playerBoard, 1);  // Show player's ships
        printf("\nComputer's Board (Hidden Ships):\n");
        printBoard(computerHitBoard, 0);  // Hide computer's ships

        // Player's turn
        printf("\nYour turn! Enter row and column (1-10): ");
        scanf("%d %d", &playerRow, &playerCol);
        playerRow--; playerCol--;  // Adjust for 0-based indexing

        if (playerRow >= 0 && playerRow < SIZE && playerCol >= 0 && playerCol < SIZE) {
            if (takeShot(computerHitBoard, playerRow, playerCol) == 1) {
                printf("You hit a ship!\n");
                playerScore++;
            } else {
                printf("You missed!\n");
            }
        } else {
            printf("Invalid coordinates. Try again.\n");
            continue;
        }

        // Check if the player has won
        if (checkGameOver(computerHitBoard, SHIP_COUNT)) {
            printBoard(computerHitBoard, 0);
            printf("Congratulations! You won the game!\n");
            break;
        }

        // Computer's turn
        printf("\nComputer's turn...\n");
        if (computerShot(playerBoard) == 1) {
            printf("The computer hit your ship!\n");
            computerScore++;
        } else {
            printf("The computer missed!\n");
        }

        // Check if the computer has won
        if (checkGameOver(playerBoard, SHIP_COUNT)) {
            printBoard(playerBoard, 0);
            printf("Sorry, the computer won the game!\n");
            break;
        }
    }
}

// Main function to start the game and loop for replay
int main() {
    char playAgain;
    do {
        playGame();

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);  // Note the space before %c to consume any trailing newline
    } while (playAgain == 'y' || playAgain == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}
