#pragma once
#define _GAME_HPP_

#include "util/maze.hpp"
#include <GL/glut.h>

// Color enumeration
enum Color
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE,
    BLACK,
    GOLD,
    PURPLE,
    ORANGE,
    SILVER,
    GRAY,
    PINK,
    CYAN,
    BROWN,
    GOLDENROD,
    SADDLEBROWN,
    INDIGO,
    LIGHT_GREEN,
    DARK_ORANGE,
    DARK_SLATE_GRAY,
    DARK_PURPLE,
    YELLOW_GREEN,
    SLATE_BLUE,
    DARK_GREEN
};

// Definition of the Colors structure
struct Colors
{
    float cor[3];

    // Constructor to facilitate initialization
    Colors(float r, float g, float b)
    {
        cor[0] = r;
        cor[1] = g;
        cor[2] = b;
    }
};
// Declaring the array of predefined colors (extern to avoid multiple definitions)
extern const Colors predefinedColors[];
extern GLuint WinTextureID;

void display();
void keyboard(unsigned char key, int x, int y);
void timer(int value);
void updateScore();
void checkCollision(int x, int y);

void initGL();
void loadMaze(const char *file);
void initTextures();
GLuint loadTexture(const char *filename);

void drawPlayer();
void drawMaze();
void drawLines();
void drawText(const char *text, float x, float y, Colors textColor, Colors shadowColor);
void drawGameOver();
void drawVictory();
