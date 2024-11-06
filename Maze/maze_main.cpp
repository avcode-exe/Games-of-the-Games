#include <clocale>
#include <iostream>
#include <limits>
#include <ncurses.h>
#include <thread>
#include "maze_game.h"

/**
 * @brief Main function to run the maze game.
 *
 * This function initializes the player position, sets up the game environment,
 * and handles user input to navigate through the maze. The player can choose
 * the level of difficulty, which determines the size of the maze. The game
 * continues until the player reaches the end of the maze or quits by pressing 'q'.
 *
 * The function uses ncurses for handling screen output and user input.
 *
 * @note The screen width must be at least 120 characters for the game to run properly.
 *
 * @details
 * - Initializes player position and game state.
 * - Prompts the user to select a difficulty level.
 * - Generates the maze based on the selected difficulty.
 * - Enters a loop to handle user input for navigating the maze:
 *   - Arrow keys to move
 *   - 'q' to quit the game
 * - Updates the maze display and checks if the player has reached the end.
 * - Ends the ncurses session and resets the game state.
 */
void maze_main() {
	setlocale(LC_ALL, "");

	int size = 0;
	int difficulty = 0;
	std::vector<int> difficulties = {11, 21, 31};
    std::vector<std::string> difficulty_levels = {"Easy (11x11)", "Medium (21x21)", "Hard (31x31)", "Quit / Exit"};
	initscr();
	cbreak();
	noecho();
    curs_set(0);

	int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Intro page
	clear();
    mvprintw(max_y / 2 - 2, max_x / 2 - 10, "Welcome to Maze Game!");
    mvprintw(max_y / 2, max_x / 2 - 12, "Press any key to continue...");
	refresh();
	getch();

    // Selection page
    int choice = 0;
    while (true) {
        clear();
        mvprintw(max_y / 2 - 2, max_x / 2 - 15, "Select a difficulty level:");
        for (int i = 0; i < difficulty_levels.size(); i++) {
            if (i == choice) {
                mvprintw(max_y / 2 + i, max_x / 2 - 15, "> %s", difficulty_levels[i].c_str());
            } else {
                mvprintw(max_y / 2 + i, max_x / 2 - 13, "  %s", difficulty_levels[i].c_str());
			}
		}
        refresh();

        int input = getch();
        if (input == KEY_UP && choice > 0) {
            choice--;
        } else if (input == KEY_DOWN && choice < difficulty_levels.size() - 1) {
            choice++;
        } else if (input == '\n') {
            if (choice == difficulty_levels.size() - 1) {
                endwin();
                return;
            }
            difficulty = choice + 1;
            size = difficulties[difficulty - 1];
            break;
	}
}

    Maze maze(size);
    maze.generate_maze(maze.start_x, maze.start_y);

    maze.player_x = 0;
    maze.player_y = 1;
    maze.win = false;

    // Game loop
    int user_input;
    int line_pointer = 0;
    while (user_input != 'q') {
        int screen_size_y;
        int screen_size_x;
        clear();
        refresh();
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
        if (user_input == KEY_UP) {
            if (maze.player_y - line_pointer < screen_size_y / 2 && line_pointer > 0) {
                line_pointer--;
            }
            if (maze.player_y > 0 && maze.maze_map[maze.player_y - 1][maze.player_x] != 1) {
                maze.player_y--;
            }
        }
        else if (user_input == KEY_DOWN) {
            if (maze.player_y > screen_size_y / 2 + line_pointer &&
                line_pointer + screen_size_y < maze.maze_map.size()) {
                line_pointer++;
            }
            if (maze.maze_map[maze.player_y + 1][maze.player_x] != 1) {
                maze.player_y++;
            }
        }
        else if (user_input == KEY_LEFT) {
            if (maze.maze_map[maze.player_y][maze.player_x - 1] != 1) {
                maze.player_x--;
            }
        }
        else if (user_input == KEY_RIGHT) {
            if (maze.maze_map[maze.player_y][maze.player_x + 1] != 1) {
                maze.player_x++;
            }
        }
        maze.display_maze(screen_size_y, line_pointer);
        refresh();
        if (maze.player_x == maze._END[0] + 1 && maze.player_y == maze._END[1] - 1) {
            clear();
            maze.win = true;
            printw("Congratulations! You have reached the end of the maze.\nPress any key to exit.");
            refresh();
            getch();
            break;
        }
        user_input = getch();
        if (user_input == ERR) {
            continue;
        }
    }
    endwin();
}