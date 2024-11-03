#include <ncurses.h>
#include <random>
#include "minesweeper_game.h"

/**
 * @brief Constructs a Minesweeper game board with the specified dimensions and number of mines.
 *
 * @param rows The number of rows in the game board.
 * @param cols The number of columns in the game board.
 * @param num_mines The number of mines to be placed on the game board.
 */
Minesweeper::Minesweeper(const int rows, const int cols, const int num_mines) :
	rows(rows), cols(cols), num_mines(num_mines), board(rows, std::vector<int>(cols, 0)),
	revealed(rows, std::vector<bool>(cols, false)), flagged(rows, std::vector<bool>(cols, false)) {
}

/**
 * @brief Generates the Minesweeper game board with mines and numbers.
 *
 * This function initializes the game board by randomly placing mines and calculating the numbers
 * for each cell that indicate how many mines are adjacent to that cell. The board is represented
 * as a 2D vector of integers, where -1 represents a mine and any non-negative integer represents
 * the count of adjacent mines.
 *
 * The function ensures that the top-left cell (0, 0) is always empty (i.e., contains 0).
 *
 * @note The function assumes that the board dimensions (rows and cols) and the number of mines
 * (num_mines) are already set. It also assumes that the board is initially filled with zeros.
 */
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

/**
 * @brief Reveals the tile at the specified row and column.
 *
 * This function reveals the tile at the given row and column. If the tile is
 * already revealed, flagged, or out of bounds, the function returns immediately.
 * If the tile is not adjacent to any mines (i.e., its value is 0), the function
 * recursively reveals all adjacent tiles.
 *
 * @param row The row index of the tile to reveal.
 * @param col The column index of the tile to reveal.
 */
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

/**
 * @brief Flags or unflags a tile at the specified position.
 *
 * This function toggles the flagged state of a tile at the given row and column.
 * If the specified position is out of bounds or the tile is already revealed,
 * the function does nothing.
 *
 * @param row The row index of the tile to be flagged or unflagged.
 * @param col The column index of the tile to be flagged or unflagged.
 */
void Minesweeper::flag_tile(const int row, const int col) {
	if (row < 0 || row >= rows || col < 0 || col >= cols || revealed[row][col]) {
		return;
	}
	flagged[row][col] = !flagged[row][col];
}

/**
 * @brief Checks if the player has won the game.
 *
 * This function iterates through the entire game board to determine if all non-mine cells have been revealed.
 *
 * @return true if all non-mine cells are revealed, indicating a win.
 * @return false if there are still non-mine cells that are not revealed.
 */
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

/**
 * @brief Initializes the color pairs for the Minesweeper game.
 *
 * This function sets up various color pairs using the ncurses library's
 * start_color() and init_pair() functions. Each color pair consists of a
 * foreground color and a background color, which are used to display
 * different elements of the game with specific colors.
 *
 * Color pairs initialized:
 * - Pair 1: White text on Black background
 * - Pair 2: Red text on Black background
 * - Pair 3: Blue text on Black background
 * - Pair 4: Green text on Black background
 * - Pair 5: Yellow text on Black background
 * - Pair 6: Magenta text on Black background
 * - Pair 7: Cyan text on Black background
 * - Pair 8: Black text on White background
 * - Pair 9: Black text on Red background
 * - Pair 10: Black text on Blue background
 * - Pair 11: Black text on Green background
 * - Pair 12: Black text on Yellow background
 * - Pair 13: Black text on Magenta background
 * - Pair 14: Black text on Cyan background
 * - Pair 15: Black text on White background
 */
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

/**
 * @brief Displays the Minesweeper game board on the screen.
 *
 * This function prints the current state of the Minesweeper game board to the screen,
 * highlighting the cursor position, flagged cells, revealed cells, and mines.
 *
 * @param cursor_row The row index of the cursor position.
 * @param cursor_col The column index of the cursor position.
 */
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

/**
 * @brief Displays the full Minesweeper board with colors.
 *
 * This function initializes the color pairs and then iterates through the entire board,
 * displaying each cell with the appropriate color and symbol. Mines are displayed with
 * an 'X' in a specific color, empty cells are displayed with a dot, and numbered cells
 * are displayed with their respective numbers in different colors.
 *
 * Color pairs:
 * - COLOR_PAIR(1): Empty cells (represented by '·')
 * - COLOR_PAIR(2): Mines (represented by 'X')
 * - COLOR_PAIR(n + 2): Numbered cells (where n is the number on the cell)
 *
 * The function uses the ncurses library for handling colors and screen output.
 */
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
