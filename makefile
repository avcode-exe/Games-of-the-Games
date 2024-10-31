CXX = g++
CPPFLAGS = -pedantic-errors -Werror -std=c++17 -fPIE -I. -I./Maze
LDFLAGS = -lncurses -lpthread

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/Maze/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJS := $(patsubst $(SRC_DIR)/Maze/%.cpp, $(OBJ_DIR)/Maze/%.o, $(OBJS))

# Executable
TARGET = $(BIN_DIR)/games_of_the_games.out

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/Maze/%.o: $(SRC_DIR)/Maze/%.cpp | $(OBJ_DIR)/Maze
	$(CXX) $(CPPFLAGS) -c $< -o $@

# Create directories if they don't exist
$(BIN_DIR) $(OBJ_DIR) $(OBJ_DIR)/Maze:
	mkdir -p $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean run