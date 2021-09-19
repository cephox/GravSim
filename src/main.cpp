#include "simulation.h"
#include "window.h"
#include "body.h"
#include "vec2.h"

#include <SFML/System/Thread.hpp>
#include <iostream>

int main() {

	BodyManager::resetBodies();

	Simulation simulation;
	sf::Thread simulationThread(&Simulation::run, &simulation);
	simulationThread.launch();

	sf::Thread windowThread(&windowLoop);
	windowThread.launch();

	windowThread.wait();
	simulationThread.wait();
	return 0;
}
