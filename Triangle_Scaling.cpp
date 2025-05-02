#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Original triangle
    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex2i(100, 100);
    glVertex2i(150, 200);
    glVertex2i(200, 100);
    glEnd();

    // Scaled triangle (from center 150,150)
    float sx = 1.5, sy = 0.5;
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(150 + (100 - 150) * sx, 150 + (100 - 150) * sy);
    glVertex2f(150 + (150 - 150) * sx, 150 + (200 - 150) * sy);
    glVertex2f(150 + (200 - 150) * sx, 150 + (100 - 150) * sy);
    glEnd();

    glFlush();
}

void init()
{
    gluOrtho2D(0, 400, 0, 400);
    glClearColor(1, 1, 1, 1);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Triangle Scaling");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
