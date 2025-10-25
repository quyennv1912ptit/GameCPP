#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> LizardAnimationPath =
    {
        {LizardState::WALK,
         {"resources/imgs/enemies/lizard/lizardwalk.png", 6}},
        {LizardState::ATTACK,
         {"resources/imgs/enemies/lizard/lizardattack.png", 5}},
        {LizardState::HURT,
         {"resources/imgs/enemies/lizard/lizardhurt.png", 2}},
        {LizardState::DEAD,
         {"resources/imgs/enemies/lizard/lizarddead.png", 6}},
         {LizardState::IDLE,
         {"resources/imgs/enemies/lizard/lizardidle.png", 3}},
};

class Lizard : public IEntity {
   private:
   public:
	Lizard();
	void setState(SDL_Renderer *renderer, EntityState newState) override;
	void attack(SDL_Renderer *renderer) override;
};