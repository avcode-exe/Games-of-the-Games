#include <iostream>
#include <ncurses.h>
#include "tic_tac_toe_game.h"
#include "minimax.h"

void tic_tac_toe_main() {
    char board[3][3] = {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    int current_row = 0, current_col = 0;
    bool selected = false;

    print_board_ncurses(board, current_row, current_col, selected);

    while (true) {
        int ch = getch();
        switch (ch) {
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
                    print_board_ncurses(board, current_row, current_col, selected);

                    if (evaluate(board) == -10) {
                        mvprintw(7, 0, "You win!\nPress any key to exit.");
                        refresh();
                        getch();
                        endwin();
                        return;
                    }

                    if (!is_moves_left(board)) {
                        mvprintw(7, 0, "It's a draw!\nPress any key to exit.");
                        refresh();
                        getch();
                        endwin();
                        return;
                    }

                    Move best_move = find_best_move(board);
                    board[best_move.row][best_move.col] = 'x';
                    print_board_ncurses(board, current_row, current_col, selected);

                    if (evaluate(board) == 10) {
                        mvprintw(7, 0, "AI wins!\nPress any key to exit.");
                        refresh();
                        getch();
                        endwin();
                        return;
                    }

                    if (!is_moves_left(board)) {
                        mvprintw(7, 0, "It's a draw!");
                        refresh();
                        getch();
                        endwin();
                        return;
                    }
                }
                break;
        }
        print_board_ncurses(board, current_row, current_col, selected);
    }

    endwin();
}
