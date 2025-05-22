#include "Renderer.h"

#include "Collision.h"
#include "func.h"

Renderer::Renderer(sf::RenderWindow* _window):
	window(_window),
	ev(),
	running(true),
	lastframetime(0.0f)
{	
	drawables.reserve(200);
	huddrawables.reserve(30);
}

Renderer::Renderer() :
	ev(),
	running(true),
	lastframetime(0.0f)
{
	int x;
	int y;
	std::cout << "Enter screen width:\n";
	std::cin >> x;
	std::cout << "Enter screen height:\n";
	std::cin >> y;
	std::cout << "Select circle spawning radius\n";
	float c_r;
	std::cin >> c_r;
	collision->setCircleRadius(c_r);


	window = new sf::RenderWindow(sf::VideoMode(x, y), "Test");
	drawables.reserve(200);
	huddrawables.reserve(30);
	//window->setVerticalSyncEnabled(true);
}

Renderer::~Renderer()
{
	delete window;

}


void Renderer::renderloop()
{
	
	while (running)
	{
		window->clear(sf::Color::White);

		while (window->pollEvent(ev))
		{
			switch (ev.type)
			{
				case sf::Event::Closed:
					running = false;
				case sf::Event::KeyPressed:
				{
					if (ev.key.code == sf::Keyboard::P)
						collision->createcircle(sf::Vector2f(rand() % getWindowX(), rand() % getWindowY()));
					if (ev.key.code == sf::Keyboard::O)
					{
						collision->createcircle(sf::Vector2f(sf::Mouse::getPosition(*window)));
					}
				}

				case sf::Event::MouseButtonReleased:
				{
					if (ev.mouseButton.button == sf::Mouse::Button::Right)
					{
						if (pointerToCircle == nullptr)
							pointerToCircle = collision->mouseCapture(sf::Vector2f(sf::Mouse::getPosition(*window)));
						else
							pointerToCircle = nullptr;
					}

				}

				case sf::Event::MouseWheelMoved:
				{
					if (pointerToCircle != nullptr)
					{
						if (ev.mouseWheel.delta == 1)
						{
							pointerToCircle->setRadius(pointerToCircle->getRadius() + 3);
							pointerToCircle->setOrigin(pointerToCircle->getRadius(), pointerToCircle->getRadius());
						}
						else {
							if (ev.mouseWheel.delta == -1 || pointerToCircle->getRadius() >= 3.5f)
							{
								pointerToCircle->setRadius(pointerToCircle->getRadius() - 3);
								pointerToCircle->setOrigin(pointerToCircle->getRadius(), pointerToCircle->getRadius());
							}

						}
					}

				}

			}


		}

		hud->cachedfps++;
		//lastframetime = clock.restart().asSeconds();
		hud->elapsedtime += lastframetime;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			collision->createcircle(sf::Vector2f(sf::Mouse::getPosition(*window)));
		}

		if (pointerToCircle != nullptr)
		{
			pointerToCircle->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));
		}

		collision->updateCollision();
		
		
		for (sf::Drawable*& _1 : drawables)
		{
			window->draw(*_1);
		}

		for (sf::Text*& _2 : huddrawables)
		{
			window->draw(*_2);
		}



		window->display();
	}


}

