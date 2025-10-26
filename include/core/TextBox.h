#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

#include "Transform.h"
#include "Vector2.h"

class TextBox
{
private:
    SDL_Texture *texture = nullptr;
    SDL_Surface *textSuf = nullptr;
    TTF_Font *font = nullptr;
    SDL_Renderer *renderer;

    float size = 0;
    std::string text = "";
    SDL_Color color = {255, 255, 255, 255};

    Transform dims;

public:
    TextBox(SDL_Renderer *rdr, const char *path, std::string txt, float sz);
    ~TextBox();
    void setText(std::string tet);
    void setPos(Vector2 pos);
    void setColor(SDL_Color color);
    void render();
    void updateTex();
    Transform getDims();
};