#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <iostream>

template <typename T>
struct Vector2
{
	Vector2();
	Vector2(T _x);
	Vector2(T _x, T _y);

	Vector2 operator*(double r) const;
	Vector2 operator/(double r) const;

	template <typename T2>
	Vector2 operator+(const Vector2<T2> r) const;
	template <typename T2>
	Vector2 operator-(const Vector2<T2> r) const;
	template <typename T2>
	Vector2<T> operator*(Vector2<T2> r) const;

	Vector2<int> operator%(Vector2<int> r) const;
	Vector2<float> operator%(Vector2<float> r) const;
	
	void operator+=(const Vector2 r);
	void operator-=(const Vector2 r);

	operator Vector2<int>() { return Vector2<int>(x, y); };
	operator Vector2<float>() { return Vector2<float>(x, y); };
	operator Vector2<double>() { return Vector2<int>(x, y); };

	Vector2 normalize();
	Vector2 rotate(double a);
	double get_angle();
	double absolute();

	void set(T _x, T _y);
	void set(Vector2 p);
	T x, y;
};

#include "Vector2.cpp"
#endif // __VECTOR_2_H__