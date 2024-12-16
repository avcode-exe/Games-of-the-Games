#include <chrono>
#include <thread>
#include "snake_game.h"

void snake_main() {
	SnakeGame game;
	game.initialize();

	while (!game.is_game_over()) {
		game.draw();
		game.input();
		game.logic();
		std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Increased sleep duration
	}

	game.end_game();
}
