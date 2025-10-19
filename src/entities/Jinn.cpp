#include "Jinn.h"

Jinn::Jinn()
{

    // attributes

    name = "Jinn";

    cost = 0;

    transform.size = {100, 100};

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 80;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void Jinn::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = JinnAnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 180);
}