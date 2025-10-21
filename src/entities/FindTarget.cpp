#include "FindTarget.h"
#include <cmath>

IEntity *TargetingSystem::FindNearestTarget(IEntity *seeker, const std::vector<IEntity *> &targets)
{
    IEntity *nearest = nullptr;
    float minDist = std::numeric_limits<float>::max();

    for (IEntity *t : targets)
    {
        float dx = t->getTransform().pos.x - seeker->getTransform().pos.x;
        float dy = t->getTransform().pos.y - seeker->getTransform().pos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= minDist)
        {
            minDist = dist;
            nearest = t;
        }
    }

    return nearest; // nullptr nếu không có target trong phạm vi
}

void TargetingSystem::MoveToTarget(SDL_Renderer *renderer, IEntity *seeker, float dt)
{
    if (!seeker->attackTarget)
        return;
    else
    {
        SDL_Log("%s\n", seeker->attackTarget->getName().c_str());
    }

    float dx = seeker->attackTarget->getTransform().pos.x - seeker->getTransform().pos.x;
    float dy = seeker->attackTarget->getTransform().pos.y - seeker->getTransform().pos.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    SDL_Log("%f\n", distance);

    if (distance <= seeker->AttackRanvge)
    {
        seeker->setState(renderer, EntityState::WALK);
    }
    else
    {
        seeker->setState(renderer, EntityState::IDLE);

        float nx = dx / distance;
        float ny = dy / distance;

        seeker->getTransform().pos.add({nx * seeker->speed * dt, ny * seeker->speed * dt});

        seeker->flip = (dx < 0);
    }
}