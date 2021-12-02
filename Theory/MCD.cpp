#include <GL/freeglut.h> 
#include <bits/stdc++.h> 

using namespace std;

void MCD_O1(int xc, int yc, int r, int xs, int ys)
{
   int k=-1,p = 1-r;
   int x=r*(-xs),y=0;
   cout << "k : " << k << "  " << "pk : " << "  ";
   cout << "(x,y) : " << "(" << x << "," << y << ")   ";
   cout << "pk+1 : " << p << endl;
   k++;
   while(abs(y)<abs(x))
   {
     cout << "k : " << k << "  " << "pk : " << p << "  ";
     if(p<0)
     {
        y=y+1*ys;
        p += 2*y*ys + 1;
     }
     else
     {
        y=y+1*ys;
        x=x+1*xs;
        p += 2*y*ys + 1 + 2*x*xs;
     }
     cout << "(x,y) : " << "(" << x << "," << y << ")   ";
     cout << "pk+1 : " << p << endl;
     k++;
   }
}

void MCD_O2(int xc, int yc, int r,int xs,int ys)
{
   int k=-1,p = 1-r;
   int x=0,y=r*(-ys);
   cout << "k : " << k << "  " << "pk : " << "  ";
   cout << "(x,y) : " << "(" << x << "," << y << ")   ";
   cout << "pk+1 : " << p << endl;
   k++;
   while(abs(x)<abs(y))
   {
     cout << "k : " << k << "  " << "pk : " << p << "  ";
     if(p<0)
     {
        x=x+1*xs;
        p += 2*x*xs + 1;
     }
     else
     {
        x=x+1*xs;
        y=y+1*ys;
        p += 2*x*xs + 1 + 2*y*ys;
     }
     cout << "(x,y) : " << "(" << x << "," << y << ")   ";
     cout << "pk+1 : " << p << endl;
     k++;
   }
}

int main()
{
    // MCD_O2(0,0,10);

    MCD_O2(0,0,20,1,-1);
}