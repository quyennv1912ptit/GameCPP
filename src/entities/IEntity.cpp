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
    const bool *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_W])
    {
        transform.pos.y -= 3;
    }
    if (keys[SDL_SCANCODE_A])
    {
        flip = true;
        transform.pos.x -= 3;
    }
    if (keys[SDL_SCANCODE_S])
    {
        transform.pos.y += 3;
    }
    if (keys[SDL_SCANCODE_D])
    {
        flip = false;
        transform.pos.x += 3;
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