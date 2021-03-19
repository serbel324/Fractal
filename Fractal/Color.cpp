#include "Color.h"
#include <cmath>
#include <algorithm>


Color::Color()
{
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 255;
}

Color::Color(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}
Color::Color(float _a)
{
	r = _a;
	g = _a;
	b = _a;
	a = 255;
}
Color::Color(float _r, float _g, float _b)
{
	r = _r;
	g = _g;
	b = _b;
	a = 255;
}


Color::~Color()
{
}

Color Color::operator+(const Color& right) const
{
	float red = r + right.r;
	float green = g + right.g;
	float blue = b + right.b;
	return Color(red, green, blue, a);
}

Color Color::operator+(const float right) const
{
	float red = r + right;
	float green = g + right;
	float blue = b + right;
	return Color(red, green, blue, a);
}

Color Color::operator-(const Color& right) const
{
	float red = r - right.r;
	float green = g - right.g;
	float blue = b - right.b;
	return Color(red, green, blue, a);
}

Color Color::operator-(const float right) const
{
	float red = r - right;
	float green = g - right;
	float blue = b - right;
	return Color(red, green, blue, a);
}

Color Color::operator*(const float right) const
{
	return Color(r * right, g * right, b * right, a);
}

Color Color::operator>>(const Color& right) const
{
	return Color((r + right.r) / 2, (g + right.g) / 2, (b + right.b) / 2, (a + right.a) / 2);
}

Color Color::to_rgb()
{
	double h = r;
	double s = g;
	double v = b;

	/**/
	if (s < 2)
	{
		float a = v * 2.55;
		return(Color(a));
	}
	/**/
	int hi = ((int)h / 60) % 6;
	double vmin = (100 - s) * v / 100;

	double a = (v - vmin) * fmod(h, 60) / 60;
	double vinc = vmin + a;
	double vdec = v - a;

	v *= 2.55;
	vmin *= 2.55;
	vinc *= 2.55;
	vdec *= 2.55;

	switch (hi)
	{
	case 0:
		return Color(v, vinc, vmin);
		break;
	case 1:
		return Color(vdec, v, vmin);
		break;
	case 2:
		return Color(vmin, v, vinc);
		break;
	case 3:
		return Color(vmin, vdec, v);
		break;
	case 4:
		return Color(vinc, vmin, v);
		break;
	case 5:
		return Color(v, vmin, vdec);
		break;
	}

	return Color(0, 0, 0);
}

Color Color::to_hsv()
{
	double r1 = r / 255;
	double g1 = g / 255;
	double b1 = b / 255;

	double h, s, v;

	double max = std::max({ r1, g1, b1 });
	double min = std::min({ r1, g1, b1 });

	if (max == r1 && g1 >= b1)
	{
		h = 60 * (g1 - b1) / (max - min);
	}
	else if (max == r1 && g1 < b1)
	{
		h = 60 * (g1 - b1) / (max - min) + 360;
	}
	else if (max == g1)
	{
		h = 60 * (b1 - r1) / (max - min) + 120;
	}
	else if (max == b1)
	{
		h = 60 * (r1 - g1) / (max - min) + 240;
	}

	if (max == 0)
	{
		s = 0;
	}
	else
	{
		s = 1 - min / max;
	}

	v = max;

	return Color(h, s * 100, v * 100);
}
