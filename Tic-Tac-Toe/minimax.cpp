#include <algorithm>
#include "minimax.h"
#include "tic_tac_toe_game.h"

int minimax(char board[3][3], int depth, bool is_max) {
    int score = evaluate(board);

    if (score == 10)
        return score - depth;

    if (score == -10)
        return score + depth;

    if (!is_moves_left(board))
        return 0;

    if (is_max) {
        int best = -1000;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '_') {
                    board[i][j] = 'x';
                    best = std::max(best, minimax(board, depth + 1, !is_max));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '_') {
                    board[i][j] = 'o';
                    best = std::min(best, minimax(board, depth + 1, !is_max));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

Move find_best_move(char board[3][3]) {
    int best_val = -1000;
    Move best_move = { -1, -1 };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '_') {
                board[i][j] = 'x';
                int move_val = minimax(board, 0, false);
                board[i][j] = '_';

                if (move_val > best_val) {
                    best_move.row = i;
                    best_move.col = j;
                    best_val = move_val;
                }
            }
        }
    }

    return best_move;
}
