#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> DemonAnimationPath = {
    {DemonState::WALK, {"resources/imgs/enemies/demon/Walk.png", 6}},
    {DemonState::ATTACK, {"resources/imgs/enemies/demon/Attack.png", 4}},
    {DemonState::HURT, {"resources/imgs/enemies/demon/Hurt.png", 2}},
    {DemonState::DEAD, {"resources/imgs/enemies/demon/Dead.png", 6}},
    {DemonState::IDLE, {"resources/imgs/enemies/demon/Idle.png", 3}}};

class Demon : public IEntity
{
private:
public:
    Demon();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void attack(SDL_Renderer *renderer) override;
};