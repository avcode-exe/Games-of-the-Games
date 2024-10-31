#include "game_header.h"
#include "player.h"
#include <vector>
#include <string>
#include <algorithm>

// #define COMPLETE

void display_menu(std::vector<std::string> games) {
    std::cout << "Welcome to Games of the Games!" << std::endl;
    std::cout << "Select a game (q or Q to quit):" << std::endl;
    for (size_t i = 0; i < games.size(); i++) {
        std::cout << i + 1 << ". " << games[i] << std::endl;
    }
    std::cout << "Enter your choice: ";
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
        if (choice == "q" || choice == "Q") {
            break;
        } else if (choice < "1" || choice > "4") {
            std::cout << "Invalid choice. Please try again." << std::endl;
        } else {
            if (choice == "1") {
                player.game_state = 1;
                maze_main();
            } else if (choice == "2") {
                player.game_state = 2;
                #ifdef COMPLETE
                minesweeper_main();
                #endif
            } else if (choice == "3") {
                player.game_state = 3;
                #ifdef COMPLETE
                main_2048();
                #endif
            } else if (choice == "4") {
                player.game_state = 4;
                #ifdef COMPLETE
                hangman_main();
                #endif
            }
        }
    }
}