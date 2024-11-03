#include <iostream>
#include <string>
#include <vector>
#include "game_header.h"
#include "player.h"

/**
 * @brief Displays a menu of available games to the user.
 *
 * This function prints a welcome message and a list of games to the console.
 * The user is prompted to select a game by entering the corresponding number.
 * The user can also quit by entering 'q' or 'Q'.
 *
 * @param games A vector of strings containing the names of the available games.
 */
void display_menu(const std::vector<std::string> &games) {
	std::cout << "\nWelcome to Games of the Games!" << std::endl;
	std::cout << "Select a game (q or Q to quit):" << std::endl;
	for (size_t i = 0; i < games.size(); i++) {
		std::cout << i + 1 << ". " << games[i] << std::endl;
	}
	std::cout << "\nEnter your choice: ";
}

/**
 * @file main.cpp
 * @brief Main entry point for the Games-of-the-Games application.
 *
 * This file contains the main function which serves as the entry point for the application.
 * It presents a menu to the user to choose between different games: Maze, Minesweeper, and 2048.
 * The user can select a game to play or quit the application.
 *
 * The available games are:
 * - Maze
 * - Minesweeper
 * - 2048
 *
 * The user can quit the application by entering 'q' or 'Q'.
 *
 * @note The Player class and the functions display_menu(), maze_main(), minesweeper_main(), and TwoZeroFourEight_main()
 * are assumed to be defined elsewhere in the project.
 *
 * @return int Returns 0 upon successful completion.
 */
int main() {
	const std::vector<std::string> games = {"Maze", "Minesweeper", "2048"};
	std::vector<int> choices = {1, 2, 3};
	std::string choice;
	Player player;
	player.game_state = 0;

	while (true) {
		display_menu(games);
		std::cin >> choice;
		std::cout << "--------------------------------" << std::endl;
		if (choice == "q" || choice == "Q") {
			break;
		}
		else if (choice < "1" || choice > "3") {
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
		else {
			if (choice == "1") {
				player.game_state = 1;
				std::cout << "-------Entering Maze Game-------\n" << std::endl;
				maze_main();
				std::cout << "\n-------Exiting Maze Game-------" << std::endl;
			}
			else if (choice == "2") {
				player.game_state = 2;
				std::cout << "-------Entering Minesweeper Game-------\n" << std::endl;
				minesweeper_main();
				std::cout << "\n-------Exiting Minesweeper Game-------" << std::endl;
			}
			else if (choice == "3") {
				player.game_state = 3;
				std::cout << "-------Entering 2048 Game-------\n" << std::endl;
				TwoZeroFourEight_main();
				std::cout << "\n-------Exiting 2048 Game-------" << std::endl;
			}
		}
	}
	std::cout << "Thanks for playing!" << std::endl;
	return 0;
}
