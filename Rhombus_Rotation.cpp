#include <GL/glut.h>
#include <cmath>

#define DEG2RAD 0.0174533

void rotate(float x, float y, float &xr, float &yr, float angle, float cx, float cy)
{
    float s = sin(angle * DEG2RAD), c = cos(angle * DEG2RAD);
    x -= cx;
    y -= cy;
    xr = x * c - y * s + cx;
    yr = x * s + y * c + cy;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float x[4] = {300, 350, 300, 250};
    float y[4] = {100, 150, 200, 150};
    float xr[4], yr[4];
    float cx = 300, cy = 150;

    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; ++i)
        glVertex2f(x[i], y[i]);
    glEnd();

    for (int i = 0; i < 4; ++i)
        rotate(x[i], y[i], xr[i], yr[i], 45, cx, cy);

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; ++i)
        glVertex2f(xr[i], yr[i]);
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
    glutCreateWindow("Rhombus Rotation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
