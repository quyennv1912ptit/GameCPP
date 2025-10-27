#pragma once

#include "IEnitity.h"
#include <map>

const std::map<EntityState, std::pair<const char *, int>> SmallDragonAnimationPath =
    {
        {SmallDragonState::WALK, {"resources/imgs/kinghts/small_dragon/Walk.png", 4}},
        {SmallDragonState::ATTACK, {"resources/imgs/kinghts/small_dragon/ATTACK (3).png", 11}},
        {SmallDragonState::HURT, {"resources/imgs/kinghts/small_dragon/Hurt.png", 2}},
        {SmallDragonState::DEAD, {"resources/imgs/kinghts/small_dragon/Dead.png", 4}},
};
class SmallDragon : public IEntity
{
private:
    bool hasFiredThisAnim = false;

    float moveSpeed = 80.0f;

    IEntity *target = nullptr;

public:
    SmallDragon();

    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void update(std::vector<IEntity *> &enemies, SDL_Renderer *renderer, float dt);
    void render(SDL_Renderer *renderer);
    void attack(SDL_Renderer *renderer) override;
};