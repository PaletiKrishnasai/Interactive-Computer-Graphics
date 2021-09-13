// CPP example to illustrate the
// reflection of a point about a line
#include <iostream>
#include <complex>

using namespace std;

typedef complex<double> point;
#define x real()
#define y imag()

// Constant PI for providing angles in radians
#define PI 3.1415926535897932384626

// Function used to display X and Y coordinates of a point
void displayPoint(point P)
{
	cout << "(" << P.x << ", " << P.y << ")" << endl;
}

// Function for Reflection of P about line AB
point reflect(point P, point A, point B)
{
	// Performing translation and shifting origin at A
	point Pt = P-A;
	point Bt = B-A;

	// Performing rotation in clockwise direction
	// BtAt becomes the X-Axis in the new coordinate system
	point Pr = Pt/Bt;

	// Reflection of Pr about the new X-Axis
	// Followed by restoring from rotation
	// Followed by restoring from translation

	return conj(Pr)*Bt + A;
}

int main()
{
	// Rotate P about line AB
	point P(-4.0, 7.0);
	point A(-1.0, 1.0);
	point B(-3.0, 3.0);

	
	point P_reflected = reflect(P, A, B);
	cout << "The point P on reflecting about AB becomes:";
	cout << "P_reflected"; displayPoint(P_reflected);

	return 0;
}
