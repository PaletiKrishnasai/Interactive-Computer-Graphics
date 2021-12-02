// g++ lab12-ced18i056.cpp -lGL -lGLU -lglut -lGLEW -o lab12

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

//Global variables_______________

int fps = 1000;
int randomizeAllValues = -1;

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
float randColor()
{
    float r = (float)((rand() % 1000)) / 999;
    return r;
}

void plot(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(round(x), round(y));
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y);

void timer(int)
{
    glutTimerFunc(fps, timer, 0);
    glutKeyboardFunc(keyboard);

    if (randomizeAllValues == 1)
    {
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(1000, 100);
    glutInitWindowSize(800, 800);

    printf("print in terminal\n");
    glutCreateWindow("window name");
    myinit();
    glutDisplayFunc(display);
    glutReshapeFunc(changeViewPort);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        glutDestroyWindow(glutGetWindow());
        printf("terminal statement\n");
        glutCreateWindow("windowname");
        myinit();
        glutDisplayFunc(display);
        break;
    case '2':

        break;
    case '3':

    case 'r':
        randomizeAllValues *= -1;
        glutPostRedisplay();
        break;

    case 'w':

        break;
    case 's':

        break;
    case 'a':

        break;
    case 'd':

        break;
    }
    glutPostRedisplay();
}
