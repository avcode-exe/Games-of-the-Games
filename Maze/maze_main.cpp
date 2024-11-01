#include "maze_game.h"
#include <iostream>
#include <thread>
#include <ncurses.h>
#include <locale.h>

void maze_main() {
    setlocale(LC_ALL, "");
    extern Player player;
    player.player_x_maze = 0;
    player.player_y_maze = 1;

    int screen_size_x;
    int screen_size_y;
    char user_input;
    int line_pointer = 0;
    int size = 0;
    while (true) {
        std::cout << "Enter the size of the maze: ";
        std::cin >> size;
        if (size < 3) {
            std::cout << "Size must be at least 3." << std::endl;
        } else {
            break;
        }
    }

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
            if (player.player_y_maze > 0 && maze.maze_map[player.player_y_maze - 1][player.player_x_maze] != 1) {
                player.player_y_maze--;
            }
        } else if (user_input == 's') {
            if (player.player_y_maze > screen_size_y / 2 + line_pointer && line_pointer + screen_size_y < maze.maze_map.size()) {
                line_pointer++;
            }
            if (maze.maze_map[player.player_y_maze + 1][player.player_x_maze] != 1) {
                player.player_y_maze++;
            }
        } else if (user_input == 'a') {
            if (maze.maze_map[player.player_y_maze][player.player_x_maze - 1] != 1) {
                player.player_x_maze--;
            }
        } else if (user_input == 'd') {
            if (maze.maze_map[player.player_y_maze][player.player_x_maze + 1] != 1) {
                player.player_x_maze++;
            }
        }
        maze.display_maze(screen_size_y, line_pointer);
        refresh();
        if (player.player_x_maze == maze._END[0] + 1 && player.player_y_maze == maze._END[1] - 1) {
            clear();
            printw("Congratulations! You have reached the end of the maze.");
            refresh();
            while (true) {
                user_input = getch();
                if (user_input == ERR) {
                    continue;
                } else if (user_input == 'x') {
                    break;
                }
            }
        }
        user_input = getch();
        if (user_input == ERR) {
            continue;
        }
    }
    endwin();
    player.game_state = 0;
    return;
}