#pragma once
#define _GAME_HPP_

#include "util/maze.hpp"
#include "util/colors.hpp"
#include <GL/glut.h>

// Declaring the array of predefined colors (extern to avoid multiple definitions)
extern const Colors predefinedColors[];
extern GLuint WinTextureID;
extern GLuint wallTextureID;
extern GLuint PlayerTextureID;
extern GLuint TreasureTextureID;
extern GLuint WinTextureID;
extern GLuint FloorTextureID;

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
