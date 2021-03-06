#include "quaternion.h"

#include <math.h>

const quaternion quaternion::rotation_identity(1.0, 0.0, 0.0, 0.0);
const double TOLERANCE = 0.001;

quaternion::quaternion(double w, double x, double y, double z):
w(w),
x(x),
y(y),
z(z)
{
}

quaternion::quaternion(const quaternion &rhs):
w(rhs.w),
x(rhs.x),
y(rhs.y),
z(rhs.z)
{
} 

quaternion::quaternion(double w, const vector3f &v):
w(w),
x(v[0]),
y(v[1]),
z(v[2])
{
}

double quaternion::magnitude() const
{
	return sqrt(w*w + x*x + y*y + z*z);
}

quaternion &quaternion::operator=(const quaternion &rhs)
{
	w = rhs.w;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

void quaternion::normalize()
{
	double mag = sqrt(w*w + x*x + y*y + z*z);
	w /= mag;
	x /= mag;
	y /= mag;
	z /= mag;
}

quaternion quaternion::conjugate() const
{
	return quaternion(-x, -y, -z, w);
}

quaternion quaternion::operator*(const quaternion &rhs) const
{
	return quaternion(w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
      			  w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
			  w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,
			  w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w);
}

vector3f quaternion::operator*(const vector3f &rhs) const
{
	/*
	vector3f v = rhs.normalize();
	quaternion vesQuat(v[0], v[1], v[2], 0.0), resQuat;
	resQuat = vesQuat * conjugate();
	resQuat = *this * resQuat;

	return vector3f(resQuat.x, resQuat.y, resQuat.z);
	*/

	vector3f q(x,y,z);

	vector3f t = 2 * q.crossprod(rhs);
	return rhs + w * t + q.crossprod(t);
}

quaternion quaternion::operator*(const float rhs) const
{
	return quaternion(w*rhs, x*rhs, y*rhs, z*rhs);
}

quaternion operator*(const float a, const quaternion &b)
{
	return quaternion(a*b.w, a*b.x, a*b.y, a*b.z);
}

quaternion quaternion::operator+(const quaternion &b) const
{
	return quaternion(w+b.w, x+b.x, y+b.y, z+b.z);
}

quaternion &quaternion::operator+=(const quaternion &b)
{
	w += b.w;
	x += b.x;
	y += b.y;
	z += b.z;
	return *this;
}

quaternion quaternion::slerp(const quaternion &b, const float t) const
{
	//assert(t>=0);
	//assert(t<=1);

	float flip = 1;

	float cosine = w*b.w + x*b.x + y*b.y + z*b.z;

	if (cosine<0) 
	{ 
		cosine = -cosine; 
		flip = -1; 
	} 

	if ((1-cosine)<TOLERANCE) 
		return (*this) * (1-t) + b * (t*flip); 

	float theta = (float)acos(cosine); 
	float sine = (float)sin(theta); 
	float beta = (float)sin((1-t)*theta) / sine; 
	float alpha = (float)sin(t*theta) / sine * flip; 

	return *this * beta + b * alpha; 
}

matrix4d quaternion::to_matrix() const
{
	double x2 = x * x;
	double y2 = y * y;
	double z2 = z * z;
	double xy = x * y;
	double xz = x * z;
	double yz = y * z;
	double wx = w * x;
	double wy = w * y;
	double wz = w * z;

	// This calculation would be a lot more complicated for non-unit length quaternions
	// Note: The constructor of Matrix4 expects the Matrix in column-major format like expected by
	//   OpenGL
	return matrix4d( 1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
			2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
			2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
}

quaternion quaternion::from_axis(const vector3f &v, float angle)
{
	angle *= 0.5f;
	vector3f vn = v.normalize() * sin(angle);
	return quaternion(cos(angle), vn);
}
