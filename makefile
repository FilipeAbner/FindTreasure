MAIN = jogo
BUILD_DIR = build
SRC = main.cpp game.cpp
OBJECTS = $(SRC:%.cpp=$(BUILD_DIR)/%.o)
FLAGS = -std=c++17 -pedantic-errors -g


# operating system identification
ifeq ($(OS),Windows_NT)
# Settings for Windows
    CC = x86_64-w64-mingw32-g++  # Cross-compiler
    OPENGL_FLAG = -lopengl32 -lglu32 -lfreeglut
    RM = rm
    EXE = .exe
else
# Settings for Linux (Ubuntu)
    CC = g++
    OPENGL_FLAG = -lGL -lGLU -lglut -lGLEW
    LDFLAGS = -L/usr/lib
    MATH = -lm # math functions (sin, cos, sqrt, etc.)
    RM = rm -rf
endif
STB_INCLUDE_DIR = /usr/include/stb

all: $(BUILD_DIR)/$(MAIN)$(EXE)

# create build dir if dont exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(MAIN)$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(FLAGS) $(OPENGL_FLAG) $(MATH) $(LDFLAGS)

# compile inside build dir
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(FLAGS) -I$(STB_INCLUDE_DIR)

# Clean Proejct
clean:
	$(RM) $(BUILD_DIR)

# compile and run
run: all
	./$(BUILD_DIR)/$(MAIN)$(EXE)
