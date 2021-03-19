#pragma once

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "Graphics.h"
#include "Complex.h"
#include "Color.h"
#include "Vector2.h"

#include <vector>
#include <sstream>

typedef std::vector<std::vector<float>> vector2df;

class Program
{
public:
	Program();

private:
	void SFML_init();
	void events();

	void main_loop();

	void config();
	void config_color();

	void update_fractal(Vector2<int> size, Vector2<long double> pos, long double scale, int iterations,
						vector2df* fractal, sf::Image* img, sf::Texture* tex, Color phase, Color period);

	void update_fractal_thread(Vector2<int> size, Vector2<long double> pos, long double scale, int iterations,
							   vector2df* fractal, sf::Image* img, sf::Texture* tex, Color phase, Color period);
	void render();
	void render_thread();
	void render_cursor(float color);

	void restart();

	void save_to_file();
	void save_to_file(std::string path);

	void update_in_high_quality();

	void draw_fractal(vector2df* fractal, sf::Image* img, sf::Texture* tex, Vector2<int> size, Color phase, Color period);

	void update_color_params();

	void console();
	void console_thread();

	void close();

	void safe_input_f(std::stringstream& in, float& param);
	void safe_input_i(std::stringstream& in, int& param);
	void safe_input_d(std::stringstream& in, double& param);
	void safe_input_ld(std::stringstream& in, long double& param);

	Graphics* gr;
	sf::RenderWindow* main_window;

	std::vector<std::vector<float>> fractal;

	std::string save_directory;
	
	std::vector<bool> color_keys;

	Vector2<int> screen_size;
	Vector2<float> cursor_pos;

	int coloring_type;

	Color first_color;
	Color second_color;

	float first_color_alt;
	float second_color_alt;

	Color phase;
	Color period;

	sf::Image fractal_image; 
	sf::Texture fractal_texture;

	bool updated;
	bool updating;

	bool animation;

	int iterations;
	int high_quality_iterations;

	int progress;
	int fractal_size;

	int pow;

	double scale;
	double scale_step;

	Vector2<long double> position;

	double lim;

	double color_step;
};

#endif

