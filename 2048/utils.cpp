#include <ncurses.h>
#include <random>
#include "2048_game.h"

/**
 * @brief Constructs a new TwoZeroFourEight object with the specified board size.
 *
 * This constructor initializes the game board to the given size, sets the player's score to zero,
 * and places two initial tiles on the board at random positions. Each tile will be either a 2 or a 4.
 *
 * @param size The size of the game board (both width and height).
 */
TwoZeroFourEight::TwoZeroFourEight(const int size) {
	map_size = size;
	score = 0;
	board = std::vector<std::vector<int>>(map_size, std::vector<int>(map_size, 0));
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(0, map_size - 1);
	for (int i = 0; i < 2; ++i) {
		int x, y;
		do {
			x = dis(gen);
			y = dis(gen);
		}
		while (board[x][y] != 0);
		board[x][y] = (dis(gen) % 2 + 1) * 2;
	}
}

/**
 * @brief Draws the current state of the 2048 game board on the screen.
 *
 * This function clears the screen and then iterates through the game board,
 * printing each tile with a color corresponding to its value. The color pairs
 * are determined as follows:
 * - 0: Color pair 1
 * - Values greater than 2048: Color pair 8
 * - Other values: Color pair calculated based on the value
 *
 * After drawing the board, the player's current score is displayed below the board.
 */
void TwoZeroFourEight::draw_board() {
	clear();
	for (int i = 0; i < map_size; ++i) {
		for (int j = 0; j < map_size; ++j) {
			int value = board[i][j];
			int color_pair = value == 0 ? 1 : (value > 2048 ? 8 : (value / 2) % 7 + 2);
			attron(COLOR_PAIR(color_pair));
			mvprintw(i, j * 5, "%4d", value);
			attroff(COLOR_PAIR(color_pair));
		}
	}
	mvprintw(map_size, 0, "Score: %d", score);
	refresh();
}

/**
 * @brief Moves all tiles on the board to the left.
 *
 * This function iterates through each row of the board and shifts all non-zero tiles to the left.
 * If two adjacent tiles have the same value, they are merged into one tile with double the value,
 * and the player's score is updated accordingly. The function returns true if any tiles were moved
 * or merged, and false otherwise.
 *
 * @return bool - True if any tiles were moved or merged, false otherwise.
 */
bool TwoZeroFourEight::move_left() {
	bool moved = false;
	for (int i = 0; i < map_size; ++i) {
		std::vector<int> new_row(map_size, 0);
		int pos = 0;
		for (int j = 0; j < map_size; ++j) {
			if (board[i][j] != 0) {
				if (pos > 0 && new_row[pos - 1] == board[i][j]) {
					new_row[pos - 1] *= 2;
					score += new_row[pos - 1];
					moved = true;
				}
				else {
					if (pos != j) moved = true;
					new_row[pos++] = board[i][j];
				}
			}
		}
		board[i] = new_row;
	}
	return moved;
}

/**
 * @brief Moves all tiles on the board to the right.
 *
 * This function iterates through each row of the board and shifts all non-zero tiles to the right.
 * If two adjacent tiles have the same value, they are merged into one tile with double the value,
 * and the player's score is updated accordingly. The function returns true if any tiles were moved
 * or merged, and false otherwise.
 *
 * @return true if any tiles were moved or merged, false otherwise.
 */
bool TwoZeroFourEight::move_right() {
	bool moved = false;
	for (int i = 0; i < map_size; ++i) {
		std::vector<int> new_row(map_size, 0);
		int pos = map_size - 1;
		for (int j = map_size - 1; j >= 0; --j) {
			if (board[i][j] != 0) {
				if (pos < map_size - 1 && new_row[pos + 1] == board[i][j]) {
					new_row[pos + 1] *= 2;
					score += new_row[pos + 1];
					moved = true;
				}
				else {
					if (pos != j) moved = true;
					new_row[pos--] = board[i][j];
				}
			}
		}
		board[i] = new_row;
	}
	return moved;
}

/**
 * @brief Moves the tiles on the board upwards, combining tiles of the same value.
 *
 * This function iterates through each column of the board, moving all non-zero tiles upwards.
 * If two adjacent tiles have the same value, they are combined into one tile with double the value,
 * and the player's score is increased by the value of the new tile. The function returns true if
 * any tiles were moved or combined, and false otherwise.
 *
 * @return true if any tiles were moved or combined, false otherwise.
 */
bool TwoZeroFourEight::move_up() {
	bool moved = false;
	for (int j = 0; j < map_size; ++j) {
		std::vector<int> new_col(map_size, 0);
		int pos = 0;
		for (int i = 0; i < map_size; ++i) {
			if (board[i][j] != 0) {
				if (pos > 0 && new_col[pos - 1] == board[i][j]) {
					new_col[pos - 1] *= 2;
					score += new_col[pos - 1];
					moved = true;
				}
				else {
					if (pos != i) moved = true;
					new_col[pos++] = board[i][j];
				}
			}
		}
		for (int i = 0; i < map_size; ++i) {
			board[i][j] = new_col[i];
		}
	}
	return moved;
}

/**
 * @brief Moves the tiles on the board downwards, combining tiles as needed.
 *
 * This function iterates over each column of the board and shifts all non-zero
 * tiles downwards. If two adjacent tiles in the same column have the same value,
 * they are combined into one tile with double the value, and the player's score
 * is updated accordingly. The function returns true if any tiles were moved or
 * combined, and false otherwise.
 *
 * @return bool - True if any tiles were moved or combined, false otherwise.
 */
bool TwoZeroFourEight::move_down() {
	bool moved = false;
	for (int j = 0; j < map_size; ++j) {
		std::vector<int> new_col(map_size, 0);
		int pos = map_size - 1;
		for (int i = map_size - 1; i >= 0; --i) {
			if (board[i][j] != 0) {
				if (pos < map_size - 1 && new_col[pos + 1] == board[i][j]) {
					new_col[pos + 1] *= 2;
					score += new_col[pos + 1];
					moved = true;
				}
				else {
					if (pos != i) moved = true;
					new_col[pos--] = board[i][j];
				}
			}
		}
		for (int i = 0; i < map_size; ++i) {
			board[i][j] = new_col[i];
		}
	}
	return moved;
}

/**
 * @brief Checks if there are any possible moves left on the 2048 game board.
 *
 * This function iterates through the entire game board and checks for the following conditions:
 * 1. If there is any empty cell (value 0) on the board.
 * 2. If there are any adjacent cells (horizontally or vertically) with the same value.
 *
 * @return true if there is at least one possible move left (either an empty cell or adjacent cells with the same
 * value).
 * @return false if there are no possible moves left.
 */
bool TwoZeroFourEight::can_move() const {
	for (int i = 0; i < map_size; ++i) {
		for (int j = 0; j < map_size; ++j) {
			if (board[i][j] == 0) return true;
			if (i > 0 && board[i][j] == board[i - 1][j]) return true;
			if (i < map_size - 1 && board[i][j] == board[i + 1][j]) return true;
			if (j > 0 && board[i][j] == board[i][j - 1]) return true;
			if (j < map_size - 1 && board[i][j] == board[i][j + 1]) return true;
		}
	}
	return false;
}

/**
 * @brief Adds a random tile to the board.
 *
 * This function generates a random position on the board and places a new tile
 * with a value of either 2 or 4 in an empty spot. It uses a random device to
 * seed the random number generator and ensures that the selected position is
 * empty before placing the new tile.
 */
void TwoZeroFourEight::add_random_tile() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, map_size - 1);
	int x, y;
	do {
		x = dis(gen);
		y = dis(gen);
	}
	while (board[x][y] != 0);
	board[x][y] = (dis(gen) % 2 + 1) * 2;
}
