#include "maze_game.h"
#include <random>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <ncurses.h>

extern Player player;

/**
 * @brief Constructs a Maze object with a specified size.
 * 
 * This constructor initializes the maze with the given size, sets the starting
 * coordinates, and fills the maze with walls.
 * 
 * @param size The size of the maze (both width and height).
 */
Maze::Maze(int size) {
    maze_size = size;
    start_x = 1;
    start_y = 0;
    maze = std::vector<std::vector<int>>(maze_size, std::vector<int>(maze_size, _WALL));
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
    stack.push({x, y});
    maze[x][y] = _PATH;
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
            if (nx > 0 && nx < maze_size - 1 && ny > 0 && ny < maze_size - 1 && maze[nx][ny] == _WALL) {
                maze[nx][ny] = _PATH;
                maze[cx + dx / 2][cy + dy / 2] = _PATH;
                stack.push({nx, ny});
                moved = true;
                break;
            }
        }
        if (!moved) {
            stack.pop();
        }
    }
}

void Maze::display_maze(int screen_size_y, int line_pointer) {
    move(0, 0);
    for (int i = line_pointer; i < std::min(screen_size_y + line_pointer, maze_size); ++i) {
        std::string display_row_str;
        for (int j = 0; j < maze_size; ++j) {
            if (i == player.player_y_maze && j == player.player_x_maze) {
                display_row_str += "P ";
            } else if (maze[i][j] == _WALL) {
                display_row_str += "##"; // ▓▓
            } else {
                display_row_str += "  ";
            }
        }
        printw("%s\n", display_row_str.c_str());
    }
    refresh();
}