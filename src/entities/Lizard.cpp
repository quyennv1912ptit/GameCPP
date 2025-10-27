#include "Lizard.h"

Lizard::Lizard()
{
    // attributes
    // hasIdle = false;

    name = "Lizard";

    transform.size = {150, 150};

    attackDamage = 20.0f;

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {200, 0, 0, 255};

    curHP = maxHP = 70;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void Lizard::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = LizardAnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 190);
}

void Lizard::attack(SDL_Renderer *renderer)
{
    setState(renderer, LizardState::ATTACK);
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