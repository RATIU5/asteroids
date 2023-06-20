#include "Alien.h"

#include "UIDraw.h"

Alien::Alien() : Motion()
{
	this->heading = 0;
	this->rotation = 0;
}


void Alien::setRotation(const float& value)
{
	rotation = value;
}


void Alien::setHeading(const float& value)
{
	if (value > 359)
	{
		heading = 0;
	}
	else if (value < -359)
	{
		heading = 0;
	}
	else
	{
		heading = value;
	}
}


void Alien::setActive(const bool& value)
{
	active = value;
}


float Alien::getRotation() const
{
	return rotation;
}


float Alien::getHeading() const
{
	return heading;
}


bool Alien::getActive() const
{
	return active;
}


void Alien::turn()
{
	setHeading(heading + rotation);
}


void Alien::thrust()
{
	vec2 force = fromAngle(heading);
	force.mult(0.35);
	acc.add(force);
}


void Alien::edges(const vec2& min, const vec2& max)
{

	int padding = 5;

	if (loc.getX() < min.getX() - (float)padding)
		loc.setX(max.getX() + (float)padding);
	else if (loc.getX() > max.getX() + (float)padding)
		loc.setX(min.getX() - (float)padding);

	if (loc.getY() < max.getY() - (float)padding)
		loc.setY(min.getY() + (float)padding);
	else if (loc.getY() > min.getY() + (float)padding)
		loc.setY(max.getY() - (float)padding);

}


void Alien::update(const vec2& dest)
{
	vec2 ship = dest;
	ship.sub(loc);
	ship.normalize();
	ship.mult(0.1);

	acc.set(ship);

	vel.add(acc);
	loc.add(vel);
	acc.mult(0);

	float max = 3;
	if (vel.getX() * vel.getX() + vel.getY() * vel.getY() > max * max)
	{
		vel.normalize();
		vel.mult(max);
	}
}


void Alien::draw()
{
	setColor(1, 1, 1);
	drawAlien(loc);
}

