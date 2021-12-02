// Author : Paleti Krishnasai - CED18I039
// g++ LineClip.cpp -o LineClip -lGL -lGLU -lglut -lGLEW
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

int refPoints = -1;
float xmin = 200+rand()%400, 
      ymin = 200+rand()%400, 
      xmax = 900-rand()%200, 
      ymax = 900-rand()%200;
float ax = 200, ay = 500, bx = 800, by = 500;
const int TOP = 1;
const int BOTTOM = 2;
const int RIGHT = 4;
const int LEFT = 8;

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

void drawClippingWindow()
{   
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();
}

int ComputeOutCode(float x, float y)
{
    int code = 0;
    if (y > ymax) //above the clip window
        code |= TOP;
    else if (y < ymin) //below the clip window
        code |= BOTTOM;
    if (x > xmax) //to the right of clip window
        code |= RIGHT;
    else if (x < xmin) //to the left of clip window
        code |= LEFT;
    return code;
}

void CSA(float x1, float y1, float x2, float y2)
{
    //Outcodes for P0, P1, and whatever point lies outside the clip rectangle
    int outcode0, outcode1, outcodeOut;
    bool accept = false, done = false;
    //compute outcodes
    outcode0 = ComputeOutCode(x1, y1);
    outcode1 = ComputeOutCode(x2, y2);
    do
    {
        if (!(outcode0 | outcode1)) //
        {
            accept = true;

            done = true;
        }
        else if (outcode0 & outcode1) // Trivially reject 
            done = true;
        else
        { //failed both tests, so calculate the line segment to clip from an
            // outside point to an intersection with clip edge
            float x, y;
            //At least one endpoint is outside the clip rectangle; pick it.
            outcodeOut = outcode0 ? outcode0 : outcode1;
            //Now find the intersection point;
            //use formulas y = y1 + slope * (x - x1), x = x1 + (1/slope)* (y - y1)
            if (outcodeOut & TOP) //point is above the clip rectangle
            {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (outcodeOut & BOTTOM) //point is below the clip rectangle
            {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (outcodeOut & RIGHT) //point is to the right of clip rectangl
            {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else //point is to the left of clip rectangle
            {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);

                x = xmin;
            }
            //Now we move outside point to intersection point to clip
            //and gets ready for next pass.
            if (outcodeOut == outcode0)
            {
                x1 = x;
                y1 = y;
                outcode0 = ComputeOutCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                outcode1 = ComputeOutCode(x2, y2);
            }
        }
    } while (!done);
    if (accept)
    {

        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);

        glEnd();
    }
}

void CohenSutherland()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawClippingWindow();
    glPointSize(5);

        ax = rand() % 1000;
        ay = rand() % 1000;
        bx = rand() % 1000;
        by = rand() % 1000;

    if (refPoints == -1)
    {
        //reference points
        glBegin(GL_POINTS);
        glColor3f(0, 0,0 );
        glVertex2f(ax, ay);
        glVertex2f(bx, by);
        glEnd();
        //reference line
        glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex2f(ax, ay);
        glVertex2f(bx, by);
        glEnd();
    }

    CSA(ax, ay, bx, by);

    glutSwapBuffers();
}

void LBA(float x1, float y1, float x2, float y2)
{
    float dx, dy, nx1, ny1, nx2, ny2;
    dx = x2 - x1;
    dy = y2 - y1;
    float p[4] = {-dx, dx, -dy, dy};
    float q[4] = {x1 - xmin, xmax - x1, y1 - ymin, ymax - y1};
    float u, u1, u2;
    vector<float> m1, m2;
    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        if (p[i] == 0 && q[i] < 0)
        {
            //the line is out of bounds
            k = 1;
            break;
        }
    }
    if (k != 1)
    {
        m1.push_back(0);
        m2.push_back(1);
        for (int i = 0; i < 4; i++)
        {
            u = (float)q[i] / (float)p[i];
            if (p[i] < 0)
                m1.push_back(u);
            else if (p[i] > 0)
                m2.push_back(u);
        }
        u1 = *max_element(m1.begin(), m1.end());
        u2 = *min_element(m2.begin(), m2.end());
        if (u1 > u2)
        {
            // The line clipping points lie outside the window
        }
        else
        {
            nx1 = x1 + u1 * dx;
            ny1 = y1 + u1 * dy;

            nx2 = x1 + u2 * dx;
            ny2 = y1 + u2 * dy;

            glColor3f(0, 1, 0);
            glBegin(GL_LINES);
            glVertex2f(nx1, ny1);
            glVertex2f(nx2, ny2);
            glEnd();
        }
    }
}

void LiangBarsky()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawClippingWindow();
    glPointSize(5);
   
    ax = rand() % 1000;
    ay = rand() % 1000;
    bx = rand() % 1000;
    by = rand() % 1000;


    if (refPoints == -1)
    {
        //reference points
        glBegin(GL_POINTS);
        glColor3f(0, 0, 0);
        glVertex2f(ax, ay);
        glVertex2f(bx, by);
        glEnd();
        //reference line
        glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex2f(ax, ay);
        glVertex2f(bx, by);
        glEnd();
    }
    LBA(ax, ay, bx, by);

    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    

	srand(time(0)); // random seeding for random color

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);




	glutInitWindowPosition(500, 500);
	glutCreateWindow("CED18I039_LBA");
	myinit();
	glutDisplayFunc(LiangBarsky);

    glutInitWindowPosition(500, 500);
	glutCreateWindow("CED18I039_CSA");
	myinit();
	glutDisplayFunc(CohenSutherland);

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