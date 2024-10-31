#include "player.h"

Player player; // Define the global player instance

void Player::reset() {
    game_state = 0;
    player_x_maze = 1;
    player_y_maze = 0;
}