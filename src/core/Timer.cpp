#include "Timer.h"

void Timer::start() {
    startTime = (int)SDL_GetTicks();
}

int Timer::elapsedTime() {
    return (int)SDL_GetTicks() - startTime;
}