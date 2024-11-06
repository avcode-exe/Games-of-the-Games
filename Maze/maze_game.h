#ifndef MAZE_GAME_H
#define MAZE_GAME_H

#include <vector>

class Maze {
private:
	int _PATH = 0; // Represents a path
	int _WALL = 1; // Represents a wall
	std::pair<int, int> _START = {1, 0}; // Starting point of the maze

public:
	int maze_size; // The size of the maze
	int start_x; // The x-coordinate of the starting point of the maze
	int start_y; // The y-coordinate of the starting point of the maze
	int player_x;
	int player_y;
	bool win;
	std::vector<std::vector<int>> maze_map; // The maze grid
	std::vector<int> _END; // Ending point of the maze

	explicit Maze(int size); // Constructor
	~Maze() = default; // Destructor
	void generate_maze(int x, int y); // Generates the maze using recursive randomized Prime's Algorithm
	void display_maze(int screen_size_y, int line_pointer); // Displays the maze to the console
};

#endif
