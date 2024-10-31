CXX = g++
CPPFLAGS = -pedantic-errors -Werror -std=c++17 -fPIE -I. -I./Maze -I./Player
LDFLAGS = -lncurses -lpthread

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

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

# Dependency files
DEPS = $(OBJS:.o=.d)

# Shared object files
MAZE_SO = $(LIB_DIR)/libmaze.so
PLAYER_SO = $(LIB_DIR)/libplayer.so

# Executable
TARGET = $(BIN_DIR)/games_of_the_games.out

# Run the executable
run: $(TARGET)
	LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH ./$(TARGET)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS) $(MAZE_SO) $(PLAYER_SO) | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -L$(LIB_DIR) -lmaze -lplayer

# Create shared object files
$(MAZE_SO): $(wildcard $(SRC_DIR)/Maze/*.cpp) | $(LIB_DIR)
	$(CXX) $(CPPFLAGS) -shared -fPIC -o $@ $^

$(PLAYER_SO): $(wildcard $(SRC_DIR)/Player/*.cpp) | $(LIB_DIR)
	$(CXX) $(CPPFLAGS) -shared -fPIC -o $@ $^

# Precompile header files
$(BIN_DIR)/%.gch: $(SRC_DIR)/%.h | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

$(BIN_DIR)/Maze/%.gch: $(SRC_DIR)/Maze/%.h | $(BIN_DIR)/Maze
	$(CXX) $(CPPFLAGS) -x c++-header $< -o $@

$(BIN_DIR)/Player/%.gch: $(SRC_DIR)/Player/%.h | $(BIN_DIR)/Player
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

# Include dependency files
-include $(DEPS)

# Create directories if they don't exist
$(BIN_DIR) $(OBJ_DIR) $(OBJ_DIR)/Maze $(BIN_DIR)/Maze $(OBJ_DIR)/Player $(BIN_DIR)/Player $(LIB_DIR):
	mkdir -p $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

# Phony targets
.PHONY: all clean run