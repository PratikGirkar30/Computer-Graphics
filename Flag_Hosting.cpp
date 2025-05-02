#include <GL/glut.h>

// Initial Y-position of the flag (starts from bottom)
float flagY = 0.0f;
bool flagRaised = false;

// Timer function to animate the flag rising
void update(int value) {
    if (flagY < 200.0f) {
        flagY += 2.0f; // Raise flag
        glutPostRedisplay(); // Redraw scene
        glutTimerFunc(30, update, 0); // Call again after 30 ms
    } else {
        flagRaised = true; // Stop raising after reaching top
    }
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw ground
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(500.0f, 0.0f);
    glVertex2f(500.0f, 50.0f);
    glVertex2f(0.0f, 50.0f);
    glEnd();

    // Draw flag pole
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(100.0f, 50.0f);
    glVertex2f(110.0f, 50.0f);
    glVertex2f(110.0f, 300.0f);
    glVertex2f(100.0f, 300.0f);
    glEnd();

    // Draw flag
    glColor3f(1.0f, 0.5f, 0.0f); // Orange
    glBegin(GL_QUADS);
    glVertex2f(110.0f, 50.0f + flagY);
    glVertex2f(160.0f, 50.0f + flagY);
    glVertex2f(160.0f, 70.0f + flagY);
    glVertex2f(110.0f, 70.0f + flagY);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // White
    glBegin(GL_QUADS);
    glVertex2f(110.0f, 70.0f + flagY);
    glVertex2f(160.0f, 70.0f + flagY);
    glVertex2f(160.0f, 90.0f + flagY);
    glVertex2f(110.0f, 90.0f + flagY);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glBegin(GL_QUADS);
    glVertex2f(110.0f, 90.0f + flagY);
    glVertex2f(160.0f, 90.0f + flagY);
    glVertex2f(160.0f, 110.0f + flagY);
    glVertex2f(110.0f, 110.0f + flagY);
    glEnd();

    glFlush();
}

// Initialize OpenGL state
void init() {
    glClearColor(0.5f, 0.8f, 0.95f, 1.0f); // Sky blue
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 400.0);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flag Hoisting Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0); // Start animation
    glutMainLoop();
    return 0;
}
