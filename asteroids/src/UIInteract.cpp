#pragma once

#include <string>
#include <sstream>
#include <cassert>
#include <time.h>
#include <cstdlib>

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
#include <Gl/glut.h>
#include <ctime>
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#include "UIInteract.h"

void sleep(unsigned long msSleep)
{
    #ifdef _WIN32
        ::Sleep(msSleep + 35);

    #else
	    timespec req = {};
	    time_t sec = (int)(msSleep / 1000);
	    msSleep -= (sec * 1000);

	    req.tv_sec = sec;
	    req.tv_nsec = msSleep * 1000000L;

	    while (nanosleep(&req, &req) == -1);
    #endif
    return;
}

void drawCallback()
{
    Interface ui;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);

    assert(ui.callBack != NULL);
    ui.callBack(&ui, ui.p);

    if (!ui.isTimeToDraw())
        sleep((unsigned long)((ui.getNextTick() - clock()) / 1000));

    ui.setNextDrawTime();

    glutSwapBuffers();

    ui.keyEvent();
}

void keyDownCallback(int key, int x, int y)
{
    Interface ui;
    ui.keyEvent(key, true);
}

void keyUpCallback(int key, int x, int y)
{
    Interface ui;
    ui.keyEvent(key, false);
}

void keyboardCallback(unsigned char key, int x, int y)
{
    Interface ui;
    ui.keyEvent(key, true);
}

void Interface::keyEvent(int key, bool fDown)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        isDownPress = fDown;
        break;
    case GLUT_KEY_UP:
        isUpPress = fDown;
        break;
    case GLUT_KEY_RIGHT:
        isRightPress = fDown;
        break;
    case GLUT_KEY_LEFT:
        isLeftPress = fDown;
        break;
    case GLUT_KEY_HOME:
    case ' ':
        isSpacePress = fDown;
        break;
    }
}

void Interface::keyEvent()
{
    if (isDownPress)
        isDownPress++;
    if (isUpPress)
        isUpPress++;
    if (isLeftPress)
        isLeftPress++;
    if (isRightPress)
        isRightPress++;
    isSpacePress = false;
}

bool Interface::isTimeToDraw()
{
    return ((unsigned int)clock() >= nextTick);
}

void Interface::setNextDrawTime()
{
    nextTick = clock() + static_cast<int> (timePeriod * CLOCKS_PER_SEC);
}

void Interface::setFramesPerSecond(double value)
{
    timePeriod = (1 / value);
}

int          Interface::isDownPress = 0;
int          Interface::isUpPress = 0;
int          Interface::isLeftPress = 0;
int          Interface::isRightPress = 0;
bool         Interface::isSpacePress = false;
bool         Interface::initialized = false;
double       Interface::timePeriod = 1.0 / 30;
unsigned int Interface::nextTick = 0;
void* Interface::p = NULL;
void (*Interface::callBack)(const Interface*, void*) = NULL;

Interface::~Interface()
{
}

void Interface::initialize(int argc, char** argv, const char* title, vec2 topLeft, vec2 bottomRight)
{
    if (initialized)
        return;
    // rand num generator
    srand((unsigned int)time(NULL));

    // create window
    glutInit(&argc, argv);
    vec2 point;
    glutInitWindowSize(
        (int)(bottomRight.getX() - topLeft.getX()),
        (int)(topLeft.getY() - bottomRight.getY()));

    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow(title);
    glutIgnoreKeyRepeat(true);


    glClearColor(0, 0, 0, 0);
    gluOrtho2D((int)topLeft.getX(), (int)bottomRight.getX(),
        (int)bottomRight.getY(), (int)topLeft.getY());

    glutDisplayFunc(drawCallback);
    glutIdleFunc(drawCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(keyDownCallback);
    glutSpecialUpFunc(keyUpCallback);
    initialized = true;

    return;
}

void Interface::run(void (*callBack)(const Interface*, void*), void* p)
{
    this->p = p;
    this->callBack = callBack;

    glutMainLoop();

    return;
}

