#ifndef MINIMAX_H
#define MINIMAX_H

struct Move {
    int row, col;
};

Move find_best_move(char board[3][3]);

#endif
