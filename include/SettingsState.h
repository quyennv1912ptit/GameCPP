#pragma once

#include "Game.h"
#include "GameState.h"
#include "string"

class SettingsState : public GameState {
   private:
	int m_CurrentMusicIndex = 0;
	int m_MusicVolume = 100;
	Vector2 m_MainDimension = {600, 250};
	int m_ButtonXAdditive = 0;

   public:
	SettingsState(Game *game);
	void Enter() override;
	void Exit() override;
	void HandleEvent(const SDL_Event &event) override;
	void Update(float dt) override;
	void Render() override;
};