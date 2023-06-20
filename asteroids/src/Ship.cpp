#include "Ship.h"

#include "UIDraw.h"


Ship::Ship() : Motion()
{
	this->heading = 0;
	this->rotation = 0;
}


void Ship::setRotation(const float& value)
{
	rotation = value;
}


void Ship::setHeading(const float& value)
{
	if (value > 359)
		heading = 0;
	else if (value < -359)
		heading = 0;
	else
		heading = value;
}


void Ship::setActive(const bool& value)
{
	active = value;
}


float Ship::getRotation() const
{
	return rotation;
}


float Ship::getHeading() const
{
	return heading;
}


bool Ship::getActive() const
{
	return active;
}


void Ship::turn()
{
	setHeading(heading + rotation);
}


void Ship::thrust()
{
	vec2 force = fromAngle(heading);
	force.mult(0.35);
	vel.add(force);
}


void Ship::edges(const vec2& min, const vec2& max)
{
	int padding = 5;

	if (loc.getX() < min.getX() - (float)padding)
	{
		loc.setX(max.getX() + (float)padding);
	}
	else if (loc.getX() > max.getX() + (float)padding)
	{
		loc.setX(min.getX() - (float)padding);
	}

	if (loc.getY() < max.getY() - (float)padding)
	{
		loc.setY(min.getY() + (float)padding);
	}
	else if (loc.getY() > min.getY() + (float)padding)
	{
		loc.setY(max.getY() - (float)padding);
	}
}


void Ship::update()
{
	vel.mult(0.965);
	loc.add(vel);
}


void Ship::draw()
{
	setColor(1, 1, 1);
	drawShip(loc, -(int)heading + 90, active);
}

