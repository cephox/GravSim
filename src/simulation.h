#pragma once

#include "camera.h"
#include <SFML/System/Clock.hpp>

class Simulation {
private:
	int deltaTime;
public:
	static int TPS;
	static bool running;
	static bool paused;

	Camera camera;

	Simulation();
	void run();
	void tick();
};
