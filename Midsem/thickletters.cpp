//g++ CED18I056.cpp -lGL -lGLU -lglut -lGLEW -o mid
/*----------------------------------------------------------------

Name: Darshan Vss

Letters : D A R S 

BLD, and general Ellipse 


Since it is general ellipse, we miss some points at 2 ends of an ellipse as we get only 1 point of x (in this algorithm)
whereas a true ellipse has more than 1 point since y is decrementing(in this algorithm)
----------------------------------------------------------------*/
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

int drawMode = 0;

int thickness = 25; //global Thickness for all letters

float DDA_MSE_TOTAL = 0;
float BLD_MSE_TOTAL = 0;

void changeViewPort(int w, int h) //viewport will always be a square at center
{
    if (w >= h)
        glViewport(w / 2 - h / 2, 0, h, h);
    else
        glViewport(0, h / 2 - w / 2, w, w);
}

void myinit(void)
{
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void plot(float x, float y) //plotting points function
{
    glBegin(GL_POINTS);
    glVertex2f(round(x), round(y));
    glEnd();
}

float randColor() //to randomize letter color
{
    float r = (float)((rand() % 1000)) / 999;
    return r;
}

struct ellipse
{
    float c[2];
    float a, b;
};

void BLD(float p1[2], float p2[2])
{
    float BLD_MSE = 0;
    float x1 = p1[0], y1 = p1[1];
    float x2 = p2[0], y2 = p2[1];
    float dx = x2 - x1;
    float dy = y2 - y1;
    float m = dy / dx;
    float dist, inX, inY;
    int x, y;

    int p;

    if (abs(dy) < abs(dx)) //if m < 1 x increments more than y
    {
        p = 2 * abs(dy) - abs(dx); //initial decision parameter
        for (int i = 0; i < abs(dx); i++)
        {
            x = round(x1);
            y = round(y1);
            plot(x, y);

            if (p > 0)
            {
                p += (2 * abs(dy) - 2 * abs(dx));
                y1 += dy / abs(dy); //value/absolute value gives us the sign/direction to travel
            }
            else
            {
                p += (2 * abs(dy));
            }
            x1 += dx / (abs(dx)); //value/absolute value gives us the sign/direction to travel
        }
    }
    else // y increments more than x
    {
        p = 2 * abs(dx) - abs(dy); //initial decision parameter
        for (int i = 0; i < abs(dy); i++)
        {
            x = round(x1);
            y = round(y1);
            plot(x, y);

            if (p > 0)
            {
                p += (2 * abs(dx) - 2 * abs(dy));
                x1 += dx / abs(dx); //value/absolute value gives us the sign/direction to travel
            }
            else
            {
                p += (2 * abs(dx));
            }
            y1 += dy / (abs(dy)); //value/absolute value gives us the sign/direction to travel
        }
    }
}

void illuminateQ(float c[2], float x, float y, int q1, int q2, int q3, int q4) //illuminates individual quadrants seperately
{
    if (q1 == 1)
        plot(c[0] + x, c[1] + y); //Q1
    if (q2 == 1)
        plot(c[0] - x, c[1] + y); //Q2
    if (q3 == 1)
        plot(c[0] - x, c[1] - y); //Q3
    if (q4 == 1)
        plot(c[0] + x, c[1] - y); //Q4
}
void generalEllipseDrawing(ellipse ell, int q1, int q2, int q3, int q4)
{
    float a = ell.a, b = ell.b;
    float x = 0;
    float y = b;
    float a2 = a * a, b2 = b * b;

    while (y >= 0) //getting points in quadrant 1
    {
        illuminateQ(ell.c, x, y, q1, q2, q3, q4);
        x++;
        y = sqrt((a2 - x * x) * b2 / a2); //brute force algorithm for ellipse
    }
}

void letters()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(3);

    //________________letter D_______________________
    glColor3f(randColor(), randColor(), randColor());

    //vertical part
    for (float i = 0; i < thickness; i++) //drawing multible times to give thickness in every letter
    {
        float top[2] = {100 + i, 600};
        float bottom[2] = {100 + i, 400};
        BLD(top, bottom);
    }
    //curve part
    for (float i = thickness; i > 0; i--)
    {
        ellipse ellD = {{100, 500}, 130 - i, 100 - i};
        generalEllipseDrawing(ellD, 1, 0, 0, 1); //illuminating q1 and q4
    }
    //________________letter A_______________________
    glColor3f(randColor(), randColor(), randColor());
    //left slant
    for (float i = 0; i < thickness; i++)
    {
        float top[2] = {350 + i, 600};
        float bottom[2] = {275 + i, 400};
        BLD(top, bottom);
    }
    //right slant
    for (float i = 0; i < thickness; i++)
    {
        float top[2] = {350 + thickness - i, 600};
        float bottom[2] = {425 + thickness - i, 400};
        BLD(top, bottom);
    }
    //horizontal parameter
    for (float i = 0; i < thickness; i++)
    {
        float left[2] = {320, 480 + i};
        float right[2] = {400, 480 + i};
        BLD(left, right);
    }

    //________________letter R __________________________
    glColor3f(randColor(), randColor(), randColor());
    //vertical part
    for (float i = 0; i < thickness; i++)
    {
        float top[2] = {500 + i, 600};
        float bottom[2] = {500 + i, 400};
        BLD(top, bottom);
    }
    //slant part
    for (float i = 0; i < thickness; i++)
    {
        float top[2] = {500 + i, 500};
        float bottom[2] = {600 + i, 400};
        BLD(top, bottom);
    }
    //curve part
    for (float i = thickness; i > 0; i--)
    {
        ellipse ellD = {{500, 550}, 130 - i, 60 - i};
        generalEllipseDrawing(ellD, 1, 0, 0, 1); //illuminating q1 and q4
    }

    //________________letter S __________________________
    glColor3f(randColor(), randColor(), randColor());
    //upper curve
    for (float i = thickness; i > 0; i--)
    {
        ellipse ellD = {{800, 550}, 90 - i, 60 - i};
        generalEllipseDrawing(ellD, 1, 1, 1, 0); //illuminating q1,q2 and q3
    }
    //lower curve
    for (float i = thickness; i > 0; i--)
    {
        ellipse ellD = {{800, 450}, 90 - i, 65 - i};
        generalEllipseDrawing(ellD, 1, 0, 1, 1); //illuminating q1,q3 and q4
    }

    glutSwapBuffers();
}

void select();
void keyboard(unsigned char key, int x, int y);
void timer(int)
{
    glutTimerFunc(1000, timer, 0); // 1 frame every 1000 ms OR 1 sec
    glutPostRedisplay();           //goes through randomizing colorsd each time
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(800, 100);
    glutInitWindowSize(800, 800);

    glutCreateWindow("Hexagon - Lab 5 - CED18I056");
    myinit();
    glutDisplayFunc(letters);
    glutReshapeFunc(changeViewPort);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}
