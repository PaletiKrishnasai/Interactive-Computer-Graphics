#include <GL/glew.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

void myinit(void)
{
	glClearColor(1.0,1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0,200.0,0.0,150.0);
}

void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.4,0.2);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex2i(180,15);
		glVertex2i(10,145);
	glEnd();
	glFlush();
}
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(10, 10);
		glVertex2f(100, 10);
		glVertex2f(100, 100);
		glVertex2f(10, 100);
	glEnd();
	glFlush();
    glutSwapBuffers();
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(800,600);
	glutCreateWindow("An Example on Open Gl");
	myinit();
	glutDisplayFunc(Display);
	glutMainLoop();
}