#include "Samurai_Archer.h"
#include <cmath>
#include <algorithm>
#include <vector>

SamuraiArcher::SamuraiArcher()
{
    transform.size = {100, 100};
    name = "SamuraiArcher";

    curHP = maxHP = 80;
    attackRange = 300.0f;  // tầm bắn xa hơn Samurai
    moveSpeed = 100.0f;
    attackCooldown = 2.3f;
    attackTimer = 0.0f;

    SDL_Color bg = {50, 50, 50, 255};
    SDL_Color fg = {0, 200, 0, 255};
    hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -30, 60);
}

void SamuraiArcher::update(std::vector<IEntity*>& enemies, SDL_Renderer* renderer, float dt)
{
    animation->update();
    hpbar->Update();

    attackTimer += dt;
    if (enemies.empty()) return;

    // --- Tìm mục tiêu gần nhất ---
    IEntity* target = nullptr;
    float minDist = 1e9f;
    Vector2 myCenter = { transform.pos.x + transform.size.x * 0.5f,
                         transform.pos.y + transform.size.y * 0.5f };

    for (IEntity* e : enemies)
    {
        Transform t = e->getTransform();
        Vector2 enemyCenter = { t.pos.x + t.size.x * 0.5f,
                                t.pos.y + t.size.y * 0.5f };
        float dx = enemyCenter.x - myCenter.x;
        float dy = enemyCenter.y - myCenter.y;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist < minDist)
        {
            minDist = dist;
            target = e;
        }
    }

    if (!target) return;

    Transform targetT = target->getTransform();
    Vector2 targetCenter = {
        targetT.pos.x + targetT.size.x * 0.5f,
        targetT.pos.y + targetT.size.y * 0.5f
    };

    flip = (targetCenter.x < myCenter.x);

    // --- Di chuyển hoặc tấn công ---
    if (minDist > attackRange)
    {
        // Đi bộ tới địch
        float dx = targetCenter.x - myCenter.x;
        float dy = targetCenter.y - myCenter.y;
        float len = sqrtf(dx * dx + dy * dy);
        transform.pos.x += (dx / len) * moveSpeed * dt;
        transform.pos.y += (dy / len) * moveSpeed * dt;

        if (state != SamuraiArcherState::WALK)
            setState(renderer, SamuraiArcherState::WALK);
    }
    else
    {
        // Trong tầm bắn → tấn công
        if (state != SamuraiArcherState::SHOT)
            setState(renderer, SamuraiArcherState::SHOT);

        const int fireFrame = 12; // frame bắn tên
        if (!hasShotThisAnim && animation->getCurrentFrame() == fireFrame && attackTimer >= attackCooldown)
        {
            attackTarget = target;
            attack(renderer);
            attackTarget = nullptr;

            hasShotThisAnim = true;
            attackTimer = 0.0f;
        }

        // reset khi animation quay lại frame 0
        if (animation->getCurrentFrame() == 0)
            hasShotThisAnim = false;
    }

    // --- Cập nhật tất cả mũi tên ---
    for (auto it = arrows.begin(); it != arrows.end();)
    {
        it->update(dt);

        // Kiểm tra va chạm với địch
        bool hit = false;
        for (IEntity* e : enemies)
        {
            if (checkCollision(it->getRect(), e->getTransform()))
            {
                e->takeDamage(*this); // gây sát thương
                hit = true;
                break;
            }
        }

        if (hit ||
            it->getPos().x < 0 || it->getPos().x > 1280 ||
            it->getPos().y < 0 || it->getPos().y > 720)
        {
            it = arrows.erase(it);
        }
        else ++it;
    }
}

void SamuraiArcher::attack(SDL_Renderer* renderer)
{
    if (!attackTarget) return;

    Transform targetT = attackTarget->getTransform();
    Vector2 targetCenter = {
        targetT.pos.x + targetT.size.x * 0.5f,
        targetT.pos.y + targetT.size.y * 0.55f
    };

    float baseX = transform.pos.x + transform.size.x * (flip ? 0.65f : 0.35f);
    float baseY = transform.pos.y + transform.size.y * 0.65f;

    float dx = targetCenter.x - baseX;
    float dy = targetCenter.y - baseY;
    float len = sqrtf(dx * dx + dy * dy);

    float startX = baseX + (dx / len) * 25.0f;
    float startY = baseY + (dy / len) * 25.0f;

    Arrow a;
    a.init(renderer, startX, startY, dx, dy);
    arrows.push_back(a);
}

void SamuraiArcher::render(SDL_Renderer* renderer)
{
    animation->render(renderer);
    hpbar->Render(renderer);

    for (auto& a : arrows)
        a.render(renderer);
}

void SamuraiArcher::setState(SDL_Renderer* renderer, EntityState newState)
{
    if (state == newState) return;
    state = newState;

    auto p = SamuraiArcherAnimationPath.at(state);
    animation->setAnim(renderer, p.first, p.second, 180);
}

// ----------------- Hàm phụ -----------------
bool SamuraiArcher::checkCollision(const SDL_Rect& a, const Transform& b)
{
    SDL_Rect rectB = { (int)b.pos.x, (int)b.pos.y, (int)b.size.x, (int)b.size.y };
    return SDL_HasIntersection(&a, &rectB);
}
