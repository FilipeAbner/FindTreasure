#pragma once
#define _GAME_HPP_

#include "maze.hpp"
#include <GL/glut.h>

// Enumeração de cores
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

// Definição da estrutura Colors
struct Colors
{
    float cor[3];

    // Construtor para facilitar a inicialização
    Colors(float r, float g, float b)
    {
        cor[0] = r;
        cor[1] = g;
        cor[2] = b;
    }
};
// Declaração do array de cores predefinidas (extern para evitar múltiplas definições)
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
