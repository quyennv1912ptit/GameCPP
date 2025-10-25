#pragma once

#include <map>

#include "IEnitity.h"

const std::map<EntityState, std::pair<const char *, int>> DragonAnimationPath =
    {
        {DragonState::WALK, {"resources/imgs/kinghts/dragon/Walk.png", 5}},
        {DragonState::ATTACK, {"resources/imgs/kinghts/dragon/Attack.png", 4}},
        {DragonState::HURT, {"resources/imgs/kinghts/dragon/Hurt.png", 2}},
        {DragonState::DEAD, {"resources/imgs/kinghts/dragon/Dead.png", 5}},
};

class SmallDragon : public IEntity 
{
private: 

    std::vector<FireAttackS> fireAttacks; 
    
    bool hasFiredThisAnim = false; 
    
    float attackTimer = 0.0f; 
    float attackCooldown = 0.5f; 
    float moveSpeed = 80.0f; 
    float lifeTime = 3.0f; 
    
public: 
    SmallDragon(); 
    
    void setState(SDL_Renderer *renderer, EntityState newState) override; 
    void update(std::vector<IEntity*>& enemies, SDL_Renderer* renderer, float dt); 
    void render(SDL_Renderer* renderer); 
    void attack(SDL_Renderer *renderer) override; 
    void updateFireAttacks(std::vector<IEntity*>& enemies, float dt); 
    void handleFireAttack(SDL_Renderer* renderer, IEntity* target); 
    void renderFireAttacks(SDL_Renderer* renderer); 

};