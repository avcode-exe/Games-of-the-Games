#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

void print_board(const char board[3][3]);
bool is_moves_left(const char board[3][3]);
int evaluate(const char board[3][3]);

#endif
