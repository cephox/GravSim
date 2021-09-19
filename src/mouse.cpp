#include "mouse.h"
#include "body.h"
#include "hud.h"

#include <SFML/Window/Mouse.hpp>
#include <iostream>

int GMouse::x;
int GMouse::y;
bool GMouse::leftPressed;
bool GMouse::rightPressed;

void GMouse::mousePressed() {

	if(Hud::selectedBody)
		Hud::selectedBody->selected = false;

	CelestialBody* selectedBody;
	selectedBody = BodyManager::getBody(x, y);
	if(selectedBody != nullptr) {
		Hud::selectedBody = selectedBody;
		Hud::selectedBody->selected = true;
	} else {
		Hud::selectedBody = nullptr;
	}
}

void GMouse::mouseReleased() {
}

void GMouse::mouseMoved() {
}
