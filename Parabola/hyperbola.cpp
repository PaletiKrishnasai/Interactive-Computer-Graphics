// Author : Paleti Krishnasai - CED18I039
// g++ hyperbola.cpp -o hyperbola -lGL -lGLU -lglut -lGLEW
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

int Mode;
float focusa,focusb;

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

struct Hyperbola
{
    float c[2];
    float a, b;
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
void PlotHyperbola(Hyperbola H, int x, int y)
{
    int quads[4] = {1, 1, 1, 1};
    if (Mode == 1) //x2-y2
        PlotQuandrants(H.c, x, y, quads);

    else //y2-x2
        PlotQuandrants(H.c, y, x, quads);
}

void BRUTE(Hyperbola H)
{
    float a = abs(H.a), b = abs(H.b);
    float x = a;
    float y = 0;
    float a2 = a * a, b2 = b * b;

    while (x < 2000)
    {
        PlotHyperbola(H, x, y);
        x++;
        y = sqrt((x * x - a2) * b2 / a2);
    }
}
void PARAMETRIC(Hyperbola H)
{
    float a = abs(H.a), b = abs(H.b);
    float x, y;

    for (float i = 0; y < 2000; i += 0.001)
    {
        x = a / cos(i); //x=a secA
        y = b * tan(i);
        PlotHyperbola(H, x, y);
    }
}

void MHD(Hyperbola H)
{
    float a = abs(H.a), b = abs(H.b);
    float x = a;
    float y = 0;
    float a2 = a * a, b2 = b * b;

    float ymid;
    if (b < a)
        ymid = b2 / sqrt(a2 - b2);
    else
        ymid = 2000;

    float p = b2 * a - a2;

    while (y < ymid)
    {
        PlotHyperbola(H, x, y);
        if (p < 0)
        {
            x++;
            p += -a2 * (2 * y + 3) + 2 * b2 * (x + 1);
        }
        else
        {

            p += -a2 * (2 * y + 3);
        }
        y++;
    }
    while (x < 2000)
    {
        PlotHyperbola(H, x, y);
        if (p < 0)
        {

            p += b2 * (2 * x + 3);
        }
        else
        {
            y++;
            p += b2 * (2 * x + 3) - 2 * a2 * (y + 1);
        }
        x++;
    }
}

void BRUTE_plot()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Hyperbola H = {{(400+rand()%200), (400+rand()%200)}, focusa, focusb};
    glPointSize(3);
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    BRUTE(H);
    glutSwapBuffers();
}

void PARAMETRIC_plot()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Hyperbola H = {{(400+rand()%200), (400+rand()%200)}, focusa, focusb};
    glPointSize(3);
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    PARAMETRIC(H);
    glutSwapBuffers();
}

void MHD_plot()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Hyperbola H = {{(400+rand()%200), (400+rand()%200)}, focusa, focusb};
    glPointSize(3);
    glColor3f(RandomColor(), RandomColor(), RandomColor());
    MHD(H);
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    //glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
  
    focusa = -100 + rand()%300;
    focusb = -100 + rand()%300;

    Mode = rand() % 2;

    glutCreateWindow("CED18I039_Hyperbola_MHD");
    glutInitWindowPosition(200, 200);
    myinit();
    glutDisplayFunc(MHD_plot);

    glutCreateWindow("CED18I039_Hyperbola_parametric");
    glutInitWindowPosition(2000, 1500);
    myinit();
    glutDisplayFunc(PARAMETRIC_plot);

    glutCreateWindow("CED18I039_Hyperbola_brute");
    glutInitWindowPosition(2800, 800);
    myinit();
    glutDisplayFunc(BRUTE_plot);

    glutReshapeFunc(changeViewPort);
    glutMainLoop();
}