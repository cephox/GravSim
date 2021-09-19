#include "body.h"
#include "universe.h"
#include "hud.h"
#include "camera.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <algorithm>
#include <iostream>

CelestialBody::CelestialBody(Vec2d pos, float mass, float radius, sf::Color color):
	pos(pos), vel(Vec2d()), mass(mass), radius(radius), color(color), affectedByGravity(true), affectsOthers(true) {visited = std::vector<Vec2d>(200);}

CelestialBody::CelestialBody(Vec2d pos, Vec2d vel, float mass, float radius, sf::Color color):
	pos(pos), vel(vel), mass(mass), radius(radius), color(color), affectedByGravity(true), affectsOthers(true) {visited = std::vector<Vec2d>(200);}

CelestialBody::CelestialBody(Vec2d pos, Vec2d vel, float mass, float radius, sf::Color color, bool affectedByGravity, bool affectsOthers):
	pos(pos), vel(vel), mass(mass), radius(radius), color(color), affectedByGravity(affectedByGravity), affectsOthers(affectsOthers) {
		visited = std::vector<Vec2d>(200);
}

void CelestialBody::updatePos() {
	if(visited.size() > 200) visited.erase(visited.begin());
	visited.push_back(Vec2d(pos));
	this->pos += this->vel;
}

void CelestialBody::updateVel() {
	this->vel += this->getTotalGForce() / this->mass;
}

Vec2d CelestialBody::getTotalGForce() {
	if(!this->affectedByGravity) return Vec2d();
	Vec2d totalForce;
	for(CelestialBody body : BodyManager::bodies) {
		if(this->operator==(body) || !body.affectsOthers)
			continue;
		Vec2d distance = body.pos - this->pos;
		double dist = distance.magnitudeSq();
		double force = 0;
		if(dist != 0)
			force = Universe::G * this->mass * body.mass / dist;
		distance.setMagnitude(force);
		totalForce += distance;
	}
	return totalForce;
}

void CelestialBody::render(sf::RenderTexture& window) {
	sf::CircleShape circle(this->radius, 512);
	circle.setPosition(this->pos.x - this->radius, this->pos.y - this->radius);
	circle.setFillColor(this->color);

	for(int i = 0; i < visited.size(); i++) {
		sf::RectangleShape point(sf::Vector2f(2, 2));
		point.setPosition(visited[i].x - 0.5, visited[i].y - 0.5);
		point.setFillColor(sf::Color(color.r, color.g, color.b, i));
		window.draw(point);
	}

	if(this->selected) {
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(2);
	}

	window.draw(circle);
}

bool CelestialBody::operator==(const CelestialBody &other) {
	return
		this->pos == other.pos &&
		this->vel == other.vel &&
		this->mass == other.mass &&
		this->radius == other.radius &&
		this->color == other.color &&
		this->affectedByGravity == other.affectedByGravity &&
		this->affectsOthers == other.affectsOthers;
}

// Bodymanager
std::vector<CelestialBody> BodyManager::bodies;

void BodyManager::resetBodies() {
	BodyManager::clear();
	BodyManager::add(CelestialBody(Vec2d(400, 500), 1000000, 20, sf::Color::Yellow));
	BodyManager::add(CelestialBody(Vec2d(500, 500), Vec2d(0, 1), 100, 10, sf::Color(0, 150, 0)));
	Hud::selectedBody = &bodies[1];
	Hud::selectedBody->selected = true;
}

void BodyManager::add(CelestialBody body) {
	BodyManager::bodies.push_back(body);
}
void BodyManager::remove(CelestialBody body) {
	std::vector<CelestialBody>::iterator itr = std::find(BodyManager::bodies.begin(), BodyManager::bodies.end(), body);
	if(itr != BodyManager::bodies.cend()) {
		BodyManager::bodies.erase(itr);
	}
}
void BodyManager::tick() {
	for(long unsigned int i = 0; i < BodyManager::bodies.size(); i++) {
		BodyManager::bodies[i].updateVel();
	}

	for(long unsigned int i = 0; i < BodyManager::bodies.size(); i++) {
		BodyManager::bodies[i].updatePos();
	}
}
void BodyManager::render(sf::RenderTexture& window) {
	for(CelestialBody body : BodyManager::getState()) {
		body.render(window);
	}
}
void BodyManager::clear() {
	BodyManager::bodies.clear();
	Hud::selectedBody = nullptr;
}
std::vector<CelestialBody> BodyManager::getState() {
	return std::vector<CelestialBody>(BodyManager::bodies);
}

CelestialBody* BodyManager::getBody(int x, int y) {
	x -= Camera::offsetX;
	y -= Camera::offsetY;

	for(long unsigned int i = 0; i < BodyManager::bodies.size(); i++) {
		double dx = x - BodyManager::bodies[i].pos.x;
		double dy = y - BodyManager::bodies[i].pos.y;
		double radius = BodyManager::bodies[i].radius;

		if(dx*dx + dy*dy < radius * radius)
			return &BodyManager::bodies[i];
	}

	return nullptr;
}
