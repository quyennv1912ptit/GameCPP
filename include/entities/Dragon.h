#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> DragonAnimationPath = {
    {DragonState::WALK, {"resources/imgs/kinghts/dragon/Walk.png", 5}},
    {DragonState::ATTACK, {"resources/imgs/kinghts/dragon/Attack.png", 4}},
    {DragonState::HURT, {"resources/imgs/kinghts/dragon/Hurt.png", 2}},
    {DragonState::DEAD, {"resources/imgs/kinghts/dragon/Dead.png", 5}},
};

class Dragon : public IEntity
{
private:
public:
    Dragon();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void attack(SDL_Renderer *renderer) override {};
};