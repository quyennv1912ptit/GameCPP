#pragma once

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <vector>

#include "MenuState.h"

class Game {
   private:
	SDL_Window *m_Window = nullptr;
	SDL_Renderer *m_Renderer = nullptr;
	bool m_Quit = true;

	int m_MasterMusicVolume = 100;

	std::vector<GameState *> states;

	MIX_Mixer *m_Mixer = nullptr;
	MIX_Track *m_BGMTrack = nullptr;
	MIX_Audio *m_BGMAudio = nullptr;
	SDL_AudioDeviceID m_AudioDevice = 0;
	SDL_PropertiesID props;

	Uint64 NOW = 0;
	Uint64 LAST = SDL_GetPerformanceCounter();
	float m_DeltaTime = 0;
	SDL_FPoint m_MousePos = {-1, -1};
	ImFont *m_BigFont = nullptr;
	void Cleanup();

   public:
	SDL_Renderer *GetRenderer() { return m_Renderer; }
	SDL_FPoint *GetMousePos() { return &m_MousePos; }
	void Init();
	void Run();
	void Quit();
	void ChangeState(GameState *);
	void PushState(GameState *);
	void PopState();
};