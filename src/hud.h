#pragma once
#include "body.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <string>

#define BODY_INFORMATION_X 700

class Hud {
public:
	static sf::Font font;
	static CelestialBody *selectedBody;

	void render(sf::RenderTexture& hud);
	void renderBodyInformation(sf::RenderTexture& hud);
	void renderAttr(sf::RenderTexture& hud, std::string title, std::string value, int x, int y);
};
