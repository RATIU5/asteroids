#include <string>
#include <sstream>
#include <cassert>
#include <time.h>

#ifdef __APPLE__
#include <openGL/gl.h>
#include <GLUT/glut.h>
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>
#include <GL/glut.h>
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#include "UIDraw.h"

#define deg2rad(value) ((M_PI / 180) * (value))


const char NUMBER_OUTLINES[10][20] =
{
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   0,10,  0, 0,  -1,-1, -1,-1},//0
  {7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//1
  {0, 0,  7, 0,   7, 0,  7, 5,   7, 5,  0, 5,   0, 5,  0,10,   0,10,  7,10},//2
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   4, 5,  7, 5,  -1,-1, -1,-1},//3
  {0, 0,  0, 5,   0, 5,  7, 5,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1},//4
  {7, 0,  0, 0,   0, 0,  0, 5,   0, 5,  7, 5,   7, 5,  7,10,   7,10,  0,10},//5
  {7, 0,  0, 0,   0, 0,  0,10,   0,10,  7,10,   7,10,  7, 5,   7, 5,  0, 5},//6
  {0, 0,  7, 0,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//7
  {0, 0,  7, 0,   0, 5,  7, 5,   0,10,  7,10,   0, 0,  0,10,   7, 0,  7,10},//8
  {0, 0,  7, 0,   7, 0,  7,10,   0, 0,  0, 5,   0, 5,  7, 5,  -1,-1, -1,-1} //9
};


void setColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}


int random(int min, int max)
{
	int num;
	if (min <= max)
		num = (rand() % (max - min)) + min;
	else
		num = (rand() % (min - max)) + max;

	return num;
}


double random(double min, double max)
{
	assert(min < max);
	return min + ((double)rand() / (double)RAND_MAX * (max - min));
}


float random(float min, float max)
{
	assert(min <= max);
	return min + ((float)rand() / (float)RAND_MAX * (max - min));
}


float randomEx(float min1, float max1, float min2, float max2)
{
	float val = (float)random(min1, max1 - min1 + max2 - min2) + min1;
	return val > max1 ? val + min2 - max1 : val;
}


void drawDigit(const vec2& topLeft, char digit)
{
    assert(isdigit(digit));
    if (!isdigit(digit))
        return;

    int r = digit - '0';
    assert(r >= 0 && r <= 9);

    for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4)
    {
        assert(NUMBER_OUTLINES[r][c] != -1 &&
            NUMBER_OUTLINES[r][c + 1] != -1 &&
            NUMBER_OUTLINES[r][c + 2] != -1 &&
            NUMBER_OUTLINES[r][c + 3] != -1);

        vec2 start;
        start.setX(topLeft.getX() + NUMBER_OUTLINES[r][c]);
        start.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 1]);
        vec2 end;
        end.setX(topLeft.getX() + NUMBER_OUTLINES[r][c + 2]);
        end.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 3]);

        drawLine(start, end);
    }
}


void drawNumber(const vec2& topLeft, int number)
{
    vec2 point = topLeft;

    bool isNegative = (number < 0);
    number *= (isNegative ? -1 : 1);

    std::ostringstream sout;
    sout << number;
    std::string text = sout.str();

    if (isNegative)
    {
        glBegin(GL_LINES);
        glVertex2f(point.getX() + 1, point.getY() - 5);
        glVertex2f(point.getX() + 5, point.getY() - 5);
        glEnd();
        point.addX(11);
    }

    for (const char* p = text.c_str(); *p; p++)
    {
        assert(isdigit(*p));
        drawDigit(point, *p);
        point.addX(11);
    }
}


void drawText(const vec2& topLeft, const char* text)
{
    void* pFont = GLUT_BITMAP_HELVETICA_12;

    glRasterPos2f(topLeft.getX(), topLeft.getY());

    for (const char* p = text; *p; p++)
        glutBitmapCharacter(pFont, *p);
}


void drawPolygon(const vec2& center, int radius, int points, int rotation)
{
    glBegin(GL_LINE_LOOP);

    for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / points)
    {
        vec2 temp(false);
        temp.setX(center.getX() + (radius * cos(i)));
        temp.setY(center.getY() + (radius * sin(i)));
        rotate(temp, center, rotation);
        glVertex2f(temp.getX(), temp.getY());
    }

    glEnd();
}


void rotate(vec2& point, const vec2& origin, int rotation)
{
    double cosA = cos(deg2rad(rotation));
    double sinA = sin(deg2rad(rotation));

    vec2 tmp(false);
    tmp.setX(point.getX() - origin.getX());
    tmp.setY(point.getY() - origin.getY());

    point.setX(static_cast<int> (tmp.getX() * cosA -
        tmp.getY() * sinA) +
        origin.getX());
    point.setY(static_cast<int> (tmp.getX() * sinA +
        tmp.getY() * cosA) +
        origin.getY());
}


void drawLine(const vec2& begin, const vec2& end,
    float red, float green, float blue)
{
    glBegin(GL_LINES);
    glColor3f(red, green, blue);

    glVertex2f(begin.getX(), begin.getY());
    glVertex2f(end.getX(), end.getY());

    glColor3f(1.0, 1.0, 1.0);
    glEnd();
}


void drawLander(const vec2& point)
{
    vec2 points[] =
    {
       {-6, 0}, {-10,0}, {-8, 0}, {-8, 3},  // left foot
       {-5, 4}, {-5, 7}, {-8, 3}, {-5, 4},  // left leg
       {-1, 4}, {-3, 2}, { 3, 2}, { 1, 4}, {-1, 4}, // bottom
       { 5, 4}, { 5, 7}, {-5, 7}, {-3, 7},  // engine square
       {-6,10}, {-6,13}, {-3,16}, { 3,16},   // left of habitat
       { 6,13}, { 6,10}, { 3, 7}, { 5, 7},   // right of habitat
       { 5, 4}, { 8, 3}, { 5, 7}, { 5, 4},  // right leg
       { 8, 3}, { 8, 0}, {10, 0}, { 6, 0}   // right foot
    };

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++)
        glVertex2f(point.getX() + points[i].getX(),
            point.getY() + points[i].getY());

    glEnd();


}


void drawLanderFlames(const vec2& point,
    bool bottom,
    bool left,
    bool right)
{


    int iFlame = random(0, 3);

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);

    if (bottom)
    {
        vec2 points[3][3] =
        {
           { {-5,  -6}, { 0, -1}, { 3, -10} },
           { {-3,  -6}, {-1, -2}, { 0, -15} },
           { { 2, -12}, { 1,  0}, { 6,  -4} }
        };

        glVertex2f(point.getX() - 2, point.getY() + 2);
        for (int i = 0; i < 3; i++)
			glVertex2f(point.getX() + points[iFlame][i].getX(),
                point.getY() + points[iFlame][i].getY());
        glVertex2f(point.getX() + 2, point.getY() + 2);
    }

    if (right)
    {
        vec2 points[3][3] =
        {
           { {10, 14}, { 8, 12}, {12, 12} },
           { {12, 10}, { 8, 10}, {10,  8} },
           { {14, 11}, {14, 11}, {14, 11} }
        };

        glVertex2f(point.getX() + 6, point.getY() + 12);
        for (int i = 0; i < 3; i++)
            glVertex2f(point.getX() + points[iFlame][i].getX(),
				point.getY() + points[iFlame][i].getY());
        glVertex2f(point.getX() + 6, point.getY() + 10);
    }

    if (left)
    {
        vec2 points[3][3] =
        {
           { {-10, 14}, { -8, 12}, {-12, 12} },
           { {-12, 10}, { -8, 10}, {-10,  8} },
           { {-14, 11}, {-14, 11}, {-14, 11} }
        };

        glVertex2f(point.getX() - 6, point.getY() + 12);
        for (int i = 0; i < 3; i++)
			glVertex2f(point.getX() + points[iFlame][i].getX(),
                point.getY() + points[iFlame][i].getY());
        glVertex2f(point.getX() - 6, point.getY() + 10);
    }

    glColor3f(1.0, 1.0, 1.0);
    glEnd();
}


void drawRect(const vec2& center, int width, int height, int rotation)
{
    vec2 tl(false);
    vec2 tr(false);
    vec2 bl(false);
    vec2 br(false);

    tl.setX(center.getX() - (width / 2));
    tl.setY(center.getY() + (height / 2));

    tr.setX(center.getX() + (width / 2));
    tr.setY(center.getY() + (height / 2));

    bl.setX(center.getX() - (width / 2));
    bl.setY(center.getY() - (height / 2));

    br.setX(center.getX() + (width / 2));
    br.setY(center.getY() - (height / 2));

    rotate(tl, center, rotation);
    rotate(tr, center, rotation);
    rotate(bl, center, rotation);
    rotate(br, center, rotation);

    glBegin(GL_LINE_STRIP);
    glVertex2f(tl.getX(), tl.getY());
    glVertex2f(tr.getX(), tr.getY());
    glVertex2f(br.getX(), br.getY());
    glVertex2f(bl.getX(), bl.getY());
    glVertex2f(tl.getX(), tl.getY());
    glEnd();
}


void drawCircle(const vec2& center, int radius)
{
    assert(radius > 1.0);
    const double increment = 1.0 / (double)radius;

    glBegin(GL_LINE_LOOP);

    for (double radians = 0; radians < M_PI * 2.0; radians += increment)
        glVertex2f(center.getX() + (radius * cos(radians)),
            center.getY() + (radius * sin(radians)));

    glEnd();
}

void drawDot(const vec2& point)
{
    glBegin(GL_POINTS);
    glVertex2f(point.getX(), point.getY());
    glVertex2f(point.getX() + 1, point.getY());
    glVertex2f(point.getX() + 1, point.getY() + 1);
    glVertex2f(point.getX(), point.getY() + 1);
    glEnd();
}


void drawSmallAsteroid(const vec2& center, int rotation)
{
    vec2 points[] =
    {
       {-5, 9},  {4, 8},   {8, 4},
       {8, -5},  {-2, -8}, {-2, -3},
       {-8, -4}, {-8, 4},  {-5, 10}
    };

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeof(points) / sizeof(vec2); i++)
    {
        vec2 pt(center.getX() + points[i].getX(),
            center.getY() + points[i].getY());
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
    }
    glEnd();
}


void drawMediumAsteroid(const vec2& center, int rotation)
{
    vec2 points[] =
    {
       {2, 8},    {8, 15},    {12, 8},
       {6, 2},    {12, -6},   {2, -15},
       {-6, -15}, {-14, -10}, {-15, 0},
       {-4, 15},  {2, 8}
    };

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeof(points) / sizeof(vec2); i++)
    {
        vec2 pt(center.getX() + points[i].getX(),
            center.getY() + points[i].getY());
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
    }
    glEnd();
}


void drawLargeAsteroid(const vec2& center, int rotation)
{
    vec2 points[] =
    {
       {0, 12},    {8, 20}, {16, 14},
       {10, 12},   {20, 0}, {0, -20},
       {-18, -10}, {-20, -2}, {-20, 14},
       {-10, 20},  {0, 12}
    };

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeof(points) / sizeof(vec2); i++)
    {
        vec2 pt(center.getX() + points[i].getX(),
			center.getY() + points[i].getY());
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
    }
    glEnd();
}


void drawShip(const vec2& center, int rotation, bool thrust)
{                                             
    const vec2 pointsShip[] =
    {
       {0, 6}, {6, -6}, {2, -3}, {-2, -3}, {-6, -6}, {0, 6}
    };

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeof(pointsShip) / sizeof(vec2); i++)
    {
        vec2 pt(center.getX() + pointsShip[i].getX(),
            center.getY() + pointsShip[i].getY());
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
    }
    glEnd();

    if (thrust)
    {
        const vec2 pointsFlame[3][5] =
        {
           { {-2, -3}, {-2, -13}, { 0, -6}, { 2, -13}, {2, -3} },
           { {-2, -3}, {-4,  -9}, {-1, -7}, { 1, -14}, {2, -3} },
           { {-2, -3}, {-1, -14}, { 1, -7}, { 4,  -9}, {2, -3} }
        };

        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0);
        int iFlame = random(0, 3);
        for (int i = 0; i < 5; i++)
        {
            vec2 pt(center.getX() + pointsFlame[iFlame][i].getX(),
                center.getY() + pointsFlame[iFlame][i].getY());
            rotate(pt, center, rotation);
            glVertex2f(pt.getX(), pt.getY());
        }
        glColor3f(1.0, 1.0, 1.0);                              
        glEnd();
    }
}


void drawAlien(const vec2& point)
{
    vec2 points[] =
    {
            {-8, 0}, {-5, 1}, {-3, 2}, {-2, 2},
            {-1, 3}, { 0, 4}, { 1, 3}, { 2, 2},
            { 3, 2}, { 5, 1}, { 8, 0}, { 5,-1}, {3, -2},
            { 2,-2}, { 1,-3}, { 0,-4}, {-1,-3},
            {-2,-2}, {-3,-2}, {-5,-1}, {-8, 0},
            { 8, 0}
    };

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++)
        glVertex2f(point.getX() + points[i].getX(),
            point.getY() + points[i].getY());

    glEnd();

}