#include "FindTarget.h"

#include <cmath>

void TargetingSystem::FindNearestTarget(IEntity* seeker, const std::vector<IEntity*>& targets) {
	IEntity* nearest = nullptr;
	float minDist = std::numeric_limits<float>::max();

	for (IEntity* t : targets) {
		float dx = t->getCenterPos().x - seeker->getCenterPos().x;
		float dy = t->getCenterPos().y - seeker->getCenterPos().y;
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
	    seeker->attackTarget->getCenterPos().x - seeker->getCenterPos().x;
	float dy =
	    seeker->attackTarget->getCenterPos().y - seeker->getCenterPos().y;
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

		float dx2 = seeker->getCenterPos().x - other->getCenterPos().x;
		float dy2 = seeker->getCenterPos().y - other->getCenterPos().y;
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