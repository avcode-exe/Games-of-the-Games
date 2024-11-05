#include <iostream>
#include <limits>
#include <ncurses.h>
#include "2048_game.h"

/**
 * @brief Main function for the 2048 game.
 *
 * This function initializes the game, sets up the difficulty level, and handles
 * the main game loop. The user is prompted to select a difficulty level, which
 * determines the size of the game board. The game is played using the keyboard
 * to move tiles in four directions: left, right, up, and down. The game continues
 * until the player can no longer make any moves or chooses to quit.
 *
 * @return int Returns 0 upon successful completion of the game.
 */
int TwoZeroFourEight_main() {
    int difficulty = 0;
    const std::vector<int> difficulties = {8, 6, 4};
    std::vector<std::string> difficulty_levels = {"Easy (8x8)", "Medium (6x6)", "Hard (4x4)", "Quit / Exit"};

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Intro page
    clear();
    mvprintw(max_y / 2 - 2, max_x / 2 - 10, "Welcome to 2048!");
    mvprintw(max_y / 2, max_x / 2 - 12, "Press any key to continue...");
    refresh();
    getch();

    // Selection page
    int choice = 0;
    while (true) {
        clear();
        mvprintw(max_y / 2 - 2, max_x / 2 - 15, "Select a difficulty level:");
        for (int i = 0; i < difficulty_levels.size(); i++) {
            if (i == choice) {
                mvprintw(max_y / 2 + i, max_x / 2 - 15, "> %s", difficulty_levels[i].c_str());
            } else {
                mvprintw(max_y / 2 + i, max_x / 2 - 13, "  %s", difficulty_levels[i].c_str());
            }
        }
        refresh();

        int input = getch();
        if (input == KEY_UP && choice > 0) {
            choice--;
        } else if (input == KEY_DOWN && choice < difficulty_levels.size() - 1) {
            choice++;
        } else if (input == '\n') {
            if (choice == difficulty_levels.size() - 1) {
                endwin();
                return 0;
            }
            break;
        }
    }

    const int user_board_size = difficulties[choice];

    keypad(stdscr, TRUE);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_CYAN, COLOR_BLACK);
        init_pair(8, COLOR_WHITE, COLOR_BLACK);
    }

    TwoZeroFourEight game(user_board_size);
    game.draw_board();

    while (true) {
        clear();
        game.draw_board();
        refresh();
        int user_input = getch();
        if (user_input == ERR) {
            continue;
        }

        bool moved = false;
        if (user_input == 'q') {
            break;
        }
        else if (user_input == KEY_UP) {
            moved = game.move_up();
        }
        else if (user_input == KEY_DOWN) {
            moved = game.move_down();
        }
        else if (user_input == KEY_LEFT) {
            moved = game.move_left();
        }
        else if (user_input == KEY_RIGHT) {
            moved = game.move_right();
        }

        if (moved) {
            game.add_random_tile();
        }

        if (!game.can_move()) {
            clear();
            printw("Game Over! No more moves available.\nPress any key to exit.");
            refresh();
            getch();
            break;
        }
    }

    endwin();
    return 0;
}
