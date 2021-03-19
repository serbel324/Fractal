#ifndef __EXTMATH_H__
#define __EXTMATH_H__

#include "Vector2.h"
#include "Color.h"
#include "Complex.h"
#include <vector>

struct ExtMath
{
public:
	static int get_random_int(int min, int max);
	static double to_radian(double a);
	static double to_degrees(double a);
	static float get_random(float min, float max);
	static float waverage(float a1, float p1, float a2, float p2);

	static float hypot(float a1, float a2);
	static float hypot(float x1, float y1, float x2, float y2);
	static double sigmoid(float x, float a);
	static int sign(double a);

	static Complex comp_sin(Complex& r);
	static Complex pow(Complex& r, const int& n);

	template <typename T>
	static float get_angle(Vector2<T> v);
	template <typename T>
	static float get_angle(Vector2<T> v1, Vector2<T> v2);

	template <typename T>
	static T dot_prod(Vector2<T> v1, Vector2<T> v2);
	template <typename T>
	static T cross_prod(Vector2<T> v1, Vector2<T> v2);

	static Color get_random_color();

	static std::vector<Vector2<int>> directions;
	static std::vector<Vector2<int>> reflections;
	static double PI;
};

#endif