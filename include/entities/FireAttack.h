#pragma once
#include "IEnitity.h"
#include "Animation.h"

class FireAttack
{
public:
    Transform transform;
    SDL_Texture* texture;
    float vx, vy;
    float angle=0;
    float speed = 250.0f;

    Animation* anim = nullptr;
    
    void init(SDL_Renderer* renderer, float x, float y, float dx, float dy);
    void update(float dt);
    void render(SDL_Renderer* renderer);

    Vector2 getPos() const { return transform.pos;}

    ~FireAttack()
    {
        if(anim) delete anim;
    }
};