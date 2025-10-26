#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "string"
#include "vector"

const std::vector<std::string> bgPaths = {"resources/imgs/backgrounds/game_background_1/game_background_1.png",
                                          "resources/imgs/backgrounds/game_background_2/game_background_2.png",
                                          "resources/imgs/backgrounds/game_background_3/game_background_3.png",
                                          "resources/imgs/backgrounds/game_background_4/game_background_4.png"};

class Background
{
private:
    std::vector<SDL_Texture *> m_BGList;

public:
    static Background &Get()
    {
        static Background m_Indtance;
        return m_Indtance;
    }

    Background();
    ~Background();
    void Init(SDL_Renderer *renderer);
    void LoadBackground(SDL_Renderer *renderer, const char *path);
    SDL_Texture *GetBG();
    void UpdateBG(int index);
    void LoadBGIndex(int &var);

    void Shutdown();

    int GetBGCount()
    {
        return m_BGList.size();
    }
};