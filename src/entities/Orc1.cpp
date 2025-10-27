#include "Orc1.h"

Orc1::Orc1()
{
    // attributes
    hasIdle = false;

    name = "Orc1";

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};
    transform.size = {64, 64};

    curHP = maxHP = 60;

    attackDamage = 15.0f;

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
        attackTarget->takeDamage(attackDamage);
        attacking = false;
    }
}