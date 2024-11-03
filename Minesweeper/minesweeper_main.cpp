#include <clocale>
#include <iostream>
#include <limits>
#include <ncurses.h>
#include "minesweeper_game.h"
#include "player.h"

/**
 * @brief Main function for the Minesweeper game.
 *
 * This function initializes the game state, prompts the user to select a difficulty level,
 * and starts the Minesweeper game loop. The game loop handles user input for moving the
 * cursor, flagging tiles, and revealing tiles. The game ends when the player either hits
 * a mine or successfully reveals all non-mine tiles.
 *
 * User controls:
 * - 'w': Move cursor up
 * - 's': Move cursor down
 * - 'a': Move cursor left
 * - 'd': Move cursor right
 * - 'f': Flag a tile
 * - 'r': Reveal a tile
 * - 'q': Quit the game
 *
 * The game displays a "Game Over" message if the player hits a mine, and a "Congratulations"
 * message if the player successfully reveals all non-mine tiles.
 */
void minesweeper_main() {
	setlocale(LC_ALL, "");
	extern Player player;
	player.game_state = 2;
	player.player_minesweeper_win = false;
	player.player_x_minesweeper = 0;
	player.player_y_minesweeper = 0;

	const std::vector<std::vector<int>> difficulties = {{10, 10, 20}, {16, 16, 40}, {16, 30, 80}};
	int difficulty = 0;

	std::cout << "Select difficulty:" << std::endl;
	std::cout << "1. Easy" << std::endl;
	std::cout << "2. Medium" << std::endl;
	std::cout << "3. Hard" << std::endl;
	std::cout << "Choose a difficulty: ";
	while (true) {
		std::cin >> difficulty;
		if (std::cin.fail() || difficulty < 1 || difficulty > 3) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid choice. Please enter a number between 1 and 3: ";
		}
		else {
			break;
		}
	}
	Minesweeper game(difficulties[difficulty - 1][0], difficulties[difficulty - 1][1], difficulties[difficulty - 1][2]);
	game.generate_board();

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	while (true) {
		clear();
		game.display_board(player.player_y_minesweeper, player.player_x_minesweeper);
		refresh();
		char user_input = getch();
		if (user_input == ERR) {
			continue;
		}

		if (user_input == 'q') {
			break;
		}
		else if (user_input == 'f') {
			game.flag_tile(player.player_y_minesweeper, player.player_x_minesweeper);
		}
		else if (user_input == 'r') {
			game.reveal_tile(player.player_y_minesweeper, player.player_x_minesweeper);
			if (game.board[player.player_y_minesweeper][player.player_x_minesweeper] == -1) {
				clear();
				printw("Game Over! You hit a mine.\nPress any key to exit.\nMine locations:\n");
				game.display_full_board();
				refresh();
				getch();
				break;
			}
		}
		else if (user_input == 'w') {
			player.player_y_minesweeper =
				(player.player_y_minesweeper > 0) ? player.player_y_minesweeper - 1 : player.player_y_minesweeper;
		}
		else if (user_input == 's') {
			player.player_y_minesweeper = (player.player_y_minesweeper < game.rows - 1)
				? player.player_y_minesweeper + 1
				: player.player_y_minesweeper;
		}
		else if (user_input == 'a') {
			player.player_x_minesweeper =
				(player.player_x_minesweeper > 0) ? player.player_x_minesweeper - 1 : player.player_x_minesweeper;
		}
		else if (user_input == 'd') {
			player.player_x_minesweeper = (player.player_x_minesweeper < game.cols - 1)
				? player.player_x_minesweeper + 1
				: player.player_x_minesweeper;
		}
		refresh();

		if (game.check_win()) {
			clear();
			printw("Congratulations! You won the game.\nPress any key to exit.");
			refresh();
			getch();
			break;
		}
	}

	endwin();
}
