#pragma once
#include "IEnitity.h"

class MagicAttack
{
public:
    Transform transform;
    SDL_Texture* texture;
    float vx, vy;
    float angle=0;
    float speed = 200;

    void init(SDL_Renderer* renderer, float x, float y, float dx, float dy);
    void update(float dt);
    void render(SDL_Renderer* renderer);

    Vector2 getPos() const { return transform.pos;}
};