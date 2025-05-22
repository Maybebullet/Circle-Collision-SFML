#pragma once

#include <iostream>
#include <chrono>
#include <thread>

#include "func.h"

extern Renderer* App;

using namespace std::chrono_literals;

class Hud
{
public:
	Hud():
		cachedfps(0),
		elapsedtime(0.0f)
	{
		font_arial.loadFromFile("assets/arial.ttf");
		text = new sf::Text("", font_arial, 14);
		App->huddrawables.emplace_back(text);
	}//

	void debug()
	{
		

		//std::this_thread::sleep_for(1000ms);
		while (true)
		{
			std::this_thread::sleep_for(300ms);
			std::cout << std::round(cachedfps / elapsedtime) << '\n';
			text->setString(std::to_string(std::round(cachedfps / elapsedtime)));
			elapsedtime = 0.0f;
			cachedfps = 0;

		}
	}//

	unsigned int cachedfps = 0;
	float elapsedtime = 0.0f;

	void setDebugText(std::string string)
	{
		text->setString(string);
	}


private:

	sf::Text* text;
	sf::Font font_arial;
};

