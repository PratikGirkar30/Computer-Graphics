#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

struct Point
{
    float x, y;
};

vector<Point> polygon;
vector<Point> clippedPolygon;

float xmin, ymin, xmax, ymax;

void drawPolygon(const vector<Point> &poly, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (auto &p : poly)
        glVertex2f(p.x, p.y);
    glEnd();
}

Point intersect(Point p1, Point p2, int edge)
{
    Point iPt;
    float m;

    if (p1.x != p2.x)
        m = (p2.y - p1.y) / (p2.x - p1.x);
    else
        m = 1e5; // very large slope

    switch (edge)
    {
    case 0: // left
        iPt.x = xmin;
        iPt.y = p1.y + m * (xmin - p1.x);
        break;
    case 1: // right
        iPt.x = xmax;
        iPt.y = p1.y + m * (xmax - p1.x);
        break;
    case 2: // bottom
        iPt.y = ymin;
        iPt.x = (p1.x != p2.x) ? (p1.x + (1 / m) * (ymin - p1.y)) : p1.x;
        break;
    case 3: // top
        iPt.y = ymax;
        iPt.x = (p1.x != p2.x) ? (p1.x + (1 / m) * (ymax - p1.y)) : p1.x;
        break;
    }

    return iPt;
}

bool inside(Point p, int edge)
{
    switch (edge)
    {
    case 0:
        return p.x >= xmin;
    case 1:
        return p.x <= xmax;
    case 2:
        return p.y >= ymin;
    case 3:
        return p.y <= ymax;
    }
    return false;
}

void clipPolygon()
{
    clippedPolygon = polygon;

    for (int edge = 0; edge < 4; edge++)
    {
        vector<Point> input = clippedPolygon;
        clippedPolygon.clear();

        for (size_t i = 0; i < input.size(); i++)
        {
            Point curr = input[i];
            Point prev = input[(i + input.size() - 1) % input.size()];

            bool curr_in = inside(curr, edge);
            bool prev_in = inside(prev, edge);

            if (curr_in && prev_in)
            {
                clippedPolygon.push_back(curr);
            }
            else if (!prev_in && curr_in)
            {
                clippedPolygon.push_back(intersect(prev, curr, edge));
                clippedPolygon.push_back(curr);
            }
            else if (prev_in && !curr_in)
            {
                clippedPolygon.push_back(intersect(prev, curr, edge));
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping rectangle
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Draw original polygon in blue
    drawPolygon(polygon, 0.0, 0.0, 1.0);

    // Draw clipped polygon in red
    clipPolygon();
    drawPolygon(clippedPolygon, 1.0, 0.0, 0.0);

    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    int n;
    cout << "Enter number of polygon vertices: ";
    cin >> n;

    cout << "Enter polygon vertices (x y):\n";
    for (int i = 0; i < n; i++)
    {
        Point p;
        cin >> p.x >> p.y;
        polygon.push_back(p);
    }

    cout << "Enter clipping rectangle (xmin ymin xmax ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
