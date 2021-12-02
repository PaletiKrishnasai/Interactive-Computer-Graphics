#include<GL/glut.h>
#include <iostream>

void display() {
	int i, n = 5;
	int x, y;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);

	glVertex2d(150, 150);
	glVertex2d(150, 350);
	glVertex2d(350, 350);
	glVertex2d(350, 150);

	glEnd();

	for (i = 0;i < n;i++) {
		x = rand() % 500, y = rand() % 500;

		glBegin(GL_POINTS);
		if (x >= 150 && x <= 350 && y >= 150 && y <= 350)
		{

			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x, y);
			printf("POINT IS INSIDE : %d %d \n", x, y);
			printf("=========================== \n");
		}
		else {
			glColor3f(0.0, 1.0, 0.0);
			glVertex2f(x, y);
		}

		glEnd();
	}printf("*************************************************** \n");
	glFlush();


}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Points");
	glutDisplayFunc(display);

	myinit();
	glutMainLoop();
}