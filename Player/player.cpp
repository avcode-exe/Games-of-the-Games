#include "player.h"

Player player;

void Player::reset() {
    game_state = 0;
    player_x_maze = 1;
    player_y_maze = 0;
    player_score_2048 = 0;
    player_2048_win = false;
}