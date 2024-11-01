#include "2048_game.h"
#include <random>
#include <ncurses.h>
#include "player.h"

extern Player player;

TwoZeroFourEight::TwoZeroFourEight(int size) {
    map_size = size;
    player.player_score_2048 = 0;
    board = std::vector<std::vector<int>>(map_size, std::vector<int>(map_size, 0));
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, map_size - 1);
    for (int i = 0; i < 2; ++i) {
        int x, y;
        do {
            x = dis(gen);
            y = dis(gen);
        } while (board[x][y] != 0);
        board[x][y] = (dis(gen) % 2 + 1) * 2;
    }
}

void TwoZeroFourEight::draw_board() {
    clear();
    for (int i = 0; i < map_size; ++i) {
        for (int j = 0; j < map_size; ++j) {
            int value = board[i][j];
            int color_pair = value == 0 ? 1 : (value > 2048 ? 8 : (value / 2) % 7 + 2);
            attron(COLOR_PAIR(color_pair));
            mvprintw(i, j * 4, "%4d", value);
            attroff(COLOR_PAIR(color_pair));
        }
    }
    mvprintw(map_size, 0, "Score: %d", player.player_score_2048);
    refresh();
}

bool TwoZeroFourEight::move_left() {
    bool moved = false;
    for (int i = 0; i < map_size; ++i) {
        std::vector<int> new_row(map_size, 0);
        int pos = 0;
        for (int j = 0; j < map_size; ++j) {
            if (board[i][j] != 0) {
                if (pos > 0 && new_row[pos - 1] == board[i][j]) {
                    new_row[pos - 1] *= 2;
                    player.player_score_2048 += new_row[pos - 1];
                    moved = true;
                } else {
                    if (pos != j) moved = true;
                    new_row[pos++] = board[i][j];
                }
            }
        }
        board[i] = new_row;
    }
    return moved;
}

bool TwoZeroFourEight::move_right() {
    bool moved = false;
    for (int i = 0; i < map_size; ++i) {
        std::vector<int> new_row(map_size, 0);
        int pos = map_size - 1;
        for (int j = map_size - 1; j >= 0; --j) {
            if (board[i][j] != 0) {
                if (pos < map_size - 1 && new_row[pos + 1] == board[i][j]) {
                    new_row[pos + 1] *= 2;
                    player.player_score_2048 += new_row[pos + 1];
                    moved = true;
                } else {
                    if (pos != j) moved = true;
                    new_row[pos--] = board[i][j];
                }
            }
        }
        board[i] = new_row;
    }
    return moved;
}

bool TwoZeroFourEight::move_up() {
    bool moved = false;
    for (int j = 0; j < map_size; ++j) {
        std::vector<int> new_col(map_size, 0);
        int pos = 0;
        for (int i = 0; i < map_size; ++i) {
            if (board[i][j] != 0) {
                if (pos > 0 && new_col[pos - 1] == board[i][j]) {
                    new_col[pos - 1] *= 2;
                    player.player_score_2048 += new_col[pos - 1];
                    moved = true;
                } else {
                    if (pos != i) moved = true;
                    new_col[pos++] = board[i][j];
                }
            }
        }
        for (int i = 0; i < map_size; ++i) {
            board[i][j] = new_col[i];
        }
    }
    return moved;
}

bool TwoZeroFourEight::move_down() {
    bool moved = false;
    for (int j = 0; j < map_size; ++j) {
        std::vector<int> new_col(map_size, 0);
        int pos = map_size - 1;
        for (int i = map_size - 1; i >= 0; --i) {
            if (board[i][j] != 0) {
                if (pos < map_size - 1 && new_col[pos + 1] == board[i][j]) {
                    new_col[pos + 1] *= 2;
                    player.player_score_2048 += new_col[pos + 1];
                    moved = true;
                } else {
                    if (pos != i) moved = true;
                    new_col[pos--] = board[i][j];
                }
            }
        }
        for (int i = 0; i < map_size; ++i) {
            board[i][j] = new_col[i];
        }
    }
    return moved;
}

bool TwoZeroFourEight::can_move() {
    for (int i = 0; i < map_size; ++i) {
        for (int j = 0; j < map_size; ++j) {
            if (board[i][j] == 0) return true;
            if (i > 0 && board[i][j] == board[i - 1][j]) return true;
            if (i < map_size - 1 && board[i][j] == board[i + 1][j]) return true;
            if (j > 0 && board[i][j] == board[i][j - 1]) return true;
            if (j < map_size - 1 && board[i][j] == board[i][j + 1]) return true;
        }
    }
    return false;
}

void TwoZeroFourEight::add_random_tile() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, map_size - 1);
    int x, y;
    do {
        x = dis(gen);
        y = dis(gen);
    } while (board[x][y] != 0);
    board[x][y] = (dis(gen) % 2 + 1) * 2;
}