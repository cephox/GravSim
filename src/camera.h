#pragma once

#include "hud.h"

#include <SFML/Graphics.hpp>

#define CAM_FPS 60
#define CAM_MOVEMENT 5

class Camera {
private:
	static const unsigned long renderTime = 1000 / CAM_FPS;
	static sf::ContextSettings settings;
public:
	static int offsetX, offsetY;
	static Hud hud;

	static void render(sf::RenderWindow& window);
	static void init();
};
