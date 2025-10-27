#include "SamuraiCommander.h"

SamuraiCommander::SamuraiCommander()
{
    // attributes

    transform.size = {100, 100};

    name = "Samurai Commander";

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 180;

    attackDamage = 35.0f;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void SamuraiCommander::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = SamuraiCommanderAnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 300);
}

void SamuraiCommander::attack(SDL_Renderer *renderer)
{
    setState(renderer, atks[atk_index]);

    if (getAnimCurFrame() == getAnimFrameCount() - 1)
    {
        attackTarget->takeDamage(attackDamage);
        atk_index = (atk_index + 1) % atks.size();
    }
}