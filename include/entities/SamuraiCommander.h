#pragma once

#include <map>
#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> SamuraiCommanderAnimationPath = {
    {SamuraiCommanderState::WALK, {"resources/imgs/kinghts/Samurai_Commander/Walk.png", 9}},
    {SamuraiCommanderState::ATTACK1, {"resources/imgs/kinghts/Samurai_Commander/Attack_1.png", 4}},
    {SamuraiCommanderState::ATTACK2, {"resources/imgs/kinghts/Samurai_Commander/Attack_2.png", 5}},
    {SamuraiCommanderState::ATTACK3, {"resources/imgs/kinghts/Samurai_Commander/Attack_3.png", 4}},
    {SamuraiCommanderState::HURT, {"resources/imgs/kinghts/Samurai_Commander/Hurt.png", 2}},
    {SamuraiCommanderState::DEAD, {"resources/imgs/kinghts/Samurai_Commander/Dead.png", 6}},
};

class SamuraiCommander : public IEntity
{
private:
public:
    SamuraiCommander();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
};