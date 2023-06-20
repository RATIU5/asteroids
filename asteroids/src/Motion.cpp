#include "Motion.h"

Motion::Motion()
{
	loc = vec2(0, 0);
	vel = vec2(0, 0);
	acc = vec2(0, 0);
	rad = 0;
}

void Motion::update()
{
	vel.add(acc);
	loc.add(vel);
	acc.mult(0);
}

void Motion::print()
{
	std::cout << "Location: " << loc << std::endl;
	std::cout << "Velocity: " << vel << std::endl;
	std::cout << "Acceleration: " << acc << std::endl;
}

