#include "maze_game.h"
#include <iostream>
#include <thread>
#include <ncurses.h>

void maze_main() { // Main function for maze game
    extern Player player;
    player.player_x_maze = 0;
    player.player_y_maze = 1;

    int screen_size_x;
    int screen_size_y;
    char user_input;
    int line_pointer = 0;
    int size = 0;
    std::cout << "Enter the size of the maze: ";
    std::cin >> size;

    Maze maze(size);
    maze.generate_maze(maze.start_x, maze.start_y);

    initscr();
    cbreak();
    noecho();

    while (user_input != 'x') {
        move(0, 0);
        getmaxyx(stdscr, screen_size_y, screen_size_x);
        if (screen_size_x < 120) {
            clear();
            printw("Screen width of 120 required\n");
            printw("Current width: %d\n", screen_size_x);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            refresh();
            continue;
        }
        if (user_input == 'w') {
            if (player.player_y_maze - line_pointer < screen_size_y / 2 && line_pointer > 0) {
                line_pointer--;
            }
            if (player.player_y_maze > 0 && maze.maze[player.player_y_maze - 1][player.player_x_maze] != 1) {
                player.player_y_maze--;
            }
        } else if (user_input == 's') {
            if (player.player_y_maze > screen_size_y / 2 + line_pointer && line_pointer + screen_size_y < maze.maze.size()) {
                line_pointer++;
            }
            if (maze.maze[player.player_y_maze + 1][player.player_x_maze] != 1) {
                player.player_y_maze++;
            }
        } else if (user_input == 'a') {
            if (maze.maze[player.player_y_maze][player.player_x_maze - 1] != 1) {
                player.player_x_maze--;
            }
        } else if (user_input == 'd') {
            if (maze.maze[player.player_y_maze][player.player_x_maze + 1] != 1) {
                player.player_x_maze++;
            }
        }
        maze.display_maze(screen_size_y, line_pointer);
        refresh();
        if (player.player_y_maze + 1 >= maze.maze.size()) {
            break;
        }
        user_input = getch();
        if (user_input == ERR) {
            continue;
        }
    }
    endwin();
    player.game_state = 0;
    return;

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