#pragma once

#include "SFML/Graphics.hpp"


class Renderer
{
public:
	Renderer(sf::RenderWindow* _window);
	Renderer();
	~Renderer();

	void renderloop();

	std::vector<sf::Drawable*> drawables;
	std::vector<sf::Text*> huddrawables;

	sf::Clock clock;
	float lastframetime;

	int getWindowX()
	{
		return window->getSize().x;
	}
	int getWindowY()
	{
		return window->getSize().y;
	}

private:

	sf::RenderWindow* window;
	bool running;
	sf::Event ev;

	sf::CircleShape* pointerToCircle = nullptr;

	

};