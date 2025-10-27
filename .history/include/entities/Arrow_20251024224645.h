#pragma once
#include "IEnitity.h" 
class Arrow 
{
public: 
    Transform transform; 
    SDL_Texture* texture; 

    float vx, vy; 
    float angle=0; 
    float speed = 250; 
    float damage = 0.0f;

    void init(SDL_Renderer* renderer, float x, float y, float dx, float dy, float dmg); 
    void update(float dt); 
    void render(SDL_Renderer* renderer); 

    Vector2 getPos() const { return transform.pos;} 
    SDL_Rect getRect() const { return { (int)transform.pos.x, (int)transform.pos.y, (int)transform.size.x, (int)transform.size.y }; } 
};