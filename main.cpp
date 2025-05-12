#include <GL/glut.h>
#include "game.hpp"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Labirinto");

    initGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, timer, 16);

    glutMainLoop();
    return 0;
}
