#pragma once

#include <map>
#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> SamuraiArcherAnimationPath = {
    {SamuraiArcherState::WALK, {"resources/imgs/kinghts/Samurai_Archer/Walk.png", 8}},
    {SamuraiArcherState::ATTACK1, {"resources/imgs/kinghts/Samurai_Archer/Attack_1.png", 5}},
    {SamuraiArcherState::ATTACK2, {"resources/imgs/kinghts/Samurai_Archer/Attack_2.png", 5}},
    {SamuraiArcherState::ATTACK3, {"resources/imgs/kinghts/Samurai_Archer/Attack_3.png", 6}},
    {SamuraiArcherState::HURT, {"resources/imgs/kinghts/Samurai_Archer/Hurt.png", 3}},
    {SamuraiArcherState::DEAD, {"resources/imgs/kinghts/Samurai_Archer/Dead.png", 5}},
    {SamuraiArcherState::SHOT,{"resources/imgs/kinghts/Samurai_Archer/Shot.png", 14}},
};

class SamuraiArcher : public IEntity
{
private:
public:
    SamuraiArcher();
    void setState(SDL_Renderer *renderer, EntityState newState) override;
};