#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

class TicTacToe {
public:
    void print_board(const char board[3][3]);
    void print_board_ncurses(const char board[3][3], int current_row, int current_col, bool selected);
    bool is_moves_left(const char board[3][3]);
    int evaluate(const char board[3][3]);
};

#endif
