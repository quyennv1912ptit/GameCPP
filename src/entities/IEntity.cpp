#include <iostream>

#include "Config.h"
#include "IEnitity.h"

IEntity::IEntity()
{
    state = EntityState::NONE;

    transform.pos = {0, 0};

    flip = false;

    animation = new Animation(transform);
}

IEntity::~IEntity()
{
    delete animation;
}

void IEntity::setPos(float x, float y)
{
    transform.pos = {x, y};
}

void IEntity::setSize(float w, float h)
{
    transform.size = {w, h};
}

// Transform& IEntity::getTransform() { return transform; }
// const Transform &IEntity::getTransform() const { return transform; }
EntityState IEntity::getState() const { return state; }
Vector2 IEntity::getPos() const { return transform.pos; }

void IEntity::update()
{
    if (name == "Castle")
    {
        if (!flip)
        {
            hitPos = {transform.pos.x + 20, transform.pos.y + transform.size.y - 90};
        }
        else
        {
            hitPos = {transform.pos.x + transform.size.x - 20, transform.pos.y + transform.size.y - 90};
        }
    }
    else
    {
        hitPos = {transform.pos.x + transform.size.x / 2, transform.pos.y + transform.size.y / 2};
    }

    if (curHP <= 0)
    {
        isAlive = false;
    }
}

void IEntity::takeDamage(float dmg)
{
    curHP -= dmg;
    if (curHP <= 0)
    {
        curHP = 0;
        isAlive = false;
    }
    hpbar->Update();
}

void IEntity::render(SDL_Renderer *renderer)
{
    animation->render(renderer);
    hpbar->Render(renderer);
}

Transform &IEntity::getTransform()
{
    return transform;
}

Vector2 &IEntity::GetHitPos()
{
    return hitPos;
}

bool IEntity::getIsAlive()
{
    return isAlive;
}

std::string IEntity::getName()
{
    return name;
}