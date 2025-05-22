#pragma once

#include "SFML/Window.hpp"

#include "func.h"

extern Collision* collision;


class Simulation
{
public:
	Simulation()
	{


	}

	void simulate()
	{
		while (true)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
			}

		}
	}//end

};

