#pragma once

#include "vec2.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#define BODY_TAIL_LENGTH 200

class CelestialBody {
private:
	std::vector<Vec2d> visited;
public:
	Vec2d pos;
	Vec2d vel;

	float mass;
	int radius;

	sf::Color color;

	bool affectedByGravity;
	bool affectsOthers;

	bool selected;

	CelestialBody(Vec2d pos, float mass, float radius, sf::Color color);
	CelestialBody(Vec2d pos, Vec2d vel, float mass, float radius, sf::Color color);
	CelestialBody(Vec2d pos, Vec2d vel, float mass, float radius, sf::Color color, bool affectedByGravity, bool affectsOthers);

	void updatePos();
	void updateVel();

	Vec2d getTotalGForce();
	void render(sf::RenderTexture& window);

	bool operator==(const CelestialBody& other);
};

class BodyManager {
public:
	static std::vector<CelestialBody> bodies;

	static void add(CelestialBody body);
	static void remove(CelestialBody body);
	static void tick();
	static void render(sf::RenderTexture& window);
	static void clear();

	static void resetBodies();

	static std::vector<CelestialBody> getState();
	static CelestialBody *getBody(int x, int y);
};
