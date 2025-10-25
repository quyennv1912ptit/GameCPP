#pragma once 

#include "IEnitity.h" 

class FireAttackD
{ 
public: 
    Transform transform; 
    Animation* animation ; 

    float vx, vy; 
    float angle=0; 
    float speed = 90.0f; 
    float damage = 0.0f; 
    float lifeTime = 3.0f; 
    
    void init(SDL_Renderer* renderer, float x, float y, float dx, float dy, float dmg); 
    void update(float dt); 
    void render(SDL_Renderer* renderer); 
    
    Vector2 getPos() const { return transform.pos;} 
    SDL_Rect getRect() const { return { (int)transform.pos.x, (int)transform.pos.y, (int)transform.size.x, (int)transform.size.y };}

};