#include "simulation.h"
#include "window.h"
#include "body.h"

#include <SFML/System.hpp>

#include <iostream>

int Simulation::TPS = 180;
bool Simulation::running = true;
bool Simulation::paused = false;

Simulation::Simulation() {}

void Simulation::run() {

	while(Simulation::running) {

		sf::Clock runTime;
		if(!Simulation::paused) {
			this->tick();
		}

		int sleepTime = 1000 / Simulation::TPS;
		this->deltaTime = runTime.getElapsedTime().asMilliseconds();
		sf::sleep(sf::milliseconds(sleepTime) - sf::milliseconds(this->deltaTime));
	}
}

void Simulation::tick() {
	BodyManager::tick();
}
