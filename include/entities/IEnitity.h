#pragma once

#include "Animation.h"
#include "EntityState.h"
#include "HPBar.h"
#include "SDL3/SDL.h"
#include "Vector2.h"

class TargetingSystem;

class IEntity
{
protected:
    float minY = 860.0f / 4.0f;
    float maxY = 1670.0f / 4.0f;

    std::string name = "";
    float curHP, maxHP;
    Transform transform;
    Vector2 hitPos;
    EntityState state;
    Animation *animation = nullptr;
    HPBar *hpbar = nullptr;
    bool isAlive = true;

    IEntity *attackTarget = nullptr;
    float AttackRange = 20.0f;
    bool attacking = false;
    float attackDamage = 5.0f;
    float speed = 80.0f;

public:
    IEntity();
    IEntity *playerCastle = nullptr;
    IEntity *enemyCastle = nullptr;

    bool flip;
    virtual ~IEntity();

    virtual void update();
    virtual void render(SDL_Renderer *renderer);
    virtual void takeDamage(float dmg);
    virtual void attack(SDL_Renderer *renderer) = 0;

    virtual void setState(SDL_Renderer *renderer, EntityState newState) = 0;
    virtual void setPos(float x, float y);
    virtual void setSize(float w, float y);
    virtual std::string getName();
    virtual float getCurHP() { return curHP; }
    virtual float getMaxHP() { return maxHP; }
    virtual bool getIsAlive();
    virtual Transform &getTransform();
    virtual Vector2 &GetHitPos();

    virtual int getAnimCurFrame()
    {
        return animation->getCurFrame();
    }

    virtual int getAnimFrameCount()
    {
        return animation->getFrameCount();
    }

    virtual EntityState getState() const { return state; }
    virtual Vector2 getPos() const { return transform.pos; }
    virtual float getAttackRange() const { return AttackRange; }

    friend class TargetingSystem;
};
