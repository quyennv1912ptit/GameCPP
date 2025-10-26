#include "TextBox.h"

TextBox::TextBox(SDL_Renderer *rdr, const char *path, std::string txt, float sz) : renderer(rdr), text(txt), size(sz)
{
    font = TTF_OpenFont(path, size);
    updateTex();
}

void TextBox::setText(std::string txt)
{
    text = txt;
    updateTex();
}

void TextBox::setColor(SDL_Color clr)
{
    color = clr;
    updateTex();
}

void TextBox::setPos(Vector2 pos)
{
    dims.pos = pos;
}

void TextBox::updateTex()
{
    textSuf = TTF_RenderText_Blended(font, text.c_str(), 0, color);
    texture = SDL_CreateTextureFromSurface(renderer, textSuf);
    dims.size = {(float)textSuf->w, (float)textSuf->h};
    SDL_DestroySurface(textSuf);
}

void TextBox::render()
{
    SDL_FRect dest = dims.toRect();
    SDL_RenderTexture(renderer, texture, nullptr, &dest);
}

Transform TextBox::getDims()
{
    return dims;
}

TextBox::~TextBox()
{
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}