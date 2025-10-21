#include "Demon.h"

Demon::Demon()
{

    // attributes

    transform.size = {130, 130};

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 80;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void Demon::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = DemonAnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 180);
}