
#define _USE_MATH_DEFINES

#include <cmath>
#include "Vector.h"


void vec2::setY(const float& value)
{
	this->y = value;
}


void vec2::setX(const float& value)
{
	this->x = value;
}


void vec2::set(const vec2& vector)
{
	setX(vector.getX());
	setY(vector.getY());
}


void vec2::add(const vec2& vector)
{
	addX(vector.getX());
	addY(vector.getY());
}


void vec2::addX(const float& value)
{
	setX(getX() + value);
}


void vec2::addY(const float& value)
{
	setY(getY() + value);
}


void vec2::subX(const float& value)
{
	setX(getX() - value);
}


void vec2::subY(const float& value)
{
	setY(getY() - value);
}


void vec2::sub(const vec2& vector)
{
	subX(vector.getX());
	subY(vector.getY());
}


void vec2::mult(const float& value)
{
	multX(value);
	multY(value);
}


void vec2::multX(const float& value)
{
	setX(getX() * value);
}


void vec2::multY(const float& value)
{
	setY(getY() * value);
}


void vec2::divX(const float& value)
{
	setX(getX() / value);
}


void vec2::divY(const float& value)
{
	setY(getY() / value);
}


void vec2::div(const float& value)
{
	divX(value);
	divY(value);
}


void vec2::normalize()
{
	float m = mag();
	if (m != 0 && m != 1) 
		div(m);
}


float vec2::mag() const
{
	return (float)sqrt((double)((double)x * (double)x + (double)y * (double)y));
}


float vec2::heading() const
{
	return (float)std::atan2(getY(), getX());
}


vec2 vec2::copy() const
{
	return { getX(), getY() };
}


vec2 sub(const vec2& value1, const vec2& value2)
{
	return { value1.getX() - value2.getX(), value1.getY() - value2.getY() };
}


vec2 fromAngle(float angle)
{
	float dx = (float)-cos(M_PI / 180.0 * angle);
	float dy = (float)sin(M_PI / 180.0 * angle);
	return { dx, dy };
}


void constrain(vec2 value, vec2 min, vec2 max)
{
	if (value.getX() >= 0)
	{
		if (value.getX() < min.getX())
		{
			value.setX(min.getX());
		}
		else if (value.getX() > max.getX())
		{
			value.setX(max.getX());
		}
	}
	else
	{
		if (value.getX() < -max.getX())
		{
			value.setX(-max.getX());
		}
		else if (value.getX() > -min.getX())
		{
			value.setX(-min.getX());
		}
	}

	if (value.getY() >= 0)
	{
		if (value.getY() < min.getY())
		{
			value.setX(min.getY());
		}
		else if (value.getY() > max.getY())
		{
			value.setX(max.getY());
		}
	}
	else
	{
		if (value.getY() < -max.getY())
		{
			value.setX(-max.getY());
		}
		else if (value.getY() > -min.getY())
		{
			value.setX(-min.getY());
		}
	}
}


float dist(const vec2& loc1, const vec2& loc2)
{
	return sqrt(
		(loc2.getX() - loc1.getX()) * (loc2.getX() - loc1.getX()) +
		(loc2.getY() - loc1.getY()) * (loc2.getY() - loc1.getY())
	);
}


float angleBetween(vec2 v1, vec2 v2) 
{

	if (v1.getX() == 0 && v1.getY() == 0) return 0.0f;
	if (v2.getX() == 0 && v2.getY() == 0) return 0.0f;

	double dot = (double)v1.getX() * (double)v2.getX() + (double)v1.getY() * (double)v2.getY();
	double v1mag = sqrt(v1.getX() * v1.getX() + v1.getY() * v1.getY());
	double v2mag = sqrt(v2.getX() * v2.getX() + v2.getY() * v2.getY());

	double amt = dot / (v1mag * v2mag);

	if (amt <= -1) {
		return (float)(180 / M_PI);
	}
	else if (amt >= 1) {
		return 0;
	}
	return (float)acos(amt) * (float)(180 / M_PI);
}


vec2 vec2::operator=(const vec2& vec)
{
	this->x = vec.getX();
	this->y = vec.getY();
	return this;
}


std::ostream& operator << (std::ostream& out, const vec2& pt)
{
	out << "(" << pt.getX() << ", " << pt.getY() << ")";
	return out;
}
