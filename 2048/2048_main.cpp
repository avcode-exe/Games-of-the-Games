#include "2048_game.h"
#include <ncurses.h>
#include <iostream>

int TwoZeroFourEight_main() {
    int difficulty = 0;
    std::vector<int> difficulties = {8, 6, 4};
    std::cout << "Level of difficulty:" << std::endl;
    std::cout << "1. Easy (8x8)" << std::endl;
    std::cout << "2. Medium (6x6)" << std::endl;
    std::cout << "3. Hard (4x4)" << std::endl;
    std::cout << "Choose a level of difficulty: ";
    while (true) {
        std::cin >> difficulty;
        if (difficulty >= 1 && difficulty <= 3) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cout << "Choose a level of difficulty: ";
        }
    }
    int user_board_size = difficulties[difficulty - 1];

    initscr();
    cbreak();
    noecho();
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

    while (game.can_move()) {
        int user_input = getch();
        bool moved = false;
        if (user_input == 'q') {
            break;
        } else if (user_input == 'a') {
            moved = game.move_left();
        } else if (user_input == 'd') {
            moved = game.move_right();
        } else if (user_input == 'w') {
            moved = game.move_up();
        } else if (user_input == 's') {
            moved = game.move_down();
        } else {
            continue;
        }
        if (moved) {
            game.add_random_tile();
        }
        game.draw_board();
    }

    endwin();
    return 0;
}