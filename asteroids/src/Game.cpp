
#include <limits>
#include <algorithm>
#include "Game.h"
#include "UIDraw.h"

#define BORDER 50

Game::Game(const vec2& tl, const vec2& br)
{
	boundsMin = tl;
	boundsMax = br;
	restart();
}


void Game::update()
{
	ship.update();
	ship.turn();
	ship.edges(boundsMin, boundsMax);

	int iB = 0;
	for (Bullet& b : bullets)
	{
		b.update();
		b.edges(boundsMin, boundsMax);

		for (Rock* r : rocks)
		{
			float d = dist(r->loc, b.loc);
			if (d < r->getSize())
			{
				split(r);
				b.setLife(-1);
				//delete &r;
			}
		}

		int iA = 0;
		for (Alien& a : aliens)
		{
			float d = dist(a.loc, b.loc);
			if (d < 10)
			{
				b.setLife(-1);
				aliens.erase(aliens.begin() + iA);
			}
			iA++;
		}

		if (b.getLife() < 0)
		{
			bullets.erase(bullets.begin() + iB);
		}
		iB++;
	}

	for (Rock* r : rocks)
	{
		r->update();
		r->edges(boundsMin, boundsMax);

		if (dist(r->loc, ship.loc) < r->getSize() + 6)
		{
			restart();
		}
	}

	if (rocks.size() < MIN_ASTEROIDS)
	{
		for (int i = 0; i < 5; i++)
		{
			addRock(boundsMin, boundsMax);
		}
	}

	for (Alien& a : aliens)
	{
		float angle = angleBetween(a.loc, ship.loc);
		a.setHeading(angle);
		a.update(ship.loc);
		a.turn();
		a.edges(boundsMin, boundsMax);

		if (dist(a.loc, ship.loc) < 10 + 6)
		{
			restart();
		}
	}


	while (aliens.size() < 2)
	{
		int randAlien = random(0, 100);
		if (randAlien == 50)
		{
			vec2 location = vec2(
				randomEx(
					-180 - BORDER,
					-180,
					180,
					180 + BORDER
				),
				randomEx(
					-180 - BORDER,
					-180,
					180,
					180 + BORDER
				)
			);

			vec2 dest(
				ship.loc.getX(),
				ship.loc.getY()
			);

			Alien a = Alien();
			a.loc = location;
			a.acc = dest;

			aliens.push_back(a);
		}
	}

}


void Game::draw(const Interface& interface)
{
	ship.draw();

	for (Bullet& b : bullets)
	{
		b.draw();
	}

	for (Alien& a : aliens)
	{
		a.draw();
	}

	for (Rock* r : rocks)
	{
		r->draw();
	}
}


void Game::handleInput(const Interface& interface)
{

	if (interface.isLeft())
		ship.setRotation(-5);
	else if (interface.isRight())
		ship.setRotation(5);
	else
		ship.setRotation(0);

	//if (interface.isRight())
	//	ship.setRotation(5);


	if (interface.isUp())
	{
		ship.thrust();
		ship.setActive(true);
	}
	else
		ship.setActive(false);


	if (interface.isSpace())
	{
		Bullet b = Bullet(ship.loc, ship.getHeading());
		bullets.push_back(b);
	}

}

void Game::split(Rock* rock)
{

	if (rock->getType() == 1) {
		vec2 cLoc = rock->loc;
		vec2 cVel = rock->vel;

		Rock* r1 = new MediumRock();
		Rock* r2 = new MediumRock();
		Rock* r3 = new SmallRock();

		r1->loc = cLoc;
		r2->loc = cLoc;
		r3->loc = cLoc;

		r1->loc.add(vec2(0.4, 0));
		r2->loc.add(vec2(-0.4, 0));
		r3->loc.add(vec2(0, 0.4));

		r1->vel = cVel;
		r2->vel = cVel;
		r3->vel = cVel;

		r1->vel.add(vec2(0, 0.4));
		r2->vel.add(vec2(0, -0.4));
		r3->vel.add(vec2(0.5, 0));

		rocks.push_back(r1);
		rocks.push_back(r2);
		rocks.push_back(r3);
	}
	else if (rock->getType() == 2)
	{
		vec2 cLoc = rock->loc;
		vec2 cVel = rock->vel;

		Rock* r1 = new SmallRock();
		Rock* r2 = new SmallRock();

		r1->loc = cLoc;
		r2->loc = cLoc;

		r1->loc.add(vec2(0.4, 0));
		r2->loc.add(vec2(0, 0.4));

		r1->vel = cVel;
		r2->vel = cVel;

		r1->vel.add(vec2(-0.6, 0));
		r2->vel.add(vec2(0.6, 0));

		rocks.push_back(r1);
		rocks.push_back(r2);
	}

	rocks.erase(std::remove(rocks.begin(), rocks.end(), rock), rocks.end());
	delete rock;

}

void Game::addRock(const vec2& bMin, const vec2& bMax)
{
	vec2 location = vec2(
		randomEx(
			-100 - BORDER,
			-100,
			100,
			100 + BORDER
		),
		randomEx(
			-100 - BORDER,
			-100,
			100,
			100 + BORDER
		)
	);

	vec2 dest(
		(float)random(-100, 100),
		(float)random(-100, 100)
	);

	dest.sub(location);
	dest.normalize();

	float randVel = random(0.1, 2.0);
	dest.mult(randVel);

	int t = random(1, 15);
	Rock* r;
	if (t < 5)
	{
		r = new BigRock();
	}
	else if (t < 10)
	{
		r = new MediumRock();
	}
	else
	{
		r = new SmallRock();
	}

	r->loc = location;
	r->vel = dest;
	rocks.push_back(r);
}

void Game::restart()
{
	ship.loc = vec2(0, 0);
	ship.vel = vec2(0, 0);
	ship.setRotation(0);
	ship.setHeading(0);
	rocks.clear();
	bullets.clear();
	aliens.clear();

	for (int i = 0; i < START_ASTEROIDS; i++)
		addRock(boundsMin, boundsMax);

}
