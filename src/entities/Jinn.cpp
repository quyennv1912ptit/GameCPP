#include "Jinn.h"

Jinn::Jinn()
{
    // attributes

    name = "Jinn";

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    attackDamage = 35.0f;

    curHP = maxHP = 80;

    curHP = maxHP = 100.0f;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -20, 60);
}

void Jinn::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = JinnAnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 80);
}

void Jinn::attack(SDL_Renderer *renderer)
{
    setState(renderer, JinnState::ATTACK);
    if (getAnimCurFrame() == 0)
    {
        attacking = true;
    }

    if (attacking && getAnimCurFrame() == 11)
    {
        attackTarget->takeDamage(attackDamage);
        attacking = false;
    }
}