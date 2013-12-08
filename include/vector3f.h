#ifndef vector3f_h_included
#define vector3f_h_included

#include <math.h>
#include <stdexcept>
#include "vector2f.h"

class vector3f {
public:
	vector3f(double a = 0, double b = 0, double c = 0, double eps = 0.000005);
	vector3f(vector2f xy, double c, double eps = 0.000005);

	bool operator==(const vector3f &rhs) const;
	bool operator!=(const vector3f &rhs) const;

	vector3f operator+(const vector3f &rhs) const;
	vector3f operator-(const vector3f &rhs) const;

	vector3f &operator+=(const vector3f &rhs);
	vector3f &operator-=(const vector3f &rhs);

	vector3f operator*(const int &rhs) const;
	vector3f operator*(const double &rhs) const;

	vector3f &operator*=(const int &rhs);
	vector3f &operator*=(const double &rhs);

	vector3f operator/(const int &rhs) const;
	vector3f operator/(const double &rhs) const;

	vector3f &operator/=(const int &rhs);
	vector3f &operator/=(const double &rhs);

	double &operator[](const unsigned int &rhs);
	const double &operator[](const unsigned int &rhs) const;

	vector3f normalize() const;
	double length();

	vector3f crossprod(const vector3f &rhs) const;
	double dotProd(const vector3f &rhs) const;

	vector2f vector2d() const;
	
protected:
	double x_,y_,z_,epsilon;
};

vector3f operator*(double a, const vector3f &b);
#endif
