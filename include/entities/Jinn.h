#pragma once

#include <map>
#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> JinnAnimationPath = {
    {JinnState::WALK, {"resources/imgs/enemies/jinn/jiinflight.png", 5}},
    {JinnState::ATTACK, {"resources/imgs/enemies/jinn/JinAttack.png", 16}},
    {JinnState::HURT, {"resources/imgs/enemies/jinn/jiinhurt.png", 2}},
    {JinnState::DEAD, {"resources/imgs/enemies/jinn/jiindead.png", 6}},
};

class Jinn : public IEntity {
   private:
    float attackDamage = 0.5f;
   public:
	Jinn();
	void setState(SDL_Renderer *renderer, EntityState newState) override;
	void attack(SDL_Renderer *renderer) override ;
    bool hasAttackedThisAnim = false;
};