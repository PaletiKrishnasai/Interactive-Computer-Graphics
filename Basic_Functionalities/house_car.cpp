// Author : Paleti Krishnasai - CED18I039

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
using namespace std;

void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

void myinit(void)
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0,100.0,0.0,100.0);
}

void House()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // sqaure
    glBegin(GL_POLYGON);
    glColor4f(0, 0.7, 1, 1);
        glVertex2f(20, 10);
        glVertex2f(60, 10);
        glVertex2f(60, 50);
        glVertex2f(20,50);
    glEnd();
    
    //Door
    glBegin(GL_POLYGON);
    glColor4f(1, 1, 1, 1);
        glVertex2f(35, 10);
        glVertex2f(45, 10);
        glVertex2f(45, 30);
        glVertex2f(35,30);
    glEnd();

    // left window
    glBegin(GL_POLYGON);
    glColor4f(1, 1, 1, 1);
        glVertex2f(25, 25);
        glVertex2f(30, 25);
        glVertex2f(30, 30);
        glVertex2f(25,30);
    glEnd();

    // right window
    glBegin(GL_POLYGON);
    glColor4f(1, 1, 1, 1);
        glVertex2f(50, 25);
        glVertex2f(55, 25);
        glVertex2f(55, 30);
        glVertex2f(50,30);
    glEnd();

    // Roof Triangle
    glBegin(GL_POLYGON);
    glColor4f(1,0.2 ,0.2 , 1);
        
        glVertex2f(20,50);
        glVertex2f(60, 50);
        glVertex2f(40,80);
    glEnd();

    // Outlines
    //square
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,0);
        glVertex2f(20, 10);
        glVertex2f(60, 10);
        glVertex2f(60, 50);
        glVertex2f(20,50);
    glEnd();
   
    //door
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,0);
        glVertex2f(35, 10);
        glVertex2f(45, 10);
        glVertex2f(45, 30);
        glVertex2f(35,30);
    glEnd();

     // left window
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,0);
        glVertex2f(25, 25);
        glVertex2f(30, 25);
        glVertex2f(30, 30);
        glVertex2f(25,30);
    glEnd();

    // right window
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,0);
        glVertex2f(50, 25);
        glVertex2f(55, 25);
        glVertex2f(55, 30);
        glVertex2f(50,30);
    glEnd();

    // Roof Triangle
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,0); 
        glVertex2f(20,50);
        glVertex2f(60, 50);
        glVertex2f(40,80);
    glEnd();

    glFlush();
    glutSwapBuffers();
}


void Car()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(4);
    
    // chassis
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,1);
        glVertex2f(10,20);
        glVertex2f(90,20);
        glVertex2f(90,40);
        glVertex2f(10,40);
    glEnd();
    
    // car roof
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,1);
        glVertex2f(30,40);
        glVertex2f(90,40);
        glVertex2f(80,65);
        glVertex2f(45,65);
    glEnd();
    
    // front window
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,1);
        glVertex2f(32,41);
        glVertex2f(58,41);
        glVertex2f(58,64);
        glVertex2f(46,64);
    glEnd();

    // back window
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,1);
        glVertex2f(61,41);
        glVertex2f(88,41);
        glVertex2f(79,64);
        glVertex2f(61,64);
    glEnd();
    
    // front wheel outline
    glBegin(GL_POLYGON); 
	glColor3f(0,0,0);       
	for(float i =0;i<=3600/3.14;i++) // radians
	{
		glVertex2f(30 +8.5*cos(i),20 +8.5*sin(i)); // x+r*cosA,y+r*sinA
	}
	glEnd();
	
    // front wheel grey
	glBegin(GL_POLYGON); 
		glColor3f(0.7,0.7,0.7); 
        
		for(float i =0;i<=3600/3.14;i++) // radians
		{
			glVertex2f(30 +8*cos(i),20 +8*sin(i)); // x+r*cosA,y+r*sinA
		}
	glEnd();

    // back wheel outline
    glBegin(GL_POLYGON); 
	glColor3f(0,0,0);       
	for(float i =0;i<=3600/3.14;i++) // radians
	{
		glVertex2f(75 +8.5*cos(i),20 +8.5*sin(i)); // x+r*cosA,y+r*sinA
	}
	glEnd();
	
    // back wheel grey
	glBegin(GL_POLYGON); 
		glColor3f(0.7,0.7,0.7); 
        
		for(float i =0;i<=3600/3.14;i++) // radians
		{
			glVertex2f(75 +8*cos(i),20 +8*sin(i)); // x+r*cosA,y+r*sinA
		}
	glEnd();


    glFlush();
    glutSwapBuffers();
}

//driver code
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 200);
    
    glutCreateWindow("house"); 
    myinit();
    glutDisplayFunc(House);
    
    glutCreateWindow("car"); 
    myinit();
    glutDisplayFunc(Car);

    glutReshapeFunc(changeViewPort);
    GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glutMainLoop();
    return 0;
}