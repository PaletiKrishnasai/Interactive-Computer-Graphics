// Author : Paleti Krishnasai - CED18I039
// g++ transforms.cpp -o transforms -lGL -lGLU -lglut -lGLEW
#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <time.h>
using namespace std;

vector<int> pntX;
vector<int> pntY;
int transX, transY;
double scaleX, scaleY;
double angle, angleRad;
char reflectionAxis, shearingAxis;
int shearingX, shearingY;
int choice = 0;
int mouse_x,mouse_y;


void changeViewPort(int w, int h)
{
	if (w >= h)
		glViewport(w / 2 - h / 2, 0, h, h);
	else
		glViewport(0, h / 2 - w / 2, w, w);
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        pntX.push_back(mouse_x);
        pntY.push_back(mouse_y);
        printf("Polygon Point: %d , %d\n", mouse_x, mouse_y);
        
    }
}
// mouse motion callback
void motion(int x, int y)
{
    mouse_x = (-800) + 2 * x;
    mouse_y = (-800) + 2 * (800 - y);
    glutPostRedisplay();
}

void Pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

float RandomColor()
{
	float color = (float)((rand() % 100)) / 99;
	return color;
}

double round(double d)
{
	return floor(d + 0.5);
}

void drawPolygon()
{
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3.5);
    for(int i=0;i<pntX.size();i++)
    Pixel(pntX[i],pntY[i]);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < pntX.size(); i++)
	{
		glVertex2i(pntX[i], pntY[i]);
	}
	glEnd();
}

void drawPolygonTrans(int x, int y)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i < pntX.size(); i++)
	{
		glVertex2i(pntX[i] + x, pntY[i] + y);
	}
	glEnd();
}

void drawPolygonScale(double x, double y)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < pntX.size(); i++)
	{
		glVertex2i(round(pntX[i] * x), round(pntY[i] * y));
	}
	glEnd();
}

void drawPolygonRotation(double angleRad)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < pntX.size(); i++)
	{
		glVertex2i(round((pntX[i] * cos(angleRad)) - (pntY[i] * sin(angleRad))), round((pntX[i] * sin(angleRad)) + (pntY[i] * cos(angleRad))));
	}
	glEnd();
}


void drawPolygonMirrorReflection(char reflectionAxis)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);

	if (reflectionAxis == 'x' || reflectionAxis == 'X')
	{
		for (int i = 0; i < pntX.size(); i++)
		{
			glVertex2i(round(pntX[i]), round(pntY[i] * -1));

		}
	}
	else if (reflectionAxis == 'y' || reflectionAxis == 'Y')
	{
		for (int i = 0; i < pntX.size(); i++)
		{
			glVertex2i(round(pntX[i] * -1), round(pntY[i]));
		}
	}
	else if (reflectionAxis == 'm' || reflectionAxis == 'M')
	{
		for (int i = 0; i < pntX.size(); i++)
		{
			glVertex2i(round(pntY[i]), round(pntX[i]));
		}
	}
	else if (reflectionAxis == 'n' || reflectionAxis == 'N')
	{
		for (int i = 0; i < pntX.size(); i++)
		{
			glVertex2i(round(pntY[i] * -1), round(pntX[i] * -1));
		}
	}
	glEnd();
}

void drawPolygonShearing()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);

	if (shearingAxis == 'x' || shearingAxis == 'X')
	{
		for (int i = 0; i < pntX.size(); i++)
		{
			glVertex2i(pntX[i]+(shearingX * pntY[i]),+pntY[i]);
		}
	}
	else if (shearingAxis == 'y' || shearingAxis == 'Y')
	{
		for (int i = 0; i < pntX.size(); i++)
		{
			glVertex2i(pntX[i],(shearingY * pntX[i])+pntY[i]);
		}
	}
	glEnd();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(0, -800);
        glVertex2f(0, 800);
        glVertex2f(-800, 0);
        glVertex2f(800,0);
    glEnd();
    Pixel(mouse_x,mouse_y);
	if (choice == 1)
	{
		drawPolygon();
		drawPolygonTrans(transX, transY);
	}
	else if (choice == 2)
	{
		drawPolygon();
		drawPolygonScale(scaleX, scaleY);
	}
	else if (choice == 3)
	{
		drawPolygon();
		drawPolygonRotation(angleRad);
	}
	else if (choice == 4)
	{
		drawPolygon();
		drawPolygonMirrorReflection(reflectionAxis);
	}
	else if (choice == 5)
	{
		drawPolygon();
		drawPolygonShearing();
	}

	glutSwapBuffers();
}



void myinit(void)
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-800.0, 800.0, -800.0, 800.0);
    glMatrixMode(GL_MODELVIEW);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    
}

int main(int argc, char **argv)
{
	srand(time(0));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
    cout << "Enter your choice:\n\n" << endl;

	cout << "1. Translation" << endl;
	cout << "2. Scaling" << endl;
	cout << "3. Rotation" << endl;
	cout << "4. Mirror Reflection" << endl;
	cout << "5. Shearing" << endl;
	cout << "6. Exit" << endl;

	cin >> choice;

	if (choice == 6) {
		return 0;
	}

    if (choice == 1)
	{
		cout << "Enter the translation factor for X and Y: "; cin >> transX >> transY;
	}
	else if (choice == 2)
	{
		cout << "Enter the scaling factor for X and Y: "; cin >> scaleX >> scaleY;
	}
	else if (choice == 3)
	{
		cout << "Enter the angle for rotation: "; cin >> angle;
		angleRad = angle * 3.1416 / 180;
	}
	else if (choice == 4)
	{
		cout << "Enter reflection axis ( x or y  or m for x=y or n for -x=y ): "; cin >> reflectionAxis;
	}
	else if (choice == 5)
	{
		cout << "Enter shearing axis ( x or y ): "; cin >> shearingAxis;
		if (shearingAxis == 'x' || shearingAxis == 'X')
		{
			cout << "Enter the shearing factor for X: "; cin >> shearingX;
		}
		else if (shearingAxis == 'y' || shearingAxis == 'Y')
		{
			cout << "Enter the shearing factor for Y: "; cin >> shearingY;
		}
	
	}
    
    glutInitWindowSize(800, 800);
	glutInitWindowPosition(200, 200);
    glutCreateWindow("CED18I039");
	myinit();
	glutDisplayFunc(Display);


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