#pragma once

#include <map>
#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> DragonAnimationPath = {
    {DragonState::WALK, {"resources/imgs/kinghts/dragon/walkdragon.png", 5}},
    {DragonState::ATTACK, {"resources/imgs/kinghts/dragon/dragonattack.png", 6}},
    {DragonState::HURT, {"resources/imgs/kinghts/dragon/hurtdragon.png", 2}},
    {DragonState::DEAD, {"resources/imgs/kinghts/dragon/deaddragon.png", 5}},
};

class Dragon : public IEntity
{
private:
public:
    Dragon();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
};