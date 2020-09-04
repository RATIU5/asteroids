#pragma once

#include "Motion.h"

#define BULLET_SPEED 5
#define BULLET_LIFE 40

class Bullet : public Motion
{
private:
	int life = BULLET_LIFE;
public:
	Bullet(const vec2& location, const float& heading);

	void setLife(const int& value);
	int getLife() const;

	void update() override;
	void edges(vec2 min, vec2 max);
	void draw();
};
