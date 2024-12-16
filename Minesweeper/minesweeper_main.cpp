#include <clocale>
#include <iostream>
#include <limits>
#include <ncurses.h>
#include "minesweeper_game.h"

/**
 * @brief Main function for the Minesweeper game.
 *
 * This function initializes the game state, prompts the user to select a difficulty level,
 * and starts the Minesweeper game loop. The game loop handles user input for moving the
 * cursor, flagging tiles, and revealing tiles. The game ends when the player either hits
 * a mine or successfully reveals all non-mine tiles.
 *
 * User controls:
 * - Arrow keys: Move cursor
 * - 'f': Flag a tile
 * - 'r': Reveal a tile
 * - 'q': Quit the game
 *
 * The game displays a "Game Over" message if the player hits a mine, and a "Congratulations"
 * message if the player successfully reveals all non-mine tiles.
 */
void minesweeper_main() {
    setlocale(LC_ALL, "");

    const std::vector<std::vector<int>> difficulties = {{10, 10, 20}, {16, 16, 40}, {16, 30, 80}};
    std::vector<std::string> difficulty_levels = {"Easy", "Medium", "Hard", "Quit / Exit"};

    if (initscr() == NULL) {
        fprintf(stderr, "Error initializing ncurses.\n");
        exit(EXIT_FAILURE);
    }
    cbreak();
    noecho();
    curs_set(0);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Intro page
    clear();
    mvprintw(max_y / 2 - 2, max_x / 2 - 10, "Welcome to Minesweeper!");
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
                return;
            }
            break;
        }
    }

    Minesweeper game(difficulties[choice][0], difficulties[choice][1], difficulties[choice][2]);
    game.generate_board();
    game.win = false;
    game.player_x = 0;
    game.player_y = 0;

    keypad(stdscr, TRUE);

    while (true) {
        clear();
        game.display_board(game.player_y, game.player_x);
        refresh();
        int user_input = getch();
        if (user_input == ERR) {
            continue;
        }

        if (user_input == 'q') {
            break;
        }
        else if (user_input == 'f') {
            game.flag_tile(game.player_y, game.player_x);
        }
        else if (user_input == 'r') {
            game.reveal_tile(game.player_y, game.player_x);
            if (game.board[game.player_y][game.player_x] == -1) {
                clear();
                printw("Game Over! You hit a mine.\nPress any key to exit.\nMine locations:\n");
                game.display_full_board();
                refresh();
                getch();
                break;
            }
        }
        else if (user_input == KEY_UP) {
            game.player_y =
                (game.player_y > 0) ? game.player_y - 1 : game.player_y;
        }
        else if (user_input == KEY_DOWN) {
            game.player_y = (game.player_y < game.rows - 1)
                ? game.player_y + 1
                : game.player_y;
        }
        else if (user_input == KEY_LEFT) {
            game.player_x =
                (game.player_x > 0) ? game.player_x - 1 : game.player_x;
        }
        else if (user_input == KEY_RIGHT) {
            game.player_x = (game.player_x < game.cols - 1)
                ? game.player_x + 1
                : game.player_x;
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
