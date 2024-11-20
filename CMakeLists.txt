cmake_minimum_required(VERSION 3.10)
project(GamesOfTheGames)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Maze)
include_directories(${PROJECT_SOURCE_DIR}/Minesweeper)
include_directories(${PROJECT_SOURCE_DIR}/2048)
include_directories(${PROJECT_SOURCE_DIR}/Tic-Tac-Toe)
include_directories(${PROJECT_SOURCE_DIR}/Snake) # Add this line

option(USE_PCH "Use precompiled headers" ON)
if(USE_PCH)
    set(PCH_HEADER "game_header.h")
    set(PCH_SOURCE "${CMAKE_BINARY_DIR}/pch.cpp")
    file(WRITE ${PCH_SOURCE} "#include \"${PCH_HEADER}\"\n")
    add_library(pch STATIC ${PCH_SOURCE})
    target_precompile_headers(pch PRIVATE ${PCH_HEADER})
endif()

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/*.cpp"
    "${PROJECT_SOURCE_DIR}/Maze/*.cpp"
    "${PROJECT_SOURCE_DIR}/Minesweeper/*.cpp"
    "${PROJECT_SOURCE_DIR}/2048/*.cpp"
    "${PROJECT_SOURCE_DIR}/Tic-Tac-Toe/*.cpp"
    "${PROJECT_SOURCE_DIR}/Snake/*.cpp" # Add this line
)

list(FILTER SOURCES EXCLUDE REGEX ".*CMakeCXXCompilerId.cpp")

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
add_library(maze SHARED ${PROJECT_SOURCE_DIR}/Maze/utils.cpp)
add_library(minesweeper SHARED ${PROJECT_SOURCE_DIR}/Minesweeper/utils.cpp ${PROJECT_SOURCE_DIR}/Minesweeper/minesweeper_main.cpp)
add_library(game2048 SHARED ${PROJECT_SOURCE_DIR}/2048/2048_main.cpp ${PROJECT_SOURCE_DIR}/2048/utils.cpp) # Added utils.cpp for 2048
add_library(tictactoe SHARED ${PROJECT_SOURCE_DIR}/Tic-Tac-Toe/utils.cpp ${PROJECT_SOURCE_DIR}/Tic-Tac-Toe/tic_tac_toe_main.cpp ${PROJECT_SOURCE_DIR}/Tic-Tac-Toe/minimax.cpp)
add_library(snake SHARED ${PROJECT_SOURCE_DIR}/Snake/utils.cpp ${PROJECT_SOURCE_DIR}/Snake/snake_main.cpp) # Add snake_main.cpp

add_executable(GamesOfTheGames.out ${SOURCES})

target_link_libraries(GamesOfTheGames.out ncursesw pthread maze minesweeper game2048 tictactoe snake)

if(USE_PCH)
    target_link_libraries(GamesOfTheGames.out pch)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MMD -MP")

add_custom_target(run
    COMMAND GamesOfTheGames.out
    DEPENDS GamesOfTheGames.out
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running GamesOfTheGames.out"
)
