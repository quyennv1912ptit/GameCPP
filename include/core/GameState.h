#pragma once

#include <SDL3/SDL.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

class Game;

class GameState {
   protected:
	Game *m_Game;

   public:
	~GameState() = default;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void HandleEvent(const SDL_Event &event) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};