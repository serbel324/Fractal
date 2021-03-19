#include "Program.h"
#include "ExtMath.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <algorithm>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#include <thread>
#include <functional>

void Program::SFML_init()
{
	std::string path = "screen.cnfg";
	std::ifstream fin(path);

	fin >> screen_size.x >> screen_size.y;

	main_window = new sf::RenderWindow(sf::VideoMode(screen_size.x, screen_size.y), "Radiant Fractal", sf::Style::Close);
}

void Program::draw_fractal(vector2df* fractal, sf::Image* img, sf::Texture* tex, Vector2<int> size, Color phase, Color period)
{
	for (double i = 0; i < size.y; i++)
	{
		for (double j = 0; j < size.x; j++)
		{
			double b = (*fractal)[i][j];
			Color col(0);
			if (b == 0)
			{
				col = Color(0);
			}
			else
			{
				double r = b;
				if (coloring_type == 0)
				{
					r /= color_step;
					col = first_color * r + second_color * (1 - r);
				}
				else if (coloring_type == 1)
				{
					r /= color_step;

					float rr = r - (int)r;
					if ((int)r % 2)
					{
						col = Color(first_color_alt, 100 * rr, 100 - 100 * rr).to_rgb();
					}
					else
					{
						col = Color(second_color_alt, 100 - 100 * rr, 100 * rr).to_rgb();
					}
				}
				else if (coloring_type == 2)
				{
					float h = std::sin(r * 2 * ExtMath::PI / period.r + phase.r) * 360 / 2 + 360 / 2;
					float s = std::sin(r * 2 * ExtMath::PI / period.g + phase.g) * 100 / 2 + 100 / 2;
					float v = std::sin(r * 2 * ExtMath::PI / period.b + phase.b) * 100 / 2 + 100 / 2;
					col = Color(h, s, v).to_rgb();
				}
			}

			sf::Color color(col.r, col.g, col.b);
			img->setPixel(j, i, color);
		}
	}

	tex->loadFromImage(*img);
	updated = true;
}

void Program::update_color_params()
{
	animation = 0;

	if ((color_keys[0] - color_keys[3] != 0) || (color_keys[1] - color_keys[4] != 0) || (color_keys[2] - color_keys[5] != 0))
	{

		float h_phase_change_speed = 0.1;
		float s_phase_change_speed = 0.1;
		float v_phase_change_speed = 0.1;

		float h_period_change_speed = 1;
		float s_period_change_speed = 1;
		float v_period_change_speed = 1;

		if (color_keys[6] == 0)
		{
			phase.r += h_phase_change_speed * (color_keys[0] - color_keys[3]);
			phase.g += s_phase_change_speed * (color_keys[1] - color_keys[4]);
			phase.b += v_phase_change_speed * (color_keys[2] - color_keys[5]);

			phase.r = fmod(phase.r, 2 * ExtMath::PI);
			phase.g = fmod(phase.g, 2 * ExtMath::PI);
			phase.b = fmod(phase.b, 2 * ExtMath::PI);
		}
		else
		{
			period.r += (color_keys[0] - color_keys[3]) * h_period_change_speed;
			period.g += (color_keys[1] - color_keys[4]) * s_period_change_speed;
			period.b += (color_keys[2] - color_keys[5]) * v_period_change_speed;

			period.r = std::max(period.r, 1.f);
			period.g = std::max(period.g, 1.f);
			period.b = std::max(period.b, 1.f);
		}

		draw_fractal(&fractal, &fractal_image, &fractal_texture, screen_size, phase, period);
		updated = true;
	}
	
	animation = true;
}

void Program::update_fractal(Vector2<int> size, Vector2<long double> pos, long double scale, int iterations,
	vector2df * fractal, sf::Image * img, sf::Texture* tex, Color phase, Color period)
{
	if (updating)
	{
		return;
	}

	auto lambda = [this, size, pos, scale, iterations, img, fractal, phase, tex, period]()
	{
		update_fractal_thread(size, pos, scale, iterations, fractal, img, tex, phase, period);
	};

	std::thread update_thread(lambda);
	update_thread.detach();
}

void Program::update_fractal_thread(Vector2<int> size, Vector2<long double> pos, long double scale, int iterations,
	vector2df * fractal, sf::Image * img, sf::Texture* tex, Color phase, Color period)
{
	Color col(0);
	updated = false;
	updating = true;

	progress = 0;

	for (int i = -size.y / 2; i < size.y / 2; i++)
	{
		for (int j = -size.x / 2; j < size.x / 2; j++)
		{
			double x = 1. * j / scale + pos.x;
			double y = 1. * i / scale + pos.y;

			Complex z;
			Complex c(x, y);

			int b = 0;

			for (int k = 1; k <= iterations; k++)
			{
				z = ExtMath::pow(z, pow) + c;
				if (z > lim)
				{
					b = k;
					break;
				}
			}

			(*fractal)[(int)(i + size.y / 2)][(int)(j + size.x / 2)] = b;
			progress++;
		}
	}


	draw_fractal(fractal, img, tex, size, phase, period);

	updating = false;
}