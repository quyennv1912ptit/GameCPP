#pragma once

#include <SDL3/SDL.h>
#include "MenuState.h"

class Game
{
private:
    SDL_Window *m_Window = nullptr;
    SDL_Renderer *m_Renderer = nullptr;
    bool m_Quit = true;
    GameState *m_CurrentState = nullptr;
    SDL_FPoint m_MousePos = {-1,-1};
    void Cleanup();

public:
    SDL_Renderer *GetRenderer()
    {
        return m_Renderer;
    }
    SDL_FPoint* GetMousePos() {
        return &m_MousePos;
    }
    void Init();
    void Run();
    void Quit();
    void ChangeState(GameState *);
};