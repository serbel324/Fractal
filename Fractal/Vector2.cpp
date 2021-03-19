#ifndef __VECTOR2_CPP__
#define __VECTOR2_CPP__

#include "Vector2.h"

#include <cmath>
#include <iostream>

template <typename T>
Vector2<T>::Vector2()
{
	x = 0;
	y = 0;
}

template <typename T>
Vector2<T>::Vector2(T _x)
{
	x = _x;
	y = _x;
}

template <typename T>
Vector2<T>::Vector2(T _x, T _y)
{
	x = _x;
	y = _y;
}
template <typename T>
Vector2<T> Vector2<T>::operator*(double r) const
{
	return Vector2<T>(x * r, y * r);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(double r) const
{
	return Vector2<T>(x / r, y / r);
}

template <typename T>
template <typename T2>
Vector2<T> Vector2<T>::operator+(const Vector2<T2> r) const
{
	return Vector2<T>(x + r.x, y + r.y);
}

template <typename T>
template <typename T2>
Vector2<T> Vector2<T>::operator-(const Vector2<T2> r) const
{
	return Vector2<T>(x - r.x, y - r.y);
}

template <typename T>
template <typename T2>
Vector2<T> Vector2<T>::operator*(Vector2<T2> r) const
{
	return Vector2<T>(x * r.x, y * r.y);
}

template <typename T>
Vector2<int> Vector2<T>::operator%(Vector2<int> r) const
{
	return Vector2<int>(((int)x % r.x + r.x) % r.x, ((int)y % r.y + r.y) % r.y);
}

template <typename T>
Vector2<float> Vector2<T>::operator%(Vector2<float> r) const
{
	return Vector2<float>(std::fmod((std::fmod(x, r.x) + r.x), r.x), std::fmod((std::fmod(y, r.y) + r.y), r.y));
}

template <typename T>
void Vector2<T>::operator+=(const Vector2 r)
{
	x += r.x;
	y += r.y;
}

template <typename T>
void Vector2<T>::operator-=(const Vector2 r)
{
	x -= r.x;
	y -= r.y;
}

template <typename T>
Vector2<T> Vector2<T>::normalize()
{
	if (absolute() == 0)
	{
		return (Vector2<T>(0, 0));
	}
	return Vector2<T>(x, y) / Vector2<T>(x, y).absolute();
}

template <typename T>
Vector2<T> Vector2<T>::rotate(double a)
{
	return Vector2(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
}

template <typename T>
double Vector2<T>::get_angle()
{
	return atan2(x, y);
}

template <typename T>
void Vector2<T>::set(T _x, T _y)
{
	x = _x;
	y = _y;
}

template <typename T>
void Vector2<T>::set(Vector2 p)
{
	x = p.x;
	y = p.y;
}

template <typename T>
double Vector2<T>::absolute()
{
	return sqrt(x * x + y * y);
}

#endif