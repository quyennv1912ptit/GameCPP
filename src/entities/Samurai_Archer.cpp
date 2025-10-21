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
    const int fireFrame = 13;
    if(target && minDist <= attackRange) 
    {
        if(state != SamuraiArcherState::SHOT)
            setState(renderer, SamuraiArcherState::SHOT);

        if (!hasShotThisAnim && animation->getCurrentFrame() >= fireFrame)
        {
            Transform targetT = target->getTransform();
            Vector2 targetCenter = {
                targetT.pos.x + targetT.size.y * 0.5f,
                targetT.pos.y + targetT.size.y *0.55f
            };
            
            
            float baseX = transform.pos.x + transform.size.x * 0.35f;
            float baseY = transform.pos.y + transform.size.y * 0.65f;

            float dx = targetCenter.x - baseX;
            float dy = targetCenter.y - baseY;
            float len = sqrt(dx * dx + dy * dy);

            float arrowStartOffset = 25.0f;

            float startX = baseX + (dx / len) * arrowStartOffset;
            float startY = baseY + (dy / len) * arrowStartOffset;

            Arrow a;
            a.init(renderer, startX, startY, dx, dy);
            arrows.push_back(a);

            hasShotThisAnim = true;
            attackTimer = 0.0f;
        }
        if(animation->getCurrentFrame()==0 )
            hasShotThisAnim = false;
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