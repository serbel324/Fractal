#include "Program.h"
#include "ExtMath.h"

#include <SFML/System.hpp>
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

Program::Program()
{
	screen_size = Vector2<int>(800, 800);

	SFML_init();
	
	gr = new Graphics(main_window, screen_size);
	Camera main_cam = Camera(Vector2<float>(), 0, 1);
	gr->apply_camera(&main_cam);
	gr->set_active(false);

	console();
	render();

	restart();

	main_loop();

	exit(0);
}

void Program::events()
{
	sf::Event e;
	while (main_window->pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			close();
			break;
		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
			case sf::Keyboard::Escape:		
				close();
				break;

			case sf::Keyboard::R:				
				if (!updating)
				{
					restart();
				}
				break;

			case sf::Keyboard::S:
				save_to_file();
				break;

			case sf::Keyboard::Q:
				update_in_high_quality();
				break;

			case sf::Keyboard::U:
				color_keys[0] = 1;
				break;
			case sf::Keyboard::I:
				color_keys[1] = 1;
				break;
			case sf::Keyboard::O:
				color_keys[2] = 1;
				break;
			case sf::Keyboard::J:
				color_keys[3] = 1;
				break;
			case sf::Keyboard::K:
				color_keys[4] = 1;
				break;
			case sf::Keyboard::L:
				color_keys[5] = 1;
				break;
			case sf::Keyboard::LShift:
				color_keys[6] = 1;
				break;
			}
			break;
		case sf::Event::KeyReleased:
			switch (e.key.code)
			{
			case sf::Keyboard::U:
				color_keys[0] = 0;
				break;
			case sf::Keyboard::I:
				color_keys[1] = 0;
				break;
			case sf::Keyboard::O:
				color_keys[2] = 0;
				break;
			case sf::Keyboard::J:
				color_keys[3] = 0;
				break;
			case sf::Keyboard::K:
				color_keys[4] = 0;
				break;
			case sf::Keyboard::L:
				color_keys[5] = 0;
				break;
			case sf::Keyboard::LShift:
				color_keys[6] = 0;
				break;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				if (!updating)
				{
					position.x = cursor_pos.x * 1. / scale + position.x;
					position.y = cursor_pos.y * 1. / scale + position.y;

					scale *= scale_step;

					update_fractal(screen_size, position, scale, iterations, &fractal, &fractal_image, &fractal_texture, phase, period);
				}
			}
			else if (e.mouseButton.button == sf::Mouse::Right)
			{
				if (!updating)
				{
					position.x = cursor_pos.x * 1. / scale + position.x;
					position.y = cursor_pos.y * 1. / scale + position.y;

					scale /= scale_step;

					update_fractal(screen_size, position, scale, iterations, &fractal, &fractal_image, &fractal_texture, phase, period);
				}
			}
			break;
		case sf::Event::MouseMoved:
			if (true)
			{
				sf::Vector2i mp = sf::Mouse::getPosition(*main_window);
				cursor_pos = Vector2<float>(mp.x - screen_size.x / 2, mp.y - screen_size.y / 2);
			}
			break;
		case sf::Event::MouseWheelMoved:
			scale_step *= 1 + 0.2 * ExtMath::sign(e.mouseWheel.delta);

			if (scale_step < 1)
			{
				scale_step = 1;
			}
			if (scale_step > 100)
			{
				scale_step = 100;
			}
			break;
		}
	}
}

void Program::main_loop()
{
	while (main_window->isOpen()) 
	{
		events();
		if (!updating)
		{
			update_color_params();
		}
	}
}

void Program::render()
{
	std::thread thread([this]() { render_thread(); });
	thread.detach();
}

void Program::render_thread()
{
	if (animation)
	{
		return;
	}

	gr->set_active(true);

	float cursor_color = 0;
	float cursor_color_step = 1;

	while (true)
	{
		if (updated)
		{
			updated = false;
		}

		gr->draw_texture(fractal_texture, Vector2<float>(0, 0), screen_size);

		render_cursor(cursor_color);
		cursor_color += cursor_color_step;
		if (cursor_color >= 255 || cursor_color <= 0)
		{
			cursor_color_step *= -1;
		}

		gr->present();
	}

	gr->set_active(false);
}

void Program::render_cursor(float color)
{
	float circle_radius = 4;
	float orbit_size = 20;
	float phase_step = 0.02;


	if (updating)
	{
		for (float i = 0; i < progress * 1. / fractal_size; i += phase_step)
		{
			float a = i * 2. * ExtMath::PI;

			Vector2<float> p(orbit_size * cos(a), orbit_size * sin(a));
			gr->set_fill_color(color);
			gr->draw_circle(p + cursor_pos, circle_radius);
		}
	}
	else
	{

		std::vector<Vector2<float>> sel;
		sel.push_back(Vector2<float>(cursor_pos.x - screen_size.x / 2 / scale_step, cursor_pos.y - screen_size.y / 2 / scale_step));
		sel.push_back(Vector2<float>(cursor_pos.x + screen_size.x / 2 / scale_step, cursor_pos.y - screen_size.y / 2 / scale_step));
		sel.push_back(Vector2<float>(cursor_pos.x + screen_size.x / 2 / scale_step, cursor_pos.y + screen_size.y / 2 / scale_step));
		sel.push_back(Vector2<float>(cursor_pos.x - screen_size.x / 2 / scale_step, cursor_pos.y + screen_size.y / 2 / scale_step));
		sel.push_back(Vector2<float>(cursor_pos.x - screen_size.x / 2 / scale_step, cursor_pos.y - screen_size.y / 2 / scale_step));

		gr->set_fill_color(0);
		gr->draw_broken_line(sel, Vector2<float>(1, 1), 1);
		gr->draw_rect(cursor_pos.x + 1, cursor_pos.y + 1, 2, 2);

		gr->set_fill_color(255);
		gr->draw_broken_line(sel, Vector2<float>(0, 0), 1);
		gr->draw_rect(cursor_pos.x, cursor_pos.y, 2, 2);
	}
}

void Program::restart()
{
	config();
	update_fractal(screen_size, position, scale, iterations, &fractal, &fractal_image, &fractal_texture, phase, period);
}

void Program::save_to_file()
{
	if (!updating)
	{
		std::string file_name = save_directory + "fractal";
		for (int pic_name = 0; pic_name < 9999; pic_name++)
		{
			file_name = "screenshots/fractal" + std::to_string(pic_name) + ".png";
			if (!std::ifstream(file_name))
			{
				break;
			}
		}
		if (!fractal_image.saveToFile(file_name))
		{
			std::cout << "FILE SAVING ERROR" << std::endl;
		}
	}
}

void Program::save_to_file(std::string path)
{
	std::string file_name = save_directory + path + ".png";
	if (!fractal_image.saveToFile(file_name))
	{
		std::cout << "FILE SAVING ERROR" << std::endl;
	}
}

void Program::update_in_high_quality()
{
	update_fractal(screen_size, position, scale, high_quality_iterations, &fractal, &fractal_image, &fractal_texture, phase, period);
}

void Program::config()
{
	std::string path = "param.cnfg";
	std::ifstream fin(path);

	std::string param;
	fin >> param;

	save_directory = "screenshots/";

	iterations = 1000;
	high_quality_iterations = 10000;
	pow = 2;
	scale = 100;
	scale_step = 5;
	position.x = 0;
	position.y = 0;

	lim = 2;
	color_step = -1;

	coloring_type = 0;
	first_color = Color(255, 255, 0);
	second_color = Color(0, 0, 255);

	first_color_alt = 0;
	second_color_alt = 180;

	cursor_pos = Vector2<float>(0, 0);

	fractal_image.create(screen_size.x, screen_size.y, sf::Color::Black);
	fractal.assign(screen_size.y, std::vector<float>(screen_size.x, 0));
	main_window->setMouseCursorVisible(false);

	fractal_size = screen_size.x * screen_size.y;
	progress = 0;

	animation = 0;

	while (fin)
	{
		if (param == "ITERATIONS")
		{
			fin >> iterations;
		}
		if (param == "HIGH_QUALITY_ITERATIONS")
		{
			fin >> high_quality_iterations;
		}
		else if (param == "SCALE")
		{
			fin >> scale;
		}
		else if (param == "POW")
		{
			fin >> pow;
		}
		else if (param == "X")
		{
			fin >> position.x;
		}
		else if (param == "Y")
		{
			fin >> position.y;
		}
		else if (param == "LIM")
		{
			fin >> lim;
		}
		else if (param == "COLOR_STEP")
		{
			fin >> color_step;
		}
		else if (param == "SCALE_STEP")
		{
			fin >> scale_step;
		}
		else if (param == "COLORING_TYPE")
		{
			fin >> coloring_type;
		}
		else if (param == "FIRST_COLOR")
		{
			if (coloring_type == 0)
			{
				fin >> first_color.r >> first_color.g >> first_color.b;
			}
			else if (coloring_type == 1)
			{
				fin >> first_color_alt;
			}
		}
		else if (param == "SECOND_COLOR")
		{
			if (coloring_type == 0)
			{
				fin >> second_color.r >> second_color.g >> second_color.b;
			}
			else if (coloring_type == 1)
			{
				fin >> second_color_alt;
			}
		}
		else if (param == "END")
		{
			break;
		}

		fin >> param;
	}

	if (color_step == -1)
	{
		color_step = iterations;
	}
	
	config_color();

	updating = false;
	updated = true;
}

void Program::config_color()
{
	color_keys = std::vector<bool>(6, 0);
	phase = Color(0); 

	if (coloring_type == 2)
	{
		std::string colpath = "color_param.cnfg";
		std::ifstream colfin(colpath);

		std::string param;

		colfin >> param;

		phase = Color(0);

		period = Color(100);

		while (colfin)
		{
			if (param == "H_PHASE")
			{
				colfin >> phase.r;
			}
			else if (param == "S_PHASE")
			{
				colfin >> phase.g;
			}
			else if (param == "V_PHASE")
			{
				colfin >> phase.b;
			}
			else if (param == "H_PERIOD")
			{
				colfin >> period.r;
			}
			else if (param == "S_PERIOD")
			{
				colfin >> period.g;
			}
			else if (param == "V_PERIOD")
			{
				colfin >> period.b;
			}
			else if (param == "END")
			{
				break;
			}
			colfin >> param;
		}
	}
}
