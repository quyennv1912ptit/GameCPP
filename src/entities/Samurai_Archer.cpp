#include "Samurai_Archer.h"
#include <cmath>
#include <algorithm>
#include <vector>

SamuraiArcher::SamuraiArcher()
{

    // attributes

    transform.size = {100, 100};

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 80;
    attackTimer = 0;

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void SamuraiArcher::update(std::vector<IEntity*> &enemies, SDL_Renderer* renderer, float dt)
{
    animation-> update();
    hpbar->Update();

    attackTimer += dt;

    if(enemies.empty()) return;

    IEntity *target=nullptr;
    float minDist = 1e9f;
    Vector2 myPos = transform.pos;

    for (IEntity* e : enemies)
    {
        Vector2 ep = e->getPos();
        float dx = ep.x - myPos.x;
        float dy = ep.y - myPos.y;
        float dist = sqrt(dx * dx + dy * dy);

        if(dist < minDist)
        {
            minDist = dist;
            target = e;
        }
    }

    if(target && minDist <= attackRange) 
    {
        if(state != SamuraiArcherState::SHOT) 
            setState(renderer, SamuraiArcherState::SHOT);

        if (attackTimer >= attackCooldown)
        {
            Vector2 targetPos = target->getPos();

            float dx = targetPos.x - transform.pos.x;
            float dy = targetPos.y - transform.pos.y;

            Arrow a;
            a.init(renderer, transform.pos.x +30, transform.pos.y +20, dx, dy);
            arrows.push_back(a);

            attackTimer = 0.0f;

        }
    }
    
    for (auto it = arrows.begin(); it != arrows.end();)
    {
        it->update(dt);

        if(it->getPos().x < 0 || it->getPos().x > 1280 || it->getPos().y < 0 || it->getPos().y > 720)
        {
            it = arrows.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void SamuraiArcher::render(SDL_Renderer *renderer)
{
    animation->render(renderer);
    hpbar->Render(renderer);

    for(auto &a : arrows)
    {
        a.render(renderer);
    }
}

void SamuraiArcher::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;
    auto p = SamuraiArcherAnimationPath.at(state);

    animation->setAnim(renderer, p.first, p.second, 180);
}