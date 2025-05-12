#include <GL/glew.h>
#include <GL/glut.h>
#include "game.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WIN32
#include <stb/stb_image.h>
#else
#include "stb_image.h"
#endif

#include <algorithm>
using namespace std;

float playerY, playerX;
int score = 0;
int windowWidth = 800;
int windowHeight = 600;
float cellSize;
bool gameOver = false;
bool victory = false;
int startTime;
Maze maze;
string mapFileName;
float timeLeft = 60000.0;
float squareSize = 1.0f;

GLuint wallTextureID;
GLuint PlayerTextureID;
GLuint TreasureTextureID;
GLuint WinTextureID;
GLuint FloorTextureID;

const Colors predefinedColors[] = {
    Colors(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f),     // RED
    Colors(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f),     // GREEN
    Colors(0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f),     // BLUE
    Colors(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f),   // YELLOW
    Colors(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f), // WHITE
    Colors(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f),       // BLACK
    Colors(218.0f / 255.0f, 165.0f / 255.0f, 32.0f / 255.0f),  // GOLD
    Colors(128.0f / 255.0f, 0.0f / 255.0f, 128.0f / 255.0f),   // PURPLE
    Colors(255.0f / 255.0f, 165.0f / 255.0f, 0.0f / 255.0f),   // ORANGE
    Colors(192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f), // SILVER
    Colors(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f), // GRAY
    Colors(255.0f / 255.0f, 192.0f / 255.0f, 203.0f / 255.0f), // PINK
    Colors(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f),   // CYAN
    Colors(165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f),   // BROWN
    Colors(255.0f / 255.0f, 215.0f / 255.0f, 0.0f / 255.0f),   // GOLDENROD
    Colors(139.0f / 255.0f, 69.0f / 255.0f, 19.0f / 255.0f),   // SADDLEBROWN
    Colors(75.0f / 255.0f, 0.0f / 255.0f, 130.0f / 255.0f),    // INDIGO
    Colors(144.0f / 255.0f, 238.0f / 255.0f, 144.0f / 255.0f), // LIGHT GREEN
    Colors(255.0f / 255.0f, 140.0f / 255.0f, 0.0f / 255.0f),   // DARK ORANGE
    Colors(47.0f / 255.0f, 79.0f / 255.0f, 79.0f / 255.0f),    // DARK SLATE GRAY
    Colors(29.0 / 255.0, 13.0 / 255.0, 89.0 / 255.0),          // DARK PURPLE
    Colors(232.0 / 255.0, 232.0 / 255.0, 5.0 / 255.0),         // YELLOW_GREEN
    Colors(106.0f / 255.0f, 90.0f / 255.0f, 205.0f / 255.0f),  // SLATE_BLUE
    Colors(2.0f / 255.0f, 48.0f / 255.0f, 32.0f / 255.0f),  // DARK GREEN
};

void initTextures()
{
    wallTextureID = loadTexture("img/assets/wall.png");
    if (wallTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura do labirinto!" << std::endl;
        exit(EXIT_FAILURE); // Sai do programa se a textura falhar
    }

    PlayerTextureID = loadTexture("img/assets/Player.png");
    if (PlayerTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura do Player!" << std::endl;
        exit(EXIT_FAILURE); // Sai do programa se a textura falhar
    }

    TreasureTextureID = loadTexture("img/assets/Treasure.png");
    if (TreasureTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura do Tesouro!" << std::endl;
        exit(EXIT_FAILURE); // Sai do programa se a textura falhar
    }

    WinTextureID = loadTexture("img/assets/Win.png");
    if (WinTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura de Win!" << std::endl;
        exit(EXIT_FAILURE); // Sai do programa se a textura falhar
    }

    FloorTextureID = loadTexture("img/assets/floor.png");
    if (FloorTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura de Floor!" << std::endl;
        exit(EXIT_FAILURE); // Sai do programa se a textura falhar
    }
}

void reloadMap()
{
}

GLuint loadTexture(const char *filename)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data)
    {
        cerr << "Falha ao carregar a textura: " << filename << endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Configuração de parâmetros da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    return textureID;
}

void drawPlayer()
{
    glColor3f(predefinedColors[WHITE].cor[0], predefinedColors[WHITE].cor[1], predefinedColors[WHITE].cor[2]); // Garante que a textura não seja afetada por cores anteriores
    glBindTexture(GL_TEXTURE_2D, PlayerTextureID);                                                             // Usa a textura do personagem
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(playerX, playerY);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(playerX + squareSize, playerY);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(playerX + squareSize, playerY + squareSize);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(playerX, playerY + squareSize);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void updateScore()
{
    score += 1;
    if (score == maze.treasures)
    {
        victory = true;
    }
}

void checkCollision(int x, int y)
{
    if (maze.grid[y][x] != '1')
    {
        playerX = x;
        playerY = y;
    }

    if (maze.grid[y][x] == '*')
    {
        updateScore();
        maze.grid[y][x] = '0';
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (!gameOver && !victory)
    {
        drawMaze();
        drawPlayer();
        drawLines();

        std::stringstream ss;
        ss << "Time: " << (int)(timeLeft / 1000) << "s";
        drawText(ss.str().c_str(), 0.8f, 0.8f, predefinedColors[GOLD], predefinedColors[GRAY]);

        string score_str = "Score: " + std::to_string(score);
        drawText(score_str.c_str(), 0.8f, 0.4f, predefinedColors[GOLD], predefinedColors[GRAY]);
    }
    else if (gameOver)
    { // tela de game over
        drawGameOver();
    }
    else
    {
        drawMaze();
        drawLines();
        drawVictory();
    }
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    float nextX, nextY;
    nextX = playerX;
    nextY = playerY;

    switch (key)
    {
    case 'w':
    case 'W':
        if (playerY > 0 && playerY <= maze.rows - 1)
        {
            // playerY--;
            nextY -= squareSize;
        }
        break;
    case 'a':
    case 'A':
        if (playerX > 0 && playerX <= maze.cols - 1)
        {
            // playerX--;
            nextX -= squareSize;
        }
        break;
    case 's':
    case 'S':
        if (playerY >= 0 && playerY < maze.rows - 1)
        {
            // playerY++;
            nextY += squareSize;
        }
        break;
    case 'd':
    case 'D':
        if (playerX >= 0 && playerX < maze.cols - 1)
        {
            // playerX++;
            nextX += squareSize;
        }
        break;
    case 'r':
    case 'R':
        if (gameOver || victory)
        {
            maze.treasures = 0;
            loadMaze(mapFileName.c_str());
            gameOver = false;
            victory = false;
            score = 0;
            timeLeft = 60000.0;
            nextX = playerX = maze.startCol;
            nextY = playerY = maze.startRow;
        }
        break;
    }

    checkCollision(nextX, nextY);
    glutPostRedisplay();
}

// Texto com Sombra
void drawText(const char *text, float x, float y, Colors textColor, Colors shadowColor)
{
    // Desenhar sombra com deslocamento
    glColor3f(shadowColor.cor[0], shadowColor.cor[1], shadowColor.cor[2]);
    glRasterPos2f(x + 0.015f, y - 0.015f); // Pequeno deslocamento para a sombra
    const char *t = text;
    while (*t)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *t);
        t++;
    }

    // Desenhar texto principal
    glColor3f(textColor.cor[0], textColor.cor[1], textColor.cor[2]);
    glRasterPos2f(x, y);
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

void timer(int value)
{
    if (timeLeft < 0 && victory == false)
    {
        gameOver = true;
        timeLeft = -1;
    }
    if (!gameOver && victory == false)
    {
        timeLeft -= value;
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 16);
}

void initGL()
{
    mapFileName = "mapa.txt";
    initTextures();
    loadMaze(mapFileName.c_str());
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, maze.cols, maze.rows, 0);
}

void loadMaze(const char *file_name)
{
    fstream file;
    file.open(file_name, fstream::in);

    string linha;
    string value;
    stringstream ss;

    // lê a linha que contém o tamanho do labirinto
    getline(file, linha);
    ss = stringstream(linha);

    getline(ss, value, ' ');
    maze.rows = stoi(value);
    getline(ss, value, ' ');
    maze.cols = stoi(value);

    maze.grid = vector<vector<char>>(maze.rows, vector<char>(maze.cols));

    // lê a linha que contém a posição inicial do jogador
    getline(file, linha);
    ss = stringstream(linha);

    getline(ss, value, ' ');
    maze.startRow = stoi(value);
    playerY = maze.startRow;

    getline(ss, value, ' ');
    maze.startCol = stoi(value);
    playerX = maze.startCol;

    // lê labirinto
    for (int i = 0; i < maze.rows; i++)
    {
        getline(file, linha);
        linha.erase(remove_if(linha.begin(), linha.end(), ::isspace), linha.end());

        for (int j = 0; j < maze.cols; j++)
        {
            maze.grid[i][j] = linha[j];
            if (maze.grid[i][j] == '*')
            {
                maze.treasures++;
            }
        }
    }
    file.close();
}

void drawMaze()
{
    for (int i = 0; i < maze.rows; i++)
    {
        for (int j = 0; j < maze.cols; j++)
        {
            if (maze.grid[i][j] == '1')
            {                                                                                                              // Paredes do labirinto
                glColor3f(predefinedColors[WHITE].cor[0], predefinedColors[WHITE].cor[1], predefinedColors[WHITE].cor[2]); // Garante que a textura não seja afetada por cores anteriores
                glBindTexture(GL_TEXTURE_2D, wallTextureID);                                                               // Reutiliza a textura carregada
                glEnable(GL_TEXTURE_2D);

                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(j * squareSize, i * squareSize);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(j * squareSize, (i * squareSize) + squareSize);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f((j * squareSize) + squareSize, (i * squareSize) + squareSize);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f((j * squareSize) + squareSize, i);
                glEnd();

                glDisable(GL_TEXTURE_2D);
            }
            else if (maze.grid[i][j] == '*')
            {
                glColor3f(predefinedColors[YELLOW_GREEN].cor[0], predefinedColors[YELLOW_GREEN].cor[1], predefinedColors[YELLOW_GREEN].cor[2]);
                // glColor3f(predefinedColors[WHITE].cor[0], predefinedColors[WHITE].cor[1], predefinedColors[WHITE].cor[2]); // Garante que a textura não seja afetada por cores anteriores
                glBindTexture(GL_TEXTURE_2D, TreasureTextureID); // Reutiliza a textura carregada
                glEnable(GL_TEXTURE_2D);

                glBegin(GL_QUADS);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(j * squareSize, i * squareSize);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(j * squareSize, (i * squareSize) + squareSize);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f((j * squareSize) + squareSize, (i * squareSize) + squareSize);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f((j * squareSize) + squareSize, i);
                glEnd();

                glDisable(GL_TEXTURE_2D);
            }
            else if(maze.grid[i][j] == '0')
            {
                glColor3f(predefinedColors[WHITE].cor[0], predefinedColors[WHITE].cor[1], predefinedColors[WHITE].cor[2]); // Garante que a textura não seja afetada por cores anteriores
                glBindTexture(GL_TEXTURE_2D, FloorTextureID);                                                               // Reutiliza a textura carregada
                glEnable(GL_TEXTURE_2D);

                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(j * squareSize, i * squareSize);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(j * squareSize, (i * squareSize) + squareSize);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f((j * squareSize) + squareSize, (i * squareSize) + squareSize);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f((j * squareSize) + squareSize, i);
                glEnd();

                glDisable(GL_TEXTURE_2D);
            }
        }
    }
}

void drawLines()
{
    glColor3f(predefinedColors[DARK_GREEN].cor[0], predefinedColors[DARK_GREEN].cor[1], predefinedColors[DARK_GREEN].cor[2]);
    // horizontal lines
    for (int i = 0; i <= maze.rows; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(maze.rows * squareSize, i * squareSize);
        glVertex2f(0, i * squareSize);
        glEnd();
    }

    // vertical lines
    for (int j = 0; j <= maze.rows; j++)
    {
        glBegin(GL_LINES);
        glVertex2f(j * squareSize, maze.cols * squareSize);
        glVertex2f(j * squareSize, 0);
        glEnd();
    }
}

void drawGameOver()
{
    static bool visible = true;
    static int frameCount = 0;
    frameCount++;
    if (frameCount > 30)
    { // Alterna visibilidade a cada 30 frames
        visible = !visible;
        frameCount = 0;
    }
    float centerX = maze.cols / 2.0f;
    float centerY = maze.rows / 2.0f;

    string final_score = "Score: " + std::to_string(score);
    string time_left = "Time Left: " + std::to_string((int)(timeLeft / 1000));

    drawText(final_score.c_str(), centerX + 2.0f, centerY - 2.5f, predefinedColors[RED], predefinedColors[DARK_ORANGE]);
    drawText(time_left.c_str(), centerX + 2.0f, centerY - 3.0f, predefinedColors[RED], predefinedColors[DARK_ORANGE]);

    if (visible)
    {
        float centerX = maze.cols / 2.0f;
        float centerY = maze.rows / 2.0f;

        // Criando efeito de sombra 3D
        drawText("GAME OVER", centerX - 1.2f, centerY, predefinedColors[RED], predefinedColors[DARK_ORANGE]);
        drawText("Press R to Try Again", centerX - 2.0f, centerY - 1.2f, predefinedColors[RED], predefinedColors[DARK_ORANGE]);
    }
}

void drawVictory()
{

    static bool visible = true;
    static int frameCount = 0;
    frameCount++;
    if (frameCount > 30)
    { // Alterna visibilidade a cada 30 frames
        visible = !visible;
        frameCount = 0;
    }
    glColor3f(1.0f, 1.0f, 1.0f);                // Garante que a textura não seja afetada por cores anteriores
    glBindTexture(GL_TEXTURE_2D, WinTextureID); // Usa a textura de vitória
    glEnable(GL_TEXTURE_2D);

    float winWidth = 3 * squareSize;  // Define a largura da imagem (ajuste conforme necessário)
    float winHeight = 3 * squareSize; // Define a altura da imagem (ajuste conforme necessário)

    float centerX = maze.cols / 2.0f;
    float centerY = maze.rows / 2.0f;

    float offsetX = 1.0f;  // Ajuste fino para centralização
    float offsetY = -1.2f; // Mantendo o ajuste que você já fez

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(centerX - 2.0f + offsetX, centerY + offsetY);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(centerX - 2.0f + winWidth + offsetX, centerY + offsetY);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(centerX - 2.0f + winWidth + offsetX, centerY + offsetY + winHeight);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(centerX - 2.0f + offsetX, centerY + offsetY + winHeight);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    string final_score = "Score: " + std::to_string(score);
    string time_left = "Time Left: " + std::to_string((int)(timeLeft / 1000));
    drawText(final_score.c_str(), centerX + 2.0f, centerY - 2.5f, predefinedColors[GREEN], predefinedColors[GREEN]);
    drawText(time_left.c_str(), centerX + 2.0f, centerY - 3.0f, predefinedColors[GREEN], predefinedColors[GREEN]);

    if (visible)
    {
        drawText("Press R to Try Again", centerX - 2.0f, centerY - 1.2f, predefinedColors[GREEN], predefinedColors[GREEN]);
    }
}
