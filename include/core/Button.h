#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

#include "Transform.h"

class TextButton
{
private:
    SDL_Texture *defaultTex = nullptr;
    SDL_Texture *hoverdTex = nullptr;

    SDL_Renderer *renderer = nullptr;

    std::string text;
    float size;
    TTF_Font *font;

    bool isHoverd = false;

    Transform dims;

public:
    TextButton(SDL_Renderer *rdr, const char *fontPath, std::string txt, float sz, SDL_Color defaultClr,
               SDL_Color hoveredClr);
    ~TextButton();
    void update(SDL_FPoint *mousePos);
    void render();
    bool getIsHovered();
    void setHovered(bool hovered);
    void setPos(Vector2 pos);
    Transform getDims();
};

class ImageButton
{
private:
    SDL_Texture *defaultTex = nullptr;
    SDL_Texture *hoverdTex = nullptr;

    SDL_Renderer *renderer = nullptr;

    Transform dims;
    Vector2 texSSize;

    bool isHovered = false;

public:
    ImageButton(SDL_Renderer *rdr, const char *path1, const char *path2);
    ImageButton(SDL_Renderer *rdr, const char *path1, const char *path2, float w, float h);
    ~ImageButton();
    void setPos(Vector2 pos);

    void setSize(Vector2 size);

    void update(SDL_FPoint *mousePos);

    void render();

    bool getIsHovered();

    void setHovered(bool hovered);

    Transform getDims();
};

class CombinedButton
{
private:
    TextButton *textBtn = nullptr;
    ImageButton *imgBtn = nullptr;

    SDL_Renderer *renderer = nullptr;

    // Transform dims;

    bool isHovered = false;

public:
    CombinedButton(SDL_Renderer *rdr, const char *imgNormal, const char *imgHover, const char *fontPath,
                   std::string text, float textSize, SDL_Color textClr, SDL_Color textHoverClr);
    CombinedButton(SDL_Renderer *rdr, const char *imgNormal, const char *imgHover, float w, float h,
                   const char *fontPath, std::string text, float textSize, SDL_Color textClr, SDL_Color textHoverClr);

    ~CombinedButton();

    void setPos(Vector2 pos);

    void update(SDL_FPoint *mousePos);

    void render();

    bool getIsHovered();

    Transform getDims();
};