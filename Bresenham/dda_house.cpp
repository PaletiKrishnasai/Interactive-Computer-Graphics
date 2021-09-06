// Author : Paleti Krishnasai - CED18I039
// g++ dda2.cpp -o dda2 -lGL -lGLU -lglut -lGLEW
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

vector<pair<float, float>> bresen_pts_house;
vector<pair<float, float>> dda_pts_house;
vector<pair<float, float>> brute_pts_house;

long long int n1 = 0, n2 = 0, n3 = 0;

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

void MSE_House()
{
	float mse_bresen_hex = 0;
	float mse_dda_hex = 0;
	for (int i = 0; i < n1; i++)
	{
		mse_bresen_hex += pow((brute_pts_house[i].first - bresen_pts_house[i].first), 2) + pow((brute_pts_house[i].second - bresen_pts_house[i].second), 2);
		mse_dda_hex += pow((brute_pts_house[i].first - dda_pts_house[i].first), 2) + pow((brute_pts_house[i].second - dda_pts_house[i].second), 2);
	}
	mse_bresen_hex /= n1;
	mse_dda_hex /= n1;
	cout << "Mean Square Error for Bresenham=" << mse_bresen_hex << " Mean Square Error for DDA=" << mse_dda_hex << endl;
}

void BRUTE(float point1[2], float point2[2])
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
		Pixel(x, y);
		brute_pts_house.push_back(make_pair(x, y));
		n3++;
		x += x_increment / precision;
		y += y_increment / precision;
	}
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
		Pixel(round(x), round(y));

		dda_pts_house.push_back(make_pair(round(x), round(y)));
		//cout<<"printing in DDA"<<endl;
		//cout<<dda_pts_house[n1].first<<" "<<dda_pts_house[n1].second<<" "<<n1<<endl;
		n1++;
		x += x_increment / precision;
		y += y_increment / precision;
	}
}

void DDA1(float point1[2], float point2[2])
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

		//dda_pts_house.push_back(make_pair(round(x), round(y)));
		//cout<<"printing in DDA"<<endl;
		//cout<<dda_pts_house[n1].first<<" "<<dda_pts_house[n1].second<<" "<<n1<<endl;
		//n1++;
		x += x_increment / precision;
		y += y_increment / precision;
	}
}


void Triangle_color_dda(float point1[2], float point2[2], float point3[2])
{
	float x1 = point1[0], y1 = point1[1];
	float x2 = point2[0], y2 = point2[1];
	float x3 = point3[0], y3 = point3[1];
	float vertex[2] = {x3, y3};

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

	for (i = 0; i < length * precision; i++)
	{
		DDA1(vertex, point);
		point[0] += x_increment / precision;
		point[1] += y_increment / precision;
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
			bresen_pts_house.push_back(make_pair(x1, y1));
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

			bresen_pts_house.push_back(make_pair(x1, y1));
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

void house_BRUTE()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(4);
//body	
	
	float a[2] = {80,40};
	float b[2] = {240,40};
	float c[2] = {240,200};
	float d[2] = {80,200};

	int a_1[2] = {80,40};
	int b_1[2] = {240,40};
	int c_1[2] = {240,200};
	int d_1[2] = {80,200};

	glColor3f(0, 0.7, 1);
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(a,c,b);
	Triangle_color_dda(a,c,d);

	glColor3f(0,0,0); // outline

    BRUTE(a,b);
	BRUTE(b,c);
	BRUTE(c,d);
	BRUTE(d,a);



//roof

	float e[2] = {160,320};
	int e_1[2] = {160,320};
	glColor3f(1,0.2 ,0.2);
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(c,d,e);

	glColor3f(0,0,0); // outline
    BRUTE(c,d);
	BRUTE(d,e);
	BRUTE(e,c);



	

// door
	
	float f[2] = {140,40};
	float g[2] = {180,40};
	float h[2] = {180,120};
	float i[2] = {140,120};

	int f_1[2] = {140,40};
	int g_1[2] = {180,40};
	int h_1[2] = {180,120};
	int i_1[2] = {140,120};

	glColor3f(1,1,1);//white
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(f,h,g);
	Triangle_color_dda(f,h,i);

	//outline
	glColor3f(0,0,0); //black outline

    BRUTE(f,g);
	BRUTE(g,h);
	BRUTE(h,i);
	BRUTE(i,f);



	

//window l

	float j[2] = {100, 100}; 
    float k[2] = {120, 100};
    float l[2] = {120, 120};
    float m[2] = {100, 120};

	int j_1[2] = {100, 100}; 
    int k_1[2] = {120, 100};
    int l_1[2] = {120, 120};
    int m_1[2] = {100, 120};

	glColor3f(1,1,1);//white
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(j,l,k);
	Triangle_color_dda(j,l,m);

	glColor3f(0,0,0); // outline

    BRUTE(j,k);
	BRUTE(k,l);
	BRUTE(l,m);
	BRUTE(m,j);





//window r

	float n[2] = {200, 100}; 
    float o[2] = {220, 100};
    float p[2] = {220, 120};
    float q[2] = {200, 120};

	int n_1[2] = {200, 100}; 
    int o_1[2] = {220, 100};
    int p_1[2] = {220, 120};
    int q_1[2] = {200, 120};

	glColor3f(1,1,1);//white	
	//glColor3f(RandomColor(),RandomColor(),RandomColor());

	Triangle_color_dda(n,p,o);
	Triangle_color_dda(n,p,q);

	glColor3f(0,0,0); // outline

    BRUTE(n,o);
	BRUTE(o,p);
	BRUTE(p,q);
	BRUTE(q,n);



    glFlush();
    glutSwapBuffers();
}

void house_DDA()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(4);
//body	
	
	float a[2] = {80,40};
	float b[2] = {240,40};
	float c[2] = {240,200};
	float d[2] = {80,200};

	int a_1[2] = {80,40};
	int b_1[2] = {240,40};
	int c_1[2] = {240,200};
	int d_1[2] = {80,200};

	glColor3f(0, 0.7, 1);
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(a,c,b);
	Triangle_color_dda(a,c,d);

	glColor3f(0,0,0); // outline



	DDA(a,b);
	DDA(b,c);
	DDA(c,d);
	DDA(d,a);




//roof

	float e[2] = {160,320};
	int e_1[2] = {160,320};
	glColor3f(1,0.2 ,0.2);
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(c,d,e);

	glColor3f(0,0,0); // outline


    DDA(c,d);
	DDA(d,e);
	DDA(e,c);
    


	

// door
	
	float f[2] = {140,40};
	float g[2] = {180,40};
	float h[2] = {180,120};
	float i[2] = {140,120};

	int f_1[2] = {140,40};
	int g_1[2] = {180,40};
	int h_1[2] = {180,120};
	int i_1[2] = {140,120};

	glColor3f(1,1,1);//white
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(f,h,g);
	Triangle_color_dda(f,h,i);

	//outline
	glColor3f(0,0,0); //black outline



    DDA(f,g);
	DDA(g,h);
	DDA(h,i);
	DDA(i,f);



	

//window l

	float j[2] = {100, 100}; 
    float k[2] = {120, 100};
    float l[2] = {120, 120};
    float m[2] = {100, 120};

	int j_1[2] = {100, 100}; 
    int k_1[2] = {120, 100};
    int l_1[2] = {120, 120};
    int m_1[2] = {100, 120};

	glColor3f(1,1,1);//white
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(j,l,k);
	Triangle_color_dda(j,l,m);

	glColor3f(0,0,0); // outline


    DDA(j,k);
	DDA(k,l);
	DDA(l,m);
	DDA(m,j);


//window r

	float n[2] = {200, 100}; 
    float o[2] = {220, 100};
    float p[2] = {220, 120};
    float q[2] = {200, 120};

	int n_1[2] = {200, 100}; 
    int o_1[2] = {220, 100};
    int p_1[2] = {220, 120};
    int q_1[2] = {200, 120};

	glColor3f(1,1,1);//white	
	//glColor3f(RandomColor(),RandomColor(),RandomColor());

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



void house_BLD()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(4);
//body	
	
	float a[2] = {80,40};
	float b[2] = {240,40};
	float c[2] = {240,200};
	float d[2] = {80,200};

	int a_1[2] = {80,40};
	int b_1[2] = {240,40};
	int c_1[2] = {240,200};
	int d_1[2] = {80,200};

	glColor3f(0, 0.7, 1);
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(a,c,b);
	Triangle_color_dda(a,c,d);

	glColor3f(0,0,0); // outline

  

	BLD(a,b);
	BLD(b,c);
	BLD(c,d);
	BLD(d,a);


//roof

	float e[2] = {160,320};
	int e_1[2] = {160,320};
	glColor3f(1,0.2 ,0.2);
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(c,d,e);

	glColor3f(0,0,0); // outline
   
    
    BLD(c,d);
	BLD(d,e);
	BLD(e,c);

	

// door
	
	float f[2] = {140,40};
	float g[2] = {180,40};
	float h[2] = {180,120};
	float i[2] = {140,120};

	int f_1[2] = {140,40};
	int g_1[2] = {180,40};
	int h_1[2] = {180,120};
	int i_1[2] = {140,120};

	glColor3f(1,1,1);//white
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(f,h,g);
	Triangle_color_dda(f,h,i);

	//outline
	glColor3f(0,0,0); //black outline

  

    BLD(f,g);
	BLD(g,h);
	BLD(h,i);
	BLD(i,f);

	

//window l

	float j[2] = {100, 100}; 
    float k[2] = {120, 100};
    float l[2] = {120, 120};
    float m[2] = {100, 120};

	int j_1[2] = {100, 100}; 
    int k_1[2] = {120, 100};
    int l_1[2] = {120, 120};
    int m_1[2] = {100, 120};

	glColor3f(1,1,1);//white
	//glColor3f(RandomColor(),RandomColor(),RandomColor());
	Triangle_color_dda(j,l,k);
	Triangle_color_dda(j,l,m);

	glColor3f(0,0,0); // outline

  

    BLD(j,k);
	BLD(k,l);
	BLD(l,m);
	BLD(m,j);



//window r

	float n[2] = {200, 100}; 
    float o[2] = {220, 100};
    float p[2] = {220, 120};
    float q[2] = {200, 120};

	int n_1[2] = {200, 100}; 
    int o_1[2] = {220, 100};
    int p_1[2] = {220, 120};
    int q_1[2] = {200, 120};

	glColor3f(1,1,1);//white	
	//glColor3f(RandomColor(),RandomColor(),RandomColor());

	Triangle_color_dda(n,p,o);
	Triangle_color_dda(n,p,q);

	glColor3f(0,0,0); // outline

   

    BLD(n,o);
	BLD(o,p);
	BLD(p,q);
	BLD(q,n);

    MSE_House();
    glFlush();
    glutSwapBuffers();
}


//driver code
int main(int argc, char **argv)
{
	srand(time(0));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);

	
// BRUTE	
	glutInitWindowPosition(900, 100);
    glutCreateWindow("CED18I039_hexagon_BRUTE"); 
    myinit();
    glutDisplayFunc(house_BRUTE);



	
 //DDA
 	glutInitWindowPosition(900, 500);
    glutCreateWindow("CED18I039_hexagon_DDA"); 
    myinit();
    glutDisplayFunc(house_DDA);
 

	// BLD

	glutInitWindowPosition(100, 800);
	glutCreateWindow("CED18I039_house_BLD");
	myinit();
	glutDisplayFunc(house_BLD);

	glutReshapeFunc(changeViewPort);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}

	//cout<<n1<<endl;

	glutMainLoop();

	return 0;
}