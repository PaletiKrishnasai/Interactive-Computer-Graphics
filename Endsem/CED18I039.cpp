// Author : Paleti Krishnasai - CED18I039
// g++ CED18I039.cpp -o endsem -lGL -lGLU -lglut -lGLEW
#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <time.h>
using namespace std;

vector<int> pntXH;
vector<int> pntYH;

vector<int> pntXK;
vector<int> pntYK;

vector<int> pntXL;
vector<int> pntYL;

vector<int> pntXW;
vector<int> pntYW;

double angle, angleRad;
double r;

void changeViewPort(int w, int h)
{
	if (w >= h)
		glViewport(w / 2 - h / 2, 0, h, h);
	else
		glViewport(0, h / 2 - w / 2, w, w);
}

void Pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

float RandomColor()
{
	float color = (float)((rand() % 100)) / 99;
	return color;
}
double round(double d)
{
	return floor(d + 0.5);
}

void myinit(void)
{
	glClearColor(0.8,0.8,0.8,0.0);     // uncomment this line to have a white background
    //glClearColor(0,0,0,0.0);            // simultaeniously comment this line allow the white background
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-400.0, 400.0, -400.0, 400.0);
	glMatrixMode(GL_MODELVIEW);
}

void letters()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //H
    pntXH.push_back(10); pntYH.push_back(10);
    pntXH.push_back(10); pntYH.push_back(30); 
    pntXH.push_back(15); pntYH.push_back(30);
    pntXH.push_back(15); pntYH.push_back(22);
    pntXH.push_back(35); pntYH.push_back(22);
    pntXH.push_back(35); pntYH.push_back(30);
    pntXH.push_back(40); pntYH.push_back(30);
    pntXH.push_back(40); pntYH.push_back(10);
    pntXH.push_back(35); pntYH.push_back(10);
    pntXH.push_back(35); pntYH.push_back(18);
    pntXH.push_back(15); pntYH.push_back(18);
    pntXH.push_back(15); pntYH.push_back(10);

    //K
    pntXK.push_back(50); pntYK.push_back(10);
    pntXK.push_back(50); pntYK.push_back(30);
    pntXK.push_back(55); pntYK.push_back(30);
    pntXK.push_back(55); pntYK.push_back(22);
    pntXK.push_back(70); pntYK.push_back(30);
    pntXK.push_back(72); pntYK.push_back(28);
    pntXK.push_back(55); pntYK.push_back(20);
    pntXK.push_back(72); pntYK.push_back(12);
    pntXK.push_back(70); pntYK.push_back(10);
    pntXK.push_back(55); pntYK.push_back(18);
    pntXK.push_back(55); pntYK.push_back(10);

    //L
    pntXL.push_back(85); pntYL.push_back(10);
    pntXL.push_back(85); pntYL.push_back(30);
    pntXL.push_back(90); pntYL.push_back(30);
    pntXL.push_back(90); pntYL.push_back(15);
    pntXL.push_back(105); pntYL.push_back(15);
    pntXL.push_back(105); pntYL.push_back(10);

    //w


}

void drawPolygonH()
{
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2);
    
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < pntXH.size(); i++)
	{
		glVertex2i(pntXH[i], pntYH[i]);
	}
	glEnd();
}


void drawPolygonReflectionH(double angleRad,double r)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < pntXH.size(); i++)
	{
		glVertex2i( round((2*r*cos(angleRad))-(pntXH[i]*cos(2*angleRad))-(pntYH[i]*sin(2*angleRad)))  , round((-2* r * sin(angleRad))- (pntXH[i] * sin(2*angleRad))+(pntYH[i]*cos(2*angleRad))));
	}

	glEnd();

}


void drawPolygonK()
{
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2);
    
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < pntXK.size(); i++)
	{
		glVertex2i(pntXK[i], pntYK[i]);
	}
	glEnd();
}


void drawPolygonReflectionK(double angleRad,double r)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < pntXK.size(); i++)
	{
		glVertex2i( round((2*r*cos(angleRad))-(pntXK[i]*cos(2*angleRad))-(pntYK[i]*sin(2*angleRad)))  , round((-2* r * sin(angleRad))- (pntXK[i] * sin(2*angleRad))+(pntYK[i]*cos(2*angleRad))));
	}
	glEnd();
}


void drawPolygonL()
{
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2);
    
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < pntXL.size(); i++)
	{
		glVertex2i(pntXL[i], pntYL[i]);
	}
	glEnd();
}


void drawPolygonReflectionL(double angleRad,double r)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < pntXL.size(); i++)
	{
		glVertex2i( round((2*r*cos(angleRad))-(pntXL[i]*cos(2*angleRad))-(pntYL[i]*sin(2*angleRad)))  , round((-2* r * sin(angleRad))- (pntXL[i] * sin(2*angleRad))+(pntYL[i]*cos(2*angleRad))));
	}
	glEnd();
}
void edgedetect(float x1,float y1,float x2,float y2,int *le,int *re)
{
    float mx,x,temp;
    int i;
    if((y2-y1)<0)
    {
    temp=y1;y1=y2;y2=temp;
    temp=x1;x1=x2;x2=temp;
    }
    if((y2-y1)!=0)
    mx=(x2-x1)/(y2-y1);
    else
    mx=x2-x1;
    x=x1;
    for(i=y1;i<=y2;i++)
    {
    if(x<(float)le[i])
    le[i]=(int)x;
    if(x>(float)re[i])
    re[i]=(int)x;
    x+=mx;
    }
}
void plot_points(int x,int y)
{
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void scanfill(vector <int> pntXH,vector <int> pntYH)
{
    int le[800],re[800];
    int i,y;
    for(i=0;i<800;i++)
    {
    le[i]=800;
    re[i]=0;
    }
    for(int i=0;i<pntXH.size();i++)
    {
        int j=i+1;
        if(i==pntXH.size()-1)
        j=0;
        edgedetect(pntXH[i],pntYH[i],pntXH[j],pntYH[j],le,re);
    }

    for(y=0;y<800;y++)
    {
    for(i=(int)le[y];i<(int)re[y];i++)
    plot_points(i,y);
    }
}
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(0, -400);
        glVertex2f(0, 400);
        glVertex2f(-400, 0);
        glVertex2f(400,0);
    glEnd();
 
		drawPolygonH();
		drawPolygonReflectionH(angleRad,r);

        drawPolygonK();
		drawPolygonReflectionK(angleRad,r);

        drawPolygonL();
		drawPolygonReflectionL(angleRad,r);
	
        //scanfill(pntXH,pntYH); // code is buggy


	glutSwapBuffers();
}


int main(int argc, char **argv)
{
	srand(time(0));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
     //H
    pntXH.push_back(10); pntYH.push_back(10);
    pntXH.push_back(10); pntYH.push_back(30); 
    pntXH.push_back(15); pntYH.push_back(30);
    pntXH.push_back(15); pntYH.push_back(22);
    pntXH.push_back(35); pntYH.push_back(22);
    pntXH.push_back(35); pntYH.push_back(30);
    pntXH.push_back(40); pntYH.push_back(30);
    pntXH.push_back(40); pntYH.push_back(10);
    pntXH.push_back(35); pntYH.push_back(10);
    pntXH.push_back(35); pntYH.push_back(18);
    pntXH.push_back(15); pntYH.push_back(18);
    pntXH.push_back(15); pntYH.push_back(10);

     //K
    pntXK.push_back(50); pntYK.push_back(10);
    pntXK.push_back(50); pntYK.push_back(30);
    pntXK.push_back(55); pntYK.push_back(30);
    pntXK.push_back(55); pntYK.push_back(22);
    pntXK.push_back(70); pntYK.push_back(30);
    pntXK.push_back(72); pntYK.push_back(28);
    pntXK.push_back(55); pntYK.push_back(20);
    pntXK.push_back(72); pntYK.push_back(12);
    pntXK.push_back(70); pntYK.push_back(10);
    pntXK.push_back(55); pntYK.push_back(18);
    pntXK.push_back(55); pntYK.push_back(10);

    //L
    pntXL.push_back(85); pntYL.push_back(10);
    pntXL.push_back(85); pntYL.push_back(30);
    pntXL.push_back(90); pntYL.push_back(30);
    pntXL.push_back(90); pntYL.push_back(15);
    pntXL.push_back(105); pntYL.push_back(15);
    pntXL.push_back(105); pntYL.push_back(10);


		cout << "Enter the angle for rotation: "; cin >> angle;
		angleRad = angle * 3.1416 / 180;
        cout<<"enter perpendicular distance: "; cin >> r;
	
	
    
    glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
    glutCreateWindow("CED18I039");
	myinit();
	glutDisplayFunc(Display);


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