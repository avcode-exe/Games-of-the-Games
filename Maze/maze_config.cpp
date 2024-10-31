#include "maze_game.h"

#include <random>
#include <algorithm>
#include <iostream> // DEBUG_ONLY
#include <set>
#include <vector>
#include <stack>

Maze::Maze(int size) {
    maze_size = size;
    start_x = 1;
    start_y = 0;
    maze = std::vector<std::vector<char>>(maze_size, std::vector<char>(maze_size, WALL));
}

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

void Maze::print_maze_DEBUG_ONLY() {
    for (auto &i : maze) {
        for (auto &j : i) {
            if (j == PATH) std::cout << "  ";
            else std::cout << "##";
        }
        std::cout << std::endl;
    }
}