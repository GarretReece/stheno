#ifndef vector2f_h_included
#define vector2f_h_included

#include <math.h>
#include <stdexcept>
class vector2f {
public:
	vector2f(double a, double b, double eps = 0.000005);
	
	bool operator==(const vector2f &rhs) const;
	bool operator!=(const vector2f &rhs) const;

	vector2f operator+(const vector2f &rhs) const;
	vector2f operator-(const vector2f &rhs) const;

	vector2f &operator+=(const vector2f &rhs);
	vector2f &operator-=(const vector2f &rhs);

	vector2f operator*(const int &rhs) const;
	vector2f operator*(const double &rhs) const;

	vector2f &operator*=(const int &rhs);
	vector2f &operator*=(const double &rhs);

	vector2f operator/(const int &rhs) const;
	vector2f operator/(const double &rhs) const;

	vector2f &operator/=(const int &rhs);
	vector2f &operator/=(const double &rhs);

	double &operator[](const unsigned int &rhs);
	const double &operator[](const unsigned int &rhs) const;

	vector2f normalize() const;
	double length() const;

	double dotProd(const vector2f &rhs) const;

protected:
	double x_, y_;
	double epsilon;

};

#endif