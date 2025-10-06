#pragma once

#include <SDL3/SDL.h>
#include "Vector2.h"
#include "Animation.h"
#include "HPBar.h"

enum class State
{
    NONE,
    WALK,
    ATTACK,
    HURT,
    DEAD
};

class IEntity
{
protected:
    float curHP, maxHP;
    Transform transform;
    State state;
    Animation *animation;
    HPBar* hpbar;
    bool flip;

public:
    IEntity(float maxHP, float x, float y);
    virtual ~IEntity();

    virtual void update();
    virtual void render(SDL_Renderer* renderer);

    void setState(SDL_Renderer* renderer, State newState);
    void setPos(float x, float y);
    void setSize(float w, float y);
    Transform& getTransform();
};
