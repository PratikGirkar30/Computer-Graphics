#include <GL/glut.h>
#include <iostream>

// Circle parameters
int xc = 250;
int yc = 250;
int radius = 100;

// Function to plot symmetrical points
void plotCirclePoints(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

// Midpoint circle drawing algorithm
void drawMidpointCircle()
{
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    plotCirclePoints(x, y);

    while (x < y)
    {
        x++;
        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
        plotCirclePoints(x, y);
    }

    glFlush(); // Force execution of OpenGL commands
}

// Display callback
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    drawMidpointCircle();
}

// OpenGL initialization
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glPointSize(2.0f);                   // Point size
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);          // 2D projection
}

// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Drawing - C++");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
