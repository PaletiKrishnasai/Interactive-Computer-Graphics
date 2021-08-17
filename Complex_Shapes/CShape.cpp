// Author : Paleti Krishnasai - CED18I039
// g++ CShape.cpp -o CShape -lGL -lGLU -lglut -lGLEW
#include <bits/stdc++.h>
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
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0,200.0,0.0,200.0);
}

struct Circle // centre (x,y) ; Radius (rx,ry)
    {
		float x;
		float y;
		float rx;
        float ry;
	};

int flag = 0 ; // triangle strip control

float RandomColor() 
{
    float color=(float)((rand() % 100))/99;
    return color;    
}

void ICG()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //lower
    glBegin(GL_QUADS);
    glColor3f(RandomColor(),RandomColor(),RandomColor());        
        glVertex2f(10, 50);
        glVertex2f(50, 50);
        glVertex2f(50, 55);
        glVertex2f(10,55);
   //upper
        glVertex2f(10, 100);
        glVertex2f(50, 100);
        glVertex2f(50, 105);
        glVertex2f(10,105);
    // vertical
        glVertex2f(27.5, 50);
        glVertex2f(32.5, 50);
        glVertex2f(32.5, 105);
        glVertex2f(27.5,105);
    glEnd();

// C

    Circle inner_C = {85,77.5,15,22.5};
    Circle outer_C = {85,77.5,20,27.5};

    glBegin(GL_TRIANGLE_STRIP); 
	glColor3f(RandomColor(),RandomColor(),RandomColor());       
	for(float i =M_PI*1.7;i>=M_PI*0.3;i-=0.001) // radians
	{
        if(flag==0)
        {
            glVertex2f(outer_C.x +outer_C.rx*cos(i),outer_C.y+outer_C.ry*sin(i)); // x+r*cosA,y+r*sinA
            flag = 1;
        }
        else
        {
            glVertex2f(inner_C.x +inner_C.rx*cos(i),inner_C.y+inner_C.ry*sin(i)); // x+r*cosA,y+r*sinA
			flag=0;
        }
	}
	glEnd();

// G 

    Circle inner_G = {137,77.5,15,22.5};
    Circle outer_G = {137,77.5,20,27.5};
    glBegin(GL_TRIANGLE_STRIP); 
	glColor3f(RandomColor(),RandomColor(),RandomColor());       
	for(float i =M_PI*2;i>=M_PI*0.3;i-=0.001) // radians
	{
        if(flag==0)
        {
            glVertex2f(outer_G.x +outer_G.rx*cos(i),outer_G.y+outer_G.ry*sin(i)); // x+r*cosA,y+r*sinA
            flag = 1;
        }
        else
        {
            glVertex2f(inner_G.x +inner_G.rx*cos(i),inner_G.y+inner_G.ry*sin(i)); // x+r*cosA,y+r*sinA
			flag=0;
        }
	}
	glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(137,77.5);
    glVertex2f(137,73.5);
    glVertex2f(157,73.5);
    glVertex2f(157,77.5);
    glEnd();

    glFlush();
    glutSwapBuffers();
}


void rollno()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 3
    Circle inner_3_top = {85,77.5,15,15};
    Circle outer_3_top = {85,77.5,20,20};

    glBegin(GL_TRIANGLE_STRIP); 
	glColor3f(RandomColor(),RandomColor(),RandomColor());       
	for(float i =M_PI*-0.6;i<=M_PI*0.8;i+=0.001) // radians
	{
        if(flag==0)
        {
            glVertex2f(outer_3_top.x +outer_3_top.rx*cos(i),outer_3_top.y+outer_3_top.ry*sin(i)); // x+r*cosA,y+r*sinA
            flag = 1;
        }
        else
        {
            glVertex2f(inner_3_top.x +inner_3_top.rx*cos(i),inner_3_top.y+inner_3_top.ry*sin(i)); // x+r*cosA,y+r*sinA
			flag=0;
        }
	}
	glEnd();


    Circle inner_3_bottom = {85,44,15,15};
    Circle outer_3_bottom = {85,44,20,20};

    glBegin(GL_TRIANGLE_STRIP); 
	for(float i =M_PI*-0.85;i<=M_PI*0.4;i+=0.001) // radians
	{
        if(flag==0)
        {
            glVertex2f(outer_3_bottom.x +outer_3_bottom.rx*cos(i),outer_3_bottom.y+outer_3_bottom.ry*sin(i)); // x+r*cosA,y+r*sinA
            flag = 1;
        }
        else
        {
            glVertex2f(inner_3_bottom.x +inner_3_bottom.rx*cos(i),inner_3_bottom.y+inner_3_bottom.ry*sin(i)); // x+r*cosA,y+r*sinA
			flag=0;
        }
	}
	glEnd();

// 9

    Circle inner_9 = {145,77.5,15,15};
    Circle outer_9 = {145,77.5,20,20};

    glBegin(GL_TRIANGLE_STRIP); 
	for(float i =M_PI*0;i<=M_PI*2.1;i+=0.001) // radians
	{
        if(flag==0)
        {
            glVertex2f(outer_9.x +outer_9.rx*cos(i),outer_9.y+outer_9.ry*sin(i)); // x+r*cosA,y+r*sinA
            flag = 1;
        }
        else
        {
            glVertex2f(inner_9.x +inner_9.rx*cos(i),inner_9.y+inner_9.ry*sin(i)); // x+r*cosA,y+r*sinA
			flag=0;
        }
	}
	glEnd();
/*
    Circle inner_9_bottom = {151,59.5,15,35};
    Circle outer_9_bottom = {151,59.5,20,39};

    glBegin(GL_TRIANGLE_STRIP); 
	for(float i =M_PI*-0.7;i<=M_PI*0.14;i+=0.001) // radians
	{
        if(flag==0)
        {
            glVertex2f(outer_9_bottom.x +outer_9_bottom.rx*cos(i),outer_9_bottom.y+outer_9_bottom.ry*sin(i)); // x+r*cosA,y+r*sinA
            flag = 1;
        }
        else
        {
            glVertex2f(inner_9_bottom.x +inner_9_bottom.rx*cos(i),inner_9_bottom.y+inner_9_bottom.ry*sin(i)); // x+r*cosA,y+r*sinA
			flag=0;
        }
	}
	glEnd();
*/
    glBegin(GL_POLYGON);
    glVertex2f(160,77.5);
    glVertex2f(165,77.5);
    glVertex2f(165,24.5);
    glVertex2f(160,24.5);
    glEnd();

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
    
    glutCreateWindow("CED18I039_ICG"); 
    myinit();
    glutDisplayFunc(ICG);
    
    glutCreateWindow("CED18I039_rollno"); 
    myinit();
    glutDisplayFunc(rollno);

    glutReshapeFunc(changeViewPort);
    GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glutMainLoop();
    return 0;
}