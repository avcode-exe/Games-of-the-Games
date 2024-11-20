// #include "snake_game.h"
// #include <cstdlib>
// #include <ctime>
// #include <thread>
// #include <chrono>
// #include <iostream> // Add this for debugging

// SnakeGame::SnakeGame() : game_over(false), width(20), height(20), x(width / 2), y(height / 2), score(0), dir(STOP) {
//     std::srand(std::time(0));
//     fruit_x = std::rand() % width;
//     fruit_y = std::rand() % height;
//     snake.push_back({x, y});
// }

// void SnakeGame::initialize() {
//     initscr();
//     clear();
//     noecho();
//     cbreak();
//     curs_set(0);
//     keypad(stdscr, TRUE);
//     nodelay(stdscr, TRUE);
// }

// void SnakeGame::draw() {
//     clear();
//     for (int i = 0; i < width + 2; ++i) mvprintw(0, i, "#");
//     for (int i = 0; i < height; ++i) {
//         for (int j = 0; j < width; ++j) {
//             if (j == 0) mvprintw(i + 1, j, "#");
//             if (i == y && j == x) mvprintw(i + 1, j + 1, "O");
//             else if (i == fruit_y && j == fruit_x) mvprintw(i + 1, j + 1, "F");
//             else {
//                 bool print = false;
//                 for (auto s : snake) {
//                     if (s.first == j && s.second == i) {
//                         mvprintw(i + 1, j + 1, "o");
//                         print = true;
//                     }
//                 }
//                 if (!print) mvprintw(i + 1, j + 1, " ");
//             }
//             if (j == width - 1) mvprintw(i + 1, j + 1, "#");
//         }
//     }
//     for (int i = 0; i < width + 2; ++i) mvprintw(height + 1, i, "#");
//     mvprintw(height + 3, 0, "Score: %d", score);
//     refresh();
// }

// void SnakeGame::input() {
//     int ch = getch();
//     switch (ch) {
//         case KEY_LEFT:
//             if (dir != RIGHT) dir = LEFT;
//             break;
//         case KEY_RIGHT:
//             if (dir != LEFT) dir = RIGHT;
//             break;
//         case KEY_UP:
//             if (dir != DOWN) dir = UP;
//             break;
//         case KEY_DOWN:
//             if (dir != UP) dir = DOWN;
//             break;
//         case 'q':
//             game_over = true;
//             break;
//     }
// }

// void SnakeGame::logic() {
//     switch (dir) {
//         case LEFT:
//             x--;
//             break;
//         case RIGHT:
//             x++;
//             break;
//         case UP:
//             y--;
//             break;
//         case DOWN:
//             y++;
//             break;
//         default:
//             break;
//     }

//     if (x >= width) x = 0; else if (x < 0) x = width - 1;
//     if (y >= height) y = 0; else if (y < 0) y = height - 1;

//     for (auto s : snake) {
//         if (s.first == x && s.second == y) {
//             game_over = true;
//         }
//     }

//     snake.push_back({x, y});
//     if (x == fruit_x && y == fruit_y) {
//         score += 10;
//         fruit_x = std::rand() % width;
//         fruit_y = std::rand() % height;
//     } else {
//         snake.erase(snake.begin());
//     }
// }

// void SnakeGame::end_game() {
//     nodelay(stdscr, FALSE);
//     mvprintw(height / 2, (width - 10) / 2, "Game Over!");
//     mvprintw(height / 2 + 1, (width - 19) / 2, "Press any key to exit...");
//     refresh();
//     getch();
//     endwin();
// }

#include "snake_game.h"
#include <cstdlib>
#include <ctime>

SnakeGame::SnakeGame() :
    game_over(false),
    width(20),
    height(20),
    x(width / 2),
    y(height / 2),
    score(0),
    dir(STOP) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    spawn_fruit();
    snake.push_back({x, y});
}

void SnakeGame::initialize() {
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    // Initialize colors
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Snake
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Fruit
    init_pair(3, COLOR_WHITE, COLOR_BLACK);  // Border
}

void SnakeGame::draw() {
    clear();

    // Draw border
    attron(COLOR_PAIR(3));
    for (int i = 0; i < width + 2; ++i) {
        mvaddch(0, i, '#');
        mvaddch(height + 1, i, '#');
    }
    for (int i = 0; i < height + 2; ++i) {
        mvaddch(i, 0, '#');
        mvaddch(i, width + 1, '#');
    }
    attroff(COLOR_PAIR(3));

    // Draw snake
    attron(COLOR_PAIR(1));
    for (const auto& segment : snake) {
        mvaddch(segment.second + 1, segment.first + 1, 'O');
    }
    attroff(COLOR_PAIR(1));

    // Draw fruit
    attron(COLOR_PAIR(2));
    mvaddch(fruit_y + 1, fruit_x + 1, 'F');
    attroff(COLOR_PAIR(2));

    // Draw score
    mvprintw(height + 3, 0, "Score: %d", score);
    refresh();
}

void SnakeGame::input() {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            if (dir != RIGHT) dir = LEFT;
            break;
        case KEY_RIGHT:
            if (dir != LEFT) dir = RIGHT;
            break;
        case KEY_UP:
            if (dir != DOWN) dir = UP;
            break;
        case KEY_DOWN:
            if (dir != UP) dir = DOWN;
            break;
        case 'q':
            game_over = true;
            break;
    }
}

void SnakeGame::logic() {
    int new_x = x;
    int new_y = y;

    switch (dir) {
        case LEFT:  new_x--; break;
        case RIGHT: new_x++; break;
        case UP:    new_y--; break;
        case DOWN:  new_y++; break;
        default: return;
    }

    // Wrap around screen edges
    if (new_x >= width) new_x = 0;
    else if (new_x < 0) new_x = width - 1;
    if (new_y >= height) new_y = 0;
    else if (new_y < 0) new_y = height - 1;

    // Check for collision with self
    if (check_collision(new_x, new_y)) {
        game_over = true;
        return;
    }

    // Update snake position
    x = new_x;
    y = new_y;
    snake.push_back({x, y});

    // Check if fruit is eaten
    if (x == fruit_x && y == fruit_y) {
        score += 10;
        spawn_fruit();
    } else {
        snake.erase(snake.begin());
    }
}

bool SnakeGame::check_collision(int new_x, int new_y) const {
    for (const auto& segment : snake) {
        if (segment.first == new_x && segment.second == new_y) {
            return true;
        }
    }
    return false;
}

void SnakeGame::spawn_fruit() {
    do {
        fruit_x = rand() % width;
        fruit_y = rand() % height;
    } while (check_collision(fruit_x, fruit_y));
}

void SnakeGame::end_game() {
    nodelay(stdscr, FALSE);
    clear();
    mvprintw(height / 2, (width - 10) / 2, "Game Over!");
    mvprintw(height / 2 + 1, (width - 19) / 2, "Final Score: %d", score);
    mvprintw(height / 2 + 2, (width - 22) / 2, "Press any key to exit...");
    refresh();
    getch();
    endwin();
}
