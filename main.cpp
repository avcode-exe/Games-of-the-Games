#include "game_header.h"
#include "player.h"
#include <vector>
#include <string>
#include <algorithm>

void display_menu(std::vector<std::string> games) {
    std::cout << "\nWelcome to Games of the Games!" << std::endl;
    std::cout << "Select a game (q or Q to quit):" << std::endl;
    for (size_t i = 0; i < games.size(); i++) {
        std::cout << i + 1 << ". " << games[i] << std::endl;
    }
    std::cout << "\nEnter your choice: ";
}

int main() {
    std::vector<std::string> games = {"Maze", "Minesweeper", "2048", "Hangman"};
    std::vector<int> choices = {1, 2, 3, 4};
    std::string choice = "";
    Player player;
    player.game_state = 0;

    while (true) {
        display_menu(games);
        std::cin >> choice;
        std::cout << "--------------------------------" << std::endl;
        if (choice == "q" || choice == "Q") {
            break;
        } else if (choice < "1" || choice > "4") {
            std::cout << "Invalid choice. Please try again." << std::endl;
        } else {
            if (choice == "1") {
                player.game_state = 1;
                std::cout << "-------Entering Maze Game-------\n" << std::endl;
                maze_main();
                std::cout << "\n-------Exiting Maze Game-------" << std::endl;
            } else if (choice == "2") {
                player.game_state = 2;
                std::cout << "-------Entering Minesweeper Game-------\n" << std::endl;
                minesweeper_main();
                std::cout << "\n-------Exiting Minesweeper Game-------" << std::endl;
            } else if (choice == "3") {
                player.game_state = 3;
                std::cout << "-------Entering 2048 Game-------\n" << std::endl;
                main_2048();
                std::cout << "\n-------Exiting 2048 Game-------" << std::endl;
            } else if (choice == "4") {
                player.game_state = 4;
                std::cout << "-------Entering Hangman Game-------\n" << std::endl;
                hangman_main();
                std::cout << "\n-------Exiting Hangman Game-------" << std::endl;
            }
        }
    }
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}