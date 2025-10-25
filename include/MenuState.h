#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <Transform.h>

#include <map>
#include <string>
#include <vector>

#include "Button.h"
#include "Game.h"
#include "GameState.h"
#include "TextBox.h"

class MenuState : public GameState {
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