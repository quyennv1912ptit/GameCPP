#pragma once

#include "GameState.h"
#include "Animation.h"

class PlayState : public GameState
{
public:
    Animation anim;
public:
    PlayState(Game *game) { m_Game = game; }
    void Enter() override;
    void HandleEvent(const SDL_Event& event) override;
    void Update(float dt) override;
    void Render() override;
    void Exit() override;
};