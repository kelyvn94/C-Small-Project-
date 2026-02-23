#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void displayBoard(char board[3][3]);
void playerMove(char board[3][3], char player);
int checkWin(char board[3][3], char player);
int isBoardFull(char board[3][3]);

int main() {
    char board[3][3];
    char currentPlayer = 'X';
    int gameOver = 0;
    int moves = 0;

    // Initialize board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    printf("=== Tic-Tac-Toe ===\n");
    printf("Positions are numbered 1-9 (top-left to bottom-right)\n\n");

    while (!gameOver) {
        system("cls");
        displayBoard(board);
        playerMove(board, currentPlayer);
        moves++;

        if (checkWin(board, currentPlayer)) {
            system("cls");
            displayBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            gameOver = 1;
        } else if (isBoardFull(board)) {
            system("cls");
            displayBoard(board);
            printf("It's a tie!\n");
            gameOver = 1;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}

void displayBoard(char board[3][3]) {
    printf(" 1 | 2 | 3\n");
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

void playerMove(char board[3][3], char player) {
    int position;
    int valid = 0;

    while (!valid) {
        printf("Player %c, enter position (1-9): ", player);
        scanf("%d", &position);

        if (position < 1 || position > 9) {
            printf("Invalid position!\n");
            continue;
        }

        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        if (board[row][col] != ' ') {
            printf("Position already taken!\n");
        } else {
            board[row][col] = player;
            valid = 1;
        }
    }
}

int checkWin(char board[3][3], char player) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return 1;
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;

    return 0;
}

int isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}