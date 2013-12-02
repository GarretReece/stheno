#ifndef vector3s_h_included
#define vector3s_h_included

#include <math.h>
#include <stdexcept>

class vector3s {
public:
	vector3s(short x, short y, short z);
	vector3s(short in[3]);

	double length();

	short &operator[] (const int &i);
	const short &operator[](const int &i) const;

	vector3s operator-(const vector3s &rhs) const;
	vector3s operator+(const vector3s &rhs) const;

	vector3s &operator+=(const vector3s &rhs);
	vector3s &operator-=(const vector3s &rhs);

	bool operator== (const vector3s &rhs) const;
	bool operator!= (const vector3s &rhs) const;

	vector3s operator*(const int &) const;
	vector3s operator/(const int &) const;

	vector3s operator*=(const int &);
	vector3s operator/=(const int &);

	double dotProd(const vector3s &rhs) const;

protected:
	short x_, y_, z_;

};

#endif
