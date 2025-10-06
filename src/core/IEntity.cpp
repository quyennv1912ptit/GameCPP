#include "IEnitity.h"

IEntity::IEntity(float MaxHP, float x, float y)
{
    state = State::NONE;

    transform.pos = {x, y};
    transform.size = {200, 200};

    maxHP = MaxHP;
    flip = false;

    curHP = 100;

    animation = new Animation(transform);

    hpbar = new HPBar(maxHP, curHP, transform, SDL_Color{50, 50, 50, 255},
                      SDL_Color{200, 0, 0, 255},
                      10.0f, -60.0f, 100.0);
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

void IEntity::setState(SDL_Renderer *renderer, State newState)
{
    if (state == newState)
        return;

    state = newState;

    switch (state)
    {
    case State::WALK:
        animation->setAnim(renderer, "resources/imgs/kinghts/Samurai/Walk.png", 9, 200);
        break;
    case State::ATTACK:
        animation->setAnim(renderer, "resources/imgs/kinghts/Samurai/Attack_1.png", 4, 200);
        break;
    case State::HURT:
        animation->setAnim(renderer, "resources/imgs/kinghts/Samurai/Hurt.png", 3, 0.2);
        break;
    case State::DEAD:
        animation->setAnim(renderer, "resources/imgs/kinghts/Samurai/Dead.png", 6, 200);
        break;
    default:
        break;
    }
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