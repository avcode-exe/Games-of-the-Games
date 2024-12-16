#ifndef MINIMAX_H
#define MINIMAX_H

struct Move {
	int row, col;
};

class Minimax {
public:
	Move find_best_move(char board[3][3]);

private:
	int minimax(char board[3][3], int depth, bool is_max);
};

#endif
