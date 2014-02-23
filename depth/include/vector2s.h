#ifndef vector2s_h_included
#define vector2s_h_included

#include <math.h>
#include <exception>
#include <stdexcept>

class vector2s {
public:
	vector2s(short x, short y);
	vector2s(short in[2]);
	//vector2s(const &vector2s rhs);
	virtual ~vector2s();

	double length();
	short &operator[] (int i);
	const short &operator[](int i) const;
	vector2s operator-(const vector2s &rhs);
	vector2s operator+(const vector2s &rhs);
	vector2s &operator+=(const vector2s &rhs);
	bool operator== (const vector2s &rhs) const;
	bool operator!= (const vector2s &rhs);
	vector2s &operator=(const vector2s &rhs);
	vector2s operator*(const int);
	
	double dotProd(const vector2s &rhs) const;

protected:
	short x_, y_;

};

#endif
