#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Vector2.h"
#include "Color.h"
#include "Camera.h"
#include <string>
#include <SFML/Graphics.hpp>

class Graphics
{
public:
	Graphics(sf::RenderWindow* win, Vector2<int> ws);
	Graphics(sf::RenderWindow* win, Vector2<int> ws, Camera* cam);

	void draw_point(Vector2<float> pos);
	void draw_point(float x, float y);

	void draw_circle(float x, float y, float radius);
	void draw_circle(Vector2<float> pos, float radius);

	void draw_broken_line(std::vector<Vector2<float>> t, Vector2<float> a, float s);

	void draw_line(Vector2<float> v1, Vector2<float> v2);
	void draw_line(float x1, float y1, float x2, float y2);

	void draw_rect(float x, float y, float w, float h);
	void draw_rect(Vector2<float> pos, Vector2<float> size);

	void draw_texture(sf::Texture& tex, float x, float y, float w, float h);
	void draw_texture(sf::Texture& tex, Vector2<float> pos, Vector2<float> size);
	void draw_texture(sf::Texture& tex, Vector2<float> pos, Vector2<float> size, float a);

	void present();

	void set_fill_color(float r, float g, float b, float a);
	void set_fill_color(Color col);

	void fill();
	void clear();
	void fill_text(float x, float y, float size, std::string t, std::string f);

	void apply_camera(Camera* cam);

	void set_active(bool b);

	void set_camera(Camera* cam);
	void set_default_camera();

private:
	sf::RenderWindow* window;
	Color fill_color;

	Camera* camera;
	Vector2<int> window_size;
};

#endif