#pragma once

#include <iostream>

class vec2
{
public:
	vec2()
		: x(0.0), y(0.0) {}
	vec2(const bool& check)
		: x(0.0), y(0.0) {}
	vec2(const float& x, const float& y)
		: x(x), y(y) {}

	vec2(const vec2& vec)
		: x(vec.getX()), y(vec.getY()) {}

	float getX() const { return x; }
	float getY() const { return y; }

	void set(const vec2& vector);
	void setX(const float& x);
	void setY(const float& y);

	void add(const vec2& vector);
	void addX(const float& dx);
	void addY(const float& dy);
	void sub(const vec2& vector);
	void subX(const float& dx);
	void subY(const float& dy);
	void multX(const float& x);
	void multY(const float& y);
	void mult(const float& value);
	void divX(const float& value);
	void divY(const float& value);
	void div(const float& value);
	void normalize();

	vec2 copy() const;
	float mag() const;
	float heading() const;

	vec2 vec2::operator= (const vec2& vec);

private:
	float x;
	float y;
};

std::ostream& operator << (std::ostream& out, const vec2& pt);

vec2  sub(const vec2& value1, const vec2& value2);
vec2  fromAngle(float angle);
void  constrain(vec2 value, vec2 min, vec2 max);
float dist(const vec2& loc1, const vec2& loc2);
float angleBetween(vec2 v1, vec2 v2);
