#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> CastleAnimationPath = {
    {CastleState::IDLE,{"resources/imgs/castle/1/Asset 1+2+3.png",1}},
    {CastleState::DAMAGED,{"resources/imgs/castle/1/castledamaged.png",1}},
    {CastleState::DESTROYED,{"resources/imgs/castle/1/castledestroyed.png",1}},
    {CastleState::HURT,{"resources/imgs/castle/1/Asset 1+2+3.png",2}},
    {CastleState::ATTACK,{"resources/imgs/castle/1/castledamaged.png",3}},
    {CastleState::DEAD,{"resources/imgs/castle/1/castledestroyed.png",5}},
    {CastleState::WALK,{"resources/imgs/castle/1/castledestroyed.png",5}},
    {CastleState::NONE,{"resources/imgs/castle/1/castledestroyed.png",5}},
};

class Castle : public IEntity {
   private:
    bool Is_Enemy;
   public:
	
    Castle(bool Is_Enemy);
	void setState(SDL_Renderer *renderer, EntityState newState) override;
	void attack(SDL_Renderer *renderer) override;
    void setFlip(bool value);
    
};