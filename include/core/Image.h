#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Game.h"
#include "Transform.h"

class Image
{
protected:
    Transform transform;
    Vector2 textureSize;
    SDL_Texture *texture = nullptr;

public:
    bool flip = false;

    void flipImage();

    void setPos(Vector2 pos);
    void setPos(float x, float y);

    SDL_FRect getRect();

    void loadTexture(SDL_Renderer *renderer, const char *path);
    void loadTexture(SDL_Renderer *renderer, const char *path, float w, float h);

    void render(SDL_Renderer *renderer);
};