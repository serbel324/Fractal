#include "Complex.h"

Complex::Complex()
{
	x = 0;
	y = 0;
}
Complex::Complex(long double x, long double y)
{
	this->x = x;
	this->y = y;
}

Complex Complex::operator+(const Complex& r) const
{
	return Complex(x + r.x, y + r.y);
}

Complex Complex::operator-(const Complex& r) const
{
	return Complex(x - r.x, y - r.y);
}

Complex Complex::operator*(const Complex& r) const
{
	return Complex(x * r.x - y * r.y, y * r.x + x * r.y);
}

Complex Complex::operator*(const double& r) const
{
	return Complex(x * r, y * r);
}

void Complex::operator*=(const Complex& r)
{
	float x1 = x * r.x - y * r.y;
	float y1 = y * r.x + x * r.y;
	x = x1;
	y = y1;
}

void Complex::operator+=(const Complex& r)
{
	x += r.x;
	y += r.y;
}

void Complex::operator-=(const Complex& r)
{
	x -= r.x;
	y -= r.y;
}

bool Complex::operator<(const long double r) const
{
	return (x * x + y * y) < r * r;
}

bool Complex::operator>(const long double r) const
{
	return (x * x + y * y) > r * r;
}
