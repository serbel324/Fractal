#include "Vector2.h"
#include "Graphics.h"
#include "ExtMath.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

Graphics::Graphics(sf::RenderWindow* win, Vector2<int> ws)
{
	window = win;
	fill_color = Color(0, 0, 0, 255);
	window_size = ws;
	set_default_camera();
}

Graphics::Graphics(sf::RenderWindow* win, Vector2<int> ws, Camera* cam)
{
	window = win;
	fill_color = Color(0, 0, 0, 255);
	window_size = ws;
	camera = cam;
}

void Graphics::draw_point(float x, float y)
{
	draw_point(Vector2<float>(x, y));
}
void Graphics::draw_point(Vector2<float> pos)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(1, 1));
	rectangle.setPosition(pos.x, pos.y);

	rectangle.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a));

	window->draw(rectangle);
}

void Graphics::draw_circle(float x, float y, float radius)
{
	draw_circle(Vector2<float>(x, y), radius);
}
void Graphics::draw_circle(Vector2<float> pos, float radius)
{
	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setPosition(pos.x - radius, pos.y - radius);

	circle.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a));

	window->draw(circle);
}

void Graphics::draw_broken_line(std::vector<Vector2<float>> t, Vector2<float> a, float s)
{
	for (int i = 1; i < t.size(); i++)
	{
		draw_line(t[i - 1] * s + a, t[i] * s + a);
	}
}

void Graphics::draw_line(Vector2<float> v1, Vector2<float> v2)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(v1.x, v1.y), sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a)),
		sf::Vertex(sf::Vector2f(v2.x, v2.y), sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a))
	};

	window->draw(line, 2, sf::Lines);
}

void Graphics::draw_line(float x1, float y1, float x2, float y2)
{
	draw_line(Vector2<float>(x1, y1), Vector2<float>(x2, y2));
}


void Graphics::draw_rect(float x, float y, float w, float h)
{
	draw_rect(Vector2<float>(x, y), Vector2<float>(w, h));
}

void Graphics::draw_rect(Vector2<float> pos, Vector2<float> size)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size.x, size.y));
	rectangle.setPosition(pos.x, pos.y);

	rectangle.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a));

	window->draw(rectangle);
}

void Graphics::draw_texture(sf::Texture& tex, float x, float y, float w, float h)
{
	draw_texture(tex, Vector2<float>(x, y), Vector2<float>(w, h));
}

void Graphics::draw_texture(sf::Texture& tex, Vector2<float> pos, Vector2<float> size)
{
	sf::Sprite sprite;
	sprite.setTexture(tex);

	sf::Vector2u s = tex.getSize();

	sprite.setPosition(pos.x - size.x / 2, pos.y - size.y / 2);
	sprite.setScale(size.x / s.x, size.y / s.y);
 	window->draw(sprite);
}

void Graphics::draw_texture(sf::Texture& tex, Vector2<float> pos, Vector2<float> size, float a)
{
	sf::Sprite sprite;
	sprite.setTexture(tex);

	sf::Vector2u s = tex.getSize();

	sprite.setPosition(pos.x - size.x / 2, pos.y - size.y / 2);
	sprite.setScale(size.x / s.x, size.y / s.y);

	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setRotation(ExtMath::to_degrees(a));

	window->draw(sprite);
}

void Graphics::present()
{
	window->display();
}

void Graphics::set_fill_color(float r, float g, float b, float a)
{
	fill_color.r = r;
	fill_color.g = g;
	fill_color.a = b;
	fill_color.a = a;
}

void Graphics::set_fill_color(Color col)
{
	fill_color = col;
}

void Graphics::fill()
{
	Camera* c = new Camera(0, 0, 0, 1);

	apply_camera(c);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	rectangle.setPosition(window_size.x * -0.5, window_size.y * -0.5);

	rectangle.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a));

	window->draw(rectangle);

	apply_camera(camera);
}

void Graphics::clear()
{
	window->clear();
}

void Graphics::fill_text(float x, float y, float size, std::string t, std::string f)
{
	sf::Font font;
	if (!font.loadFromFile(f + ".ttf"))
	{
		return;
	}
	sf::Text text;

	text.setFont(font);
	text.setString(t);
	text.setPosition(x, y);
	text.setCharacterSize(size);
	text.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a));
	window->draw(text);
}

void Graphics::apply_camera(Camera* cam)
{
	sf::View view;
	Vector2<float> p = cam->position - window_size / 2;
	Vector2<float> s = window_size * cam->scale;

	view.reset(sf::FloatRect(p.x, p.y, s.x, s.y));
	view.rotate(cam->angle);
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	window->setView(view);
}

void Graphics::set_active(bool b)
{
	window->setActive(b);
}

void Graphics::set_camera(Camera* cam)
{
	camera = cam;
}

void Graphics::set_default_camera()
{
	camera = new Camera(0, 0, 0, 1);
}
