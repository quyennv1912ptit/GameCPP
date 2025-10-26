#include "Castle.h"

void Castle::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto c = CastleAnimationPath.at(state);

    animation->setAnim(renderer, c.first, c.second, 150);
}

void Castle::attack(SDL_Renderer *renderer)
{
    setState(renderer, CastleState::IDLE);

    if (getAnimCurFrame() == 0)
    {
        attackTarget->takeDamage(*(IEntity *)this);
    }
}

void Castle::setFlip(bool value)
{
    flip = value;
}

Castle::Castle(bool Is_Enemy)
{
    // attributes
    name = "Castle";
    this->Is_Enemy = Is_Enemy;

    transform.size = {278, 566};

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg;
    if (this->Is_Enemy)
    {
        fg = {200, 0, 0, 255};
        flip = false;
    }
    else
    {
        flip = true;
        fg = {0, 200, 0, 255};
    }

    curHP = maxHP = 200;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 10, -20, 200);
    // flip=true;
}