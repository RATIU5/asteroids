#pragma once

#include <vector>
#include "Motion.h"
#include "Vector.h"
#include "Rocks.h"
#include "Ship.h"
#include "Bullet.h"
#include "Alien.h"
#include "UIInteract.h"

#define START_ASTEROIDS 5
#define MIN_ASTEROIDS 5

class Game
{
private:
	vec2 boundsMin;
	vec2 boundsMax;
	std::vector<Rock*> rocks;
	std::vector<Bullet> bullets;
	std::vector<Alien> aliens;
	Ship ship;

public:
	Game(const vec2& tl, const vec2& br);
	void update();
	void handleInput(const Interface& interface);
	void draw(const Interface& interface);
	void split(Rock* rock);
	void restart();

	void addRock(const vec2& pos, const vec2& vel);
};
