#include "Dragon.h"
#include "FireAttackD.h"
#include <cmath>

Dragon::Dragon()
{

    // attributes

    transform.size = {100, 100};

    name = "Small Dragon";

    cost = 100;

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    curHP = maxHP = 100;

    AttackRange = 700.0f;

    state = DragonState::WALK;


    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void Dragon::update(std::vector<IEntity*>& enemies, SDL_Renderer* renderer, float dt)
{
    animation->update();
    hpbar->Update();

    attackTimer += dt;

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
        if(state != DragonState::WALK)
        {
            setState(renderer, DragonState::WALK);
        }
        updateFireAttacks(enemies, dt);
        return;
    }

    IEntity* target = nullptr;
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
        if(dist < minDist) { minDist = dist; target = e; }
    }

    if(!target || !target->getIsAlive())
    {
        if(state != DragonState::WALK)
        {
            setState(renderer, DragonState::WALK);
        }

        updateFireAttacks(enemies, dt);
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

            if(state != DragonState::WALK)
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
            hasFiredThisAnim = false;
            attackTimer = 0.0f;
            break;

        case DragonState::ATTACK:
            if(animation->getCurFrame()==0) 
            {
                hasFiredThisAnim = false;
            }

            handleFireAttack(renderer, target);
           
           if(animation->isLastFrame())
                animation->reset();
            break;

        default:
            setState(renderer, DragonState::ATTACK);
            hasFiredThisAnim = false;
            attackTimer = 0.0f;
            break;
        }
    }

    updateFireAttacks(enemies, dt);
}

void Dragon::handleFireAttack(SDL_Renderer* renderer, IEntity* target)
{
    const int fireFrame = 1;
    if(!hasFiredThisAnim && animation->getCurrentFrame() >= fireFrame && attackTimer >= attackCooldown)
    {
        attackTarget = target;
        attack(renderer);
        attackTarget = nullptr;

        hasFiredThisAnim = true;
        attackTimer = 0.0f;
    }
    
}

void Dragon::updateFireAttacks(std::vector<IEntity*>& enemies, float dt)
{
    for(auto it = fireAttacks.begin(); it != fireAttacks.end();)
    {
        it->update(dt);
        bool hit = false;
        for (IEntity* e : enemies)
        {
            if(!e->getIsAlive()) continue;
            SDL_Rect a = it->getRect();
            Transform b = e->getTransform();
            SDL_Rect rectB = { (int)b.pos.x, (int)b.pos.y, (int)b.size.x, (int)b.size.y };
            if(SDL_HasRectIntersection(&a, &rectB))
            {
                e->takeDamage(it->damage);
                hit = true;
                break;
            }
        }
        if(hit || it->lifeTime <= 0.0f)
        {
            it = fireAttacks.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
void Dragon::attack(SDL_Renderer* renderer)
{
    if(!attackTarget) return;

    Transform targetT = attackTarget->getTransform();
    Vector2 targetCenter = { targetT.pos.x + targetT.size.x * 0.5f,
                             targetT.pos.y + targetT.size.y * 0.5f };

    float baseX = transform.pos.x + transform.size.x * (flip ? 0.1f : 0.8f );
    float baseY = transform.pos.y + transform.size.y * 0.2f;

    float dx = targetCenter.x - baseX;
    float dy = targetCenter.y - baseY;

    FireAttackD fire;
    fire.init(renderer, baseX, baseY, dx, dy, 20.0f);
    fire.animation->flip = flip;
    fireAttacks.push_back(fire);
}

void Dragon::render(SDL_Renderer* renderer)
{
    animation->render(renderer);
    hpbar->Render(renderer);
    renderFireAttacks(renderer);
}

void Dragon::renderFireAttacks(SDL_Renderer* renderer)
{
    for(auto& f : fireAttacks)
        f.render(renderer);
}

void Dragon::setState(SDL_Renderer *renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;

    if(DragonAnimationPath.find(state) != DragonAnimationPath.end())
    {
        auto p = DragonAnimationPath.at(state);

        animation->setAnim(renderer, p.first, p.second, 450);
        animation->reset();
    }
}