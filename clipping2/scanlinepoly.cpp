//CED18I039 + CED18I056
//g++ scanlinepoly.cpp -o scanline -lGL -lGLU -lglut -lGLEW
#include<bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <fstream>


using namespace std;

// Classes.

// Defintion of an edge of our polygon. Contains useful coordinates for the scanline.
class Edges {
public:
    GLint minY;
    GLint maxY;
    GLint minX;
    GLint maxX;
    GLfloat xVal; // X value at the minimum vertex, this is where we start our scanline on the x-axis.
    GLfloat slope;
    // Tuples are (x, y).
    Edges(tuple<GLint, GLint> vertexOne, tuple<GLint, GLint> vertexTwo);
};

// Calculates neccessary values from two vertexes.
Edges::Edges(tuple<GLint, GLint> vertexOne, tuple<GLint, GLint> vertexTwo) {
    this->minY = min(get<1>(vertexOne), get<1>(vertexTwo));
    this->maxY = max(get<1>(vertexOne), get<1>(vertexTwo));
    this->minX = min(get<0>(vertexOne), get<0>(vertexTwo));
    this->maxX = max(get<0>(vertexOne), get<0>(vertexTwo));
    
    
    if (min(get<1>(vertexOne), get<1>(vertexTwo)) == get<1>(vertexOne)) {
        this->xVal = get<0>(vertexOne);
    } else {
        this->xVal = get<0>(vertexTwo);
    }
    
    // Calculates scope, casting for float division.
    this->slope =
    static_cast<GLfloat>(static_cast<GLfloat>(get<1>(vertexOne) - get<1>(vertexTwo)))
    / static_cast<GLfloat>((get<0>(vertexOne) - get<0>(vertexTwo)));
}

// Structs.

// Sort Edges by minY values and, if the same, then sort by minX values.
struct less_than_key
{
    inline bool operator() (const Edges& struct1, const Edges& struct2)
    {
        if (struct1.minY != struct2.minY)
            return (struct1.minY < struct2.minY);
        return (struct1.minX < struct2.minX);
    }
};

// Sorts Edges by current x values.
struct by_x_val_key
{
    inline bool operator() (const Edges& struct1, const Edges& struct2)
    {
        return (struct1.xVal < struct2.xVal);
    }
};

// Stores color data for a single pixel.
struct RGBType {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

// Globals
int X_DOWN;
GLint scanline;
bool TOGGLE_STATE;
bool MOUSE_STATE;
bool DRAWING; // Enables or disables user input.
bool EDGE_PARITY;
vector<tuple<GLint, GLint>> points; // Contains all the vertexes.
vector<Edges> allEdges; // Contains every Edge.
vector<Edges> activeEdges; // Contains Edges currently intersecting the scanline.
RGBType *pixels; // Contains every pixel on the screen.

// Draws pixels from (x1, scanline) to (x2, scanline).
void drawPixels(GLfloat x1, GLfloat x2) {
    // round points, not floor, as we want the x values to change with the scanline.
    int i1 = roundf(x1);
    int i2 = roundf(x2);
    int count = 0;
    
    for (int i = ((500 * (500 - scanline)) + i1); i < ((500 * (500 - scanline)) + i2); i++, count++) {
        pixels[i].r = 0;
        pixels[i].b = 0;
        pixels[i].g = 0;
        glutPostRedisplay();
        printf("change pixel %d, %d\n", (i1 + count), scanline);
    }
    printf("Pixels drawn.\n");
}

// Removes edges from the Active Edges if the maxY of the edge is the same as the scanline.
void removeActiveEdgesByScanline() {
    for (vector<Edges>::iterator it = activeEdges.begin(); it < activeEdges.end(); ) {
        if (it->maxY == scanline) {
            activeEdges.erase(it);
        } else {
            it++;
        }
    }
}

// Updates the x values of the Active Edges for the next scanline.
void updateXValues() {
    for (vector<Edges>::iterator it = activeEdges.begin(); it < activeEdges.end(); it++) {
        it->xVal += (1/it->slope);
    }
}

// Adds new Active Edges from All Edges if the scanline reaches their minimum Y value.
void updateActiveEdges() {
    for (vector<Edges>::iterator it = allEdges.begin(); it < allEdges.end(); it++) {
        if (it->minY == scanline) {
            activeEdges.push_back(*it);
        }
        if (it->minY > scanline) {
            return;
        }
    }
}

// Set scanline value to the smallest Y value
void initScanline() {
    if (allEdges.size() != 0) {
        scanline = allEdges.at(0).minY;
        glutPostRedisplay();
    }
}

// Sort Edges to know which order the scanline hits them.
void sortAndFilterEdges() {
    sort(allEdges.begin(), allEdges.end(), less_than_key());
    for (vector<Edges>::iterator it = allEdges.begin(); it < allEdges.end(); it++) {
        // Don't need to deal with horizontal lines, as that's the direction we're scanning.
        if (it->slope == 0) {
            allEdges.erase(it);
        }
    }
}

void sortActiveEdgesByXValues() {
    sort(activeEdges.begin(), activeEdges.end(), by_x_val_key());
}

// Actually fills the polygon, finds the intersections of the edges and the scanline, draws, and updates
// the Edges.
void fillPolygon() {
    printf("Filling...");
    while (activeEdges.size() != 0) {
        for (vector<Edges>::iterator it = activeEdges.begin(); it < activeEdges.end(); it++) {
            printf("drawing from %f to %f\n", it->xVal, (it+1)->xVal);
            drawPixels(it->xVal, (it+1)->xVal);
            it++;
        }
        scanline++;
        removeActiveEdgesByScanline();
        updateXValues();
        updateActiveEdges();
        sortActiveEdgesByXValues();
        glutPostRedisplay();
    }
}

void init(void) {
    
    //Set background color
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    //Initialize camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500, 500, 0.0, 0.0, 1.0);
    
    //Initialize RGB array
    pixels = new RGBType[500*500];
    
    // Set everything to white initially.
    for (int i = 0; i < 500*500; i++) {
        pixels[i].r = 1;
        pixels[i].g = 1;
        pixels[i].b = 1;
    }
    
    DRAWING = false;
}

// Esc to exit.
void keyboard(unsigned char key, int xmouse, int ymouse) {
    switch (key) {
        case 27:
            free(pixels);
            glutDestroyWindow(0);
            exit(0);
            break;
    }
    glutPostRedisplay();
}

// Right click to complete polygon and kick off filling process.
void menu(int id) {
    switch (id) {
        case 1:
            Edges newEdge(points.at(0), points.at(points.size()-1));
            allEdges.push_back(newEdge);
            sortAndFilterEdges();
            initScanline();
            updateActiveEdges();
            DRAWING = true;
            glutPostRedisplay();
            fillPolygon();
            break;
    }
    glutPostRedisplay();
}

// Stores vertexes on click.
void mouse_down(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN && !DRAWING) {
                printf("ADDING POINT %d and %d", x, 500 - y);
                points.push_back(tuple<GLint, GLint>(x, y));
                if (points.size() > 1) {
                    Edges newEdge(points.at(points.size()-2), points.at(points.size()-1));
                    allEdges.push_back(newEdge);
                }
                glutPostRedisplay();
            }
    }
    glutPostRedisplay();
}

void display(void) {
    
    //Print OpenGL errors
    GLenum err_code;
    do {
        err_code = glGetError();
        if (err_code != GL_NO_ERROR)
            printf("Error: %s\n", gluErrorString(err_code));
    } while (err_code != GL_NO_ERROR);
    
    //Clear buffer data
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Draw pixels
    glDrawPixels(500, 500, GL_RGB, GL_FLOAT, pixels);
    
    glPointSize(5);
    glColor3f(1.0, 0.0, 1.0);
    
    // Draws points.
    if (!DRAWING) {
        for (int i = 0; i < points.size(); i++) {
            glBegin(GL_POINTS);
            glVertex2f(get<0>(points.at(i)), get<1>(points.at(i)));
            glEnd();
        }
    }
    
    // Draws the final polygon outline.
    if (DRAWING) {
        glDrawPixels(500, 500, GL_RGB, GL_FLOAT, pixels);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        for (int i = 0; i < points.size(); i++) {
            glVertex2f(get<0>(points.at(i)), get<1>(points.at(i)));
        }
        glEnd();
    }
    
    //Flush data
    glFlush();
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Scan-line poly fill");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse_down);
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Draw Polygon", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
    
    return 0;
    
}
