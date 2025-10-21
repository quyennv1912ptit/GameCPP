#include "Arrow.h"
#include <cmath>

void Arrow::init(SDL_Renderer* renderer, float x, float y, float dx, float dy)
{
    transform.pos = {x, y};
    texture = IMG_LoadTexture(renderer,"resources/imgs/kinghts/Samurai_Archer/Arrow.png");

    float len = sqrt(dx * dx + dy * dy);
    vx = (dx / len) *speed;
    vy = (dy / len) *speed;

}

void Arrow::update(float dt)
{
    transform.pos.x += vx * dt;
    transform.pos.y += vy * dt;
}

void Arrow::render(SDL_Renderer* renderer) 
{
    SDL_FRect dest = {
        (int)transform.pos.x,
        (int)transform.pos.y,
          40, 10
        };
    SDL_RenderTexture(renderer, texture, NULL, &dest);
}