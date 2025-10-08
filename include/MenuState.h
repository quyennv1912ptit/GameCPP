#pragma once

#include <string>
#include <vector>
#include <map>

#include "GameState.h"
#include "Game.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <Transform.h>
#include "TextBox.h"
#include "Button.h"

class MenuState : public GameState
{
private:
    TextBox *logoBox;
    TextButton *startBtn;
    TextButton *settingBtn;
    TextButton *exitBtn;

public:
    MenuState(Game *game) { m_Game = game; }
    void Enter() override;
    void Exit() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render() override;
};