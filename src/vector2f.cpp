#include "vector2f.h"

vector2f::vector2f(double a, double b, double eps)
: x_(a), y_(b), epsilon(eps) { }

double vector2f::length() const {
	return sqrt((x_*x_) + (y_*y_));
}

bool vector2f::operator==(const vector2f &rhs) const {
	if (x_ - rhs.x_ > epsilon || x_ - rhs.x_ < -epsilon)
		return false;
	if (y_ - rhs.y_ > epsilon || y_ - rhs.y_ < -epsilon)
		return false;
	return true;
}

bool vector2f::operator !=(const vector2f &rhs) const {
	return !(*this == rhs);
}

vector2f vector2f::operator+(const vector2f &rhs) const {
	vector2f sum(*this);
	sum.x_ += rhs.x_;
	sum.y_ += rhs.y_;
	return sum;
}

vector2f vector2f::operator-(const vector2f &rhs) const {
	vector2f diff(*this);
	diff.x_ -= rhs.x_;
	diff.y_ -= rhs.y_;
	return diff;
}

vector2f &vector2f::operator +=(const vector2f &rhs) {
	*this = *this + rhs;
	return *this;
}

vector2f &vector2f::operator -=(const vector2f &rhs) {
	*this = *this - rhs;
	return *this;
}

vector2f vector2f::operator *(const int &rhs) const {
	vector2f product(*this);
	product.x_ *= rhs;
	product.y_ *= rhs;
	return product;
}

vector2f vector2f::operator *(const double &rhs) const {
	vector2f product(*this);
	product.x_ *= rhs;
	product.y_ *= rhs;
	return product;
}

vector2f &vector2f::operator *=(const int &rhs) {
	*this = *this * rhs;
	return *this;
}

vector2f &vector2f::operator *=(const double &rhs) {
	*this = *this * rhs;
	return *this;
}

vector2f vector2f::operator /(const int &rhs) const {
	vector2f product(*this);
	product.x_ /= rhs;
	product.y_ /= rhs;
	return product;
}

vector2f vector2f::operator /(const double &rhs) const {
	vector2f product(*this);
	product.x_ /= rhs;
	product.y_ /= rhs;
	return product;
}

vector2f &vector2f::operator /=(const int &rhs) {
	*this = *this / rhs;
	return *this;
}

vector2f &vector2f::operator /=(const double &rhs) {
	*this = *this / rhs;
	return *this;
}

double &vector2f::operator [](const unsigned int &index) {
	if (index == 0)
		return x_;
	if (index == 1)
		return y_;
	throw std::out_of_range("vector2f operator[]");
}

const double &vector2f::operator [](const unsigned int &index) const {
	if (index == 0)
		return x_;
	if (index == 1)
		return y_;
	throw std::out_of_range("vector2f operator[]");
}

vector2f vector2f::normalize() const {
	vector2f rval(*this);
	if (rval.length() < rval.epsilon) {
		rval *= 0;
		return rval;
	}
	rval /= rval.length();
	return rval;
}

double vector2f::dotProd(const vector2f &rhs) const {
	return (x_*rhs.x_) + (y_*rhs.y_);
}