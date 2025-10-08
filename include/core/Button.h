#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "Transform.h"
#include <string>

enum class ButtonID {
    //Menu
    START,
    SETTINGS,
    EXIT
};

class TextButton
{
private:
    ButtonID ID;

    SDL_Texture *defaultTex = nullptr;
    SDL_Texture *hoverdTex = nullptr;

    SDL_Renderer *renderer = nullptr;

    std::string text;
    float size;
    TTF_Font *font;

    bool isHoverd = false;

    Transform dims;

public:
    TextButton(SDL_Renderer *rdr, const char *fontPath, std::string txt, float sz, SDL_Color defaultClr, SDL_Color hoveredClr);
    ~TextButton();
    void update(SDL_FPoint *mousePos);
    void render();
    bool getIsHovered();
    void setPos(Vector2 pos);
    Transform getDims();
};