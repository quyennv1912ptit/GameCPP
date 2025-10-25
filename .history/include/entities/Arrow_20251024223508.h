#pragma once

#include "IEntity.h"
#include "Animation.h"
#include <SDL3/SDL.h>
#include <cmath>

class Arrow
{
public:
    Transform transform;
    Animation* animation;
    float vx, vy;
    float speed = 400.0f;
    float angle = 0.0f;
    float damage = 0.0f;
    float lifeTime = 2.5f;

    Arrow() : animation(nullptr), vx(0), vy(0) {}

    void init(SDL_Renderer* renderer, float x, float y, float dx, float dy, float dmg);
    void update(float dt);
    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
};
