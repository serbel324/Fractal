#ifndef __EXTMATH_CPP__
#define __EXTMATH_CPP__

#include "ExtMath.h"
#include <cstdlib>
#include <cmath>

int ExtMath::get_random_int(int min, int max)
{
	return(((float)rand() / RAND_MAX) * (max - min) + min);
}

double ExtMath::to_radian(double a)
{
	return (a * PI / 180);
}

double ExtMath::to_degrees(double a)
{
	return (a * 180 / PI);
}

float ExtMath::get_random(float min, float max) {
	return(((float)rand() / RAND_MAX) * (max - min) + min);
}

float ExtMath::waverage(float a1, float p1, float a2, float p2)
{
	return (a1 * p1 + a2 * p2) / (p1 + p2);
}

float ExtMath::hypot(float a1, float a2)
{
	return(sqrt(a1 * a1 + a2 * a2));
}

float ExtMath::hypot(float x1, float y1, float x2, float y2)
{
	return(std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2)));
}

double ExtMath::sigmoid(float x, float a)
{
	return 1 / (1 + exp(-x * a));
}

int ExtMath::sign(double a)
{
	if (a == 0)	return 0;
	if (a > 0) return 1;
	return -1;
}

Complex ExtMath::comp_sin(Complex& r)
{
	return Complex(std::sin(r.x), std::cos(r.y));
}

Complex ExtMath::pow(Complex& r, const int& n)
{
	Complex r0(r.x, r.y);
	Complex c(r.x, r.y);
	for (int i = 1; i < n; i++)
	{
		c = c * r0;
	}
	return c;
}

template <typename T>
float ExtMath::get_angle(Vector2<T> v)
{
	return v.get_angle();
}

template <typename T>
float ExtMath::get_angle(Vector2<T> v1, Vector2<T> v2)
{
	return atan2(cross_prod(v1, v2), dot_prod(v1, v2));
}

template <typename T>
T ExtMath::dot_prod(Vector2<T> v1, Vector2<T> v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
T ExtMath::cross_prod(Vector2<T> v1, Vector2<T> v2)
{
	return v1.x* v2.y - v1.y * v2.x;
}

Color ExtMath::get_random_color()
{
	return Color(get_random_int(-255, 255), get_random_int(-255, 255), get_random_int(-255, 255));
}

std::vector<Vector2<int>> ExtMath::directions = {
	Vector2<int>(1, 0), Vector2<int>(0, 1), Vector2<int>(-1, 0), Vector2<int>(0, -1)
};

std::vector<Vector2<int>> ExtMath::reflections = {
	Vector2<int>(1, 1), Vector2<int>(0, 1), Vector2<int>(-1, 1),
	Vector2<int>(1, 0), Vector2<int>(0, 0), Vector2<int>(-1, 0),
	Vector2<int>(1, -1), Vector2<int>(0, -1), Vector2<int>(-1, -1)
};

double ExtMath::PI = 3.14159265359;

#endif