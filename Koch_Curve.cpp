#include <GL/glut.h>
#include <cmath>

int recursionLevel = 4;

void drawKoch(float x1, float y1, float x2, float y2, int level)
{
    if (level == 0)
    {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }

    float dx = (x2 - x1) / 3;
    float dy = (y2 - y1) / 3;

    float x3 = x1 + dx;
    float y3 = y1 + dy;

    float x5 = x2 - dx;
    float y5 = y2 - dy;

    // Calculate the peak of the equilateral triangle
    float midX = (x1 + x2) / 2;
    float midY = (y1 + y2) / 2;

    float x4 = x3 + (dx * cos(M_PI / 3) - dy * sin(M_PI / 3));
    float y4 = y3 + (dx * sin(M_PI / 3) + dy * cos(M_PI / 3));

    // Recursively draw the 4 sides
    drawKoch(x1, y1, x3, y3, level - 1);
    drawKoch(x3, y3, x4, y4, level - 1);
    drawKoch(x4, y4, x5, y5, level - 1);
    drawKoch(x5, y5, x2, y2, level - 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1f, 0.2f, 0.6f);
    glBegin(GL_LINES);

    // Base line
    drawKoch(100, 300, 500, 300, recursionLevel);

    // To draw full snowflake, uncomment below:
    // drawKoch(100, 300, 300, 520, recursionLevel);
    // drawKoch(300, 520, 500, 300, recursionLevel);
    // drawKoch(500, 300, 100, 300, recursionLevel);

    glEnd();
    glFlush();
}

void init()
{
    gluOrtho2D(0, 600, 0, 600);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Koch Curve Fractal");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
