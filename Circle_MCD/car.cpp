// Author : Paleti Krishnasai - CED18I039
// g++ car.cpp -o car -lGL -lGLU -lglut -lGLEW
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
using namespace std;

void changeViewPort(int w, int h) 
{
	if(w>=h)
		glViewport(w/2-h/2, 0, h, h);
	else
		glViewport(0, h/2-w/2, w, w);
}

void myinit(void)
{
	glClearColor(0.8,0.8,0.8,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0,1000.0,0.0,1000.0);
	glMatrixMode(GL_MODELVIEW);
}

float RandomColor() 
{
    float color=(float)((rand() % 100))/99;
    return color;    
}

void Pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

struct circle
{
    float c[2];
    float r;
};


void PlotOctants(float c[2], float x, float y)
{
    Pixel(c[0] + y, c[1] + x); //O1
    Pixel(c[0] + x, c[1] + y); //O2
    Pixel(c[0] - x, c[1] + y); //O3
    Pixel(c[0] - y, c[1] + x); //O4

    Pixel(c[0] - y, c[1] - x); //O5
    Pixel(c[0] - x, c[1] - y); //O6
    Pixel(c[0] + x, c[1] - y); //O7
    Pixel(c[0] + y, c[1] - x); //O8
}

void mcd(circle cir, int mode)
{
    float x = 0;
    float y = cir.r;

    float p = 1 - cir.r;

    int x_limit = cir.r / sqrt(2);

    for (int i = 0; i < x_limit; i++)
    {

       
    PlotOctants(cir.c, x, y);
        
        if (p < 0) //y does not change
            p += 2 * x + 3;
        else //y decrement
        {
            p += 2 * x - 2 * y + 5;
            y--;
        }
        x++;
    }
}



void BLD(float point1[2], float point2[2])
{
	int x1 = point1[0], y1 = point1[1];
	int x2 = point2[0], y2 = point2[1];

	int dx = (int)(x2 - x1);
	int dy = (int)(y2 - y1);
	int p;

	if (abs(dy) <= abs(dx))
	{
		p = 2 * abs(dy) - abs(dx);
		for (int i = 0; i < abs(dx); i++)
		{
			
			if (p >= 0)
			{
				p += (2 * abs(dy) - 2 * abs(dx));
				y1 += dy / abs(dy);
			}
			else
			{
				p += (2 * abs(dy));
			}
			x1 += dx / (abs(dx));

			
			Pixel(round(x1), round(y1));
			

			
		}
	}
	else
	{
		p = 2 * abs(dx) - abs(dy);
		for (int i = 0; i < abs(dy); i++)
		{
            

			if (p >= 0)
			{
				p += (2 * abs(dx) - 2 * abs(dy));
				x1 += dx / abs(dx);
			}
			else
			{
				p += (2 * abs(dx));
			}
			y1 += dy / (abs(dy));

			Pixel(round(x1), round(y1));

		}
	}
}

void car()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //car body
    float a[2] = {50, 400};
    float b[2] = {800, 400};
    float c[2] = {800, 600};
    float d[2] = {50, 600};
    // Front Window
    float e[2] = {270, 610};
    float f[2] = {410, 790};
    float g[2] = {500, 790};
    float h[2] = {500, 610};
    //Rear Window
    float i[2] = {510, 610};
    float j[2] = {510, 790};
    float k[2] = {690, 790};
    float l[2] = {780, 610};
    //car roof
    // point c
    float m[2] = {700, 800};
    float n[2] = {400, 800};
    float o[2] = {240, 600};

    //Drawing Line segments  with BLD
    //car body
    glColor3f(0, 0, 0);
    glPointSize(3);
    BLD(a, b);
    BLD(b, c);
    BLD(c, d);
    BLD(d, a);
    //front window
    BLD(e, f);
    BLD(f, g);
    BLD(g, h);
    BLD(h, e);
    //rear Window
    BLD(i, j);
    BLD(j, k);
    BLD(k, l);
    BLD(l, i);
    //car roof
    BLD(c, m);
    BLD(m, n);
    BLD(n, o);

    //WHEELS
    circle frontW = {{250, 400}, 100};
    circle backW = {{650, 400}, 100};
    mcd(frontW, 0);
    mcd(backW, 0);
    //Colouring the wheel
    glColor3f(0.5, 0.5, 0.5);
    float temp = frontW.r - 3;
    while (temp--)
    {

        circle f = {{frontW.c[0], frontW.c[1]}, temp};
        circle b = {{backW.c[0], backW.c[1]}, temp};
        glColor3f(0.5, 0.5, 0.5);
        mcd(f, 0);
        mcd(b, 0);
    }

    glutSwapBuffers();
}




int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);

    glutCreateWindow("CED18I039_Car_MCD");
    myinit();
    glutDisplayFunc(car);
    
    glutReshapeFunc(changeViewPort);
  
    glutMainLoop();
}
