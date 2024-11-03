#ifndef PLAYER_H
#define PLAYER_H

/**
 * @class Player
 * @brief Represents a player in various games with their respective states and positions.
 *
 * The Player class keeps track of the player's state and positions in different games,
 * including a maze game, Minesweeper, and 2048. It also provides a method to reset the player's state.
 */
class Player {
public:
	int game_state = 0;

	int player_x_maze = 1;
	int player_y_maze = 0;
	bool player_maze_win = false;

	int player_x_minesweeper = 0;
	int player_y_minesweeper = 0;
	bool player_minesweeper_win = false;

	int player_score_2048 = 0;

	void reset();
	~Player() = default;
};

#endif
