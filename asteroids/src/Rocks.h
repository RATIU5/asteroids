#pragma once

#include "Motion.h"

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10


class Rock : public Motion
{
private:
	float spin;
	float size;
	int type;
public:
	Rock();

	void  setSpin(const float& value);
	void  setSize(const float& value);
	void  setType(const int& value);

	float getSpin() const;
	float getSize() const;
	int   getType() const;

	virtual void draw();
	void edges(const vec2& min, const vec2& max);
};


class BigRock : public Rock
{
public:
	BigRock();
	void draw() override;
};


class MediumRock : public Rock
{
public:
	MediumRock();
	void draw() override;
};


class SmallRock : public Rock
{
public:
	SmallRock();
	void draw() override;
};
