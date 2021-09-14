// Author : Paleti Krishnasai - CED18I039
// g++ med.cpp -o med -lGL -lGLU -lglut -lGLEW
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

float alpha;
float beta;
float horizontal_axis;
float vertical_axis;
float checkAngle;

struct ellipse
{
    float c[2];
    float rx;
    float ry;
};

void changeViewPort(int w, int h) ;
void myinit(void);
void Pixel(float x, float y);
void PlotArc(float c[2], float x, float y);
void MED(ellipse cir,int mode);
void BLD(float point1[2], float point2[2]);
void PlotArc(float c[2], float x, float y);
void draw_arcs();

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

void Pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

float RandomColor() 
{
    float color=(float)((rand() % 100))/99;
    return color;    
}

void Plot_Region1_symmettry(float c[2], float x, float y)
{
    Pixel(x + c[0] , y + c[1]); //O1
    Pixel(-x + c[0] , y + c[1]); //O2
    Pixel(x + c[0] , -y + c[1]); //O3
    Pixel(-x + c[0] , -y + c[1]); //O4

    
}


void Plot_Region2_symmettry(float c[2], float x, float y)
{
   Pixel(x + c[0] , y + c[1]); //O1
    Pixel(-x + c[0] , y + c[1]); //O2
    Pixel(x + c[0] , -y + c[1]); //O3
    Pixel(-x + c[0] , -y + c[1]); //O4
}

void MED(ellipse cir)
{
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = cir.ry;
 
    // Initial decision parameter of region 1
    d1 = (cir.ry * cir.ry) - (cir.rx * cir.rx * cir.ry) +
                     (0.25 * cir.rx * cir.rx);
    dx = 2 * cir.ry * cir.ry * x;
    dy = 2 * cir.rx * cir.rx * y;
 
    // For region 1 (octant 2 esque)
    while (dx < dy)
    {
 
        // Print points based on 4-way symmetry
        Plot_Region1_symmettry(cir.c, x, y);

 
        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * cir.ry * cir.ry);
            d1 = d1 + dx + (cir.ry * cir.ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * cir.ry * cir.ry);
            dy = dy - (2 * cir.rx * cir.rx);
            d1 = d1 + dx - dy + (cir.ry * cir.ry);
        }
    }
 
    // Decision parameter of region 2
    d2 = ((cir.ry * cir.ry) * ((x + 0.5) * (x + 0.5))) +
         ((cir.rx * cir.rx) * ((y - 1) * (y - 1))) -
          (cir.rx * cir.rx * cir.ry * cir.ry);
 
    // Plotting points of region 2
    while (y >= 0)
    {
 
        // Print points based on 4-way symmetry
        Plot_Region2_symmettry(cir.c, x, y);
        
 
        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * cir.rx * cir.rx);
            d2 = d2 + (cir.rx * cir.rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * cir.ry * cir.ry);
            dy = dy - (2 * cir.rx * cir.rx);
            d2 = d2 + dx - dy + (cir.rx * cir.rx);
        }
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

void Parametric(ellipse cir)
{
    float cx = cir.c[0];
    float cy = cir.c[1];
    float h_rx = cir.rx;
    float v_ry = cir.ry;
    
    for(float i =M_PI*0;i<=M_PI*2;i+=0.001) // radians
    {
        Pixel( cx + h_rx*cos(i) , cy + v_ry*sin(i) ); // x+r*cosA,y+r*sinA
    }
    


}

void Brute(ellipse cir)
{
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

void ellipse_med()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    ellipse ell = {{(400+rand()%200), (400+rand()%200)}, horizontal_axis, vertical_axis};
    glPointSize(1);
    glColor3f(0.5, 0.5, 0.5);
    float xAxis[2][2] = {{ell.c[0] - 1000, ell.c[1]},
                         {ell.c[0] + 1000, ell.c[1]}};

    float yAxis[2][2] = {{ell.c[0], ell.c[1] - 1000},
                         {ell.c[0], ell.c[1] + 1000}};
    BLD(xAxis[0], xAxis[1]);
    BLD(yAxis[0], yAxis[1]);
    
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    glPointSize(3);
    MED(ell);
    glutSwapBuffers();
}

void ellipse_parameteric()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    ellipse ell_1 = {{(400+rand()%200), (400+rand()%200)}, horizontal_axis, vertical_axis};
    glPointSize(1);
    glColor3f(0.5, 0.5, 0.5);
    float xAxis[2][2] = {{ell_1.c[0] - 1000, ell_1.c[1]},
                         {ell_1.c[0] + 1000, ell_1.c[1]}};

    float yAxis[2][2] = {{ell_1.c[0], ell_1.c[1] - 1000},
                         {ell_1.c[0], ell_1.c[1] + 1000}};
    BLD(xAxis[0], xAxis[1]);
    BLD(yAxis[0], yAxis[1]);
    
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    glPointSize(3);
    Parametric(ell_1);
    glutSwapBuffers();
}

void ellipse_brute()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    ellipse ell_1 = {{(400+rand()%200), (400+rand()%200)}, horizontal_axis, vertical_axis};
    glPointSize(1);
    glColor3f(0.5, 0.5, 0.5);
    float xAxis[2][2] = {{ell_1.c[0] - 1000, ell_1.c[1]},
                         {ell_1.c[0] + 1000, ell_1.c[1]}};

    float yAxis[2][2] = {{ell_1.c[0], ell_1.c[1] - 1000},
                         {ell_1.c[0], ell_1.c[1] + 1000}};
    BLD(xAxis[0], xAxis[1]);
    BLD(yAxis[0], yAxis[1]);
    
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    glPointSize(3);
    Brute(ell_1);
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    //glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
  
   // cin>>horizontal_axis;
    horizontal_axis = rand() % 500;
  //  cout<<"enter vertical"<<endl;
   // cin>>vertical_axis;
    vertical_axis = rand() % 500;

    glutCreateWindow("CED18I039_ellipse_MED");
    glutInitWindowPosition(200, 200);
    myinit();
    glutDisplayFunc(ellipse_med);

    glutCreateWindow("CED18I039_ellipse_parametric");
    glutInitWindowPosition(2000, 1500);
    myinit();
    glutDisplayFunc(ellipse_parameteric);

    glutCreateWindow("CED18I039_ellipse_brute");
    glutInitWindowPosition(2800, 800);
    myinit();
    glutDisplayFunc(ellipse_brute);

    glutReshapeFunc(changeViewPort);
    glutMainLoop();
}