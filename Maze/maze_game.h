#ifndef MAZE_GAME_H
#define MAZE_GAME_H

#include "player.h"
#include <vector>
#include <set>

class Maze { // A square maze
private:
    int _PATH = 0; // Represents a path
    int _WALL = 1; // Represents a wall

public:
    int maze_size; // The size of the maze
    int start_x; // The x-coordinate of the starting point of the maze
    int start_y; // The y-coordinate of the starting point of the maze
    std::vector<std::vector<int>> maze; // The maze grid

    Maze(int size); // Constructor
    void generate_maze(int x, int y); // Generates the maze using recursive randomized Prim's Algorithm
    void display_maze(int screen_size_y, int line_pointer); // Displays the maze to the console
};

#endif