#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float cx = 300, cy = 150;
    float sx = 1.2, sy = 0.6;

    float x[4] = {300, 350, 300, 250};
    float y[4] = {100, 150, 200, 150};

    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
        glVertex2f(x[i], y[i]);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
        glVertex2f(cx + (x[i] - cx) * sx, cy + (y[i] - cy) * sy);
    glEnd();

    glFlush();
}

void init()
{
    gluOrtho2D(0, 600, 400, 0);
    glClearColor(1, 1, 1, 1);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Rhombus Scaling");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
