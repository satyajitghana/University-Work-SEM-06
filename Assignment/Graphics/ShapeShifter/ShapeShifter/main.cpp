#include <iostream>
#include <string>
#include <GL/freeglut.h>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
#define GRID_X_MIN -8
#define GRID_X_MAX 60
#define GRID_Y_MIN -8
#define GRID_Y_MAX 60

#define WIN_TITLE "Graphics Assignement"

int state = 0;
const unsigned char state_title[][20] = { "ORIGINAL", "ROTATED", "TRANSLATED", "SCALED", "FINAL TRANSFORMED" };
int total_states = 5;

void render();
void reshape(int, int);
void keyboard(unsigned char, int, int);
void special_keys(int key, int x, int y);
void init();

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	// initialize the display mode
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	// for anti-aliasing
	glEnable(GLUT_MULTISAMPLE);
	// set the window position
	glutInitWindowPosition(100, 100);
	// set the window size
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	// now create the window
	glutCreateWindow(WIN_TITLE);

	// register the core functions
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);

	init();
	glutMainLoop();

	return 0;
}

void init() {
	glClearColor(164 / 255.0, 176 / 255.0, 190 / 255.0, 0.8);
	glFlush();
}

void reshape(int w, int h) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(GRID_X_MIN, GRID_X_MAX, GRID_Y_MIN, GRID_Y_MAX);
}

void show_grid() {

	glBegin(GL_LINES);
	const GLubyte prestigeBlue[] = { 47.0, 53.0, 66.0, 1.0 };
	const GLubyte pureRed[] = { 255.0, 0.0, 0.0, 1.0 };

	for (float i = GRID_X_MIN; i <= GRID_X_MAX; i += 1.0) {
		glColor4ubv(prestigeBlue);
		if (i == 0)
			glColor4ubv(pureRed);
		glVertex2f(i, GRID_Y_MIN);
		glVertex2f(i, GRID_Y_MAX);
	}

	for (float i = GRID_Y_MIN; i <= GRID_Y_MAX; i += 1.0) {
		glColor4ubv(prestigeBlue);
		if (i == 0)
			glColor4ubv(pureRed);
		glVertex2f(GRID_X_MIN, i);
		glVertex2f(GRID_X_MAX, i);
	}

	glEnd();
}

void square() {
	glBegin(GL_POLYGON);

	const GLubyte jalapenoRed[] = { 183.0, 21.0, 64.0, 1.0 };
	const GLubyte darkSapphire[] = { 12.0, 36.0, 97.0, 1.0 };
	const GLubyte forestBlues[] = { 10.0, 61.0, 98.0, 1.0 };
	const GLubyte reefEncounter[] = { 7.0, 153.0, 146.0, 1.0 };

	glColor4ubv(jalapenoRed);
	glVertex2f(-1.0, 1.0);
	glColor4ubv(darkSapphire);
	glVertex2f(-1.0, -1.0);
	glColor4ubv(forestBlues);
	glVertex2f(1.0, -1.0);
	glColor4ubv(reefEncounter);
	glVertex2f(1.0, 1.0);
	glEnd();
}

void show_original() {
	glPushMatrix();
	square();
	glPopMatrix();
}

void show_transformed() {
	glPushMatrix();
	glScalef(5.0, 6.0, 1.0);
	glTranslatef(4.0, 8.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	square();
	glPopMatrix();
}

void show_text() {
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(30.0, 30.0, 1.0);
	glRasterPos2f(0.0, 0.0);
	const unsigned char *string = state_title[state];
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, string);
	glPopMatrix();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	show_text();
	show_grid();

	switch (state) {
		//ORIGINAL
	case 0:
		glPushMatrix();
		square();
		glPopMatrix();
		break;
		// ROTATED
	case 1:
		glPushMatrix();
		glRotatef(90, 0.0, 0.0, 1.0);
		square();
		glPopMatrix();
		break;
		// TRANSLATED
	case 2:
		glPushMatrix();
		glTranslatef(4.0, 8.0, 0.0);
		square();
		glPopMatrix();
		break;
		// SCALED
	case 3:
		glPushMatrix();
		glScalef(5.0, 6.0, 1.0);
		square();
		glPopMatrix();
		break;
		// FINAL TRANSFORMED
	case 4:
		show_grid();
		show_original();
		show_transformed();
		break;
	}

	glFlush();

	glutSwapBuffers();

}

void keyboard(unsigned char c, int x, int y) {
	switch (c) {
	case 13:
	case 'q':
	case 'Q':
		exit(EXIT_SUCCESS);
		break;
	}
}

void special_keys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		state = ((state + 1) % total_states + total_states) % total_states;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		state = ((state - 1) % total_states + total_states) % total_states;
		glutPostRedisplay();
		break;
	}
}

