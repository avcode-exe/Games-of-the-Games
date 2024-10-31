#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int game_state = 0;
    int player_x_maze = 1;
    int player_y_maze = 0;

    void reset();
};

#endif