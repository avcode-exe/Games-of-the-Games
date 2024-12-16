#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include "Snake/snake_game.h"
#include "game_header.h"

const int MENU_WIDTH = 30;
const int MENU_HEIGHT = 10;
const int BORDER_PADDING = 2;

/**
 * @brief Displays an interactive menu using ncurses.
 *
 * Allows the user to navigate the menu with arrow keys and select a game.
 *
 * @param games A vector of strings containing the names of the available games.
 * @return The index of the selected game (0-based), or -1 if the user quits.
 */
int display_menu_ncurses(const std::vector<std::string>& games) {
	if (initscr() == NULL) {
		fprintf(stderr, "Error initializing ncurses.\n");
		exit(EXIT_FAILURE);
	}
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	int selected_item = 0;
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	std::vector<std::string> menu_items = games;
	menu_items.push_back("Quit / Exit");

	while (true) {
		clear();
		mvprintw(max_y / 2 - MENU_HEIGHT / 2, max_x / 2 - MENU_WIDTH / 2, "Welcome to Games of the Games!");
		box(stdscr, 0, 0); // Add border

		for (size_t i = 0; i < menu_items.size(); ++i) {
			if (i == selected_item) {
				mvprintw(max_y / 2 - MENU_HEIGHT / 2 + i + BORDER_PADDING, max_x / 2 - MENU_WIDTH / 2 + BORDER_PADDING,
						 "> %s", menu_items[i].c_str());
			}
			else {
				mvprintw(max_y / 2 - MENU_HEIGHT / 2 + i + BORDER_PADDING,
						 max_x / 2 - MENU_WIDTH / 2 + 2 * BORDER_PADDING, "  %s", menu_items[i].c_str());
			}
		}

		mvprintw(max_y / 2 + MENU_HEIGHT / 2, max_x / 2 - MENU_WIDTH / 2 + BORDER_PADDING,
				 "Use arrow keys to navigate");
		mvprintw(max_y / 2 + MENU_HEIGHT / 2 + 1, max_x / 2 - MENU_WIDTH / 2 + BORDER_PADDING, "Press Enter to select");

		refresh();

		int ch = getch();

		switch (ch) {
		case KEY_UP:
			selected_item = (selected_item - 1 + menu_items.size()) % menu_items.size();
			break;
		case KEY_DOWN:
			selected_item = (selected_item + 1) % menu_items.size();
			break;
		case 10: // Enter key
			endwin();
			return selected_item;
		}
	}
}

enum GameChoice { MAZE, MINESWEEPER, TWO_ZERO_FOUR_EIGHT, TIC_TAC_TOE, SNAKE, QUIT };

void (*game_functions[])(void) = {maze_main, minesweeper_main, two_zero_four_eight_main, tic_tac_toe_main, snake_main};

int main() {
	const std::vector<std::string> games = {"Maze", "Minesweeper", "2048", "Tic-Tac-Toe", "Snake"};

	while (true) {
		int choice = display_menu_ncurses(games);

		if (choice == games.size()) {
			clear();
			int max_y, max_x;
			getmaxyx(stdscr, max_y, max_x);
			mvprintw(max_y / 2, (max_x - 10) / 2, "Thanks for playing!");
			mvprintw(max_y / 2 + 1, (max_x - 10) / 2 - 2, "Press any key to exit...");
			box(stdscr, 0, 0); // Add border
			refresh();
			getch();
			endwin();
			break;
		}
		else {
			clear();
			game_functions[choice]();
		}
		refresh();
	}

	return 0;
}
