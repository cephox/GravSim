#include "camera.h"
#include "body.h"

#include <iostream>

Hud Camera::hud;
int Camera::offsetX;
int Camera::offsetY;

sf::ContextSettings Camera::settings;

void Camera::init() {
	settings.antialiasingLevel = 16;
}

void Camera::render(sf::RenderWindow& window) {

	sf::RenderTexture rTex;
	if(!rTex.create(1000, 1000, settings)) {}

	rTex.clear();
	BodyManager::render(rTex);
	rTex.display();

	const sf::Texture tex = rTex.getTexture();
	sf::Sprite spr(tex);
	spr.setPosition(offsetX, offsetY);
	window.draw(spr);

	Camera::hud.render();
}
