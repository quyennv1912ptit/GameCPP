#pragma once 

#include <map> 

#include "IEnitity.h" 
#include "FireAttackS.h" 

const std::map<EntityState, std::pair<const char *, int>> SmallDragonAnimationPath = 
{ 
    {SmallDragonState::WALK, {"resources/imgs/kinghts/small_dragon/Walk.png", 4}}, 
    {SmallDragonState::ATTACK, {"resources/imgs/kinghts/small_dragon/Attack.png", 3}}, 
    {SmallDragonState::HURT, {"resources/imgs/kinghts/small_dragon/Hurt.png", 2}}, 
    {SmallDragonState::DEAD, {"resources/imgs/kinghts/small_dragon/Dead.png", 4}}, 
    {SmallDragonState::FIRE, {"resources/imgs/kinghts/small_dragon/Fire_Attack.png", 9}}, 
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