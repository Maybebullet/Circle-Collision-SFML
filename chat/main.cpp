#include <iostream>
#include <future>

#include "func.h"

Renderer* App = new Renderer();
Hud* hud = new Hud();
Collision* collision = new Collision();
Simulation* simulation = new Simulation();

int main()
{
	//std::future <void> th = std::async(std::launch::async, &Hud::debug, hud);
	//std::future <void> test2 = std::async(std::launch::async, &Simulation::simulate, simulation);
	//std::future <void> col = std::async(std::launch::async, &Collision::updateCollision, collision);




	App -> renderloop();
	return 0;
}
