// Author : Paleti Krishnasai - CED18I039
// g++ CED18I039.cpp -o ced -lGL -lGLU -lglut -lGLEW
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


float precision = 1; // detail , increase this to get more points in DDA ( useful when raster size is not equal to window size which causes dotted lines).

struct ellipse // structure to hold ellipse parameters
{
    float c[2];
    float rx;
    float ry;
};

void changeViewPort(int w, int h) 
{
	if(w>=h)
		glViewport(w/2-h/2, 0, h, h);
	else
		glViewport(0, h/2-w/2, w, w);
}

void myinit(void)
{
	//glClearColor(0.8,0.8,0.8,0.0);     // uncomment this line to have a white background
    glClearColor(0,0,0,0.0);            // simultaeniously comment this line allow the white background
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0,700.0,0.0,700.0);
	glMatrixMode(GL_MODELVIEW);
}

void Pixel(float x, float y) // plots a point on raster
{
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void Plot_Region1_symmettry(float c[2], float x, float y)   // plots 4 point symmettry , Q2 and Q3 are commented out as they are not needed for "P"
{ 
    Pixel(x + c[0] , y + c[1]); //Q1
    //Pixel(-x + c[0] , y + c[1]); //Q2
    Pixel(x + c[0] , -y + c[1]); //Q4
    //Pixel(-x + c[0] , -y + c[1]); //Q3
}

float RandomColor()                             // generated random color for the points 
{
	float color = (float)((rand() % 100)) / 99;
	return color;
}

void DDA(float point1[2], float point2[2])      // DDA line drawing algorithm
{
	float x1 = point1[0], y1 = point1[1];
	float x2 = point2[0], y2 = point2[1];
	float dx = x2 - x1;
	float dy = y2 - y1;
	float m = dy / dx;
	float length, x_increment, y_increment;
	if (abs(dx) > abs(dy))
		length = abs(dx);
	else
		length = abs(dy);

	x_increment = dx / length;
	y_increment = dy / length;

	float x, y;
	int i;
	x = x1;
	y = y1;
	for (i = 0; i < length * precision; i++)
	{
		Pixel(round(x), round(y));
		x += x_increment / precision;
		y += y_increment / precision;
	}
}

void Brute(ellipse cir)         // Brute force or general ellipse drawing algorithm
{   
    /*
        here the ellipse is distorted near the horizontal axis as we are increasing x all the time
    */
    float cx = cir.c[0];        
    float cy = cir.c[1];
    float h_rx = cir.rx;
    float v_ry = cir.ry;
    float a2=h_rx*h_rx;
    float b2 =v_ry*v_ry;
    float y=b2, x=0;
    while (y >= 0)
    {
        Plot_Region1_symmettry(cir.c, x, y);
        x++;
        y = sqrt((a2 - x * x) * b2 / a2);
    }


}

void my_name()      // display function 
// PALE ti krishnasai
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //P
    float point1[2] = {120, 120};
	float point2[2] = {120, 340};
    ellipse ell_1 = {{ 120,285 }, 100, 55};

    //A
    float point3[2] = {260, 120};
	float point4[2] = {320, 340};
	float point5[2] = {380, 120};
	float point6[2] = {290, 230};  // found using 2 point line equation
    float point7[2] = {350, 230};  // found using 2 point line equation
    
    //L
    float point8[2] = {460, 340};
    float point9[2] = {460, 120};
    float point10[2] = {540, 120};
    
    //E
    float point11[2] = {580, 340};
    float point12[2] = {670, 340};
    float point13[2] = {580, 120};
    float point14[2] = {670, 120};
    float point15[2] = {580, 230};
    float point16[2] = {650, 230};

    //setting the point size and font color
    glPointSize(10);                     // sets point size to give thickness to the lines
	//glColor3f(0, 0, 0);               // uncomment to get a black text on light background

    //P plot
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    DDA(point1, point2);
    Brute(ell_1);
    
    //A plot 
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    DDA(point3, point4);
    DDA(point4, point5);
    DDA(point6, point7);

    //L plot 
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    DDA(point8, point9);
    DDA(point9, point10);

    //E plot
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    DDA(point11, point12);
    DDA(point13, point14);
    DDA(point15, point16);
    DDA(point11, point13); //vertical line

    glFlush();
	glutSwapBuffers();
}


//driver code
int main(int argc, char **argv)
{
	srand(time(0)); // random seeding for random color

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);


	glutInitWindowPosition(500, 500);
	glutCreateWindow("CED18I039");
	myinit();
	glutDisplayFunc(my_name);

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