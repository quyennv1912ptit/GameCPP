#include "PlayState.h"

void PlayState::Enter()
{
    e = new Samurai();
    e->setState(m_Game->GetRenderer(), SamuraiState::ATTACK2);
}

void PlayState::HandleEvent(const SDL_Event &event)
{
}

void PlayState::Update(float dt)
{
    e->update();
}

void PlayState::Render()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    e->render(renderer);

    SDL_RenderPresent(renderer);
}

void PlayState::Exit()
{
    delete e;
}