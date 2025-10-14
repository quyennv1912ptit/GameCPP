#pragma once

#include <map>
#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> Orc2AnimationPath = {
    {Orc2State::WALK, {"resources/imgs/enemies/orc1/orc2walk.png", 6}},
    {Orc2State::ATTACK, {"resources/imgs/enemies/orc1/orc2attack.png", 8}},
    {Orc2State::HURT, {"resources/imgs/enemies/orc1/orc2hurt.png", 6}},
    {Orc2State::DEAD, {"resources/imgs/enemies/orc1/orc2dead.png", 8}},
};

class Orc2 : public IEntity
{
private:
public:
    Orc2();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
};