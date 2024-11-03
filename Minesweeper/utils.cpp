#include <ncurses.h>
#include <random>
#include "minesweeper_game.h"

Minesweeper::Minesweeper(const int rows, const int cols, const int num_mines) :
	rows(rows), cols(cols), num_mines(num_mines), board(rows, std::vector<int>(cols, 0)),
	revealed(rows, std::vector<bool>(cols, false)), flagged(rows, std::vector<bool>(cols, false)) {
}

void Minesweeper::generate_board() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis_rows(0, rows - 1);
	std::uniform_int_distribution<int> dis_cols(0, cols - 1);
	int mines_placed = 0;
	while (mines_placed < num_mines) {
		const int row = dis_rows(gen);
		if (const int col = dis_cols(gen); board[row][col] == 0) {
			bool surrounded_by_mines = true;
			for (int dr = -1; dr <= 1; dr++) {
				for (int dc = -1; dc <= 1; dc++) {
					const int nr = row + dr;
					if (const int nc = col + dc; nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc] != -1) {
						surrounded_by_mines = false;
						break;
					}
				}
				if (!surrounded_by_mines) break;
			}
			if (surrounded_by_mines) continue;

			board[row][col] = -1;
			mines_placed++;
		}
	}

	board[0][0] = 0;

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (board[r][c] == -1) continue;
			int mine_count = 0;
			for (int dr = -1; dr <= 1; dr++) {
				for (int dc = -1; dc <= 1; dc++) {
					const int nr = r + dr;
					if (const int nc = c + dc; nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc] == -1) {
						mine_count++;
					}
				}
			}
			board[r][c] = mine_count;
		}
	}
}

void Minesweeper::reveal_tile(const int row, const int col) {
	if (row < 0 || row >= rows || col < 0 || col >= cols || revealed[row][col] || flagged[row][col]) {
		return;
	}
	revealed[row][col] = true;
	if (board[row][col] == 0) {
		for (int dr = -1; dr <= 1; dr++) {
			for (int dc = -1; dc <= 1; dc++) {
				reveal_tile(row + dr, col + dc);
			}
		}
	}
}

void Minesweeper::flag_tile(const int row, const int col) {
	if (row < 0 || row >= rows || col < 0 || col >= cols || revealed[row][col]) {
		return;
	}
	flagged[row][col] = !flagged[row][col];
}

bool Minesweeper::check_win() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (board[r][c] != -1 && !revealed[r][c]) {
				return false;
			}
		}
	}
	return true;
}

void Minesweeper::initialize_colors() {
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_BLUE);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_BLACK, COLOR_YELLOW);
	init_pair(13, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(14, COLOR_BLACK, COLOR_CYAN);
	init_pair(15, COLOR_BLACK, COLOR_WHITE);
}

void Minesweeper::display_board(const int cursor_row, const int cursor_col) {
	initialize_colors();
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (r == cursor_row && c == cursor_col) {
				attron(COLOR_PAIR(5));
				printw("# ");
				attroff(COLOR_PAIR(5));
			}
			else if (flagged[r][c]) {
				attron(COLOR_PAIR(9));
				printw("F ");
				attroff(COLOR_PAIR(9));
			}
			else if (!revealed[r][c]) {
				attron(COLOR_PAIR(1));
				printw("· ");
				attroff(COLOR_PAIR(1));
			}
			else if (board[r][c] == -1) {
				attron(COLOR_PAIR(2));
				printw("X ");
				attroff(COLOR_PAIR(2));
			}
			else if (board[r][c] == 0) {
				attron(COLOR_PAIR(1));
				printw("  ");
				attroff(COLOR_PAIR(1));
			}
			else {
				attron(COLOR_PAIR(board[r][c] + 2));
				printw("%d ", board[r][c]);
				attroff(COLOR_PAIR(board[r][c] + 2));
			}
		}
		printw("\n");
	}
	refresh();
}

void Minesweeper::display_full_board() {
	initialize_colors();
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (board[r][c] == -1) {
				attron(COLOR_PAIR(2));
				printw("X ");
				attroff(COLOR_PAIR(2));
			}
			else if (board[r][c] == 0) {
				attron(COLOR_PAIR(1));
				printw("· ");
				attroff(COLOR_PAIR(1));
			}
			else {
				attron(COLOR_PAIR(board[r][c] + 2));
				printw("%d ", board[r][c]);
				attroff(COLOR_PAIR(board[r][c] + 2));
			}
		}
		printw("\n");
	}
	refresh();
}