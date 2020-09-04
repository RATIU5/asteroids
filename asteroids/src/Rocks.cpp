#include "Rocks.h"

#include "UIDraw.h"


Rock::Rock() : Motion() {}


void Rock::setSpin(const float& value)
{
	this->spin = value;
}


void Rock::setSize(const float& value)
{
	this->size = value;
}


float Rock::getSpin() const
{
	return this->spin;
}


float Rock::getSize() const
{
	return this->size;
}


void Rock::draw()
{
	drawCircle(loc, 10);
}


void Rock::edges(const vec2& min, const vec2& max)
{
	int padding = (int)(getSize() + 20);

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


void Rock::setType(const int& value)
{
	type = value;
}


int Rock::getType() const
{
	return type;
}


BigRock::BigRock() : Rock()
{
	setSpin(BIG_ROCK_SPIN);
	setSize(BIG_ROCK_SIZE + 1);
	setType(1);
}


void BigRock::draw()
{
	setColor(1, 1, 1);
	drawLargeAsteroid(loc, 2);
}


MediumRock::MediumRock() : Rock()
{
	setSpin(MEDIUM_ROCK_SPIN);
	setSize(MEDIUM_ROCK_SIZE + 5);
	setType(2);
}


void MediumRock::draw()
{
	setColor(1, 1, 1);
	drawMediumAsteroid(loc, (int)getSpin());
}


SmallRock::SmallRock() : Rock()
{
	setSpin(SMALL_ROCK_SPIN);
	setSize(SMALL_ROCK_SIZE + 4);
	setType(3);
}


void SmallRock::draw()
{
	setColor(1, 1, 1);
	drawSmallAsteroid(loc, (int)getSpin());
}
