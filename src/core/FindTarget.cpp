#include "FindTarget.h"
#include <cmath>
#include <limits>

void TargetingSystem::FindNearestTarget(IEntity* seeker,
                                        const std::vector<IEntity*>& targets) {
    if(seeker->name=="Castle") return;
    IEntity* nearest = nullptr;
    
    float minDist = std::numeric_limits<float>::max();
    
    for (IEntity* t : targets) {
        if (!t || !t->getIsAlive()) continue;

        float dx = t->getCenterPos().x - seeker->getCenterPos().x;
        float dy = t->getCenterPos().y - seeker->getCenterPos().y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < minDist) {
            minDist = dist;
            nearest = t;
        }
    }

    // 🏰 Nếu không còn kẻ địch, chuyển sang tấn công castle đối diện
    if (!nearest) {
        const float SCREEN_MID = 640.0f; // nửa màn hình (1280x720)
        if (seeker->getCenterPos().x < SCREEN_MID) {
            // Phe trái (người chơi) => tấn công castle bên phải
            nearest = seeker->enemyCastle;
        } else {
            // Phe phải (kẻ địch) => tấn công castle bên trái
            nearest = seeker->playerCastle;
        }
    }

    seeker->attackTarget = nearest;
}

void TargetingSystem::MoveToTarget(SDL_Renderer* renderer, IEntity* seeker,
                                   std::vector<IEntity*> ar, float dt) {
    if (!seeker || seeker->attackTarget == nullptr) {
        seeker->setState(renderer, EntityState::IDLE);
        return;
    }

    float dx = seeker->attackTarget->getCenterPos().x - seeker->getCenterPos().x;
    float dy = seeker->attackTarget->getCenterPos().y - seeker->getCenterPos().y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // ⚔️ Trong phạm vi tấn công
    if (distance <= seeker->AttackRanvge) {
        seeker->attack(renderer);
    } else {
        // 🚶‍♂️ Di chuyển về phía mục tiêu
        seeker->setState(renderer, EntityState::WALK);

        float nx = dx / distance;
        float ny = dy / distance;

        seeker->getTransform().pos.add(
            {nx * seeker->speed * dt, ny * seeker->speed * dt});

        // Cập nhật hướng (flip)
        seeker->flip = (dx < 0);
    }

    
}
