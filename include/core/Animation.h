#pragma once 
#include <SDL3/SDL.h> 
#include "Timer.h" 
#include "Image.h" 

class Animation : public Image 
{
private: 
	Timer *innerTimer; 
	int curFrame, 
	frameCount; 
	int deltaTime; 
	
	SDL_FRect srcRect; 
	Transform &entityTransform; 
	std::string currentPath; 
	
public: 
	
	Animation(Transform &EntityTransform); 
	~Animation();

	void setFrame(int index); 
	int getCurFrame() { return curFrame; } 
	int getFrameCount() { return frameCount; } 
	void update(); 
	void render(SDL_Renderer *renderer); 
	void setAnim(SDL_Renderer *renderer, const char *path, int framecount, int dt); 
	void reset(); 
	
	SDL_FRect getRect(); 
	
	int getCurrentFrame() const { return curFrame; } 
	int getTotalFrame() const { return frameCount;} 
	
	SDL_Texture* getTexture() const {return texture; } 
	SDL_FRect getSrcRect() const {return srcRect; } 
	
	bool isLastFrame() const; 


};