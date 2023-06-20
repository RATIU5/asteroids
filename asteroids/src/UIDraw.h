#pragma once

#include <string>
#include <cmath>
#include "Vector.h"

void setColor(float r, float g, float b);

void rotate(vec2& point, const vec2& origin, int rotation = 0);

int    random(int    min, int    max);
double random(double min, double max);
float  random(float min, float max);
float  randomEx(float min1, float max1, float min2, float max2);

void drawDot(const vec2& point);
void drawDigit(const vec2& topLeft, char digit);
void drawNumber(const vec2& topLeft, int number);
void drawText(const vec2& topLeft, const char* text);
void drawRect(const vec2& center, int width, int height, int rotation);
void drawCircle(const vec2& center, int radius);
void drawPolygon(const vec2& center,
    int radius = 20,
    int points = 4,
    int rotation = 0);
void drawLine(const vec2& begin, const vec2& end,
    float red = 1.0, float green = 1.0, float blue = 1.0);

void drawLander(const vec2& point);
void drawLanderFlames(const vec2& point,
    bool bottom,
    bool left,
    bool right);
void drawAlien(const vec2& point);
void drawShip(const vec2& point, int rotation, bool thrust = false);
void drawSmallAsteroid(const vec2& point, int rotation);
void drawMediumAsteroid(const vec2& point, int rotation);
void drawLargeAsteroid(const vec2& point, int rotation);
