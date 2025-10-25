#pragma once

#include <SDL3/SDL.h>

#include "Vector2.h"

struct Transform {
	Vector2 pos;
	Vector2 size;
	float scale;
	float zIndex = 0;
	SDL_FRect toRect() { return (SDL_FRect){pos.x, pos.y, size.x, size.y}; }
};