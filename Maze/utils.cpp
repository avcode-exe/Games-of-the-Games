#include <algorithm>
#include <ncurses.h>
#include <random>
#include <stack>
#include <vector>
#include "maze_game.h"

extern Player player;

/**
 * @brief Constructs a Maze object with a specified size.
 *
 * This constructor initializes the maze with the given size, sets the starting
 * coordinates, and fills the maze with walls.
 *
 * @param size The size of the maze (both width and height).
 */
Maze::Maze(const int size) {
	maze_size = size;
	start_x = 1;
	start_y = 0;
	_END = {maze_size - 2, maze_size - 1};
	maze_map = std::vector<std::vector<int>>(maze_size, std::vector<int>(maze_size, _WALL));
}

/**
 * @brief Generates a maze using a depth-first search algorithm.
 *
 * This function generates a maze starting from the given coordinates (x, y).
 * It uses a stack to perform a depth-first search and carves out a path in the maze.
 * The maze is represented as a 2D grid where PATH and WALL are predefined constants.
 *
 * @param x The starting x-coordinate for maze generation.
 * @param y The starting y-coordinate for maze generation.
 */
void Maze::generate_maze(int x, int y) {
	std::stack<std::pair<int, int>> stack;
	stack.emplace(x, y);
	maze_map[x][y] = _PATH;
	std::vector<std::pair<int, int>> directions = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};
	std::random_device rd;
	std::mt19937 g(rd());
	while (!stack.empty()) {
		auto [cx, cy] = stack.top();
		std::shuffle(directions.begin(), directions.end(), g);
		bool moved = false;
		for (auto [dx, dy] : directions) {
			int nx = cx + dx;
			int ny = cy + dy;
			if (nx > 0 && nx < maze_size - 1 && ny > 0 && ny < maze_size - 1 && maze_map[nx][ny] == _WALL) {
				maze_map[nx][ny] = _PATH;
				maze_map[cx + dx / 2][cy + dy / 2] = _PATH;
				stack.emplace(nx, ny);
				moved = true;
				break;
			}
		}
		if (!moved) {
			stack.pop();
		}
	}
	maze_map[start_x][start_y] = _PATH;
	maze_map[_END[0]][_END[1]] = _PATH;
	maze_map[_END[0]][_END[1] - 1] = _PATH;
}

void Maze::display_maze(const int screen_size_y, const int line_pointer) {
	move(0, 0);
	for (int i = line_pointer; i < std::min(screen_size_y + line_pointer, maze_size); ++i) {
		std::string display_row_str;
		for (int j = 0; j < maze_size; ++j) {
			if (i == player.player_y_maze && j == player.player_x_maze) {
				display_row_str += "PP";
			}
			else if (maze_map[i][j] == _WALL) {
				display_row_str += "##";
			}
			else if (i == _END[1] - 1 && j == _END[0]) {
				display_row_str += " G";
			}
			else {
				display_row_str += "  ";
			}
		}
		printw("%s\n", display_row_str.c_str());
	}
	refresh();
}
