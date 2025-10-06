#include "Image.h"

void Image::loadTexture(SDL_Renderer *renderer, const char *path)
{
    texture = IMG_LoadTexture(renderer, path);
    SDL_GetTextureSize(texture, &transform.size.x, &transform.size.y);
}

void Image::flipImage()
{
    flip = !flip;
}

void Image::render(SDL_Renderer *renderer)
{
    SDL_FRect dest = transform.toRect();
    SDL_RenderTextureRotated(renderer, texture, nullptr, &dest, 0.0f, nullptr,
                             flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

SDL_FRect Image::getRect()
{
    return transform.toRect();
}

void Image::setPos(Vector2 pos)
{
    transform.pos.x = pos.x;
    transform.pos.y = pos.y;
}

void Image::setPos(float x, float y)
{
    transform.pos.x = x;
    transform.pos.y = y;
}
