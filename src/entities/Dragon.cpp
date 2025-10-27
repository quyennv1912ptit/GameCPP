#include "Dragon.h"
#include <cmath>

Dragon::Dragon()
{

    // attributes

    transform.size = {300, 300};

    name = "Dragon";

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 400;

    AttackRange = 100.0f;

    attackDamage = 80.0f;

    speed = 40.0f;

    state = DragonState::WALK;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -80, 80);
}

void Dragon::attack(SDL_Renderer *renderer)
{
    setState(renderer, DragonState::ATTACK);

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

void Dragon::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;

    auto p = DragonAnimationPath.at(state);
    animation->setAnim(renderer, p.first, p.second, 280);
}