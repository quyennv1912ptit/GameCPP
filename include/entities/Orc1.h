#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> Orc1AnimationPath = {
    {Orc1State::WALK, {"resources/imgs/enemies/orc1/orc1walk.png", 6}},
    {Orc1State::ATTACK, {"resources/imgs/enemies/orc1/orc1attack.png", 8}},
    {Orc1State::HURT, {"resources/imgs/enemies/orc1/orc1hurt.png", 6}},
    {Orc1State::DEAD, {"resources/imgs/enemies/orc1/orc1dead.png", 8}},
};

class Orc1 : public IEntity
{
private:
public:
    Orc1();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void attack(SDL_Renderer *renderer) override {}
};