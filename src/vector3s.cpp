#include "vector3s.h"


vector3s::vector3s(short x, short y, short z) : x_(x),y_(y),z_(z) { }
vector3s::vector3s(short in[3]) : x_(in[0]),y_(in[1]),z_(in[2]) { }


double vector3s::length() {
	return sqrt((x_*x_) + (y_*y_) + (z_*z_));
}

short &vector3s::operator[] (const int &i) {
	if (i == 0)
		return x_;
	if (i == 1)
		return y_;
	if (i == 2)
		return z_;
	throw std::out_of_range("vector3s operator[]");
}

const short &vector3s::operator[](const int &i) const {
	if (i == 0)
		return x_;
	if (i == 1)
		return y_;
	if (i == 2)
		return z_;
	throw std::out_of_range("vector3s operator[]");
}

vector3s vector3s::operator-(const vector3s &rhs) const {
	vector3s diff(*this);
	diff.x_ -= rhs.x_;
	diff.y_ -= rhs.y_;
	diff.z_ -= rhs.z_;
	return diff;
}

vector3s vector3s::operator+(const vector3s &rhs) const {
	vector3s sum(*this);
	sum.x_ += rhs.x_;
	sum.y_ += rhs.y_;
	sum.z_ += rhs.z_;
	return sum;
}

vector3s &vector3s::operator+=(const vector3s &rhs) {
	*this = *this + rhs;
	return *this;
}

vector3s &vector3s::operator-=(const vector3s &rhs) {
	*this = *this - rhs;
	return *this;
}

bool vector3s::operator== (const vector3s &rhs) const {
	if (x_ != rhs.x_)
		return false;
	if (y_ != rhs.y_)
		return false;
	if (z_ != rhs.z_)
		return false;
	return true;
}

bool vector3s::operator!= (const vector3s &rhs) const {
	return !(*this == rhs);
}

vector3s vector3s::operator*(const int &rhs) const {
	vector3s product(*this);
	product.x_ *= rhs;
	product.y_ *= rhs;
	product.z_ *= rhs;
	return product;
}

vector3s vector3s::operator/(const int &rhs) const {
	vector3s quotient(*this);
	quotient.x_ /= rhs;
	quotient.y_ /= rhs;
	quotient.z_ /= rhs;
	return quotient;
}

vector3s vector3s::operator*=(const int &rhs) {
	*this = *this * rhs;
	return *this;
}

vector3s vector3s::operator/=(const int &rhs) {
	*this = *this / rhs;
	return *this;
}

double vector3s::dotProd(const vector3s &rhs) const {
	return (x_*rhs.x_) + (y_*rhs.y_) + (z_*rhs.z_);
}