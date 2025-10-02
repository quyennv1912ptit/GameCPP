#pragma once

#include "GameState.h"

class PlayState : public GameState
{
public:
    PlayState(Game *game) { m_Game = game; }
    void Enter() override;
    void HandleEvent(const SDL_Event& event) override;
    void Update() override;
    void Render() override;
    void Exit() override;
};