#include "Camera.h"

Camera::Camera(float x, float y, float a, float s)
{
	position = Vector2<float>(x, y);
	angle = a;
	scale = s;
}

Camera::Camera(Vector2<float> pos, float a, float s)
{
	position = Vector2<float>(pos);
	angle = a;
	scale = s;
}
