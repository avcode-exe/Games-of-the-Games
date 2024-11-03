#ifndef PLAYER_H
#define PLAYER_H

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
