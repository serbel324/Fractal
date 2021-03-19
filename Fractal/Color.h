#pragma once
#ifndef __COLOR_H__
#define __COLOR_H__
class Color
{
public:
	Color();
	Color(float _r, float _g, float _b, float _a);
	Color(float _a);
	Color(float _r, float _g, float _b);
	~Color();

	Color operator+ (const Color& right) const;
	Color operator- (const Color& right) const;
	Color operator+ (const float right) const;
	Color operator- (const float right) const;
	Color operator* (const float right) const;
	Color operator>> (const Color& right) const;


	Color to_hsv();
	Color to_rgb();

	float r;
	float g;
	float b;
	float a;
};

#endif