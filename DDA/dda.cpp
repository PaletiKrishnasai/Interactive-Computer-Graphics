// Author : Paleti Krishnasai - CED18I039
// g++ dda.cpp -o dda -lGL -lGLU -lglut -lGLEW
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
	gluOrtho2D (0.0,100.0,0.0,100.0);
	glMatrixMode(GL_MODELVIEW);
}

struct Circle // centre (x,y) ; Radius (rx,ry)
    {
		float x;
		float y;
		float rx;
        float ry;
	};

int flag = 0 ; // triangle strip control
float precision = 20;


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
	//glFlush();

}

void DDA (float point1[2],float point2[2])
{
    float x1 = point1[0] , y1 = point1[1];
	float x2 = point2[0] , y2 = point2[1];
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
	for (i = 0; i < length*precision; i++)
	{
		Pixel(x , y );
		x += x_increment/precision;
		y += y_increment/precision;
	}
}

void Triangle_color_dda(float point1[2],float point2[2],float point3[2])
{
	float x1 = point1[0] , y1 = point1[1];
	float x2 = point2[0] , y2 = point2[1];
	float x3 = point3[0] , y3 = point3[1];
	float vertex[2] = {x3,y3};

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

	int i;
	float point[2] = {x1, y1};
	
	for (i = 0; i < length*precision; i++)
	{
		DDA(vertex,point); 
		point[0] += x_increment/precision;
		point[1] += y_increment/precision;
	}
}

void hexagon_DDA()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//HEXAGON 
	float centre[2] = {50,50};	//centre
	float r = 40;			// length
	float rotation=30; 		//  degrees

	float point1[2] = {centre[0]+r*(float)cos((rotation+90)*M_PI/180),centre[1]+r*(float)sin((rotation+90)*M_PI/180)};
	float point2[2] = {centre[0]+r*(float)cos((rotation+30)*M_PI/180),centre[1]+r*(float)sin((rotation+30)*M_PI/180)};
	float point3[2] = {centre[0]+r*(float)cos((rotation+-30)*M_PI/180),centre[1]+r*(float)sin((rotation+-30)*M_PI/180)};
	float point4[2] = {centre[0]+r*(float)cos((rotation+-90)*M_PI/180),centre[1]+r*(float)sin((rotation+-90)*M_PI/180)};
	float point5[2] = {centre[0]+r*(float)cos((rotation+-150)*M_PI/180),centre[1]+r*(float)sin((rotation+-150)*M_PI/180)};
	float point6[2] = {centre[0]+r*(float)cos((rotation+150)*M_PI/180),centre[1]+r*(float)sin((rotation+150)*M_PI/180)};
	glPointSize(4);
	//glColor3f(0,0,0);
	glColor3f(RandomColor(),RandomColor(),RandomColor());
	DDA(point1,point2);
	DDA(point2,point3);
	DDA(point3,point4);
	DDA(point4,point5);
	DDA(point5,point6);
	DDA(point6,point1);

    glFlush();
    glutSwapBuffers();
}

void house_DDA()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(4);
//body	
	
	float a[2] = {20,10};
	float b[2] = {60,10};
	float c[2] = {60,50};
	float d[2] = {20,50};

	//glColor3f(0, 0.7, 1);
	glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(a,c,b);
	Triangle_color_dda(a,c,d);

	glColor3f(0,0,0); // outline
	DDA(a,b);
	DDA(b,c);
	DDA(c,d);
	DDA(d,a);

//roof

	float e[2] = {40,80};
	//glColor3f(1,0.2 ,0.2);
	glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(c,d,e);

	glColor3f(0,0,0); // outline
	DDA(c,d);
	DDA(d,e);
	DDA(e,c);

// door
	
	float f[2] = {35,10};
	float g[2] = {45,10};
	float h[2] = {45,30};
	float i[2] = {35,30};

	//glColor3f(1,1,1);//white
	glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(f,h,g);
	Triangle_color_dda(f,h,i);

	//outline
	glColor3f(0,0,0); //black outline
	DDA(f,g);
	DDA(g,h);
	DDA(h,i);
	DDA(i,f);

//window l

	float j[2] = {25, 25}; 
    float k[2] = {30, 25};
    float l[2] = {30, 30};
    float m[2] = {25, 30};

	//glColor3f(1,1,1);//white
	glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(j,l,k);
	Triangle_color_dda(j,l,m);

	glColor3f(0,0,0); // outline
	DDA(j,k);
	DDA(k,l);
	DDA(l,m);
	DDA(m,j);

//window r

	float n[2] = {50, 25}; 
    float o[2] = {55, 25};
    float p[2] = {55, 30};
    float q[2] = {50, 30};

	//glColor3f(1,1,1);//white	
	glColor3f(RandomColor(),RandomColor(),RandomColor());

	Triangle_color_dda(n,p,o);
	Triangle_color_dda(n,p,q);

	glColor3f(0,0,0); // outline
	DDA(n,o);
	DDA(o,p);
	DDA(p,q);
	DDA(q,n);


    glFlush();
    glutSwapBuffers();
}

//driver code
int main(int argc,char** argv)
{
    srand(time(0));

    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
    glutInitWindowPosition(200, 200);
    //int 
    glutCreateWindow("CED18I039_hexagon_DDA"); 
    myinit();
    glutDisplayFunc(hexagon_DDA);
   
    glutInitWindowPosition(800, 800);
    glutCreateWindow("CED18I039_house_DDA"); 
    myinit();
    glutDisplayFunc(house_DDA);

    glutReshapeFunc(changeViewPort);
    GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glutMainLoop();
    return 0;
}