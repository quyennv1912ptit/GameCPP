#pragma once

#include <SDL3/SDL.h>
#include "Vector2.h"
#include "HPBar.h"
#include "EntityState.h"
#include "Animation.h"

class IEntity
{
protected:
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
    virtual Transform &getTransform();
    virtual const Transform &getTransform() const;
    virtual EntityState getState() const;
    virtual Vector2 getPos() const;
};
