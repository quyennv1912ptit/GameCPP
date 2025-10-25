#include "FireAttackS.h" 

#include <cmath> 

void FireAttackS::init(SDL_Renderer* renderer, float x , float y, float dx, float dy, float dmg) 
{ 
    transform.pos = {x, y}; 
    
    float len = sqrt(dx * dx + dy * dy); 
    vx = (dx / len) *speed; 
    vy = (dy / len) *speed; 
    damage = dmg ; 
    
    lifeTime = 2.0f; 
    
    animation = new Animation(transform); 
    animation->setAnim(renderer,"resources/imgs/kinghts/small_dragon/Fire_Attack.png", 9,200); 
    transform.size = {64, 64}; 
    animation->reset(); 
} 

void FireAttackS::update(float dt) 
{ 
    transform.pos.x += vx * dt; 
    transform.pos.y += vy * dt; 
    
    animation->update(); 
    
    lifeTime -= dt; 

} 

void FireAttackS::render(SDL_Renderer* renderer) 
{ 
    if(animation) 
    { 
        animation->render(renderer); 
        SDL_FRect r = transform.toRect(); 
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100); 
        SDL_RenderRect(renderer, &r); 
    } 
}