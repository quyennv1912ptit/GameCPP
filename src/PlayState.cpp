#include "PlayState.h"
#include "Game.h"

void PlayState::Enter() {

}

void PlayState::HandleEvent(const SDL_Event& event) {

}

void PlayState::Update() {

}

void PlayState::Render() {
    SDL_SetRenderDrawColor(m_Game->GetRenderer(), 69, 186, 255, 255);
    SDL_RenderClear(m_Game->GetRenderer());
    SDL_RenderPresent(m_Game->GetRenderer());
}

void PlayState::Exit() {


}