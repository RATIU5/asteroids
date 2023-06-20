#pragma once

#include "Vector.h"

class Motion
{
public:
	vec2 loc;
	vec2 vel;
	vec2 acc;
	float rad;

	Motion();

	virtual void update();
	void print();

};
