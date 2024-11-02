CXX = g++
CPPFLAGS = -pedantic-errors -Werror -std=c++17 -fPIE -I. -I./Maze -I./Player -I./Minesweeper -I./2048
LDFLAGS = -lncursesw -lpthread

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

# Header files
HEADERS = $(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/Maze/*.h) $(wildcard $(SRC_DIR)/Player/*.h) $(wildcard $(SRC_DIR)/Minesweeper/*.h) $(wildcard $(SRC_DIR)/2048/*.h)
PCHS = $(patsubst $(SRC_DIR)/%.h, $(BIN_DIR)/%.gch, $(HEADERS))
PCHS := $(patsubst $(SRC_DIR)/Maze/%.h, $(BIN_DIR)/Maze/%.gch, $(PCHS))
PCHS := $(patsubst $(SRC_DIR)/Player/%.h, $(BIN_DIR)/Player/%.gch, $(PCHS))
PCHS := $(patsubst $(SRC_DIR)/Minesweeper/%.h, $(BIN_DIR)/Minesweeper/%.gch, $(PCHS))
PCHS := $(patsubst $(SRC_DIR)/2048/%.h, $(BIN_DIR)/2048/%.gch, $(PCHS))

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/Maze/*.cpp) $(wildcard $(SRC_DIR)/Player/*.cpp) $(wildcard $(SRC_DIR)/Minesweeper/*.cpp) $(wildcard $(SRC_DIR)/2048/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJS := $(patsubst $(SRC_DIR)/Maze/%.cpp, $(OBJ_DIR)/Maze/%.o, $(OBJS))
OBJS := $(patsubst $(SRC_DIR)/Player/%.cpp, $(OBJ_DIR)/Player/%.o, $(OBJS))
OBJS := $(patsubst $(SRC_DIR)/Minesweeper/%.cpp, $(OBJ_DIR)/Minesweeper/%.o, $(OBJS))
OBJS := $(patsubst $(SRC_DIR)/2048/%.cpp, $(OBJ_DIR)/2048/%.o, $(OBJS))

# Dependency files
DEPS = $(OBJS:.o=.d)

# Shared object files
MAZE_SO = $(LIB_DIR)/libmaze.so
PLAYER_SO = $(LIB_DIR)/libplayer.so
MINESWEEPER_SO = $(LIB_DIR)/libminesweeper.so
GAME2048_SO = $(LIB_DIR)/libgame2048.so

# Executable
TARGET = $(BIN_DIR)/games_of_the_games.out

# Run the executable
run: $(TARGET)
	LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH ./$(TARGET)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS) $(MAZE_SO) $(PLAYER_SO) $(MINESWEEPER_SO) $(GAME2048_SO) | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -L$(LIB_DIR) -lmaze -lplayer -lminesweeper -lgame2048

# Create shared object files
$(MAZE_SO): $(wildcard $(SRC_DIR)/Maze/*.cpp) | $(LIB_DIR)
	$(CXX) $(CPPFLAGS) -shared -fPIC -o $@ $^

$(PLAYER_SO): $(wildcard $(SRC_DIR)/Player/*.cpp) | $(LIB_DIR)
	$(CXX) $(CPPFLAGS) -shared -fPIC -o $@ $^

$(MINESWEEPER_SO): $(wildcard $(SRC_DIR)/Minesweeper/*.cpp) | $(LIB_DIR)
	$(CXX) $(CPPFLAGS) -shared -fPIC -o $@ $^

$(GAME2048_SO): $(wildcard $(SRC_DIR)/2048/*.cpp) | $(LIB_DIR)
	$(CXX) $(CPPFLAGS) -shared -fPIC -o $@ $^

# Precompile header files
$(BIN_DIR)/%.gch: $(SRC_DIR)/%.h | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

$(BIN_DIR)/Maze/%.gch: $(SRC_DIR)/Maze/%.h | $(BIN_DIR)/Maze
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

$(BIN_DIR)/Player/%.gch: $(SRC_DIR)/Player/%.h | $(BIN_DIR)/Player
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

$(BIN_DIR)/Minesweeper/%.gch: $(SRC_DIR)/Minesweeper/%.h | $(BIN_DIR)/Minesweeper
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

$(BIN_DIR)/2048/%.gch: $(SRC_DIR)/2048/%.h | $(BIN_DIR)/2048
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

# Mark .gch files as secondary to prevent them from being removed
.SECONDARY: $(PCHS)

# Compile source files into object files and generate dependency files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(PCHS) | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -MMD -MF $(@:.o=.d) -c $< -o $@

$(OBJ_DIR)/Maze/%.o: $(SRC_DIR)/Maze/%.cpp $(PCHS) | $(OBJ_DIR)/Maze
	$(CXX) $(CPPFLAGS) -MMD -MF $(@:.o=.d) -c $< -o $@

$(OBJ_DIR)/Player/%.o: $(SRC_DIR)/Player/%.cpp $(PCHS) | $(OBJ_DIR)/Player
	$(CXX) $(CPPFLAGS) -MMD -MF $(@:.o=.d) -c $< -o $@

$(OBJ_DIR)/Minesweeper/%.o: $(SRC_DIR)/Minesweeper/%.cpp $(PCHS) | $(OBJ_DIR)/Minesweeper
	$(CXX) $(CPPFLAGS) -MMD -MF $(@:.o=.d) -c $< -o $@

$(OBJ_DIR)/2048/%.o: $(SRC_DIR)/2048/%.cpp $(PCHS) | $(OBJ_DIR)/2048
	$(CXX) $(CPPFLAGS) -MMD -MF $(@:.o=.d) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Create directories if they don't exist
$(BIN_DIR) $(OBJ_DIR) $(OBJ_DIR)/Maze $(BIN_DIR)/Maze $(OBJ_DIR)/Player $(BIN_DIR)/Player $(OBJ_DIR)/Minesweeper $(BIN_DIR)/Minesweeper $(OBJ_DIR)/2048 $(BIN_DIR)/2048 $(LIB_DIR):
	mkdir -p $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

# Phony targets
.PHONY: all clean run