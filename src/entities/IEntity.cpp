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
    if(moving)
    {
        float dx = targetPos.pos.x - transform.pos.x;
        float dy = targetPos.pos.y - transform.pos.y;
        float dist = sqrt(dx*dx + dy*dy);

        if(dist < speed)
        {
            transform.pos = targetPos.pos;
            moving = false;
        }
        else
        {
            transform.pos.x += speed * dx / dist;
            transform.pos.y += speed * dy / dist;
        }

        state = EntityState::WALK;
        flip = (dx < 0);
    }
    else
    {
        state = EntityState::IDLE;
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