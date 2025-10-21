#pragma once

#include <SDL3/SDL.h>
#include "Vector2.h"
#include "HPBar.h"
#include "EntityState.h"
#include "Animation.h"

class TargetingSystem;

class IEntity
{
protected:
    std::string name = "";
    int cost = 0;
    float curHP, maxHP;
    Transform transform;
    EntityState state;
    Animation *animation;
    HPBar *hpbar;
    bool isAlive = true;

    IEntity *attackTarget = nullptr;
    float AttackRanvge = 20.0f;

    bool attacking = false;
    float attackDamage = 0.1f;

    bool flip;

    float speed = 80.0f;

public:
    IEntity();
    virtual ~IEntity();

    virtual void update();
    virtual void render(SDL_Renderer *renderer);
    virtual void takeDamage(const IEntity &e);
    virtual void attack(SDL_Renderer *renderer) = 0;

    virtual void setState(SDL_Renderer *renderer, EntityState newState) = 0;
    virtual void setPos(float x, float y);
    virtual void setSize(float w, float y);
    virtual std::string getName();
    virtual int getCost();
    virtual bool getIsAlive();
    virtual Transform &getTransform();

    virtual int getAnimCurFrame()
    {
        return animation->getCurFrame();
    }

    virtual int getAnimFrameCount() {
        return animation->getFrameCount();
    }

    friend class TargetingSystem;
};
