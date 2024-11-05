#include "player.h"

Player player; // Define player variable

/**
 * @brief Resets the player's state for all games.
 *
 * This function resets the player's state variables for different games to their initial values.
 * It sets the game state to 0, initializes the player's position in the maze and Minesweeper games,
 * and resets the win status and score for the respective games.
 */
void Player::reset() {
    game_state = 0;
    player_x_maze = 1;
    player_y_maze = 0;
    player_maze_win = false;
    player_x_minesweeper = 0;
    player_y_minesweeper = 0;
    player_minesweeper_win = false;
    player_score_2048 = 0;
    player_x_tic_tac_toe = 0;
    player_y_tic_tac_toe = 0;
    player_tic_tac_toe_win = false;
}
