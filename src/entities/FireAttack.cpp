#include "FireAttack.h"
#include <cmath>

void FireAttack::init(SDL_Renderer* renderer, float x , float y, float dx, float dy)
{
    transform.pos = {x, y};
    anim = new Animation(transform);
    anim->setAnim(renderer,"resources/imgs/kinghts/small_dragon/fireAttack.png", 9, 80);

    float len = sqrt(dx * dx + dy * dy);
    vx = (dx / len) *speed;
    vy = (dy / len) *speed;

    angle = atan2(vy, vx) *180.0f / M_PI;
}

void FireAttack::update(float dt)
{
    transform.pos.x += vx * dt;
    transform.pos.y += vy * dt;

    if(anim) anim->update();
}

void FireAttack::render(SDL_Renderer* renderer) 
{
    if(!anim) return;

    SDL_FRect srcRect = anim->getSrcRect();

    const float Width = 80.0f;
    const float Height = 40.0f;

    SDL_FRect dest = {
        transform.pos.x - Width / 2.0f,
        transform.pos.y - Height / 2.0f,
        Width, Height,
        };

    SDL_FPoint center = {dest.w * 0.75f, dest.h / 2.0f};
    SDL_RenderTextureRotated(renderer, anim->getTexture(), &srcRect, &dest, angle, &center, SDL_FLIP_NONE);
}