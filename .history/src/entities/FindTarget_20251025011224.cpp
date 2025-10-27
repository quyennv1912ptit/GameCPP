#include "FindTarget.h"

#include <cmath>

void TargetingSystem::FindNearestTarget(IEntity* seeker,
                                        const std::vector<IEntity*>& targets) {
	IEntity* nearest = nullptr;
	float minDist = std::numeric_limits<float>::max();

	for (IEntity* t : targets) {
		float dx = t->GetHitPos().x - seeker->GetHitPos().x;
		float dy = t->GetHitPos().y - seeker->GetHitPos().y;
		float dist = std::sqrt(dx * dx + dy * dy);

		if (dist <= minDist) {
			minDist = dist;
			nearest = t;
		}
	}

	seeker->attackTarget = nearest;
}

void TargetingSystem::MoveToTarget(SDL_Renderer* renderer, IEntity* seeker,
                                   std::vector<IEntity*> ar, float dt) {
	if (seeker->attackTarget == nullptr) {
		seeker->setState(renderer, EntityState::IDLE);
		return;
	}
	float dx =
	    seeker->attackTarget->GetHitPos().x - seeker->GetHitPos().x;
	float dy =
	    seeker->attackTarget->GetHitPos().y - seeker->GetHitPos().y;
	float distance = std::sqrt(dx * dx + dy * dy);

	if (distance <= seeker->AttackRange) {
		seeker->attack(renderer);
	} else {
		seeker->setState(renderer, EntityState::WALK);

		float nx = dx / distance;
		float ny = dy / distance;

		seeker->getTransform().pos.add(
		    {nx * seeker->speed * dt, ny * seeker->speed * dt});

		seeker->flip = (dx < 0);
	}

	for (IEntity* other : ar) {
		if (other == seeker) continue;

		float dx2 = seeker->GetHitPos().x - other->GetHitPos().x;
		float dy2 = seeker->GetHitPos().y - other->GetHitPos().y;
		float dist2 = std::sqrt(dx2 * dx2 + dy2 * dy2);

		float minDist = 30.0f;

		if (dist2 < minDist && dist2 > 0.001f) {
			float pushX = dx2 / dist2 * (minDist - dist2) * 0.5f;
			float pushY = dy2 / dist2 * (minDist - dist2) * 0.5f;

			seeker->getTransform().pos.x += pushX;
			seeker->getTransform().pos.y += pushY;
		}
	}
}