#include "Animation.h"

Animation::Animation(Transform &EntityTransform) : entityTransform(EntityTransform) 
{
	 innerTimer = new Timer(); 
	 curFrame = frameCount = 0; 
	 deltaTime = 0; 
	 flip = false; 
	
} 

Animation::~Animation() 
{ 
	delete innerTimer; 
}

void Animation::setAnim(SDL_Renderer *renderer, const char *path, int count, int dt) 
{
	 if(currentPath != path) 
	 {
		 loadTexture(renderer, path); 
		 currentPath = path; 
	}
		  
	frameCount = count; 
	deltaTime = dt; 
	float texW, texH; 
	SDL_GetTextureSize(texture, &texW, &texH) ; 
	SDL_Log("🔥 Texture loaded: %s | size = %.0fx%.0f | frames = %d", path, texW, texH, frameCount); 
	srcRect.w = texW / frameCount; 
	srcRect.h = texH; 
	srcRect.x = 0; 
	srcRect.y = 0; 
	entityTransform.size.x = srcRect.w; 
	entityTransform.size.y = srcRect.h; 
	curFrame = 0; 
	innerTimer->start(); 
	setFrame(curFrame); 
} 

void Animation::update() 
{ 
	if (innerTimer->elapsedTime() >= deltaTime) 
	{ 
		curFrame = (curFrame + 1) % frameCount; 
		innerTimer->start(); 
		setFrame(curFrame); 
	} 

} 

void Animation::setFrame(int index) 
{
	 srcRect.x = index * srcRect.w; 
	
} 

void Animation::render(SDL_Renderer *renderer) 
{ 
	
	if(!texture) return; 
	SDL_FRect dest = entityTransform.toRect(); 
	SDL_RenderTextureRotated(renderer, texture, &srcRect, &dest, 0.0f, nullptr, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE); 
} 

SDL_FRect Animation::getRect() 
{
	 return entityTransform.toRect(); 
	
} 

void Animation::reset() 
{ 
	curFrame = 0; 
	innerTimer->start(); 
	setFrame(curFrame); 

}

bool Animation::isLastFrame() const 
{
	 return curFrame >= frameCount - 1; 
	
}