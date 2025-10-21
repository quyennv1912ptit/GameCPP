#pragma once

#include <map>
#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> DemonAnimationPath = {
    {DemonState::WALK, {"resources/imgs/enemies/demon/demonwalk.png", 6}},
    {DemonState::ATTACK, {"resources/imgs/enemies/demon/demonattack.png", 4}},
    {DemonState::HURT, {"resources/imgs/enemies/demon/demonhurt.png", 2}},
    {DemonState::DEAD, {"resources/imgs/enemies/demon/demondead.png", 6}},
    {DemonState::IDLE, {"resources/imgs/enemies/demon/demonidle.png", 3}}
};

class Demon : public IEntity
{
private:
public:
    Demon();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void attack(SDL_Renderer* renderer) override;
};