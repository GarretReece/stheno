#include "vector2s.h"

vector2s::vector2s(short in[]) : x_(in[0]),y_(in[1])
{
}

vector2s::vector2s(short x, short y) : x_(x), y_(y)
{
}

vector2s::~vector2s()
{
}

double vector2s::length() {
	return sqrt((x_*x_) + (y_*y_));
}

short &vector2s::operator[] (int i) {
	if (i == 0) return x_; 
	if (i == 1) return y_;
	throw std::out_of_range("operator[]");
}

const short &vector2s::operator[] (int i) const {
	if (i == 0) return x_; 
	if (i == 1) return y_; 
	throw std::out_of_range("operator[]");
}

vector2s vector2s::operator-(const vector2s &rhs) {
	vector2s diff(*this);
	diff[0] -= rhs[0];
	diff[1] -= rhs[1];
	return diff;
}

vector2s vector2s::operator+(const vector2s &rhs) {
	vector2s sum(*this);
	return (sum += rhs);
}

vector2s &vector2s::operator+=(const vector2s &rhs) {
	this->x_ += rhs.x_;
	this->y_ += rhs.y_;
	return *this;
}

vector2s &vector2s::operator=(const vector2s &rhs) {
	if (this == &rhs) {
		return *this;
	}
	this->x_ = rhs.x_;
	this->y_ = rhs.y_;
	return *this;
}

bool vector2s::operator== (const vector2s &rhs) const {
	if (x_ != rhs.x_) return false;
	if (y_ != rhs.y_) return false;
	return true;
}

bool vector2s::operator !=(const vector2s &rhs) {
	return operator==(rhs) == false;
}

vector2s vector2s::operator *(const int rhs) {
	vector2s product(*this);
	product.x_ *= rhs;
	product.y_ *= rhs;
	return product;
}

double vector2s::dotProd(const vector2s &rhs) const {
	return (x_*rhs.x_) + (y_*rhs.y_);
}