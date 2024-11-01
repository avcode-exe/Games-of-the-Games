#ifndef TWO_ZERO_FOUR_EIGHT_GAME_H
#define TWO_ZERO_FOUR_EIGHT_GAME_H

#include <vector>

class TwoZeroFourEight {
public:
    int map_size;
    int score;
    std::vector<std::vector<int>> board;

    TwoZeroFourEight(int size);
    void draw_board();
    bool move_left();
    bool move_right();
    bool move_up();
    bool move_down();
    bool can_move();
    void add_random_tile();
};

#endif