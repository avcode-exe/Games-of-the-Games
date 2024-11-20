// #ifndef SNAKE_GAME_H
// #define SNAKE_GAME_H

// #include <vector>
// #include <ncurses.h>

// class SnakeGame {
// public:
//     SnakeGame();
//     void initialize();
//     void draw();
//     void input();
//     void logic();
//     void end_game();

//     bool game_over;
//     int width, height;
//     int x, y, fruit_x, fruit_y, score;
//     enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
//     Direction dir;
//     std::vector<std::pair<int, int>> snake;
// };

// #endif

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <vector>
#include <ncurses.h>

class SnakeGame {
public:
    SnakeGame();
    void initialize();
    void draw();
    void input();
    void logic();
    void end_game();
    [[nodiscard]] bool is_game_over() const { return game_over; }

private:
    bool game_over;
    int width, height;
    int x, y, fruit_x, fruit_y, score;
    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    Direction dir;
    std::vector<std::pair<int, int>> snake;
    bool check_collision(int new_x, int new_y) const;
    void spawn_fruit();
};

#endif
