#include "player.h"

Player player;

void Player::reset() {
    game_state = 0;
    player_x_maze = 1;
    player_y_maze = 0;
    player_maze_win = false;
    player_x_minesweeper = 0;
    player_y_minesweeper = 0;
    player_minesweeper_win = false;
    player_score_2048 = 0;
}