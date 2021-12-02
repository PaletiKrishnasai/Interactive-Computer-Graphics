#include <GL/freeglut.h> 
#include <bits/stdc++.h> 

using namespace std;
#define LENGTH 600
#define HEIGHT 500

float DDA_MSE_TOTAL = 0;
float BLD_MSE_TOTAL = 0;

void MPD_1(int xc, int yc, int a, int c, int xl, int yl)
{
    glPointSize(1.5);
    glColor3f(0, 0, 0);
   int k=-1;
   //REGION 1
   int p = 1-2*a;
   int x=0,y=0;
   cout << "REGION 1: " << endl;
   cout << "k : -1  pk: null    (xk+1,yk+1) : (0,0)      pk+1 : " << p << endl;
   while(y<2*a && y < yl)
   {
       glBegin(GL_POINTS);
            glVertex2f(x+xc,y+yc);
        glEnd();
        glBegin(GL_POINTS);
            glVertex2f(x+xc,-y+yc);
        glEnd();
       cout << "k : " << k++ << "    pk : " << p;
       y++;
       if(p<0)
       {
           p = p + 2*y + 1;
       }
       else
       {
           p = p + 2*y + 1 - 4*a;
           x += c;
       }
       cout << "    (xk+1,yk+1) : (" << x << ", " << y << ")    pk+1 : " << p << endl; 
   } 


   //REGION 2
   cout << "REGION 2: " << endl;
   p = round((1/4.0)-2*a);
//    x=a;
//    y=2*a;
   cout << "k : -1  pk: null    (xk+1,yk+1) : (" << x << ", " << y << ")      pk+1 : " << p << endl;
   while(abs(x)<abs(xl))
   {
       glBegin(GL_POINTS);
            glVertex2f(x+xc,y+yc);
        glEnd();
        glBegin(GL_POINTS);
            glVertex2f(x+xc,-y+yc);
        glEnd();
       cout << "k : " << k++ << "    pk : " << p;
       x += c;
       if(p<0)
       {
           y++;
           p = p + 2*y - 4*a;
       }
       else
       {
           p = p - 4*a;
       }
       cout << "    (xk+1,yk+1) : (" << x << ", " << y << ")    pk+1 : " << p << endl; 
   } 

}

void MPD_2(int xc, int yc, int a, int c, int xl, int yl)
{
    glPointSize(1.5);
    glColor3f(0, 0, 0);
   int k=-1;
   //REGION 1
   int p = 1-2*a;
   int x=0,y=0;
   cout << "REGION 1: " << endl;
   cout << "k : -1  pk: null    (xk+1,yk+1) : (0,0)      pk+1 : " << p << endl;
   while(x<2*a && x < xl)
   {
       glBegin(GL_POINTS);
            glVertex2f(x+xc,y+yc);
        glEnd();
        glBegin(GL_POINTS);
            glVertex2f(-x+xc,y+yc);
        glEnd();
       cout << "k : " << k++ << "    pk : " << p;
       x++;
       if(p<0)
       {
           p = p + 2*x + 1;
       }
       else
       {
           p = p + 2*x + 1 - 4*a;
           y += c;
       }
       cout << "    (xk+1,yk+1) : (" << x << ", " << y << ")    pk+1 : " << p << endl; 
   } 


   //REGION 2
   cout << "REGION 2: " << endl;
   p = round((1/4.0)-2*a);
//    x=a;
//    y=2*a;
   cout << "k : -1  pk: null    (xk+1,yk+1) : (" << x << ", " << y << ")      pk+1 : " << p << endl;
   while(abs(y)<abs(yl))
   {
       glBegin(GL_POINTS);
            glVertex2f(x+xc,y+yc);
        glEnd();
        glBegin(GL_POINTS);
            glVertex2f(-x+xc,y+yc);
        glEnd();
       cout << "k : " << k++ << "    pk : " << p;
       y += c;
       if(p<0)
       {
           x++;
           p = p + 2*x - 4*a;
       }
       else
       {
           p = p - 4*a;
       }
       cout << "    (xk+1,yk+1) : (" << x << ", " << y << ")    pk+1 : " << p << endl; 
   } 

}

void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

void window_color()
{

	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

}


void draw_line()
{
	window_color();
    MPD_1(0,0,1,1,9,6);
   // MPD_1(300,300,10,-1,-190,160);
    //MPD_2(300,300,10,1,160,190);
    //MPD_2(300,300,10,-1,160,-190);
	
	glFlush();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(LENGTH, HEIGHT);
	glutCreateWindow("ICG"); 
	glutReshapeFunc(changeViewPort);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, LENGTH, 0.0, HEIGHT);
	glutDisplayFunc(draw_line);
	glutMainLoop();
}