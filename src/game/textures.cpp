#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#ifdef _WIN32
#include <stb/stb_image.h>
#else
#include "stb_image.h"
#endif
#include "textures.hpp"
using namespace std;

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