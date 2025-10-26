#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> JinnAnimationPath = {
    {JinnState::WALK, {"resources/imgs/enemes/jinn/jiinflight.png", 5}},
    {JinnState::ATTACK, {"resources/imgs/enemies/jinn/jiinattack.png", 4}},
    {JinnState::HURT, {"resources/imgs/enemies/jinn/jiinhurt.png", 2}},
    {JinnState::DEAD, {"resources/imgs/enemies/jinn/jiindead.png", 6}},
};

class Jinn : public IEntity
{
private:
public:
    Jinn();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void attack(SDL_Renderer *renderer) override {}
};