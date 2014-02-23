#include "matrix4d.h"

matrix4d::matrix4d(double a1, double b1, double c1, double d1,
		double a2, double b2, double c2, double d2,
		double a3, double b3, double c3, double d3,
		double a4, double b4, double c4, double d4)
{
	data[0] = a1;
	data[1] = b1;
	data[2] = c1;
	data[3] = d1;
	data[4] = a2;
	data[5] = b2;
	data[6] = c2;
	data[7] = d2;
	data[8] = a3;
	data[9] = b3;
	data[10] = c3;
	data[11] = d3;
	data[12] = a4;
	data[13] = b4;
	data[14] = c4;
	data[15] = d4;
}
