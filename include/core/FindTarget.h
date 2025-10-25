#pragma once
#include <vector>

#include "IEnitity.h"  // hoặc IEntity.h tùy dự án của bạn

class TargetingSystem {
   public:
	// Tìm mục tiêu gần nhất trong phạm vi attackRange
	// seeker: entity đang tìm target
	// targets: danh sách entity khả dụng
	// attackRange: phạm vi tìm target
	static void FindNearestTarget(IEntity* seeker,
	                              const std::vector<IEntity*>& targets);

	// Di chuyển entity tới target nếu có
	static void MoveToTarget(SDL_Renderer* renderer, IEntity* seeker,
	                         std::vector<IEntity*> ar, float dt);
};
