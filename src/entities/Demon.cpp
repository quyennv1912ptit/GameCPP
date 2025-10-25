#include "Demon.h"
#include<iostream>

Demon::Demon() {
	// attributes
	name = "Demon";

	cost = 0;

	transform.size = {200, 200};

	SDL_Color bg = {50, 50, 50, 255};
	SDL_Color fg = {200, 0, 0, 255};

	curHP = maxHP = 200;

	hpbar = new HPBar(maxHP, curHP, transform, bg, fg, 5, -50, 100);
}

void Demon::setState(SDL_Renderer *renderer, EntityState newState) {
	if (state == newState) return;

	state = newState;
	auto p = DemonAnimationPath.at(state);

	animation->setAnim(renderer, p.first, p.second, 150);
}

void Demon::attack(SDL_Renderer *renderer) {
	setState(renderer, DemonState::ATTACK);

std::cout<<attackTarget->getName()<<"\n";
	if (getAnimCurFrame() == 0) {
		attackTarget->takeDamage(*(IEntity *)this);
	}
}