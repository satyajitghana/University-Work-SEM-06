#include <Windows.h>
#include <GL/glut.h>

void GL_display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireTeapot(1.0);
	glutSolidSphere(1.0, 24, 24);
	
	glRectf(0, 0, 1, 1);
	glFlush();
}

void GL_reshape(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-2.0f, 2.0f, -2.0f / aspectRatio, 2.0f / aspectRatio, -2.0f, 2.0f);
	else
		glOrtho(-2.0f*aspectRatio, 2.0f*aspectRatio, -2.0f, 2.0f, -2.0f, 2.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 300);

	glutCreateWindow("OpenGL Setup Test");
	

	glutDisplayFunc(GL_display);
	glutReshapeFunc(GL_reshape);
	glutMainLoop();
}