MAIN = jogo
BUILD_DIR = build
SRC = src/main.cpp src/game/game.cpp src/game/textures.cpp
OBJECTS = $(SRC:%.cpp=$(BUILD_DIR)/%.o)
FLAGS = -std=c++17 -pedantic-errors -g

# operating system identification
ifeq ($(OS),Windows_NT)
    CC = x86_64-w64-mingw32-g++  # Cross-compiler for Windows
    OPENGL_FLAG = -lopengl32 -lglu32 -lfreeglut
    RM = rm
    EXE = .exe
else
    CC = g++  # Default compiler for Linux
    OPENGL_FLAG = -lGL -lGLU -lglut -lGLEW
    LDFLAGS = -L/usr/lib
    MATH = -lm  # math functions (sin, cos, sqrt, etc.)
    RM = rm -rf
endif

# header include directories
STB_INCLUDE_DIR = /usr/include/stb
INCLUDE_DIRS = -I$(STB_INCLUDE_DIR) -Isrc

# default target: build executable
all: $(BUILD_DIR)/$(MAIN)$(EXE)

# rule for generating the executable file
$(BUILD_DIR)/$(MAIN)$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(FLAGS) $(OPENGL_FLAG) $(MATH) $(LDFLAGS)

# compile each source file and create the output directory if needed
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDE_DIRS)

# remove all compiled files
clean:
	$(RM) $(BUILD_DIR)

# compile and run
run: all
	./$(BUILD_DIR)/$(MAIN)$(EXE)
