#include "SamuraiArcher.h"
#include "Arrow.h"
#include <cmath>

SamuraiArcher::SamuraiArcher()
{
    transform.size = {80, 80};
    name = "Samurai Archer";
    cost = 120;
    curHP = maxHP = 100;
    AttackRange = 400.0f;
    state = SamuraiArcherState::IDLE;

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};

    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -25, 60);
}

void SamuraiArcher::update(std::vector<IEntity*>& enemies, SDL_Renderer* renderer, float dt)
{
    animation->update();
    hpbar->Update();

    attackTimer += dt;
    bool hasAliveEnemies = false;

    for (IEntity* e : enemies)
    {
        if (e->getIsAlive())
        {
            hasAliveEnemies = true;
            break;
        }
    }

    if (!hasAliveEnemies)
    {
        if (state != SamuraiArcherState::IDLE)
            setState(renderer, SamuraiArcherState::IDLE);

        updateArrows(enemies, dt);
        return;
    }

    IEntity* target = nullptr;
    float minDist = 1e9f;
    Vector2 myCenter = {transform.pos.x + transform.size.x * 0.5f,
                        transform.pos.y + transform.size.y * 0.5f};

    for (IEntity* e : enemies)
    {
        if (!e->getIsAlive()) continue;

        Transform t = e->getTransform();
        Vector2 targetCenter = {t.pos.x + t.size.x * 0.5f, t.pos.y + t.size.y * 0.5f};
        float dx = targetCenter.x - myCenter.x;
        float dy = targetCenter.y - myCenter.y;
        float dist = sqrt(dx * dx + dy * dy);

        if (dist < minDist)
        {
            minDist = dist;
            target = e;
        }
    }

    if (!target || !target->getIsAlive())
    {
        if (state != SamuraiArcherState::IDLE)
            setState(renderer, SamuraiArcherState::IDLE);

        updateArrows(enemies, dt);
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

        if (state != SamuraiArcherState::WALK)
            setState(renderer, SamuraiArcherState::WALK);
    }
    else
    {
        switch (state)
        {
        case SamuraiArcherState::WALK:
            setState(renderer, SamuraiArcherState::ATTACK);
            hasFiredThisAnim = false;
            attackTimer = 0.0f;
            break;

        case SamuraiArcherState::ATTACK:
            if (animation->getCurFrame() == 0)
                hasFiredThisAnim = false;

            handleArrowAttack(renderer, target);

            if (animation->isLastFrame())
                animation->reset();
            break;

        default:
            setState(renderer, SamuraiArcherState::ATTACK);
            hasFiredThisAnim = false;
            attackTimer = 0.0f;
            break;
        }
    }

    updateArrows(enemies, dt);
}

void SamuraiArcher::handleArrowAttack(SDL_Renderer* renderer, IEntity* target)
{
    const int attackFrame = 3;
    if (!hasFiredThisAnim && animation->getCurrentFrame() >= attackFrame && attackTimer >= attackCooldown)
    {
        attackTarget = target;
        attack(renderer);
        attackTarget = nullptr;

        hasFiredThisAnim = true;
        attackTimer = 0.0f;
    }
}

void SamuraiArcher::updateArrows(std::vector<IEntity*>& enemies, float dt)
{
    for (auto it = arrows.begin(); it != arrows.end();)
    {
        it->update(dt);

        bool hit = false;
        for (IEntity* e : enemies)
        {
            if (!e->getIsAlive()) continue;

            SDL_Rect a = it->getRect();
            Transform b = e->getTransform();
            SDL_Rect rectB = {(int)b.pos.x, (int)b.pos.y, (int)b.size.x, (int)b.size.y};

            if (SDL_HasRectIntersection(&a, &rectB))
            {
                e->takeDamage(it->damage);
                hit = true;
                break;
            }
        }

        if (hit || it->lifeTime <= 0.0f)
            it = arrows.erase(it);
        else
            ++it;
    }
}

void SamuraiArcher::attack(SDL_Renderer* renderer)
{
    if (!attackTarget) return;

    Transform targetT = attackTarget->getTransform();
    Vector2 targetCenter = {targetT.pos.x + targetT.size.x * 0.5f,
                             targetT.pos.y + targetT.size.y * 0.5f};

    float baseX = transform.pos.x + transform.size.x * (flip ? 0.2f : 0.8f);
    float baseY = transform.pos.y + transform.size.y * 0.3f;

    float dx = targetCenter.x - baseX;
    float dy = targetCenter.y - baseY;

    Arrow arrow;
    arrow.init(renderer, baseX, baseY, dx, dy, 25.0f);
    arrow.animation->flip = flip;
    arrows.push_back(arrow);
}

void SamuraiArcher::render(SDL_Renderer* renderer)
{
    animation->render(renderer);
    hpbar->Render(renderer);
    renderArrows(renderer);
}

void SamuraiArcher::renderArrows(SDL_Renderer* renderer)
{
    for (auto& a : arrows)
        a.render(renderer);
}

void SamuraiArcher::setState(SDL_Renderer* renderer, EntityState newState)
{
    if (state == newState)
        return;

    state = newState;

    if (SamuraiArcherAnimationPath.find(state) != SamuraiArcherAnimationPath.end())
    {
        auto p = SamuraiArcherAnimationPath.at(state);
        animation->setAnim(renderer, p.first, p.second, 100);
        animation->reset();
    }
}
