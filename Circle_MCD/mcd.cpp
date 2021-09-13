//g++ mcd.cpp -lGL -lGLU -lglut -lGLEW -o mcd

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

struct circle
{
    float c[2];
    float r;
};
void plot(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(round(x), round(y));
    glEnd();
}

void illuminateAllOctants(float c[2], float x, float y)
{
    plot(c[0] + y, c[1] + x);  //Q1
    plot(c[0] + x, c[1] + y);  //Q2
    plot(c[0] + -x, c[1] + y); //Q3
    plot(c[0] + -y, c[1] + x); //Q4

    plot(c[0] + -y, c[1] - x); //Q5
    plot(c[0] + -x, c[1] - y); //Q6
    plot(c[0] + x, c[1] - y);  //Q7
    plot(c[0] + y, c[1] - x);  //Q8
}

void mcd(circle cir)
{
    float x = 0;
    float y = cir.r;

    float p = 1 - cir.r;

    int x_limit = cir.r / sqrt(2);

    for (int i = 0; i < x_limit; i++)
    {
        glColor3f(1, 1, 1);
        glPointSize(5);
        illuminateAllOctants(cir.c, x, y);
        if (p < 0) //y does not change
            p += 2 * x + 3;
        else //y decrement
        {
            p += 2 * x - 2 * y + 5;
            y--;
        }
        x++;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    circle cir = {{500, 500}, 200};
    mcd(cir);
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
    glutInitWindowPosition(800, 100);
    glutInitWindowSize(1000, 1000);

    glutCreateWindow("Hexagon - Lab 5 - CED18I056");
    myinit();
    glutDisplayFunc(display);
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
