//g++ mpd.cpp -lGL -lGLU -lglut -lGLEW -o mpd

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

int drawMode = 0;

float DDA_MSE_TOTAL = 0;
float BLD_MSE_TOTAL = 0;

void changeViewPort(int w, int h)
{
    if (w >= h)
        glViewport(w / 2 - h / 2, 0, h, h);
    else
        glViewport(0, h / 2 - w / 2, w, w);
}

void myinit(void)
{
    glClearColor(0.1, 0.11, 0.12, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
}

struct Parabola
{
    float c[2];
    float a;
};
void plot(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(round(x), round(y));
    glEnd();
}

void illuminate2Q(float c[2], float x, float y)
{
    //plot(c[0] + x, c[1] + y); //Q1
    cout<<c[0] + x<<" "<<c[1] + y<<endl;
    //plot(c[0] - x, c[1] + y); //Q2
    //plot(c[0] - x, c[1] - y); //Q3
    //plot(c[0] + x, c[1] - y); //Q4
}

void med(Parabola P)
{
    float a = P.a;
    float x = 0;
    float y = 0;

    float p = 1 - 2 * a;

    float ymid = 2 * a;

    for (int i = 0; y <= ymid; i++) //wider part of Parabola where we iterate x
    {	
    	cout<<p<<endl;
        illuminate2Q(P.c, x, y);
        if (p < 0) //y does not change
        {

            p += 2 * y + 3;
            
        }
        else //y decrement
        {
            x++;
            p += 2 * y + 3 - 4 * a;
        }
        y++;
    }

    for (int i = 0; x <= 10; i++)
    {
	cout<<p<<endl;
        illuminate2Q(P.c, x, y);
        if (p > 0)
        {
            p += -4 * a; //pk for vertical part
        }
        else
        {

            p += -4 * a + 2 * y + 2;
            y++;
        }

        x++;
    }
}

void drawParabola()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Parabola P = {{0, 0}, 1};
    med(P);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y);
void timer(int)
{
    glutTimerFunc(33, timer, 0);
    //glutKeyboardFunc(keyboard);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(1000, 100);
    glutInitWindowSize(800, 800);

    glutCreateWindow("Parabola - Lab 6 - CED18I056");
    myinit();
    glutDisplayFunc(drawParabola);
    glutReshapeFunc(changeViewPort);
    //glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        break;
    }
    glutPostRedisplay();
}
