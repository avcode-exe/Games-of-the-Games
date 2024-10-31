CXX = g++
CPPFLAGS = -pedantic-errors -Werror -std=c++17 -fPIE -I. -I./Maze -I./Player
LDFLAGS = -lncurses -lpthread

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Header files
HEADERS = $(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/Maze/*.h) $(wildcard $(SRC_DIR)/Player/*.h)
PCHS = $(patsubst $(SRC_DIR)/%.h, $(BIN_DIR)/%.gch, $(HEADERS))
PCHS := $(patsubst $(SRC_DIR)/Maze/%.h, $(BIN_DIR)/Maze/%.gch, $(PCHS))
PCHS := $(patsubst $(SRC_DIR)/Player/%.h, $(BIN_DIR)/Player/%.gch, $(PCHS))

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/Maze/*.cpp) $(wildcard $(SRC_DIR)/Player/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJS := $(patsubst $(SRC_DIR)/Maze/%.cpp, $(OBJ_DIR)/Maze/%.o, $(OBJS))
OBJS := $(patsubst $(SRC_DIR)/Player/%.cpp, $(OBJ_DIR)/Player/%.o, $(OBJS))

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

# Precompile header files
$(BIN_DIR)/%.gch: $(SRC_DIR)/%.h | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

$(BIN_DIR)/Maze/%.gch: $(SRC_DIR)/Maze/%.h | $(BIN_DIR)/Maze
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

$(BIN_DIR)/Player/%.gch: $(SRC_DIR)/Player/%.h | $(BIN_DIR)/Player
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

# Mark .gch files as secondary to prevent them from being removed
.SECONDARY: $(PCHS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(PCHS) | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/Maze/%.o: $(SRC_DIR)/Maze/%.cpp $(PCHS) | $(OBJ_DIR)/Maze
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/Player/%.o: $(SRC_DIR)/Player/%.cpp $(PCHS) | $(OBJ_DIR)/Player
	$(CXX) $(CPPFLAGS) -c $< -o $@

# Create directories if they don't exist
$(BIN_DIR) $(OBJ_DIR) $(OBJ_DIR)/Maze $(BIN_DIR)/Maze $(OBJ_DIR)/Player $(BIN_DIR)/Player:
	mkdir -p $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean run