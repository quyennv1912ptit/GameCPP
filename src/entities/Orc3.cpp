#include "Orc3.h"

Orc3::Orc3()
{
    // attributes
    name = "Orc3";

    transform.size = {100, 100};

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {200, 0, 0, 255};

    curHP = maxHP = 65;

    attackDamage = 20.0f;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void Orc3::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = Orc3AnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 180);
}


void Orc3::attack(SDL_Renderer *renderer)
{
    setState(renderer, Orc3State::ATTACK);
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