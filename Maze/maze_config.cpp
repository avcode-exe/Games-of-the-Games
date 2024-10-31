#include "maze_game.h"
#include <random>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

#ifdef DEBUG
#include <iostream> // DEBUG_ONLY
#endif

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
    maze = std::vector<std::vector<char>>(maze_size, std::vector<char>(maze_size, WALL));
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
    maze[x][y] = PATH;
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
            if (nx > 0 && nx < maze_size - 1 && ny > 0 && ny < maze_size - 1 && maze[nx][ny] == WALL) {
                maze[nx][ny] = PATH;
                maze[cx + dx / 2][cy + dy / 2] = PATH;
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

#ifdef DEBUG
void Maze::print_maze_DEBUG_ONLY() {
    for (auto &i : maze) {
        for (auto &j : i) {
            if (j == PATH) std::cout << "  ";
            else std::cout << "▓▓";
        }
        std::cout << std::endl;
    }
}
#endif