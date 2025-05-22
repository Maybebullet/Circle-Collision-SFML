#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

#include "SFML/Graphics.hpp"

extern Renderer* App;

class Collision
{
public:
	Collision()
	{
		circle_Entities.reserve(20000);
		clock2.restart();
	}
//values

	void createcircle(sf::Vector2f position)
	{
		sf::CircleShape* circle = new sf::CircleShape(circle_radius);
		//std::shared_ptr<sf::CircleShape> circle = std::make_shared<sf::CircleShape>(20.0f);

		circle->setOrigin(circle->getRadius(), circle->getRadius());
		circle->setPosition(position);

		circle->setFillColor(sf::Color::Transparent);
		circle->setOutlineThickness(-4.0f);
		circle->setOutlineColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

		addentities(circle);
		//updateCollision();

	}

	void updateCollision()
	{
		//clock2.restart();
		//static float elapsedtime = 0.0f;
		static float elapsedtime2 = 0.0f;
		static size_t fps = 0;
		//while (true)
		
			float el = clock2.restart().asSeconds();
			//elapsedtime += el;
			elapsedtime2 += el;

			//if (elapsedtime > 0.0167f)
				
				if (elapsedtime2 > 1.0f)
				{
					elapsedtime2 -= 1.0f;
					std::cout << "Simulation Rate:  " << fps << '\n';
					//hud->setDebugText(std::to_string(fps));
					fps = 0;
				}
				fps++;


				//elapsedtime -= 0.01666f;

				for (auto& i : circle_Entities)
				{
					sf::Vector2f pos = i->getPosition();
					if (pos.x < 0.0f)
						i->setPosition(0.0f, i->getPosition().y); //get new position
					else if (pos.x > App->getWindowX())
						i->setPosition(App->getWindowX(), i->getPosition().y);
					if (pos.y < 0.0f)
						i->setPosition(i->getPosition().x, 0.0f);
					else if (pos.y > App->getWindowY())
						i->setPosition(i->getPosition().x, App->getWindowY());

					for (auto& o : circle_Entities)
					{
						if (i == o)
							continue;
						float _x = i->getPosition().x - o->getPosition().x;
						float _y = i->getPosition().y - o->getPosition().y;

						float i_radius = i->getRadius();
						float o_radius = o->getRadius();

						float distance = sqrtf(abs(_x * _x) + abs(_y * _y));

						if (distance < i_radius + o_radius)
						{
							float overlap = 0.5 * ((i_radius + o_radius) - distance);
							float x_move = overlap * _x / distance;
							float y_move = overlap * _y / distance;

							i->move(x_move, y_move);
							o->move(-x_move, -y_move);

						}

					}

				}
			
		
		

	}//end

	sf::CircleShape* mouseCapture(sf::Vector2f mouseposition)
	{
		for (auto& i : circle_Entities)
		{
			float _x = fabsf(i->getPosition().x - mouseposition.x);
			float _y = fabsf(i->getPosition().y - mouseposition.y);
			float distance = _x * _x + _y * _y;

			if (sqrt(distance) < i -> getRadius())
				return i;

		}
		return nullptr;

	}

	void setCircleRadius(float radius)
	{
		circle_radius = radius;
	}

	

	std::vector<sf::CircleShape*> circle_Entities;

private:

	sf::Clock clock2;
	static inline float circle_radius;

	void addentities(auto*& entity)
	{
		circle_Entities.push_back(entity);
		App->drawables.push_back(entity);
	}


	
};

