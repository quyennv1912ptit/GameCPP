
#pragma once 
#include <map> 
#include "IEnitity.h" 
#include "Arrow.h" 
const std::map<EntityState, std::pair<const char *, int>> SamuraiArcherAnimationPath = 
{ 
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
private: float attackRange = 800.0f; 
     float attackCooldown = 2.3f; 
     float attackTimer = 0.0f; 
     std::vector<Arrow> arrows; 
     bool hasShotThisAnim = false; 
     float moveSpeed = 100.0f; 

public: 
     
     SamuraiArcher(); 
     void setState(SDL_Renderer *renderer, EntityState newState) override; 
     void update(std::vector<IEntity*> &enemies, SDL_Renderer *renderer, float dt); 
     void render(SDL_Renderer *renderer); 
     void attack(SDL_Renderer *renderer) override; 
     bool checkCollision(const SDL_Rect& a, const Transform& b); 


};