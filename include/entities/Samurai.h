#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> SamuraiAnimationPath = {
    {SamuraiState::WALK, {"resources/imgs/kinghts/Samurai/Walk.png", 9}},
    {SamuraiState::ATTACK1, {"resources/imgs/kinghts/Samurai/Attack_1.png", 4}},
    {SamuraiState::ATTACK2, {"resources/imgs/kinghts/Samurai/Attack_2.png", 5}},
    {SamuraiState::ATTACK3, {"resources/imgs/kinghts/Samurai/Attack_3.png", 4}},
    {SamuraiState::HURT, {"resources/imgs/kinghts/Samurai/Hurt.png", 3}},
    {SamuraiState::DEAD, {"resources/imgs/kinghts/Samurai/Dead.png", 6}},
    {SamuraiState::IDLE, {"resources/imgs/kinghts/Samurai/Idle.png", 6}}};

class Samurai : public IEntity
{
private:
    int atk_index = 0;
    const std::vector<EntityState> atks = {
        SamuraiState::ATTACK1, SamuraiState::ATTACK2, SamuraiState::ATTACK3};

public:
    Samurai();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
    void attack(SDL_Renderer *renderer) override;
};