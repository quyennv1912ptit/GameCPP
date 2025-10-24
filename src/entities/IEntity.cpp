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

void IEntity::update()
{
    transform.pos.y = std::clamp(transform.pos.y, minY, maxY);

    if (curHP <= 0)
    {
        isAlive = false;
    }

    hpbar->Update();

    animation->flip = flip;
    animation->update();
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

bool IEntity::getIsAlive()
{
    return isAlive;
}

void IEntity::takeDamage(const IEntity &e)
{
    curHP -= e.attackDamage;
}

std::string IEntity::getName()
{
    return name;
}

int IEntity::getCost()
{
    return cost;
}