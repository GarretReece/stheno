#ifndef _matrix4d_h_
#define _matrix4d_h_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class matrix4d
{
	public:
	matrix4d(double a1, double b1, double c1, double d1,
		double a2, double b2, double c2, double d2,
		double a3, double b3, double c3, double d3,
		double a4, double b4, double c4, double d4);
	GLfloat data[16];
};
#endif
