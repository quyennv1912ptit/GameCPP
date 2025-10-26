#include "Orc1.h"

Orc1::Orc1()
{
    // attributes

    name = "Orc1";

    transform.size = {100, 100};

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 80;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void Orc1::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = Orc1AnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 180);
}

void Orc1::attack(SDL_Renderer *renderer)
{
    setState(renderer, Orc1State::ATTACK);
    if (getAnimCurFrame() == 0)
    {
        attacking = true;
    }
    if (attacking && getAnimCurFrame() == getAnimFrameCount() - 1)
    {
        attackTarget->takeDamage(*(IEntity *)this);
        attacking = false;
    }
}