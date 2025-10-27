#include "SmallDragon.h"
#include <cmath>

SmallDragon::SmallDragon()
{

    // attributes

    transform.size = {100, 100};

    name = "Small Dragon";

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 130;

    AttackRange = 100.0f;

    speed = 80.0f;

    attackDamage = 25.0f;

    state = SmallDragonState::WALK;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void SmallDragon::attack(SDL_Renderer *renderer)
{
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

void SmallDragon::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = SmallDragonAnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 200);
}