#include "Bullet.h"

#include "UIDraw.h"

Bullet::Bullet(const vec2& location, const float& heading)
{
	loc = location;
	vel = fromAngle(heading);
	vel.mult(BULLET_SPEED);
}


void Bullet::setLife(const int& value)
{
	life = value;
}
int Bullet::getLife() const
{
	return life;
}


void Bullet::update()
{
	Motion::update();
	life--;
}


void Bullet::edges(vec2 min, vec2 max)
{

	int padding = 1;

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


void Bullet::draw()
{
	drawDot(loc);
}

