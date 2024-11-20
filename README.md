# Games-of-the-Games

## Introduction

Welcome to the Games-of-the-Games project! This project is a collection of games written in C++. The games included are Maze, Minesweeper, Hangman, 2048, and Tic-Tac-Toe. The project is designed to be easily extendable, and more games can be added in the future.

## Project Description

This project is a collection of games that I have created. The games are written in C++. I'm planning to add more games
in the future.

|  Game Name  |   Status   |
|:-----------:|:----------:|
|  Maze Game  | Completed  |
| Minesweeper | Completed  |
|   Hangman   | Terminated |
|    2048     | Completed  |
| Tic-Tac-Toe | Completed  |
| Snake Game  | Completed  |
|   Sudoku    |  Planned   |

# Installation and Compilation

**Currently only supported on Linux**

To compile the games, you need to have a C++ compiler installed on your machine. You can use any C++ compiler of your
choice. I have used g++ compiler to compile the games.

You need to install the most important library for this project, which is `ncurses`. You can install it by running the
following command in your terminal:

```bash
sudo apt install libncurses5-dev libncursesw5-dev
```

## Method 1: Using Makefile

Next, make sure that your machine has `make`, if you don't have `make` installed, you can install it by running the
following command in your terminal:

```bash
sudo apt install make
```

After that, clone the repository by running the following command in your terminal:

```bash
git clone https://github.com/avcode-exe/Games-of-the-Games.git
```

After cloning the repository, you can compile the games by running the following commands in your terminal:

```bash
cd Games-of-the-Games
make run
```

**Important**: If you want to try out the latest unreleased features, you need to switch to the corresponding branch.
You can switch to the branch by running the following command in your terminal:

```bash
git checkout <branch-name>
```

Once you have switched to the branch, you can compile the program as mentioned above.

## Method 2: Using CMake

Alternatively, you can use CMake to build the project. The project using CMake with precompiled headers, shared
libraries, and dependency files.

Follow these steps:

1. Create a build directory:

```bash
mkdir build
cd build
```

2. Run CMake to configure the project and generate the build files:

```bash
cmake ..
```

3. Build the project using the generated build files:

```bash
cmake --build .
```

4. Run the compiled executable:

```bash
./games-of-the-games
```

or

```bash
cmake --build . --target run
```

**Note**: If you want to build the project without precompiled headers, shared libraries, and dependency files, you can
follow these steps:

1. Run CMake to configure the project and generate the build files without precompiled headers, shared libraries, and
   dependency files:

```bash
cmake -DUSE_PCH=OFF -DBUILD_SHARED_LIBS=OFF -DCMAKE_DEPENDS_USE_COMPILER=OFF ..
```

2. Build the project using the generated build files:

```bash
cmake --build .
```

3. Run the compiled executable:

```bash
./games-of-the-games
```

or

```bash
cmake --build . --target run
```

# List of Features

**Important**: The features that are not in the `main` branch are not listed here, and in the future, the development of
the features may be terminated.

## Maze Game

* The game has a maze that the player needs to solve.
* The player can move the character using the arrow keys.
* The maze was generated randomly using the Depth-First Search algorithm.

## Minesweeper

* The game has a grid of cells that contain mines.
* The player needs to clear the grid without detonating any mines.
* The player can flag the cells that contain mines.
* The player can reveal the cells that do not contain mines.
* The game has three difficulty levels: Easy, Medium, and Hard.

## 2048

* The game has a grid of cells that contain numbers.
* The player needs to merge the cells to create a cell with the number 2048.
* The player can move the cells using the arrow keys.
* The game has a score system that keeps track of the player's score.

## Tic-Tac-Toe

* The game has a grid of cells that the player needs to fill with their symbol.
* The player is playing against the computer with minimax algorithm.
* The player can move the cursor using the arrow keys.

## Snake Game

* The game has a snake that the player needs to control with the arrow keys.
* The snake needs to eat the food to grow.
* The game has a score system that keeps track of the player's score.
* The snake can go through the walls and appear on the opposite side.

# Credit

Some of the games in this project (maze and minewseeper) are based on the origin
project (https://github.com/avcode-exe/ENGG1340-Group-19-Project). Thanks for the contributors of that project!

# License

This project is licensed under the Apache License - see the [LICENSE](LICENSE) file for details.

# Contributing

If you want to contribute to this project, you can fork the repository and create a pull request. I will review the pull
request and merge it if it meets the requirements.
