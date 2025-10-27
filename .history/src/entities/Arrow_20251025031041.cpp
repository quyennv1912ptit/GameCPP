#include "Arrow.h" 
#include <cmath> 
void Arrow::init(SDL_Renderer* renderer, float x , float y, float dx, float dy, float dmg) 
{ 
    transform.pos = {x, y}; 
    transform.size = {60, 25 };
    texture = IMG_LoadTexture(renderer,"resources/imgs/kinghts/Samurai_Archer/Arrow.png"); 
    float len = sqrt(dx * dx + dy * dy); 
    vx = (dx / len) *speed; 
    vy = (dy / len) *speed; 
    damage = dmg ; 
    angle = atan2(vy, vx) *180.0f / M_PI;
} 
void Arrow::update(float dt) 
{
     transform.pos.x += vx * dt; 
     transform.pos.y += vy * dt; 
    
} 

void Arrow::render(SDL_Renderer* renderer) 
{
     const float arrowWidth = 60.0f; 
     const float arrowHeight = 25.0f; 
     SDL_FRect dest = 
     {
        transform.pos.x - arrowWidth / 2.0f, 
        transform.pos.y - arrowHeight / 2.0f, 
        arrowWidth, 
        arrowHeight, 
    }; 
    SDL_FPoint center = {arrowWidth * 0.75f, arrowHeight / 2.0f}; 
    SDL_RenderTextureRotated(renderer, texture, nullptr, &dest, angle, &center, SDL_FLIP_NONE); 
}