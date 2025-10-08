#include "Button.h"

TextButton::TextButton(SDL_Renderer *rdr, const char *fontPath, std::string txt, float sz, SDL_Color defaultClr, SDL_Color hoveredClr) : renderer(rdr), text(txt), size(sz)
{
    font = TTF_OpenFont(fontPath, size);
    SDL_Surface *textSuf = TTF_RenderText_Blended(font, text.c_str(), 0, defaultClr);
    defaultTex = SDL_CreateTextureFromSurface(renderer, textSuf);
    textSuf = TTF_RenderText_Blended(font, text.c_str(), 0, hoveredClr);
    hoverdTex = SDL_CreateTextureFromSurface(renderer, textSuf);
    dims.size = {(float)textSuf->w, (float)textSuf->h};
    SDL_DestroySurface(textSuf);
}

bool TextButton::getIsHovered() {
    return isHoverd;
}

void TextButton::update(SDL_FPoint *mousePos)
{
    SDL_FRect dest = dims.toRect();

    if (SDL_PointInRectFloat(mousePos, &dest))
    {
        isHoverd = true;
    }
    else
    {
        isHoverd = false;
    };
}

void TextButton::render()
{
    SDL_FRect dest = dims.toRect();
    SDL_RenderTexture(renderer, (isHoverd ? hoverdTex : defaultTex), nullptr, &dest);
}

void TextButton::setPos(Vector2 pos)
{
    dims.pos = pos;
}

Transform TextButton::getDims()
{
    return dims;
}

TextButton::~TextButton()
{
    SDL_DestroyTexture(defaultTex);
    SDL_DestroyTexture(hoverdTex);
    TTF_CloseFont(font);
}