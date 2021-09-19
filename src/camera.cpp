#include "camera.h"
#include "body.h"

#include <iostream>

Hud Camera::hud;

void Camera::render(sf::RenderWindow& window) {
	BodyManager::render(window);
	Camera::hud.render();
}
