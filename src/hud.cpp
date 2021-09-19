#include "hud.h"
#include "simulation.h"

#include <cmath>
#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>

CelestialBody* Hud::selectedBody;
sf::Font Hud::font;
void drawText(sf::RenderTexture& hud, std::string string, int fontsize, sf::Color color, int x, int y) {

	sf::Text text;
	text.setString(string);
	text.setCharacterSize(fontsize);
	text.setPosition(x, y);
	text.setFillColor(color);
	text.setFont(Hud::font);
	hud.draw(text);
}

void Hud::render(sf::RenderTexture &hud) {
	this->renderBodyInformation(hud);

	if(Simulation::paused) {
		sf::ConvexShape tri;
		tri.setPointCount(3);
		tri.setPoint(0, sf::Vector2f(20, 20));
		tri.setPoint(1, sf::Vector2f(20, 70));
		tri.setPoint(2, sf::Vector2f(63, 45));
		hud.draw(tri);
	} else {
		sf::RectangleShape r1(sf::Vector2f(15, 50));
		r1.setPosition(20, 20);
		hud.draw(r1);
		sf::RectangleShape r2(sf::Vector2f(15, 50));
		r2.setPosition(48, 20);
		hud.draw(r2);
	}
}

void Hud::renderBodyInformation(sf::RenderTexture &hud) {
	sf::RectangleShape backg(sf::Vector2f(300, 1000));
	backg.setPosition(BODY_INFORMATION_X, 0);
	backg.setFillColor(sf::Color(255, 255, 255, 100));
	hud.draw(backg);

	int currentY = 0;

	if(selectedBody != nullptr) {
		renderAttr(hud, "Mass", std::to_string(selectedBody->mass), 710, currentY += 50);
		renderAttr(hud, "Radius", std::to_string(selectedBody->radius) + " pixels", 710, currentY += 80);
		renderAttr(hud, "Velocity", std::to_string(selectedBody->vel.magnitude()) + " pixels/step", 710, currentY += 80);
		renderAttr(hud, "Affected", selectedBody->affectedByGravity ? "Yes" : "No", 710, currentY += 80);
		renderAttr(hud, "Affects others", selectedBody->affectsOthers ? "Yes" : "No", 710, currentY += 80);
	} else {
		drawText(hud, "No body is currently selected\nSelect one by clicking.", 16, sf::Color::White, 710, 50);
	}
}

void Hud::renderAttr(sf::RenderTexture &hud, std::string title, std::string value, int x, int y) {
	drawText(hud, title, 30, sf::Color::White, x, y);
	drawText(hud, value, 16, sf::Color::White, x, y + 40);
}

