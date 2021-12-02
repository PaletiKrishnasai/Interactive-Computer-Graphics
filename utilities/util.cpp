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

vector<pair<float, float>> bresen_pts_hexagon;
vector<pair<float, float>> dda_pts_hexagon;
vector<pair<float, float>> brute_pts_hexagon;

long long int n1 = 0, n2 = 0, n3 = 0;

struct circle
{
    float c[2];
    float r;
};

void changeViewPort(int w, int h)
{
	if (w >= h)
		glViewport(w / 2 - h / 2, 0, h, h);
	else
		glViewport(0, h / 2 - w / 2, w, w);
}

void myinit(void)
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
	glMatrixMode(GL_MODELVIEW);
}

float precision = 1; // detail

float RandomColor()
{
	float color = (float)((rand() % 100)) / 99;
	return color;
}

void Pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void draw_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void PlotOctants(float c[2], float x, float y)
{
    //cout <<c[0] + y<<" "<<c[1] + x<<" "<<"O1"<<endl; //O1
   // cout <<c[0] + x<<" "<<c[1] + y<<" "<<"O2"<<endl; //O2
    cout <<c[0] - x<<" "<<c[1] + y<<" "<<"O3"<<endl; //O3
  //  cout <<c[0] - y<<" "<<c[1] + x<<" "<<"O4"<<endl; //O4

   // cout <<c[0] - y<<" "<<c[1] - x<<" "<<"O5"<<endl; //O5
  //  cout <<c[0] - x<<" "<<c[1] - y<<" "<<"O6"<<endl; //O6
   // cout <<c[0] + x<<" "<<c[1] - y<<" "<<"O7"<<endl; //O7
   // cout <<c[0] + y<<" "<<c[1] - x<<" "<<"O8"<<endl; //O8
}

void DDA(float point1[2], float point2[2])
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
		cout<<round(x)<<" "<<round(y)<<endl;

		dda_pts_hexagon.push_back(make_pair(round(x), round(y)));
		//cout<<"printing in DDA"<<endl;
		//cout<<dda_pts_hexagon[n1].first<<" "<<dda_pts_hexagon[n1].second<<" "<<n1<<endl;
		n1++;
		x += x_increment / precision;
		y += y_increment / precision;
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

			cout<<round(x1)<<" "<<round(y1)<<" DP:"<<p<<endl;

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

			cout<<round(x1)<<" "<<round(y1)<<" DP:"<<p<<endl;
			n2++;
		}
	}
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

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);

   float point1[2]={20,10};
   float point2[2]={10,23};
   circle frontW = {{7, 8}, 5};

    DDA(point1, point2);
	cout<<"BLD"<<endl;
    BLD(point1,point2);
    //mcd(frontW, 0);

    
    glutReshapeFunc(changeViewPort);
  
    glutMainLoop();
}