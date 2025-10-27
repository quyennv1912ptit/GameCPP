#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> Orc1AnimationPath = {
    {Orc1State::WALK, {"resources/imgs/enemies/orc1/orc1_walk_full .png", 6}},
    {Orc1State::ATTACK, {"resources/imgs/enemies/orc1/orc1_attack_full.png", 8}},
    {Orc1State::HURT, {"resources/imgs/enemies/orc1/orc1_hurt_full.png", 6}},
    {Orc1State::DEAD, {"resources/imgs/enemies/orc1/orc1_death_full.png", 8}},
    {Orc1State::IDLE, {"resources/imgs/enemies/orc1/Idle.png", 1}},
};

class Orc1 : public IEntity
{
private:
public:
    Orc1();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void attack(SDL_Renderer *renderer) override;
};