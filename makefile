MAIN = jogo
OBJECTS = main.o game.o
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

all: $(MAIN)$(EXE)

# rule for generating the executable file
$(MAIN)$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(MAIN)$(EXE) $(FLAGS) $(OPENGL_FLAG) $(MATH) $(LDFLAGS)

# object compilation rule (ensuring that all objects use the -g flag)
$(OBJECTS): %.o: %.cpp
	$(CC) -c $< -o $@ $(FLAGS) -I$(STB_INCLUDE_DIR)

# Clean Proejct
clean:
	$(RM) $(OBJECTS) $(MAIN)$(EXE)

# compile and run
run: all
	./$(MAIN)$(EXE)
