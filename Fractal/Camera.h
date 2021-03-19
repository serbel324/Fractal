#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Vector2.h"

class Camera
{
public:
	Camera(float x, float y, float a, float s);
	Camera(Vector2<float> pos, float a, float s);
	Vector2<float> position;
	float angle, scale;
};

#endif