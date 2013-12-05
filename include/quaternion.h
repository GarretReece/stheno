#ifndef _quaternion_h_
#define _quaternion_h_

#include "vector3f.h"
#include "matrix4d.h"

class quaternion
{
	public:

	static const quaternion rotation_identity;

	quaternion(double w = 0.0f, double x = 0.0f, double y = 0.0f, double z = 0.0f);
	quaternion(const quaternion &rhs);
	quaternion(double, const vector3f &);
	quaternion& operator=(const quaternion &rhs);

	double magnitude() const;

	void normalize();

	quaternion conjugate() const;

	quaternion operator*(const quaternion &rhs) const;
	vector3f operator*(const vector3f &rhs) const;

	quaternion operator*(const float rhs) const;
	friend quaternion operator*(const float a, const quaternion &b);

	quaternion operator+(const quaternion &rhs) const;

	matrix4d to_matrix() const;

	static quaternion from_axis(const vector3f &, float);

	double w, x, y, z;
};
#endif
