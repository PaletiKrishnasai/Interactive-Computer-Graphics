#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1, 1, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f( 0.5, 0.5);
        glVertex2f( 0.5, -0.5);
    glEnd();
    glFlush();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(800, 400); 
    glutCreateWindow("Rectangle_color");
    glutDisplayFunc(Display);
    glutReshapeFunc(changeViewPort);
    GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
    glutMainLoop();
    return 0;
}