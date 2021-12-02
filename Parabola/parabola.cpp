// Author : Paleti Krishnasai - CED18I039
// g++ parabola.cpp -o parabola -lGL -lGLU -lglut -lGLEW
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

int Mode;
float focus;

void changeViewPort(int w, int h)
{
    if (w >= h)
        glViewport(w / 2 - h / 2, 0, h, h);
    else
        glViewport(0, h / 2 - w / 2, w, w);
}

void myinit(void)
{
	glClearColor(0.8,0.8,0.8,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0,1000.0,0.0,1000.0);
	glMatrixMode(GL_MODELVIEW);
}

float RandomColor() 
{
    float color=(float)((rand() % 100))/99;
    return color;    
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

void PlotQuandrants(float c[2], float x, float y, int q[4])
{
    if (q[0] == 1)
        plot(c[0] + x, c[1] + y); //Q1
    if (q[1] == 1)
        plot(c[0] - x, c[1] + y); //Q2
    if (q[2] == 1)
        plot(c[0] - x, c[1] - y); //Q3
    if (q[3] == 1)
        plot(c[0] + x, c[1] - y); //Q4
}

void PlotParabola(Parabola P, int x, int y)
{
    int quads[4] = {0};
    if (Mode == 1) //y2=4ax
    {

        if (P.a > 0)
            quads[0] = quads[3] = 1;
        else
            quads[1] = quads[2] = 1;
        PlotQuandrants(P.c, x, y, quads);
    }

    else //x2=4ay
    {
        if (P.a > 0)
            quads[0] = quads[1] = 1;
        else
            quads[2] = quads[3] = 1;
        PlotQuandrants(P.c, y, x, quads);
    }
}

void MPD(Parabola P)
{
    float a = abs(P.a);
    float x = 0;
    float y = 0;

    float p = 1 - 2 * a;
    float ymid = 2 * a;
    while (y <= ymid)
    {

        PlotParabola(P, x, y);

        if (p < 0)
        {

            p += 2 * y + 3;
        }
        else
        {
            x++;
            p += 2 * y + 3 - 4 * a;
        }
        y++;
    }

    while (x < 2000)
    {

        PlotParabola(P, x, y);
        if (p > 0)
        {
            p += -4 * a;
        }
        else
        {

            p += -4 * a + 2 * y + 2;
            y++;
        }

        x++;
    }
}



void BRUTE(Parabola P)
{
    float a = abs(P.a);
    float x = 0;
    float y = 0;

    while (y < 2000)
    {
        y = 2 * sqrt(a * x);
        int quads[4] = {0};
        PlotParabola(P, x, y);
        x++;
    }
}
void PARAMETRIC(Parabola P)
{
    float a = abs(P.a);
    float x = 0;
    float y = 0;
    float t = 0;
    while (y < 2000)
    {
        x = a * t * t;
        y = 2 * a * t;
        PlotParabola(P, x, y);
        t += 0.001;
    }
}

void MPD_plot()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(3);
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    Parabola P = {{(400+rand()%200), (400+rand()%200)}, focus};
    MPD(P);
    glutSwapBuffers();
}

void BRUTE_plot()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(3);
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    Parabola P = {{(400+rand()%200), (400+rand()%200)}, focus};
    BRUTE(P);
    glutSwapBuffers();
}

void PARA_plot()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(3);
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    Parabola P = {{(400+rand()%200), (400+rand()%200)}, focus};
    PARAMETRIC(P);
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
    focus = -50 ;
    Mode = rand() % 2;
  //  cout<<"enter vertical"<<endl;
   // cin>>vertical_axis;

    glutCreateWindow("CED18I039_parabola_MPD");
    glutInitWindowPosition(200, 200);
    myinit();
    glutDisplayFunc(MPD_plot);

    glutCreateWindow("CED18I039_parabola_parametric");
    glutInitWindowPosition(2000, 1500);
    myinit();
    glutDisplayFunc(PARA_plot);

    glutCreateWindow("CED18I039_parabola_brute");
    glutInitWindowPosition(2800, 800);
    myinit();
    glutDisplayFunc(BRUTE_plot);

    glutReshapeFunc(changeViewPort);
    glutMainLoop();
}