#include "Background.h"

#include "Config.h"

Background::Background() {}

Background::~Background() {}

void Background::Init(SDL_Renderer *renderer)
{
    for (const std::string &path : bgPaths)
        LoadBackground(renderer, path.c_str());
}

void Background::LoadBackground(SDL_Renderer *renderer, const char *path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, path);

    m_BGList.push_back(texture);
}

SDL_Texture *Background::GetBG()
{
    return m_BGList[Config::GetBackground()];
}

void Background::UpdateBG(int index)
{
    if (index < 0 || index >= GetBGCount())
        return;
    if (index == Config::GetBackground())
        return;
    Config::UpdateBackground(index);
}

void Background::Shutdown()
{
    for (auto texture : m_BGList)
    {
        SDL_DestroyTexture(texture);
    }
    m_BGList.clear();
}