#include <iostream>
#include <ncurses.h>
#include "tic_tac_toe_game.h"
#include "minimax.h"

void tic_tac_toe_main() {
    if (initscr() == NULL) {
        fprintf(stderr, "Error initializing ncurses.\n");
        exit(EXIT_FAILURE);
    }
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    int max_x;
    int max_y;
    getmaxyx(stdscr, max_y, max_x);

    clear();
    mvprintw(max_y / 2 - 4, max_x / 2 - 15, "Welcome to Tic Tac Toe Game");
    mvprintw(max_y / 2 - 3, max_x / 2 - 15, "Press any key to continue...");
    refresh();
    getch();
    clear();

    TicTacToe game;
    Minimax ai;
    char board[3][3] = {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

    int current_row = 0, current_col = 0;
    bool selected = false;

    game.print_board_ncurses(board, current_row, current_col, selected);

    while (true) {
        int ch = getch();
        switch (ch) {
            case 'q':
                endwin();
                return;
            case KEY_UP:
                current_row = (current_row - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                current_row = (current_row + 1) % 3;
                break;
            case KEY_LEFT:
                current_col = (current_col - 1 + 3) % 3;
                break;
            case KEY_RIGHT:
                current_col = (current_col + 1) % 3;
                break;
            case ' ':
                if (board[current_row][current_col] == '_') {
                    selected = !selected;
                }
                break;
            case 10: // Enter key
                if (selected && board[current_row][current_col] == '_') {
                    board[current_row][current_col] = 'o';
                    selected = false;
                    game.print_board_ncurses(board, current_row, current_col, selected);

                    if (game.evaluate(board) == -10) {
                        mvprintw(7, 0, "You win!\nPress any key to exit.");
                        refresh();
                        getch();
                        endwin();
                        return;
                    }

                    if (!game.is_moves_left(board)) {
                        mvprintw(7, 0, "It's a draw!\nPress any key to exit.");
                        refresh();
                        getch();
                        endwin();
                        return;
                    }

                    Move best_move = ai.find_best_move(board);
                    board[best_move.row][best_move.col] = 'x';
                    game.print_board_ncurses(board, current_row, current_col, selected);

                    if (game.evaluate(board) == 10) {
                        mvprintw(7, 0, "AI wins!\nPress any key to exit.");
                        refresh();
                        getch();
                        endwin();
                        return;
                    }

                    if (!game.is_moves_left(board)) {
                        mvprintw(7, 0, "It's a draw!");
                        refresh();
                        getch();
                        endwin();
                        return;
                    }
                }
                break;
        }
        game.print_board_ncurses(board, current_row, current_col, selected);
    }

    endwin();
}
