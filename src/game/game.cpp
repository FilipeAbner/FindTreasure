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

void initTextures()
{
    wallTextureID = loadTexture("img/assets/wall.png");
    if (wallTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura do labirinto!" << std::endl;
        exit(EXIT_FAILURE); // Exit the program if the texture fails
    }

    PlayerTextureID = loadTexture("img/assets/Player.png");
    if (PlayerTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura do Player!" << std::endl;
        exit(EXIT_FAILURE); // Exit the program if the texture fails
    }

    TreasureTextureID = loadTexture("img/assets/Treasure.png");
    if (TreasureTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura do Tesouro!" << std::endl;
        exit(EXIT_FAILURE); // Exit the program if the texture fails
    }

    WinTextureID = loadTexture("img/assets/Win.png");
    if (WinTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura de Win!" << std::endl;
        exit(EXIT_FAILURE); // Exit the program if the texture fails
    }

    FloorTextureID = loadTexture("img/assets/floor.png");
    if (FloorTextureID == 0)
    {
        std::cerr << "Erro ao carregar a textura de Floor!" << std::endl;
        exit(EXIT_FAILURE); // Exit the program if the texture fails
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

    // Texture parameter configuration
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
    glColor3f(predefinedColors[WHITE].cor[0], predefinedColors[WHITE].cor[1], predefinedColors[WHITE].cor[2]); // Ensures that the texture is not affected by previous colors
    glBindTexture(GL_TEXTURE_2D, PlayerTextureID);                                                             // Uses the character's texture
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
    { // game over screen
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

// Text with Shadow
void drawText(const char *text, float x, float y, Colors textColor, Colors shadowColor)
{
    // Draw shadow with offset
    glColor3f(shadowColor.cor[0], shadowColor.cor[1], shadowColor.cor[2]);
    glRasterPos2f(x + 0.015f, y - 0.015f); // Small shift to the shadow
    const char *t = text;
    while (*t)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *t);
        t++;
    }

    // Draw main text
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
    mapFileName = "src/util/map.txt";
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

    // read the line containing the maze size
    getline(file, linha);
    ss = stringstream(linha);

    getline(ss, value, ' ');
    maze.rows = stoi(value);
    getline(ss, value, ' ');
    maze.cols = stoi(value);

    maze.grid = vector<vector<char>>(maze.rows, vector<char>(maze.cols));

    // read the line containing the player's initial position
    getline(file, linha);
    ss = stringstream(linha);

    getline(ss, value, ' ');
    maze.startRow = stoi(value);
    playerY = maze.startRow;

    getline(ss, value, ' ');
    maze.startCol = stoi(value);
    playerX = maze.startCol;

    // read maze
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
            {                                                                                                              // Maze Walls
                glColor3f(predefinedColors[WHITE].cor[0], predefinedColors[WHITE].cor[1], predefinedColors[WHITE].cor[2]); // Ensures that the texture is not affected by previous colors
                glBindTexture(GL_TEXTURE_2D, wallTextureID);                                                               // Reuse the loaded texture
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
                glBindTexture(GL_TEXTURE_2D, TreasureTextureID); // Reuse the loaded texture
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
                glColor3f(predefinedColors[WHITE].cor[0], predefinedColors[WHITE].cor[1], predefinedColors[WHITE].cor[2]); // Ensures that the texture is not affected by previous colors
                glBindTexture(GL_TEXTURE_2D, FloorTextureID);                                                               // Reuse the loaded texture
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
    { // Toggle visibility every 30 frames
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

        // Creating 3D shadow effect
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
    { // Toggle visibility every 30 frames
        visible = !visible;
        frameCount = 0;
    }
    glColor3f(1.0f, 1.0f, 1.0f);                // Ensures that the texture is not affected by previous colors
    glBindTexture(GL_TEXTURE_2D, WinTextureID); // Use the victory texture
    glEnable(GL_TEXTURE_2D);

    float winWidth = 3 * squareSize;  // Set the width of the image (adjust as needed)
    float winHeight = 3 * squareSize; // Sets the height of the image (adjust as needed)

    float centerX = maze.cols / 2.0f;
    float centerY = maze.rows / 2.0f;

    float offsetX = 1.0f;  // Fine-tuning for centering
    float offsetY = -1.2f; // Keeping the adjustment you already made

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
