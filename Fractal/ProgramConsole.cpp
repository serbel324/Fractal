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

void Program::console()
{
	if (updating)
	{
		return;
	}

	auto lambda = [this]()
	{
		console_thread();
	};

	std::thread thread(lambda);
	thread.detach();
}

void Program::console_thread()
{
	std::string command_line;
	std::stringstream splitter;

	std::string param;

	while (true)
	{
		std::cout << ">";
		splitter.clear();
		std::getline(std::cin, command_line);
		splitter << command_line;

		while (splitter >> param)
		{
			if (param == "get")
			{
				splitter >> param;

				if (param == "pos")
				{
					std::cout << std::setprecision(20) << "x = " << position.x << " y = " << position.y << std::endl;
				}
				if (param == "scale")
				{
					std::cout << std::setprecision(20)  << "scale = " << scale << std::endl;
				}
				else if (param == "itnum")
				{
					std::cout << iterations << std::endl;
				}
				else if (param == "phase")
				{
					std::cout << "H = " << phase.r << " S = " << phase.g << " V = " << phase.b << std::endl;
				}
				else if (param == "period")
				{
					std::cout << "H = " << period.r << " S = " << period.g << " V = " << period.b << std::endl;
				}
			}
			else if (param == "set")
			{
				splitter >> param;

				if (param == "pos")
				{
					safe_input_ld(splitter, position.x);
					safe_input_ld(splitter, position.y);
				}
				else if (param == "scale")
				{
					safe_input_d(splitter, scale);
				}
				else if (param == "itnum")
				{
					safe_input_i(splitter, iterations);
				}
				else if (param == "phase")
				{
					safe_input_f(splitter, phase.r);
					safe_input_f(splitter, phase.g);
					safe_input_f(splitter, phase.b);
				}
				else if (param == "period")
				{
					safe_input_f(splitter, period.r);
					safe_input_f(splitter, period.g);
					safe_input_f(splitter, period.b);
				}
			}			
			else if (param == "draw")
			{
				draw_fractal(&fractal, &fractal_image, &fractal_texture, screen_size, phase, period);
			}			
			else if (param == "update")
			{
				update_fractal(screen_size, position, scale, iterations, &fractal, &fractal_image, &fractal_texture, phase, period);
			}
			else if (param == "save")
			{
				param = "";
				splitter >> param;

				if (param == "")
				{
					save_to_file();
				}
				else
				{
					save_to_file(param);
				}
			}
			else if (param == "restart")
			{
				restart();
			}
			else if (param == "kill")
			{
				exit(0);
			}
			else if (param == "help")
			{
				std::cout << "------------------" << std::endl;
				std::ifstream txt("console_help.txt");
				std::string s;

				std::getline(txt, s);
				while (txt)
				{
					std::cout << s << std::endl;
					std::getline(txt, s);
				}
				std::cout << "------------------" << std::endl;
			}
			else
			{
				std::cout << "wrong command" << std::endl;
			}
		}
		std::cout << std::endl;
	}
}

void Program::close()
{
	main_window->close();
	exit(0);
}

void Program::safe_input_ld(std::stringstream& in, long double& param)
{
	std::string s;
	in >> s;

	if (s != "~")
	{
		param = stold(s);
	}
}
void Program::safe_input_f(std::stringstream& in, float& param)
{
	std::string s;
	in >> s;

	if (s != "~")
	{
		param = stof(s);
	}
}
void Program::safe_input_i(std::stringstream& in, int& param)
{
	std::string s;
	in >> s;

	if (s != "~")
	{
		param = stoi(s);
	}
}
void Program::safe_input_d(std::stringstream& in, double& param)
{
	std::string s;
	in >> s;

	if (s != "~")
	{
		param = stod(s);
	}
}