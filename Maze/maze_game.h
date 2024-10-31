#ifndef MAZE_GAME_H
#define MAZE_GAME_H

#include <vector>
#include <set>

// #define DEBUG

class Maze { // A square maze
private:
    int PATH = 0; // Represents a path
    int WALL = 1; // Represents a wall
    std::vector<std::vector<int>> directions = { {0, -2}, {2, 0}, {0, 2}, {-2, 0} }; // The possible directions to move in the maze
    std::vector<std::vector<int>> potentialFrontier; // The list of potential frontier cells

public:
    int maze_size; // The size of the maze
    int start_x; // The x-coordinate of the starting point of the maze
    int start_y; // The y-coordinate of the starting point of the maze
    std::vector<std::vector<char>> maze; // The maze grid

    Maze(int size); // Constructor
    void generate_maze(int x, int y); // Generates the maze using recursive randomized Prim's Algorithm
    
    #ifdef DEBUG
    void print_maze_DEBUG_ONLY(); // Prints the maze to the console (DEBUG_ONLY)
    #endif
};

#endif