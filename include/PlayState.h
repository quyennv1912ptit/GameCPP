#pragma once

#include <vector>
#include "GameState.h"
#include "PauseState.h"
#include "Animation.h"
#include "Image.h"
#include "Samurai.h"
#include"Samurai_Archer.h"

class PlayState : public GameState
{
private:
    //ui
    //pause button
    ImageButton* pauseBtn;
    //all entities
    std::vector<IEntity*> knights;
    std::vector<IEntity*> enemies; 

public:
    PlayState(Game *game) { m_Game = game; }
    void Enter() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render() override;
    void Exit() override;
};