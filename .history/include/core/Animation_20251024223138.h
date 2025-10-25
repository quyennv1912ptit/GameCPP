#pragma once

#include <SDL3/SDL.h>

#include "Image.h"
#include "Timer.h"

class Animation : public Image {
   private:
	Timer *innerTimer;
	int curFrame, frameCount;
	int deltaTime;
	SDL_FRect srcRect;
	Transform &entityTransform;

   public:
	Animation(Transform &EntityTransform);

	~Animation();

	void setFrame(int index);

	int getCurFrame() { return curFrame; }

	int getFrameCount() { return frameCount; }

	void update();

	void render(SDL_Renderer *renderer);

	void setAnim(SDL_Renderer *renderer, const char *path, int framecount,
	             int dt);

	SDL_FRect getRect();
};