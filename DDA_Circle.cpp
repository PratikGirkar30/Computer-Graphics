#include <GL/glut.h>
#include <cmath>
#include <iostream>

#define PI 3.14159265

int xc, yc, radius;

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void ddaCircle(int xc, int yc, int r)
{
    float theta = 0;
    float end = 2 * PI;
    float step = 1.0 / r; // smaller step for smoother circle

    while (theta <= end)
    {
        int x = round(xc + r * cos(theta));
        int y = round(yc + r * sin(theta));
        plot(x, y);
        theta += step;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0); // Red
    ddaCircle(xc, yc, radius);
    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);   // White background
    gluOrtho2D(0, 500, 0, 500); // Coordinate system
}

int main(int argc, char **argv)
{
    std::cout << "Enter center (xc yc) and radius: ";
    std::cin >> xc >> yc >> radius;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Circle Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
