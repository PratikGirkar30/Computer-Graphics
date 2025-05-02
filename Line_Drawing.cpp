#include <GL/glut.h>
#include <iostream>
#include <cmath>

const int squareSize = 100;
const int boardSize = 4;

void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void getPixelColor(int x, int y, float *color)
{
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void seedFill(int x, int y, float *fillColor, float *borderColor)
{
    float currentColor[3];
    getPixelColor(x, y, currentColor);

    if ((currentColor[0] != borderColor[0] || currentColor[1] != borderColor[1] || currentColor[2] != borderColor[2]) &&
        (currentColor[0] != fillColor[0] || currentColor[1] != fillColor[1] || currentColor[2] != fillColor[2]))
    {

        glColor3fv(fillColor);
        setPixel(x, y);
        glFlush();

        seedFill(x + 1, y, fillColor, borderColor);
        seedFill(x - 1, y, fillColor, borderColor);
        seedFill(x, y + 1, fillColor, borderColor);
        seedFill(x, y - 1, fillColor, borderColor);
    }
}

// DDA Line Drawing Algorithm
void drawLine(int x1, int y1, int x2, int y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++)
    {
        setPixel(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

void drawChessboard()
{
    glColor3f(0.0, 0.0, 0.0); // black lines

    // Vertical lines
    for (int i = 0; i <= boardSize; i++)
    {
        drawLine(i * squareSize, 0, i * squareSize, boardSize * squareSize);
    }

    // Horizontal lines
    for (int i = 0; i <= boardSize; i++)
    {
        drawLine(0, i * squareSize, boardSize * squareSize, i * squareSize);
    }

    // Fill alternate squares (black)
    float fillColor[] = {0.0f, 0.0f, 0.0f};
    float borderColor[] = {0.0f, 0.0f, 0.0f}; // treat lines as border

    for (int row = 0; row < boardSize; row++)
    {
        for (int col = 0; col < boardSize; col++)
        {
            if ((row + col) % 2 == 0)
            {
                int seedX = col * squareSize + squareSize / 2;
                int seedY = row * squareSize + squareSize / 2;
                seedFill(seedX, seedY, fillColor, borderColor);
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawChessboard();
    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    gluOrtho2D(0, 400, 0, 400);       // 2D orthographic projection
    glPointSize(1.0f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("4x4 Chessboard with Seed Fill");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
