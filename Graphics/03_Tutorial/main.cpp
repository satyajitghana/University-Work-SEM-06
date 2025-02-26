#include <iostream>

#include <GL/glut.h>

void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Primitive");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    glutWireTeapot(1.0);
    glPolygonMode(GL_FRONT, GL_LINE);

    glLineWidth(5.0);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 2.0f, 0.0f);
    glVertex3f(4.5f, 0.0f, 0.0f);
    glVertex3f(4.5f, 2.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(1.0f, 2.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(2.0f, 2.0f, 0.0f);
    glVertex3f(2.0f, 1.0f, 0.0f);
    glVertex3f(3.0f, 2.0f, 0.0f);
    glVertex3f(4.0f, 1.0f, 0.0f);
    glEnd();

    glutSolidSphere(1.0, 24, 24);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
        case 'q':
        case 'Q':
            exit(0);
            break;
    }
}
