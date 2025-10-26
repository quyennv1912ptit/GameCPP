#include "SmallDragon.h"

#include <cmath>


SmallDragon::SmallDragon()
{

    // attributes

    transform.size = {100, 100};

    name = "Small Dragon";

    cost = 100;


    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 100;

    AttackRange = 200.0f;

    state = SmallDragonState::WALK;


    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void SmallDragon::update(std::vector<IEntity*>& enemies, SDL_Renderer* renderer, float dt)
{
    animation->update();
    hpbar->Update();

    bool hasAliveEnemies = false;

    
    for(IEntity* e : enemies) 
    {
        if(e->getIsAlive()) 
        {
            hasAliveEnemies = true;
            break;
        }
    }

    if(!hasAliveEnemies) 
    {
        if(state != SmallDragonState::WALK)
        {
            setState(renderer, SmallDragonState::WALK);
        }
        return;
    }

    this->target = nullptr;
    float minDist = 1e9f;
    Vector2 myCenter = { transform.pos.x + transform.size.x * 0.3f,
                         transform.pos.y + transform.size.y * 0.5f };

    for(IEntity* e : enemies)
    {   
        if(!e->getIsAlive()) continue;
        Transform t = e->getTransform();
        Vector2 targetCenter = { t.pos.x + t.size.x * 0.5f, t.pos.y + t.size.y * 0.5f };
        float dx = targetCenter.x - myCenter.x;
        float dy = targetCenter.y - myCenter.y;
        float dist = sqrt(dx*dx + dy*dy);
        if(dist < minDist) { minDist = dist; this->target = e; }
    }

    if(!target || !target->getIsAlive())
    {
        if(state != SmallDragonState::WALK)
        {
            setState(renderer, SmallDragonState::WALK);
        }

        return;
    }

    Transform targetT = target->getTransform();
    Vector2 targetCenter = { targetT.pos.x + targetT.size.x * 0.5f,
                             targetT.pos.y + targetT.size.y * 0.5f };

    flip = (targetCenter.x < myCenter.x);
        animation->flip = flip;

    if(minDist > AttackRange)
    {
            float dx = targetCenter.x - myCenter.x;
            float dy = targetCenter.y - myCenter.y;
            float len = sqrt(dx*dx + dy*dy);

            if(len > 0 )
            {
            transform.pos.x += (dx / len) * moveSpeed * dt;
            transform.pos.y += (dy / len) * moveSpeed * dt;
            }

            if(state != SmallDragonState::WALK)
            {
                setState(renderer, SmallDragonState::WALK);
            }
           
    }
    else
    {
        switch (state)
        {
        case SmallDragonState::WALK:
            setState(renderer, SmallDragonState::ATTACK);
            hasFiredThisAnim = false;
            break;

        case SmallDragonState::ATTACK:
            if(animation->getCurFrame()== animation->getFrameCount() - 1) 
            {
                hasFiredThisAnim = false;
            }
            
            attack(renderer);
            break;

        default:
            setState(renderer, SmallDragonState::ATTACK);
            hasFiredThisAnim = false;
            break;
        }
    }

}

void SmallDragon::attack(SDL_Renderer* renderer)
{
    const int fireFrame = 4;
    if(!hasFiredThisAnim && animation->getCurFrame() == fireFrame)
    {
        if(target && target->getIsAlive())
            target->takeDamage(25);

        hasFiredThisAnim = true;

    }
    
}

void SmallDragon::render(SDL_Renderer* renderer)
{
    animation->render(renderer);
    hpbar->Render(renderer);

}


void SmallDragon::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;

    if(SmallDragonAnimationPath.find(state) != SmallDragonAnimationPath.end())
    {
        auto p = SmallDragonAnimationPath.at(state);

        animation->setAnim(renderer, p.first, p.second, 300);
        animation->reset();
    }

}