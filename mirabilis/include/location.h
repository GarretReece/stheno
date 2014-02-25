#ifndef _mirabilis_location_h_
#define _mirabilis_location_h_

#include <stdint.h>
#include <math.h>

class location
{
	public:
	location(int a, int b, int c): x(a), y(b), z(c) { }
	location(const location &rhs): x(rhs.x), y(rhs.y), z(rhs.z) { }
	location operator+(const location &rhs)
	{
		return location(x+rhs.x, y+rhs.y, z+rhs.z);
	}

	location operator-(const location &rhs)
	{
		return location(x-rhs.x, y-rhs.y, z-rhs.z);
	}

	void operator +=(const location &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
	}

	double magnitude() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	int x, y, z;
};

#endif
