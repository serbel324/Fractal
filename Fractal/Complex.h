#pragma once
class Complex
{
public:
	Complex();
	Complex(long double x, long double y);

	Complex operator+ (const Complex& r) const;
	Complex operator- (const Complex& r) const;
	Complex operator* (const Complex& r) const;
	Complex operator* (const double& r) const;

	void operator*= (const Complex& r);
	void operator+= (const Complex& r);
	void operator-= (const Complex& r);

	bool operator< (const long double r) const;
	bool operator> (const long double r) const;

	long double x, y;
};

