#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> MedusaAnimationPath = {
    {MedusaState::WALK, {"resources/imgs/enemies/medusa/Medusawalk.png", 4}},
    {MedusaState::ATTACK, {"resources/imgs/enemies/medusa/Medusaattack.png", 6}},
    {MedusaState::HURT, {"resources/imgs/enemies/medusa/Medusahurt.png", 2}},
    {MedusaState::DEAD, {"resources/imgs/enemies/medusa/Medusadead.png", 6}},
};

class Medusa : public IEntity
{
private:
public:
    Medusa();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void attack(SDL_Renderer *renderer) override {}
};