#include <GL/freeglut.h> 
#include <bits/stdc++.h> 


using namespace std;
#define LENGTH 600
#define HEIGHT 600


void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

void window_color()
{

	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

}

int Point_Sign(int x1, int y1, int x2, int y2, int x, int y)
{
    int c = (((x2-x1)*(y-y1) - (y2-y1)*(x-x1))>=0)? 1:-1;
    return c;
}

pair<int,int> Find_Intersection(pair<int,int>w1, pair<int,int>w2, pair<int,int>p1, pair<int,int> p2)
{
    // cout << "Inside intersection module" << endl;
    // float w_slope = (float)(w2.second-w1.second)/(w2.first-w1.first);
    // float p_slope = (float)(p2.second-p1.second)/(p2.first-p1.first);
    // if(w_slope!=inf)
    //     float w_c = w1.second - w_slope*w1.first;
    // else 
    // float p_c = p1.second - p_slope*p1.first;
    // int interx = round((w_c-p_c)/(p_slope-w_slope));
    // int intery = round(w_slope*((w_c-p_c)/(p_slope-w_slope)) + w_c);
    // cout << "Intersection points: " << interx << "  " << intery << endl;
    // cout << "Finished intersection module" << endl;
    // return make_pair(interx, intery);
    cout << endl <<"Inside Intersection module" << endl;
    double a1 = w2.second - w1.second;
    double b1 = w1.first - w2.first;
    double c1 = a1*(w1.first) + b1*(w1.second);
  
    // Line CD represented as a2x + b2y = c2
    double a2 = p2.second - p1.second;
    double b2 = p1.first - p2.first;
    double c2 = a2*(p1.first)+ b2*(p1.second);
  
    double determinant = a1*b2 - a2*b1;
  
    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return make_pair(FLT_MAX, FLT_MAX);
    }
    else
    {
        int x = round((b2*c1 - b1*c2)/determinant);
        int y = round((a1*c2 - a2*c1)/determinant);
        cout << x << " , " << y << endl;
        cout << "Finished Intersection module" << endl << endl;
        return make_pair(x, y);
    }
}

vector<pair<int,int>> Find_Points(vector<pair<int,int>> W, vector<pair<int,int>> P, int n1,int n2)
{
    int N1=n1,N2=n2;
    vector<pair<int, int>> T;
    for(int i=0;i<N1;i++)
    {
        for(int j=0;j<N2;j++)
        {
            printf("%d,%d  %d,%d  %d,%d\n",W[i%N1].first,W[i%N1].second,W[(i+1)%N1].first,W[(i+1)%N1].second,P[j%N2].first,P[j%N2].second);
            printf("%d,%d  %d,%d  %d,%d\n",W[i%N1].first,W[i%N1].second,W[(i+1)%N1].first,W[(i+1)%N1].second,P[(j+1)%N2].first,P[(j+1)%N2].second);   
            int c1 = Point_Sign(W[i%N1].first,W[i%N1].second,W[(i+1)%N1].first,W[(i+1)%N1].second,P[j%N2].first,P[j%N2].second);
            int c2 = Point_Sign(W[i%N1].first,W[i%N1].second,W[(i+1)%N1].first,W[(i+1)%N1].second,P[(j+1)%N2].first,P[(j+1)%N2].second);
            cout << c1 << "  " << c2 << endl;
            //4 conditions for considering the 2 selected points of the polygon to be clipped
            if(c1>=0 && c2>=0)
            {
                cout << "Case 1" << endl;
                T.push_back(P[(j+1)%N2]);
            }
            else if(c1>=0 && c2<0)
            {
                cout << "Case 2" << endl;
                //Find intersection and pushback
                pair<int,int> I = Find_Intersection(W[i%N1],W[(i+1)%N1],P[j%N2],P[(j+1)%N2]);
                T.push_back(I);
                
            }
            else if(c1<0 && c2>=0)
            {
                cout << "Case 3" << endl;
                //FInd intersection and pushback
                pair<int,int> I = Find_Intersection(W[i%N1],W[(i+1)%N1],P[j%N2],P[(j+1)%N2]);
                T.push_back(I);
                //Then pushback P[(j+1)%N2]
                T.push_back(P[(j+1)%N2]);
            }
            else if(c1<0 && c2<0)
            {
                cout << "Case 4" << endl;
                //Nothing happens
            }
            else;
        }
        if(T.size()!=0)
        {
            N2 = T.size();
            P = T;
        }
        T.clear();
    }
    return P;
}

void Polygon_Clipping()
{
    int p1,p2;
    int w1,w2;
    int n1,n2;
    vector<pair<int,int>>P;
    vector<pair<int,int>>W;
    cout << "Enter the number of sides in the clipping polygon: ";
    cin >> n1;
    cout << "Enter the number of sides in the polygon to be clipped: ";
    cin >> n2;
    int k1=n1,k2=n2;
    cout << "Enter the coordinates of clipping polygon:" << endl;
    while(n1--)
    {
        cin >> w1 >> w2;
        W.push_back(make_pair(w1,w2));
    }
    cout << "Enter the coordinates of polygon to be clipped:" << endl;
    while(n2--)
    {
        cin >> p1 >> p2;
        P.push_back(make_pair(p1,p2));
    }
    n1=k1,n2=k2;
    glPointSize(1);
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
    while(n1-->0)
        glVertex2f(W[n1].first, W[n1].second);   
    glEnd();
    glBegin(GL_LINE_LOOP);
    while(n2-->0)
        glVertex2f(P[n2].first, P[n2].second);   
    glEnd();
    vector<pair<int,int>> K = Find_Points(W,P,k1,k2);
    for(int i=0;i<K.size();i++)
    {
        cout << K[i].first << " , " << K[i].second << endl;
    }
    glPointSize(1.5);
    glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<K.size();i++)
            glVertex2f(K[i].first,K[i].second);
        
    glEnd();


}


void draw()
{
    
	window_color();
    srand(time(0));
    Polygon_Clipping();

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





