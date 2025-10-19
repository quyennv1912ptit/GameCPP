#include "FindTarget.h"
#include <cmath>

IEntity* TargetingSystem::FindNearestTarget(IEntity* seeker, const std::vector<IEntity*>& targets, float attackRange)
{
    IEntity* nearest = nullptr;
    float minDist = attackRange;

    for(IEntity* t : targets)
    {
        float dx = t->getTransform().pos.x - seeker->getTransform().pos.x;
        float dy = t->getTransform().pos.y - seeker->getTransform().pos.y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if(dist <= minDist)
        {
            minDist = dist;
            nearest = t;
        }
    }

    return nearest;  // nullptr nếu không có target trong phạm vi
}

void TargetingSystem::MoveToTarget(IEntity* seeker, float dt)
{
    if(!seeker->attackTarget) return;

    float dx = seeker->attackTarget->getTransform().pos.x - seeker->getTransform().pos.x;
    float dy = seeker->attackTarget->getTransform().pos.y - seeker->getTransform().pos.y;
    float distance = std::sqrt(dx*dx + dy*dy);

    // Di chuyển nếu target trong phạm vi attackRange
    if(distance <= seeker->attackRange)
    {
        float nx = dx / distance;
        float ny = dy / distance;

        seeker->getTransform().pos.x += nx * seeker->speed * dt;
        seeker->getTransform().pos.y += ny * seeker->speed * dt;

        seeker->flip = (dx < 0); // quay mặt đúng hướng
        seeker->moving = true;
    }
    else
    {
        seeker->moving = false;
    }
}