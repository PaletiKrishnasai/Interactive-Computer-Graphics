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

#define size_of_array 100000

vector<pair<float,float>> bresen_pts_hexagon;
vector<pair<float,float>> dda_pts_hexagon;
vector<pair<float,float>> brute_pts_hexagon;


long long int n1=0,n2=0,n3=0;

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
	gluOrtho2D (0.0,400.0,0.0,400.0);
	glMatrixMode(GL_MODELVIEW);
}

float precision = 1; // detail


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

void draw_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void MSE_Hexagon()
{
    float mse_bresen_hex=0;
    float mse_dda_hex=0;
    for(int i=0;i<n1;i++)
    {
        mse_bresen_hex += pow((brute_pts_hexagon[i].first-bresen_pts_hexagon[i].first),2) + pow((brute_pts_hexagon[i].second-bresen_pts_hexagon[i].second),2) ;
        mse_dda_hex += pow((brute_pts_hexagon[i].first-dda_pts_hexagon[i].first),2)+pow((brute_pts_hexagon[i].second-dda_pts_hexagon[i].second),2) ;
    }
    mse_bresen_hex/=n1;
    mse_dda_hex/=n1;
    cout<<"Mean Square Error for Bresenham="<<mse_bresen_hex<<" Mean Square Error for DDA="<<mse_dda_hex<<endl;
}

void BRUTE(float point1[2],float point2[2])
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
		brute_pts_hexagon.push_back(make_pair(x,y));
		n3++;
		x += x_increment/precision;
		y += y_increment/precision;
	}
    

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
		Pixel(round(x) , round(y) );
		
		dda_pts_hexagon.push_back(make_pair(round(x),round(y)));
		//cout<<"printing in DDA"<<endl;
		//cout<<dda_pts_hexagon[n1].first<<" "<<dda_pts_hexagon[n1].second<<" "<<n1<<endl;
		n1++;
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
			bresen_pts_hexagon.push_back(make_pair(x1, y1));
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

			glBegin(GL_POINTS);
			glVertex2f(round(x1), round(y1));
			glEnd();

			n2++;
		}
	}
	else
	{
		p = 2 * abs(dx) - abs(dy);
		for (int i = 0; i < abs(dy); i++)
		{

			bresen_pts_hexagon.push_back(make_pair(x1, y1));
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

			glBegin(GL_POINTS);
			glVertex2f(round(x1), round(y1));
			glEnd();

			n2++;
		}
	}
}



void hexagon_DDA()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//HEXAGON 
	
/*
	float point1[2] = {centre[0]+r*(float)cos((rotation+90)*M_PI/180),centre[1]+r*(float)sin((rotation+90)*M_PI/180)};
	float point2[2] = {centre[0]+r*(float)cos((rotation+30)*M_PI/180),centre[1]+r*(float)sin((rotation+30)*M_PI/180)};
	float point3[2] = {centre[0]+r*(float)cos((rotation+-30)*M_PI/180),centre[1]+r*(float)sin((rotation+-30)*M_PI/180)};
	float point4[2] = {centre[0]+r*(float)cos((rotation+-90)*M_PI/180),centre[1]+r*(float)sin((rotation+-90)*M_PI/180)};
	float point5[2] = {centre[0]+r*(float)cos((rotation+-150)*M_PI/180),centre[1]+r*(float)sin((rotation+-150)*M_PI/180)};
	float point6[2] = {centre[0]+r*(float)cos((rotation+150)*M_PI/180),centre[1]+r*(float)sin((rotation+150)*M_PI/180)};
*/
	float point1[2] = {120,340};
	float point2[2] = {280,340};
	float point3[2] = {360,200};
	float point4[2] = {280,60};
	float point5[2] = {120,60};
	float point6[2] = {40,200};
	
	/*
	printf("%f,%f\n",point1[0],point1[1]);
	printf("%f,%f\n",point2[0],point2[1]);
	printf("%f,%f\n",point3[0],point3[1]);
	printf("%f,%f\n",point4[0],point4[1]);
	printf("%f,%f\n",point5[0],point5[1]);
	printf("%f,%f\n",point6[0],point6[1]);
	*/
	glPointSize(4);
	glColor3f(0,0,0);
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	DDA(point1,point2);
	DDA(point2,point3);
	DDA(point3,point4);
	DDA(point4,point5);
	DDA(point5,point6);
	DDA(point6,point1);

    glFlush();
    glutSwapBuffers();
}

void hexagon_BLD()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//HEXAGON 
	float point1[2] = {120,340};
	float point2[2] = {280,340};
	float point3[2] = {360,200};
	float point4[2] = {280,60};
	float point5[2] = {120,60};
	float point6[2] = {40,200};
	glPointSize(4);
	glColor3f(0,0,0);
	//glColor3f(RandomColor(),RandomColor(),RandomColor());

	

	

	BLD(point1,point2);
	BLD(point2,point3);
	BLD(point3,point4);
	BLD(point4,point5);
	BLD(point5,point6);
	BLD(point6,point1);

	MSE_Hexagon();

    glFlush();
    glutSwapBuffers();
	
}







void line_brute_hexagon()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//HEXAGON 
	float point1[2] = {120,340};
	float point2[2] = {280,340};
	float point3[2] = {360,200};
	float point4[2] = {280,60};
	float point5[2] = {120,60};
	float point6[2] = {40,200};
	glPointSize(4);
	glColor3f(0,0,0);
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	
	BRUTE(point1,point2);
	BRUTE(point2,point3);
	BRUTE(point3,point4);
	BRUTE(point4,point5);
	BRUTE(point5,point6);
	BRUTE(point6,point1);
    glFlush();
    glutSwapBuffers();
}




//driver code
int main(int argc,char** argv)
{
    srand(time(0));

    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);
 
 
// BRUTE	
	glutInitWindowPosition(900, 100);
    glutCreateWindow("CED18I039_hexagon_BRUTE"); 
    myinit();
    glutDisplayFunc(line_brute_hexagon);

	

 
 //DDA
    glutInitWindowPosition(900, 500);
    glutCreateWindow("CED18I039_hexagon_DDA"); 
    myinit();
    glutDisplayFunc(hexagon_DDA);
 
 


// BLD

	glutInitWindowPosition(100, 800);
    glutCreateWindow("CED18I039_hexagon_BLD"); 
    myinit();
    glutDisplayFunc(hexagon_BLD);





    glutReshapeFunc(changeViewPort);
    GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	//cout<<n1<<endl;

	glutMainLoop();

	
    return 0;
}
