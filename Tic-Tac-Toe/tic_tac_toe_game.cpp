#include "tic_tac_toe_game.h"
#include <iostream>
#include <ncurses.h>

void TicTacToe::print_board(const char board[3][3]) {
	std::cout << "-------------\n";
	for (int i = 0; i < 3; ++i) {
		std::cout << "| ";
		for (int j = 0; j < 3; ++j) {
			std::cout << board[i][j] << " | ";
		}
		std::cout << "\n-------------\n";
	}
}

void TicTacToe::print_board_ncurses(const char board[3][3], int current_row, int current_col, bool selected) {
	clear();
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == current_row && j == current_col) {
				attron(COLOR_PAIR(1));
				mvprintw(i * 2, j * 4, selected && board[i][j] == '_' ? "[o]" : "[%c]", board[i][j]);
				attroff(COLOR_PAIR(1));
			}
			else {
				mvprintw(i * 2, j * 4, " %c ", board[i][j]);
			}
		}
	}
	refresh();
}

bool TicTacToe::is_moves_left(const char board[3][3]) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (board[i][j] == '_') return true;
	return false;
}

int TicTacToe::evaluate(const char board[3][3]) {
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
