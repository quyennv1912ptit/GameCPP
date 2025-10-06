#include "PlayState.h"

float maxHp = 100, curHp = 60;

SDL_FRect monsterRect = {100, 100, 100, 100};

void PlayState::Enter()
{
    e = new IEntity(100, 100, 100);
    e->setState(m_Game->GetRenderer(), State::ATTACK);
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
    SDL_SetRenderDrawColor(renderer, 50, 200, 50, 255);
    SDL_RenderClear(renderer);

    e->render(renderer);

    SDL_RenderPresent(renderer);
}

void PlayState::Exit()
{
    delete e;
}