#include "Animation.h"

Animation::Animation(Transform& EntityTransform)
    : entityTransform(EntityTransform) {
	innerTimer = new Timer();
	curFrame = frameCount = 0;
	deltaTime = 0;
	flip = false;
}

Animation::~Animation() { delete innerTimer; }

void Animation::setAnim(SDL_Renderer* renderer, const char* path, int count,
                        int dt) {
	loadTexture(renderer, path);
	frameCount = count;
	deltaTime = dt;

	float texW, texH;
	SDL_GetTextureSize(texture, &texW, &texH);

	srcRect = {0, 0, texW / frameCount, texH};

	curFrame = 0;
	innerTimer->start();
}

void Animation::update() {
	if (innerTimer->elapsedTime() >= deltaTime) {
		curFrame = (curFrame + 1) % frameCount;
		innerTimer->start();
	}
	setFrame(curFrame);
}

void Animation::setFrame(int index) { srcRect.x = index * srcRect.w; }

void Animation::render(SDL_Renderer* renderer) {
	SDL_FRect dest = entityTransform.toRect();

	SDL_RenderTextureRotated(renderer, texture, &srcRect, &dest, 0.0f, nullptr,
	                         flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

SDL_FRect Animation::getRect() { return entityTransform.toRect(); }