#include "window.h"
#include "camera.h"
#include "simulation.h"
#include "mouse.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <iostream>

void windowLoop() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "GravSim", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);

	if(!Hud::font.loadFromFile("res/arial.ttf")) {
		std::cout << "Error: Cannot load fonts!" << std::endl;
		std::cout << "To access fonts, put `arial.ttf` in the `res` folder" << std::endl;
		exit(0);
	}

	while(window.isOpen()) {
		sf::Event event;

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				Simulation::running = false;
				window.close();
			}

			// Mouse events
			if(event.type == sf::Event::MouseButtonPressed) {
				if(event.mouseButton.button == sf::Mouse::Right)
					GMouse::rightPressed = true;
				if(event.mouseButton.button == sf::Mouse::Left)
					GMouse::leftPressed = true;
				GMouse::x = sf::Mouse::getPosition(window).x;
				GMouse::y = sf::Mouse::getPosition(window).y;
				GMouse::mousePressed();
			}
			if(event.type == sf::Event::MouseButtonReleased) {
				if(event.mouseButton.button == sf::Mouse::Right)
					GMouse::rightPressed = false;
				if(event.mouseButton.button == sf::Mouse::Left)
					GMouse::leftPressed = false;
				GMouse::x = sf::Mouse::getPosition(window).x;
				GMouse::y = sf::Mouse::getPosition(window).y;
				GMouse::mouseReleased();
			}
			if(event.type == sf::Event::MouseMoved) {
				GMouse::x = sf::Mouse::getPosition(window).x;
				GMouse::y = sf::Mouse::getPosition(window).y;
				GMouse::mouseMoved();
			}

			// Keyboard events
			if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Space)
					Simulation::paused = !Simulation::paused;
			}
		}

		window.clear(sf::Color::Black);
		// Draw stuff
		Camera::render(window);

		window.display();
	}
}
