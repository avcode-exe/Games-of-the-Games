#include <iostream>
#include "tic_tac_toe_game.h"
#include "minimax.h"

void tic_tac_toe_main() {
    char board[3][3] = {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

    print_board(board);

    while (true) {
        int row, col;
        std::cout << "Enter your move (row and column): ";
        std::cin >> row >> col;

        if (board[row][col] != '_') {
            std::cout << "Invalid move. Try again.\n";
            continue;
        }

        board[row][col] = 'o';
        print_board(board);

        if (evaluate(board) == -10) {
            std::cout << "You win!\n";
            break;
        }

        if (!is_moves_left(board)) {
            std::cout << "It's a draw!\n";
            break;
        }

        Move best_move = find_best_move(board);
        board[best_move.row][best_move.col] = 'x';
        print_board(board);

        if (evaluate(board) == 10) {
            std::cout << "AI wins!\n";
            break;
        }

        if (!is_moves_left(board)) {
            std::cout << "It's a draw!\n";
            break;
        }
    }
}
