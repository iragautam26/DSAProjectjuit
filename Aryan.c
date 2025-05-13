#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char player, computer;
    int result;

    printf("Rock, Paper, Scissors Game!\n");
    printf("Choose:\n r for Rock\n p for Paper\n s for Scissors\n");
    printf("Enter your choice: ");
    scanf(" %c", &player);

    // Validate input
    if (player != 'r' && player != 'p' && player != 's') {
        printf("Invalid input! Please enter r, p, or s.\n");
        return 1;
    }

    // Seed random and get computer's choice
    srand(time(NULL));
    int rand_num = rand() % 3;
    if (rand_num == 0) computer = 'r';
    else if (rand_num == 1) computer = 'p';
    else computer = 's';

    printf("Computer chose: %c\n", computer);

    // Determine result
    if (player == computer) {
        printf("It's a draw!\n");
    } else if ((player == 'r' && computer == 's') ||
               (player == 'p' && computer == 'r') ||
               (player == 's' && computer == 'p')) {
        printf("You win!\n");
    } else {
        printf("Computer wins!\n");
    }

    return 0;
}