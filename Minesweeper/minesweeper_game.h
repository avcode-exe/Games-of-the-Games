#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include <vector>

class Minesweeper {
public:
    int rows;
    int cols;
    int num_mines;
    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> flagged;

    Minesweeper(int rows, int cols, int num_mines);
    void generate_board();
    void reveal_tile(int row, int col);
    void flag_tile(int row, int col);
    bool check_win();
    void initialize_colors();
    void display_board(int cursor_row, int cursor_col);
    void display_full_board();
};

#endif