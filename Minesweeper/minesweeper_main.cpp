#include "minesweeper_game.h"
#include "player.h"
#include <iostream>
#include <ncurses.h>
#include <locale.h>

void minesweeper_main() {
    setlocale(LC_ALL, "");
    char user_input;
    extern Player player;
    player.game_state = 2;
    player.player_minesweeper_win = false;
    player.player_x_minesweeper = 0;
    player.player_y_minesweeper = 0;

    std::vector<std::vector<int>> difficulties = {
        {10, 10, 20},
        {16, 16, 40},
        {16, 30, 80}
    };
    int difficulty = 0;

    std::cout << "Select difficulty:" << std::endl;
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Medium" << std::endl;
    std::cout << "3. Hard" << std::endl;
    while (true) {
        std::cout << "Enter your choice: ";
        std::cin >> difficulty;
        if (difficulty < 1 || difficulty > 3) {
            std::cout << "Invalid choice. Please try again." << std::endl;
        } else {
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
        user_input = getch();
        if (user_input == ERR) {
            continue;
        }

        if (user_input == 'x') {
            break;
        } else if (user_input == 'f') {
            game.flag_tile(player.player_y_minesweeper, player.player_x_minesweeper);
        } else if (user_input == 'r') {
            game.reveal_tile(player.player_y_minesweeper, player.player_x_minesweeper);
            if (game.board[player.player_y_minesweeper][player.player_x_minesweeper] == -1) {
                clear();
                printw("Game Over! You hit a mine.\nPress any key to exit.");
                refresh();
                getch();
                break;
            }
        } else if (user_input == 'w') {
            player.player_y_minesweeper = (player.player_y_minesweeper > 0) ? player.player_y_minesweeper - 1 : player.player_y_minesweeper;
        } else if (user_input == 's') {
            player.player_y_minesweeper = (player.player_y_minesweeper < game.rows - 1) ? player.player_y_minesweeper + 1 : player.player_y_minesweeper;
        } else if (user_input == 'a') {
            player.player_x_minesweeper = (player.player_x_minesweeper > 0) ? player.player_x_minesweeper - 1 : player.player_x_minesweeper;
        } else if (user_input == 'd') {
            player.player_x_minesweeper = (player.player_x_minesweeper < game.cols - 1) ? player.player_x_minesweeper + 1 : player.player_x_minesweeper;
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