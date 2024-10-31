#include "game_header.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void display_menu(std::vector<std::string> games) {
    std::cout << "Welcome to Games of the Games!" << std::endl;
    std::cout << "Select a game (q or Q to quit):" << std::endl;
    for (int i = 0; i < games.size(); i++) {
        std::cout << i + 1 << ". " << games[i] << std::endl;
    }
    std::cout << "Enter your choice: ";
}

int main() {
    std::vector<std::string> games = {"Maze", "Minesweeper", "2048", "Hangman"};
    std::string choice = "";
    while (true) {
        display_menu(games);
        std::cin >> choice;
        if (choice == "q" || choice == "Q") {
            break;
        } else if (std::find(games.begin(), games.end(), choice) == games.end()) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue;
        }
    }
}