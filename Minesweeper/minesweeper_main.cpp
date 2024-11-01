#include "minesweeper_game.h"
#include <iostream>
#include <ncurses.h>

void minesweeper_main() {
    std::vector<std::vector<int>> difficulties = {
        {10, 10, 20},
        {16, 16, 40},
        {16, 30, 99}
    };
    int difficulty = 0;

    std::cout << "Select difficulty: \n";
    std::cout << "1. Easy\n";
    std::cout << "2. Medium\n";
    std::cout << "3. Hard\n";
    std::cin >> difficulty;
    Minesweeper game(difficulties[difficulty - 1][0], difficulties[difficulty - 1][1], difficulties[difficulty - 1][2]);
    game.generate_board();
    char user_input;
    int row = 0, col = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (true) {
        clear();
        game.display_board(row, col);
        refresh();
        user_input = getch();
        if (user_input == ERR) {
            continue;
        }

        if (user_input == 'x') {
            break;
        } else if (user_input == 'f') {
            game.flag_tile(row, col);
        } else if (user_input == 'r') {
            game.reveal_tile(row, col);
            if (game.board[row][col] == -1) {
                clear();
                printw("Game Over! You hit a mine.\nPress 'x' to exit.");
                refresh();
                getch();
                break;
            }
        } else if (user_input == 'w') {
            row = (row > 0) ? row - 1 : row;
        } else if (user_input == 's') {
            row = (row < game.rows - 1) ? row + 1 : row;
        } else if (user_input == 'a') {
            col = (col > 0) ? col - 1 : col;
        } else if (user_input == 'd') {
            col = (col < game.cols - 1) ? col + 1 : col;
        }
        refresh();

        if (game.check_win()) {
            clear();
            printw("Congratulations! You won the game.\n");
            refresh();
            getch();
            break;
        }
    }

    endwin();
}