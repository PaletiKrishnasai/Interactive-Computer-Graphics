#include <GL/freeglut.h> 
#include <bits/stdc++.h> 


using namespace std;
#define LENGTH 600
#define HEIGHT 600

float R[600][600];
float G[600][600];
float B[600][600];


void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

void window_color()
{

	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

}

void DDA(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    float dx = x2-x1;
    float dy = y2-y1;
    float slope = dy/dx;
    cout << "Slope :" << slope*1.0 << endl;
    glColor3f(r,g,b);
    glPointSize(2.5);
    if(abs(slope) <= 1)
    {
      float step = 1.0; // In x direction
      float x=x1,y=y1;
      if(x1<x2)
      {
        while(x<=x2)
        {
            glBegin(GL_POINTS);
                glVertex2f(x,y);
                x = x+step;
                y = y+slope*step;
            glEnd();
        }
      }
      else
      {
         while(x>=x2)
        {
            glBegin(GL_POINTS);
                glVertex2f(x,y);
                x = x-step;
                y = y-slope*step;
            glEnd();
        } 
      }
    }
    if(abs(slope) > 1)
    {
      float step = 1.0; // In x direction
      float x=x1,y=y1;
      if(y1<y2)
      {
        while(y<=y2)
        {
            glBegin(GL_POINTS);
                glVertex2f(x,y);
                x = x+step/slope;
                y = y+step;
            glEnd();
        }
      }
      else
      {
         while(y>=y2)
        {
            glBegin(GL_POINTS);
                glVertex2f(x,y);
                x = x-step/slope;
                y = y-step;
            glEnd();
        } 
      }
    }
}

int Point_Sign(int x1, int y1, int x2, int y2, int x, int y)
{
    int c = (((x2-x1)*(y-y1) - (y2-y1)*(x-x1))>=0)? 1:-1;
    return c;
}

int Point_Check(pair<int,int> P, vector<pair<int,int>>W, int n)
{
    int p=0;
    int s = Point_Sign(W[p].first,W[p].second,W[p+1].first, W[p+1].second,P.first, P.second);
    cout << s;
    while(p<n-1)
    {
        cout << Point_Sign(W[p].first,W[p].second,W[p+1].first, W[p+1].second,P.first, P.second);
        if(s!=Point_Sign(W[p].first,W[p].second,W[p+1].first, W[p+1].second,P.first, P.second))
        {
            return -1;
        }
        p++;
    }
    cout << Point_Sign(W[p].first,W[p].second,W[0].first, W[0].second,P.first, P.second) << endl;
    if(s!=Point_Sign(W[p].first,W[p].second,W[0].first, W[0].second,P.first, P.second))
    {
     return -1;
    }
    else
    {
     return 1;
    }
    return 0;
}

bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second < b.second);
}

struct Point {
    int x;
    int y;
};

struct Color {
    float r;
    float g;
    float b;
};

Color getPixelColor(GLint x, GLint y) {
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

int Start_Flood_Filling(vector<pair<int,int>>W, float r, float g, float b, int x, int y)
{
    if(Point_Check(make_pair(x,y),W,W.size())==-1)
    {
        cout << "Out of range" << endl;
        return 0;
    }
    if(R[x][y]!=1.0 && G[x][y]!=1.0 && B[x][y]!=1.0)
    {
        cout << x << " " << y << " "  << R[x][y] << " " << G[x][y] << " " << B[x][y] << endl;
        cout << "Already coloured" << endl;
        return 0;
    }
    R[x][y]=r;
    G[x][y]=g;
    B[x][y]=b;
    glPointSize(1);
    glColor3f(r,g,b);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    Start_Flood_Filling(W,r,g,b,x+1,y);
    Start_Flood_Filling(W,r,g,b,x-1,y);
    Start_Flood_Filling(W,r,g,b,x,y+1);
    Start_Flood_Filling(W,r,g,b,x,y-1);
    Start_Flood_Filling(W,r,g,b,x+1,y+1);
    Start_Flood_Filling(W,r,g,b,x+1,y-1);
    Start_Flood_Filling(W,r,g,b,x-1,y+1);
    Start_Flood_Filling(W,r,g,b,x-1,y-1);

}

void Flood_Fill()
{
    int w1,w2;
    int k,n;
    vector<pair<int,int>>W,S;
    cout << "Number of sides: ";
    cin >> n;
    k=n;
    cout << "Enter the vertices of the polygon : " << endl;
    while(n-->0)
    {
        cin >> w1 >> w2;
        W.push_back(make_pair(w1,w2));
    }
    n=k;
    S=W;
    sort(S.begin(), S.end());
    int xmin = S[0].first;
    int xmax = S[n-1].first;

    sort(S.begin(), S.end(), sortbysec);
    int ymin = S[0].second;
    int ymax = S[n-1].second;

    glPointSize(1);
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++)
    {
        glVertex2f(W[i].first, W[i].second);   
    }
    glEnd();


    float rc,bc,gc;
    cout << "Enter your colour choice: ";
    cin >> rc >> gc >> bc;
    int xs,ys;
    cout << "Enter seed coordinates :";
    cin >> xs >> ys;

    //Initialise pixels to background colour(white)
    Color BC;
    for(int i=0;i<600;i++)
    {
        for(int j=0;j<600;j++)
        {
            BC = getPixelColor(i,j);
            R[i][j] = BC.r;
            G[i][j] = BC.g;
            B[i][j] = BC.b;

        }
    }

    Start_Flood_Filling(W,rc,gc,bc,xs,ys);

}


int Start_Border_Filling(float rc, float gc, float bc, float rb, float gb, float bb, int x, int y)
{
    
    if((R[x][y]!=rb && G[x][y]!=gb && B[x][y]!=bb) && (R[x][y]!=rc && G[x][y]!=gc && B[x][y]!=bc))
    {
       
        cout << "Coloured at point " << x << " , " << y << endl;
        R[x][y]=rc;
        G[x][y]=gc;
        B[x][y]=bc;
        glPointSize(1);
        glColor3f(rc,gc,bc);
        glBegin(GL_POINTS);
            glVertex2f(x,y);
        glEnd();
        Start_Border_Filling(rc,gc,bc,rb,gb,bb,x+1,y);
        Start_Border_Filling(rc,gc,bc,rb,gb,bb,x-1,y);
        Start_Border_Filling(rc,gc,bc,rb,gb,bb,x,y+1);
        Start_Border_Filling(rc,gc,bc,rb,gb,bb,x,y-1);
        Start_Border_Filling(rc,gc,bc,rb,gb,bb,x+1,y+1);
        Start_Border_Filling(rc,gc,bc,rb,gb,bb,x+1,y-1);
        Start_Border_Filling(rc,gc,bc,rb,gb,bb,x-1,y+1);
        Start_Border_Filling(rc,gc,bc,rb,gb,bb,x-1,y-1);
    }

}

void Border_Fill()
{
    int w1,w2;
    int k,n;
    vector<pair<int,int>>W,S;
    cout << "Number of sides: ";
    cin >> n;
    k=n;
    cout << "Enter the vertices of the polygon : " << endl;
    while(n-->0)
    {
        cin >> w1 >> w2;
        W.push_back(make_pair(w1,w2));
    }
    n=k;
    S=W;
    sort(S.begin(), S.end());
    int xmin = S[0].first;
    int xmax = S[n-1].first;

    sort(S.begin(), S.end(), sortbysec);
    int ymin = S[0].second;
    int ymax = S[n-1].second;

    float rb,bb,gb;
    cout << "Enter your colour choice(for border region): ";
    cin >> rb >> gb >> bb;

 
    for(int i=0;i<n;i++)
    {
        DDA(W[i%n].first,W[i%n].second,W[(i+1)%n].first,W[(i+1)%n].second,rb,gb,bb);
    }

    
    float rc,bc,gc;
    cout << "Enter your colour choice(for interior region): ";
    cin >> rc >> gc >> bc;
    int xs,ys;
    cout << "Enter seed coordinates :";
    cin >> xs >> ys;

    //Initialise pixels to background colour(white)
    Color BC;
    for(int i=0;i<600;i++)
    {
        for(int j=0;j<600;j++)
        {
            BC = getPixelColor(i,j);
            R[i][j] = BC.r;
            G[i][j] = BC.g;
            B[i][j] = BC.b;
            if(R[i][j]!=1 && G[i][j]!=1 && B[i][j]!=1)
            {
                rb = R[i][j];
                gb = G[i][j];
                bb = B[i][j];
            }
        }
    }

    Start_Border_Filling(rc,gc,bc,rb,gb,bb,xs,ys);

}


void draw()
{
    
	window_color();
    srand(time(0));
    // Flood_Fill();
    Border_Fill();
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
	glutDisplayFunc(draw);
	glutMainLoop();
}





