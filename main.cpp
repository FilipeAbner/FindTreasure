#include <GL/glut.h>
#include "src/game/game.hpp"
#include "src/util/adjust_directory.cpp"

int main(int argc, char **argv)
{
    setWorkingDirectoryToProjectRoot();
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Labirinth");

    initGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, timer, 16);

    glutMainLoop();
    return 0;
}
