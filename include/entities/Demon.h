#pragma once

#include <map>
#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> DemonAnimationPath = {
    {DemonState::WALK, {"resources/imgs/enemies/demon/demonwalk.png", 6}},
    {DemonState::ATTACK, {"resources/imgs/enemies/demon/demonattack.png", 4}},
    {DemonState::HURT, {"resources/imgs/enemies/demon/demonhurt.png", 2}},
    {DemonState::DEAD, {"resources/imgs/enemies/demon/demondead.png", 6}},
};

class Demon : public IEntity
{
private:
public:
    Demon();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
};