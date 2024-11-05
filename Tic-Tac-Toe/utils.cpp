#include <iostream>
#include "tic_tac_toe_game.h"

void print_board(const char board[3][3]) {
    std::cout << "-------------\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "| ";
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << "\n-------------\n";
    }
}

bool is_moves_left(const char board[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == '_')
                return true;
    return false;
}

int evaluate(const char board[3][3]) {
    // Check rows for victory
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'x')
                return +10;
            else if (board[row][0] == 'o')
                return -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'x')
                return +10;
            else if (board[0][col] == 'o')
                return -10;
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'x')
            return +10;
        else if (board[0][0] == 'o')
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'x')
            return +10;
        else if (board[0][2] == 'o')
            return -10;
    }

    // No winner
    return 0;
}
