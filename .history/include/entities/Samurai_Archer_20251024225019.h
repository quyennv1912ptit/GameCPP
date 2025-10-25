#pragma once

#include "IEnitity.h"
#include "Arrow.h"
#include <vector>

const std::map<EntityState, std::pair<const char*, int>> SamuraiArcherAnimationPath = {
    {SamuraiArcherState::IDLE, {"resources/imgs/kinghts/Samurai_Archer/Idle.png", 4}},
    {SamuraiArcherState::WALK, {"resources/imgs/kinghts/Samurai_Archer/Walk.png", 8}},
    {SamuraiArcherState::ATTACK, {"resources/imgs/kinghts/Samurai_Archer/Attack.png", 6}},
    {SamuraiArcherState::HURT, {"resources/imgs/kinghts/Samurai_Archer/Hurt.png", 2}},
    {SamuraiArcherState::DEAD, {"resources/imgs/kinghts/Samurai_Archer/Dead.png", 4}}
};

class SamuraiArcher : public IEntity
{
private:
    std::vector<Arrow> arrows;
    bool hasFiredThisAnim = false;
    float attackTimer = 0.0f;
    float attackCooldown = 0.8f;
    float moveSpeed = 90.0f;

public:
    SamuraiArcher();
    void setState(SDL_Renderer* renderer, EntityState newState) override;
    void update(std::vector<IEntity*>& enemies, SDL_Renderer* renderer, float dt);
    void render(SDL_Renderer* renderer);
    void attack(SDL_Renderer* renderer) override;
    void updateArrows(std::vector<IEntity*>& enemies, float dt);
    void handleArrowAttack(SDL_Renderer* renderer, IEntity* target);
    void renderArrows(SDL_Renderer* renderer);
};
