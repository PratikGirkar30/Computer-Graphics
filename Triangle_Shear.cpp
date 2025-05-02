#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Original
    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex2i(100, 100);
    glVertex2i(150, 200);
    glVertex2i(200, 100);
    glEnd();

    float shx = 0.5;

    // Sheared (X shear)
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(100 + 100 * shx, 100);
    glVertex2f(150 + 200 * shx, 200);
    glVertex2f(200 + 100 * shx, 100);
    glEnd();

    glFlush();
}

void init()
{
    gluOrtho2D(0, 600, 0, 400);
    glClearColor(1, 1, 1, 1);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Triangle Shear");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
