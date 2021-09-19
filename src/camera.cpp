#include "camera.h"
#include "body.h"

#include <iostream>

Hud Camera::hud;

void Camera::render(sf::RenderWindow& window) {
	BodyManager::render(window);

	// Drawing the hud on a separate texture
	sf::ContextSettings hudSettings;
	hudSettings.antialiasingLevel = 16;
	sf::RenderTexture hudTexture;
	if(!hudTexture.create(1000, 1000, hudSettings)) {
		std::cout << "Error: Cannot create HUD texture!" << std::endl;
		return;
	}

	hudTexture.clear(sf::Color::Transparent);
	Camera::hud.render(hudTexture);
	hudTexture.display();

	const sf::Texture hudTex = hudTexture.getTexture();
	window.draw(sf::Sprite(hudTex));
}
