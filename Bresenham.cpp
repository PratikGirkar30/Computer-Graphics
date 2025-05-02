#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <algorithm>

int x1_b, y1_b, x2_b, y2_b;

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void Bresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        plot(x1, y1);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Red color
    Bresenham(x1_b, y1_b, x2_b, y2_b);
    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    gluOrtho2D(0, 500, 0, 500);       // Set coordinate system
}

int main(int argc, char **argv)
{
    std::cout << "Enter Bresenham line coordinates (x1 y1 x2 y2): ";
    std::cin >> x1_b >> y1_b >> x2_b >> y2_b;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
