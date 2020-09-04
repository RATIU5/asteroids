#pragma once

#include "Vector.h"


class Interface
{
public:

    Interface() { initialize(0, 0x0000, "Window", vec2(-50, 50), vec2(50, -50)); };

    Interface(int argc, char** argv, const char* title, vec2 topLeft, vec2 bottomRight)
    {
        initialize(argc, argv, title, topLeft, bottomRight);
    }

    ~Interface();

    void run(void (*callBack)(const Interface*, void*), void* p);

    bool isTimeToDraw();

    void setNextDrawTime();

    unsigned int getNextTick() { return nextTick; };

    void setFramesPerSecond(double value);

    void keyEvent(int key, bool fDown);
    void keyEvent();

    // Current frame rate
    double frameRate() const { return timePeriod; };

    int  isDown()   const { return isDownPress; };
    int  isUp()     const { return isUpPress; };
    int  isLeft()   const { return isLeftPress; };
    int  isRight()  const { return isRightPress; };
    bool isSpace()  const { return isSpacePress; };

    static void* p;
    static void (*callBack)(const Interface*, void*);

private:
    void initialize(int argc, char** argv, const char* title, vec2 topLeft, vec2 bottomRight);

    static bool         initialized;
    static double       timePeriod;
    static unsigned int nextTick;

    static int  isDownPress;
    static int  isUpPress;
    static int  isLeftPress;
    static int  isRightPress;
    static bool isSpacePress;
};

void drawCallback();

void keyDownCallback(int key, int x, int y);

void keyUpCallback(int key, int x, int y);

void keyboardCallback(unsigned char key, int x, int y);

void run();

