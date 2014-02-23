#include "vector3f.h"

vector3f::vector3f(double a, double b, double c, double eps)
: x_(a), y_(b), z_(c), epsilon(eps) { }

vector3f::vector3f(vector2f xy, double c, double eps)
: x_(xy[0]),y_(xy[1]),z_(c),epsilon(eps) { }

bool vector3f::operator==(const vector3f &rhs) const {
	if (x_ - rhs.x_ > epsilon || x_ - rhs.x_ < -epsilon)
		return false;
	if (y_ - rhs.y_ > epsilon || y_ - rhs.y_ < -epsilon)
		return false;
	if (z_ - rhs.z_ > epsilon || z_ - rhs.z_ < -epsilon)
		return false;
	return true;
}

bool vector3f::operator !=(const vector3f &rhs) const {
	return !(*this == rhs);
}

vector3f vector3f::operator+(const vector3f &rhs) const {
	vector3f sum(*this);
	sum.x_ += rhs.x_;
	sum.y_ += rhs.y_;
	sum.z_ += rhs.z_;
	return sum;
}

vector3f vector3f::operator-(const vector3f &rhs) const {
	vector3f diff(*this);
	diff.x_ -= rhs.x_;
	diff.y_ -= rhs.y_;
	diff.z_ -= rhs.z_;
	return diff;
}

vector3f &vector3f::operator +=(const vector3f &rhs) {
	*this = *this + rhs;
	return *this;
}

vector3f &vector3f::operator -=(const vector3f &rhs) {
	*this = *this - rhs;
	return *this;
}

vector3f vector3f::operator *(const int &rhs) const {
	vector3f product(*this);
	product.x_ *= rhs;
	product.y_ *= rhs;
	product.z_ *= rhs;
	return product;
}

vector3f vector3f::operator *(const double &rhs) const {
	vector3f product(*this);
	product.x_ *= rhs;
	product.y_ *= rhs;
	product.z_ *= rhs;
	return product;
}

vector3f operator*(double a, const vector3f &b)
{
	return vector3f(a*b[0], a*b[1], a*b[2]);
}

vector3f &vector3f::operator *=(const int &rhs) {
	*this = *this * rhs;
	return *this;
}

vector3f &vector3f::operator *=(const double &rhs) {
	*this = *this * rhs;
	return *this;
}

vector3f vector3f::operator /(const int &rhs) const {
	vector3f product(*this);
	product.x_ /= rhs;
	product.y_ /= rhs;
	product.z_ /= rhs;
	return product;
}

vector3f vector3f::operator /(const double &rhs) const {
	vector3f product(*this);
	product.x_ /= rhs;
	product.y_ /= rhs;
	product.z_ /= rhs;
	return product;
}

vector3f &vector3f::operator /=(const int &rhs) {
	*this = *this / rhs;
	return *this;
}

vector3f &vector3f::operator /=(const double &rhs) {
	*this = *this / rhs;
	return *this;
}
double &vector3f::operator [](const unsigned int &index) {
	if (index == 0)
		return x_;
	if (index == 1)
		return y_;
	if (index == 2)
		return z_;
	throw std::out_of_range("vector3f operator[]");
}

const double &vector3f::operator [](const unsigned int &index) const {
	if (index == 0)
		return x_;
	if (index == 1)
		return y_;
	if (index == 2)
		return z_;
	throw std::out_of_range("vector3f operator[]");
}

vector3f vector3f::normalize() const {
	vector3f rval(*this);
	if (rval.length() < rval.epsilon) {
		rval *= 0;
		return rval;
	}
	rval /= rval.length();
	return rval;
}

double vector3f::length() {
	return sqrt((x_*x_)+(y_*y_)+(z_*z_));
}

vector3f vector3f::crossprod(const vector3f &rhs) const {
	vector3f rval(0,0,0);
	rval[0] = y_*rhs.z_ - z_*rhs.y_;
	rval[1] = z_*rhs.x_ - x_*rhs.z_;
	rval[2] = x_*rhs.y_ - y_*rhs.x_;
	return rval;
}

double vector3f::dotProd(const vector3f &rhs) const {
	return (x_*rhs.x_) + (y_*rhs.y_) + (z_*rhs.z_);
}

vector2f vector3f::vector2d() const {
	vector2f rval(this->x_,this->y_);
	return rval;
}
