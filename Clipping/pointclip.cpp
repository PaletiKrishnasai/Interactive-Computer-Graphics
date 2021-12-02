// Author : Paleti Krishnasai - CED18I039
// g++ PointClip.cpp -o PointClip -lGL -lGLU -lglut -lGLEW
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

int refPoints = -1;
float xmin = 300, ymin = 300, xmax = 700, ymax = 700;
float ax = 200, ay = 500, bx = 800, by = 500;


void changeViewPort(int w, int h)
{
    if (w >= h)
        glViewport(w / 2 - h / 2, 0, h, h);
    else
        glViewport(0, h / 2 - w / 2, w, w);
}

void myinit(void)
{
    glClearColor(0.8,0.8,0.8,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
}
float randColor()
{
    float r = (float)((rand() % 1000)) / 999;
    return r;
}

void plot(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(round(x), round(y));
    glEnd();
}

void drawClippingWindow()
{   
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();
}

void PointClip()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    int x, y;
    drawClippingWindow();
    for (int i = 0; i < 400; i++)
    {
        x = rand() % 1000;
        y = rand() % 1000;

        //reference points
        if (refPoints == -1)
        {
            glColor3f(1, 0, 0);
            glPointSize(4);
            plot(x, y);
        }

        glColor3f(0, 1, 0);
        glPointSize(4);
        if (x >= xmin && x <= xmax)
            if (y >= ymin && y <= ymax)
                plot(x, y);
    }

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    

	srand(time(0)); // random seeding for random color

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);


	glutInitWindowPosition(500, 500);
	glutCreateWindow("CED18I039");
	myinit();
	glutDisplayFunc(PointClip);

	glutReshapeFunc(changeViewPort);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}


	glutMainLoop();

	return 0;
}
