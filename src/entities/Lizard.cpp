#include "Lizard.h"

#include <iostream>
Lizard::Lizard()
{
    // attributes

    name = "Lizard";

    cost = 0;

    transform.size = {150, 150};

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {200, 0, 0, 255};

    curHP = maxHP = 10;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void Lizard::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = LizardAnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 180);
}
void Lizard::attack(SDL_Renderer *renderer)
{
    setState(renderer, LizardState::ATTACK);
    if (getAnimCurFrame() == 0)
    {
        attackTarget->takeDamage(*(IEntity *)this);
    }
}