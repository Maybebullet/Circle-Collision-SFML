#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow* _window):
	window(_window),
	ev(),
	running(true)
{	
	//window->setActive(true);
	//threading = std::async(std::launch::async, &Renderer::render, this);
}

Renderer::Renderer() :
	ev(),
	running(true),
	window(new sf::RenderWindow(sf::VideoMode(800, 600), "Test"))
{

}

Renderer::~Renderer()
{
	delete window;

}


void Renderer::renderloop()
{
	sf::Font font;
	font.loadFromFile("assets/arial.ttf");
	sf::Text text("", font, 12);

	float ballsize;
	std::cout << "Select Ball(s) size:\t" << std::endl;
	std::cin >> ballsize;
	std::cout << "Press any key to reset\nFps: \n";


	while (running)
	{
		window->clear();

		while (window->pollEvent(ev))
		{
			switch (ev.type)
			{
				case sf::Event::Closed:
					running = false;
				case sf::Event::KeyPressed:
					clearvector();

			}


		}


		//fps counter
		static float timesincelastupdate = 0.0f;
		static unsigned int fps = 0;
		fps++;
		timesincelastupdate += clock.restart().asSeconds();
		if (timesincelastupdate > 1.0f)
		{
			timesincelastupdate -= 1.0f;
			std::cout << fps << std::endl;
			fps = 0;
		}//

		//std::shared_ptr<sf::CircleShape> circle =  std::make_shared<sf::CircleShape>();
		sf::CircleShape* circle = new sf::CircleShape(ballsize);
		circle->setOrigin(sf::Vector2f(ballsize, ballsize));
		circle->setPosition(sf::Vector2f(rand() % 800, rand() % 600));
		circle->setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		drawables.emplace_back(circle);

		text.setString("Sprites: " + std::to_string(drawables.size()));

		for (auto& a : drawables)
		{
			window->draw(*a);
		}

		window->draw(text);
		window->display();
	}


}


void Renderer::clearvector()
{
	for (auto& a : drawables)
	{
		delete a;
	}
	drawables.clear();

}