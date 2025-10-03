#include "Game.h"

void Game::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    if (!SDL_CreateWindowAndRenderer("GameCPP", 1220, 720, 0, &m_Window, &m_Renderer))
    {
        SDL_Log("SDL_CreateWindowAndRenderer Error: %s\n", SDL_GetError());
        return;
    }

    m_Quit = false;

    ChangeState(new MenuState(this));
}

void Game::Run()
{
    SDL_Event event;
    while (!m_Quit)
    {
        NOW = SDL_GetPerformanceCounter();

        m_DeltaTime = (float)(NOW - LAST) / (float)SDL_GetPerformanceFrequency();

        LAST = NOW;

        SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
        if (m_CurrentState)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    Quit();
                }
                else
                {
                    m_CurrentState->HandleEvent(event);
                }
            }
            m_CurrentState->Update(m_DeltaTime);
            m_CurrentState->Render();
        }
    }

    Cleanup();
}

void Game::ChangeState(GameState *newState)
{
    if (m_CurrentState)
    {
        m_CurrentState->Exit();
        delete m_CurrentState;
    }

    m_CurrentState = newState;

    if (m_CurrentState)
    {
        m_CurrentState->Enter();
    }
}

void Game::Cleanup()
{
    if (m_CurrentState)
    {
        m_CurrentState->Exit();
        delete m_CurrentState;
        m_CurrentState = nullptr;
    }

    if (m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }
    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }
    SDL_Quit();
}

void Game::Quit()
{
    m_Quit = true;
}