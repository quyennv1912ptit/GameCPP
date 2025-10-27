#include "Samurai.h"

#include <iostream>
Samurai::Samurai()
{
    // attributes

    transform.size = {100, 100};

    name = "Samurai";

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 50;

    attackDamage = 15.0f;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void Samurai::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = SamuraiAnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 250);
}

void Samurai::attack(SDL_Renderer *renderer)
{
    setState(renderer, atks[atk_index]);
    if (getAnimCurFrame() == 0)
    {
        attacking = true;
    }
    if (attacking && getAnimCurFrame() == getAnimFrameCount() - 1)
    {
        attackTarget->takeDamage(attackDamage);
        atk_index = (atk_index + 1) % atks.size();
        attacking = false;
    }
}