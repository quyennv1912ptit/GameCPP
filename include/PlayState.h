#pragma once

#include <vector>
#include "GameState.h"
#include "Animation.h"
#include "IEnitity.h"

class PlayState : public GameState
{
private:
    IEntity* e;

public:
    PlayState(Game *game) { m_Game = game; }
    void Enter() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render() override;
    void Exit() override;
};