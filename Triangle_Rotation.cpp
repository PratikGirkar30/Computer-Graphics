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

    float x[3] = {100, 150, 200};
    float y[3] = {100, 200, 100};
    float xr[3], yr[3];
    float cx = 150, cy = 150;

    // Original triangle
    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; ++i)
        glVertex2i(x[i], y[i]);
    glEnd();

    // Rotate each point
    for (int i = 0; i < 3; ++i)
        rotate(x[i], y[i], xr[i], yr[i], 45, cx, cy);

    // Rotated triangle
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; ++i)
        glVertex2f(xr[i], yr[i]);
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
    glutCreateWindow("Triangle Rotation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

