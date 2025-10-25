#pragma once
#include <vector>

#include "IEnitity.h"

class TargetingSystem {
   public:
	static void FindNearestTarget(IEntity* seeker,
	                              const std::vector<IEntity*>& targets);

	static void MoveToTarget(SDL_Renderer* renderer, IEntity* seeker,
	                         std::vector<IEntity*> ar, float dt);
};
