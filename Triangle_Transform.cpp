#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

struct Point
{
    float x, y;
};

Point triangle[3]; // Original triangle

// Transformation parameters
float tx = 0, ty = 0;   // translation
float angle = 0;        // rotation angle (degrees)
float sx = 1, sy = 1;   // scaling
float shx = 0, shy = 0; // shearing

void drawTriangle(Point p[3])
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++)
        glVertex2f(p[i].x, p[i].y);
    glEnd();
}

void applyTransformations()
{
    Point result[3];
    float rad = angle * M_PI / 180.0;

    for (int i = 0; i < 3; i++)
    {
        float x = triangle[i].x;
        float y = triangle[i].y;

        // Scaling
        x *= sx;
        y *= sy;

        // Shearing
        float x_shear = x + shx * y;
        float y_shear = y + shy * x;
        x = x_shear;
        y = y_shear;

        // Rotation
        float x_rot = x * cos(rad) - y * sin(rad);
        float y_rot = x * sin(rad) + y * cos(rad);
        x = x_rot;
        y = y_rot;

        // Translation
        x += tx;
        y += ty;

        result[i] = {x, y};
    }

    glColor3f(1, 0, 0); // red
    drawTriangle(result);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1); // original - blue
    drawTriangle(triangle);

    applyTransformations();

    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    // Define an equilateral triangle
    triangle[0] = {200, 200};
    triangle[1] = {300, 200};
    triangle[2] = {250, 200 + (float)(sqrt(3) * 50)}; // height ≈ 86.6

    cout << "Enter translation (tx ty): ";
    cin >> tx >> ty;

    cout << "Enter rotation angle (degrees): ";
    cin >> angle;

    cout << "Enter scaling (sx sy): ";
    cin >> sx >> sy;

    cout << "Enter shearing (shx shy): ";
    cin >> shx >> shy;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Triangle Transformations");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
