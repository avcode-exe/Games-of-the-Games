cmake_minimum_required(VERSION 3.10)

# Project name
project(GamesOfTheGames)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Maze)
include_directories(${PROJECT_SOURCE_DIR}/Player)
include_directories(${PROJECT_SOURCE_DIR}/Minesweeper)

# Precompiled headers
if(USE_PCH)
    set(PCH_HEADER "game_header.h")
    set(PCH_SOURCE "${CMAKE_BINARY_DIR}/pch.cpp")
    file(WRITE ${PCH_SOURCE} "#include \"${PCH_HEADER}\"\n")
    add_library(pch STATIC ${PCH_SOURCE})
    target_precompile_headers(pch PRIVATE ${PCH_HEADER})
endif()

# Source files
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/*.cpp"
    "${PROJECT_SOURCE_DIR}/Maze/*.cpp"
    "${PROJECT_SOURCE_DIR}/Player/*.cpp"
    "${PROJECT_SOURCE_DIR}/Minesweeper/*.cpp"
)

# Exclude CMakeCXXCompilerId.cpp
list(FILTER SOURCES EXCLUDE REGEX ".*CMakeCXXCompilerId.cpp")

# Shared libraries
add_library(maze SHARED ${PROJECT_SOURCE_DIR}/Maze/utils.cpp)
add_library(player SHARED ${PROJECT_SOURCE_DIR}/Player/player.cpp)
add_library(minesweeper SHARED ${PROJECT_SOURCE_DIR}/Minesweeper/utils.cpp ${PROJECT_SOURCE_DIR}/Minesweeper/minesweeper_main.cpp)

# Executable
add_executable(GamesOfTheGames.out ${SOURCES} ${PROJECT_SOURCE_DIR}/game_functions.cpp)

# Link libraries
target_link_libraries(GamesOfTheGames.out ncursesw pthread maze player minesweeper)
if(USE_PCH)
    target_link_libraries(GamesOfTheGames.out pch)
endif()

# Generate dependency files
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MMD -MP")

# Custom target to run the executable
add_custom_target(run
    COMMAND GamesOfTheGames.out
    DEPENDS GamesOfTheGames.out
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running GamesOfTheGames.out"
)
