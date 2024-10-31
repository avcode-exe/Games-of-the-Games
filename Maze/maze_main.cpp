#include "maze_game.h"
#include <iostream>

void maze_main() { // Main function for maze game
    int size = 0;
    std::cout << "Enter the size of the maze: ";
    std::cin >> size;

    Maze maze(size);
    maze.generate_maze(maze.start_x, maze.start_y);

    #ifdef DEBUG
    maze.print_maze_DEBUG_ONLY();
    #endif
}

#ifdef DEBUG
int main() { // DEBUG ONLY
    int size = 0;
    std::cout << "Enter the size of the maze: ";
    std::cin >> size;

    Maze maze(size);
    maze.generate_maze(maze.start_x, maze.start_y);
    maze.print_maze_DEBUG_ONLY();
}
#endif