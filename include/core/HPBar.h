#pragma once
#include <SDL3/SDL.h>

#include <algorithm>

#include "Transform.h"

class HPBar {
   private:
	SDL_Color backgroundColor;
	SDL_Color foregroundColor;

	float &maxHP;
	float &currentHP;
	Transform &entityTransform;

	SDL_FRect backgroundRect;
	SDL_FRect barRect;

	float verticalOffset;
	float height;
	float width;

   public:
	HPBar(float &MaxHP, float &CurrentHP, Transform &EntityTransform,
	      SDL_Color BackgroundColor, SDL_Color ForegroundColor, float Height,
	      float VerticalOffset, float Width);

	void Update();

	void Render(SDL_Renderer *renderer);
};
