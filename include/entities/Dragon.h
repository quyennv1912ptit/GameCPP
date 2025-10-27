#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> DragonAnimationPath =
    {
        {DragonState::WALK, {"resources/imgs/kinghts/dragon/Walk.png", 5}},
        {DragonState::ATTACK, {"resources/imgs/kinghts/dragon/Attack (1).png", 10}},
        {DragonState::HURT, {"resources/imgs/kinghts/dragon/Hurt.png", 2}},
        {DragonState::DEAD, {"resources/imgs/kinghts/dragon/Dead.png", 5}},
};

class Dragon : public IEntity
{
private:
    bool hasFiredThisAnim = false;

    float moveSpeed = 40.0f;

    IEntity *target = nullptr;

public:
    Dragon();

    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void update(std::vector<IEntity *> &enemies, SDL_Renderer *renderer, float dt);
    void render(SDL_Renderer *renderer);
    void attack(SDL_Renderer *renderer) override;
};