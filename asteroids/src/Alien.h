#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include "Motion.h"

class Alien : public Motion
{
private:
	float rotation;
	float heading;
	bool active;
public:
	Alien();

	void setRotation(const float& value);
	void setHeading(const float& value);
	void setActive(const bool& value);

	float getRotation() const;
	float getHeading() const;
	bool getActive() const;

	void thrust();

	void update(const vec2& dest);
	void edges(const vec2& min, const vec2& max);
	void turn();
	void draw();
};

