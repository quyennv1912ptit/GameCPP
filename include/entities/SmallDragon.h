#pragma once

#include <map>
#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> SmallDragonAnimationPath = {
    {SmallDragonState::WALK, {"resources/imgs/kinghts/small_dragon/walk.png", 4}},
    {SmallDragonState::ATTACK, {"resources/imgs/kinghts/small_dragon/Attack.png", 3}},
    {SmallDragonState::HURT, {"resources/imgs/kinghts/small_dragon/hurt.png", 3}},
    {SmallDragonState::DEAD, {"resources/imgs/kinghts/small_dragon/dead.png", 4}},
};

class SmallDragon : public IEntity
{
private:
public:
    SmallDragon();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
};