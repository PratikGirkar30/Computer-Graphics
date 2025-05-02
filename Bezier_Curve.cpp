#include <GL/glut.h>
#include <vector>

// Define control points
std::vector<float*> controlPoints = {
    new float[3]{100.0, 100.0, 0.0},
    new float[3]{150.0, 300.0, 0.0},
    new float[3]{250.0, 300.0, 0.0},
    new float[3]{300.0, 100.0, 0.0}
};

// Evaluate the Bezier curve at a parameter t
void bezierCurve(float t, float* p) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    for (int i = 0; i < 3; i++) {
        p[i] = uuu * controlPoints[0][i] + 
               3 * uu * t * controlPoints[1][i] + 
               3 * u * tt * controlPoints[2][i] + 
               ttt * controlPoints[3][i];
    }
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw control points
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    for (auto& pt : controlPoints) {
        glVertex3fv(pt);
    }
    glEnd();

    // Draw Bezier curve
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0; t <= 1.0; t += 0.01) {
        float p[3];
        bezierCurve(t, p);
        glVertex3fv(p);
    }
    glEnd();

    glFlush();
}

// Initialize OpenGL state
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curve - OpenGL GLUT");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
