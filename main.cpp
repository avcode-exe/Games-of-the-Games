#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "game_header.h"
#include "Snake/snake_game.h"

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
        mvprintw(max_y / 2 - 4, max_x / 2 - 15, "Welcome to Games of the Games!");
        box(stdscr, 0, 0); // Add border

        for (size_t i = 0; i < menu_items.size(); ++i) {
            if (i == selected_item) {
                mvprintw(max_y / 2 - 2 + i, max_x / 2 - 15, "> %s", menu_items[i].c_str());
            } else {
                mvprintw(max_y / 2 - 2 + i, max_x / 2 - 13, "  %s", menu_items[i].c_str());
            }
        }

        mvprintw(max_y / 2 + menu_items.size(), max_x / 2 - 15, "Use arrow keys to navigate");
        mvprintw(max_y / 2 + menu_items.size() + 1, max_x / 2 - 15, "Press Enter to select");

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
        } else {
            clear();
            if (choice == 0) {
                maze_main();
            } else if (choice == 1) {
                minesweeper_main();
            } else if (choice == 2) {
                two_zero_four_eight_main();
            } else if (choice == 3) {
                tic_tac_toe_main();
            } else if (choice == 4) {
                snake_main();
            }
        }
        refresh();
    }

    return 0;
}
