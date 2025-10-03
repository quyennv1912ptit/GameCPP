#include "PlayState.h"
#include "Game.h"
#include "Animation.h"

const std::vector<std::string> path = {
    "resources/imgs/enemies/demon/Attack1.png",
    "resources/imgs/enemies/demon/Attack2.png",
    "resources/imgs/enemies/demon/Attack3.png",
    "resources/imgs/enemies/demon/Attack4.png",
};

SDL_FRect src = {0, 0, 256, 256};
SDL_FRect dest = {100, 100, 256, 256};


void PlayState::Enter() {
    std::vector<SDL_Texture*> arr;
    for(const std::string& p : path) {
        SDL_Texture* texture = IMG_LoadTexture(m_Game->GetRenderer(), p.c_str());
        arr.push_back(texture);
    }

    anim.Load(arr, src, dest, 4, 0.25);
}

void PlayState::HandleEvent(const SDL_Event& event) {

}

void PlayState::Update(float dt) {
    anim.Update(dt);
}

void PlayState::Render() {
    SDL_SetRenderDrawColor(m_Game->GetRenderer(), 69, 186, 255, 255);
    SDL_RenderClear(m_Game->GetRenderer());
    anim.Render(m_Game->GetRenderer());
    SDL_RenderPresent(m_Game->GetRenderer());
}

void PlayState::Exit() {


}