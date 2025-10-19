#pragma once

#include <SDL3/SDL.h>
#include "Vector2.h"
#include "HPBar.h"
#include "EntityState.h"
#include "Animation.h"

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
    bool flip;

public:
    IEntity();
    virtual ~IEntity();

    virtual void update();
    virtual void render(SDL_Renderer *renderer);

    virtual void setState(SDL_Renderer *renderer, EntityState newState) = 0;
    virtual void setPos(float x, float y);
    virtual void setSize(float w, float y);
    virtual std::string getName();
    virtual int getCost();
    virtual Transform &getTransform();
};
