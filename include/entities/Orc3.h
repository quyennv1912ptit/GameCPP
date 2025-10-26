#pragma once

#include <map>
#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> Orc3AnimationPath = {
    {Orc3State::WALK, {"resources/imgs/enemies/orc3/orc3_walk_full.png", 6}},
    {Orc3State::ATTACK, {"resources/imgs/enemies/orc3/orc3_attack_full.png", 8}},
    {Orc3State::HURT, {"resources/imgs/enemies/orc3/orc3_hurt_full.png", 6}},
    {Orc3State::DEAD, {"resources/imgs/enemies/orc3/orc3_death_full.png", 8}},
};


class Orc3 : public IEntity {
   private:
   public:
	Orc3();
	void setState(SDL_Renderer *renderer, EntityState newState) override;
	void attack(SDL_Renderer *renderer) override ;

};