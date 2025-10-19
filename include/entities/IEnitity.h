#pragma once

#include <SDL3/SDL.h>
#include "Vector2.h"
#include "HPBar.h"
#include "EntityState.h"
#include "Animation.h"



class IEntity
{
protected:
    float curHP, maxHP;
    Transform transform;
    EntityState state;
    Animation *animation;
    HPBar *hpbar;
    

     

public:
    // --- Tấn công ---
    IEntity* attackTarget = nullptr;   // mục tiêu đang nhắm
    float attackRange = 150.0f;        // phạm vi tìm mục tiêu
    float attackDistance = 50.0f;      // phạm vi tấn công tự động
    bool attacking = false;            // trạng thái tấn công
    float attackDamage = 10.0f;        // sát thương cơ bản
    bool mouseControlActive;

    bool flip;
    // --- Di chuyển theo chuột ---
    Transform targetPos;   // điểm click
    bool moving = false;   // có đang di chuyển không
    float speed = 3.0f;    // tốc độ di chuyển
    
    IEntity();
    virtual ~IEntity();

    virtual void update();
    virtual void render(SDL_Renderer *renderer);

    virtual void setState(SDL_Renderer *renderer, EntityState newState) = 0;
    virtual void setPos(float x, float y);
    virtual void setSize(float w, float y);
    virtual Transform &getTransform();
    public:
    void setTargetPos(float x, float y) {
        targetPos.pos = {x, y};
        moving = true;
    }

    bool isMoving() const { return moving; }

};
