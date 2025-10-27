#include "Dragon.h"
#include <cmath>

Dragon::Dragon()
{

    // attributes

    transform.size = {100, 100};

    name = "Small Dragon";

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 280;

    AttackRange = 150.0f;

    state = DragonState::WALK;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -70, 60);
}

void Dragon::update(std::vector<IEntity *> &enemies, SDL_Renderer *renderer, float dt)
{

    animation->update();
    hpbar->Update();

    bool hasAliveEnemies = false;

    for (IEntity *e : enemies)
    {
        if (e->getIsAlive())
        {
            hasAliveEnemies = true;
            break;
        }
    }

    if (!hasAliveEnemies)
    {
        if (state != DragonState::WALK)
        {
            setState(renderer, DragonState::WALK);
        }
        return;
    }

    this->target = nullptr;
    float minDist = 1e9f;
    Vector2 myCenter = {transform.pos.x + transform.size.x * 0.5f,
                        transform.pos.y + transform.size.y * 0.5f};

    for (IEntity *e : enemies)
    {
        if (!e->getIsAlive())
            continue;
        Transform t = e->getTransform();
        Vector2 targetCenter = {t.pos.x + t.size.x * 0.5f, t.pos.y + t.size.y * 0.5f};
        float dx = targetCenter.x - myCenter.x;
        float dy = targetCenter.y - myCenter.y;
        float dist = sqrt(dx * dx + dy * dy);
        if (dist < minDist)
        {
            minDist = dist;
            this->target = e;
        }
    }

    if (!target || !target->getIsAlive())
    {
        if (state != DragonState::WALK)
        {
            setState(renderer, DragonState::WALK);
        }

        return;
    }

    Transform targetT = target->getTransform();
    Vector2 targetCenter = {targetT.pos.x + targetT.size.x * 0.5f,
                            targetT.pos.y + targetT.size.y * 0.5f};

    flip = (targetCenter.x < myCenter.x);
    animation->flip = flip;

    if (minDist > AttackRange)
    {
        float dx = targetCenter.x - myCenter.x;
        float dy = targetCenter.y - myCenter.y;
        float len = sqrt(dx * dx + dy * dy);

        if (len > 0)
        {
            transform.pos.x += (dx / len) * moveSpeed * dt;
            transform.pos.y += (dy / len) * moveSpeed * dt;
        }

        if (state != DragonState::WALK)
        {
            setState(renderer, DragonState::WALK);
        }
    }
    else
    {
        switch (state)
        {
        case DragonState::WALK:
            setState(renderer, DragonState::ATTACK);
            attacking = true;
            break;

        case DragonState::ATTACK:
            if (animation->getCurFrame() == 0)
            {
                attacking = true;
            }

            attack(renderer);

            break;

        default:
            setState(renderer, DragonState::ATTACK);
            attacking = true;
            break;
        }
    }
}

void Dragon::attack(SDL_Renderer *renderer)
{
    const int fireFrame = 6;
    if (attacking && animation->getCurFrame() == fireFrame)
    {
        if (target && target->getIsAlive())
            target->takeDamage(45);

        attacking = false;
    }
}

void Dragon::render(SDL_Renderer *renderer)
{
    animation->render(renderer);
    hpbar->Render(renderer);
}

void Dragon::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;

    if (DragonAnimationPath.find(state) != DragonAnimationPath.end())
    {
        auto p = DragonAnimationPath.at(state);

        animation->setAnim(renderer, p.first, p.second, 280);
        animation->setFrame(0);
    }
}