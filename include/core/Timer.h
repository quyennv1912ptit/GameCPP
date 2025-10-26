#pragma once

#include <SDL3/SDL.h>

class Timer
{
private:
    int startTime;

public:
    void start();
    int elapsedTime();
};