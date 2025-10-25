#include "Game.h"

#include "Audio.h"
#include "Config.h"

SDL_Texture *tex = nullptr;

void Game::Init() {
	Config::Init();

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
		return;
	}

	if (!SDL_CreateWindowAndRenderer("GameCPP", Config::GetWindowSize().x,
	                                 Config::GetWindowSize().y, 0, &m_Window,
	                                 &m_Renderer)) {
		SDL_Log("SDL_CreateWindowAndRenderer Error: %s\n", SDL_GetError());
		return;
	}

	if (!TTF_Init()) {
		SDL_Log("TTF_Init Error: %s\n", SDL_GetError());
		return;
	}

	if (!MIX_Init()) {
		SDL_Log("MIX_Init %s\n", SDL_GetError());
		return;
	}

	tex = IMG_LoadTexture(
	    m_Renderer,
	    "resources/imgs/backgrounds/game_background_1/game_background_1.png");
	Audio::Get().Init();
	Audio::Get().PlayMusic(Config::GetMusic());
	Audio::Get().LoadVolume(m_MasterMusicVolume);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();

	io.Fonts->AddFontFromFileTTF("resources/fonts/arial.ttf", 22.0f);
	io.FontDefault = io.Fonts->Fonts.back();

	m_BigFont =
	    io.Fonts->AddFontFromFileTTF("resources/fonts/mightysouly.ttf", 28.0f);

	ImGui_ImplSDL3_InitForSDLRenderer(m_Window, m_Renderer);
	ImGui_ImplSDLRenderer3_Init(m_Renderer);

	m_Quit = false;

	ChangeState(new MenuState(this));
}

void Game::Run() {
	SDL_Event event;
	while (!m_Quit) {
		NOW = SDL_GetPerformanceCounter();

		m_DeltaTime =
		    (float)(NOW - LAST) / (float)SDL_GetPerformanceFrequency();

		LAST = NOW;

		SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
		if (!states.empty()) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EVENT_QUIT) {
					Quit();
				} else {
					states.back()->HandleEvent(event);
				}

				ImGui_ImplSDL3_ProcessEvent(&event);
			}
			states.back()->Update(m_DeltaTime);

			SDL_SetRenderDrawColor(m_Renderer, 200, 200, 200, 255);
			SDL_RenderClear(m_Renderer);

			SDL_FRect dest = {0, 0, Config::GetWindowSize().x,
			                  Config::GetWindowSize().y};
			SDL_RenderTexture(m_Renderer, tex, NULL, &dest);

			ImGui_ImplSDL3_NewFrame();
			ImGui_ImplSDLRenderer3_NewFrame();
			ImGui::NewFrame();

			for (auto state : states) state->Render();

			ImGui::Render();
			ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),
			                                      m_Renderer);

			SDL_RenderPresent(m_Renderer);
		}
	}

	Cleanup();
}

void Game::ChangeState(GameState *newState) {
	if (!states.empty()) {
		states.back()->Exit();
		delete states.back();
		states.pop_back();
	}

	states.push_back(newState);

	states.back()->Enter();
}

void Game::PushState(GameState *state) {
	states.push_back(state);
	states.back()->Enter();
}

void Game::PopState() {
	if (!states.empty()) {
		states.back()->Exit();
		delete states.back();
		states.pop_back();
	}
}

void Game::Cleanup() {
	if (!states.empty()) {
		for (auto state : states) {
			{
				state->Exit();
				delete state;
				state = nullptr;
			}
		}
	}

	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	Audio::Get().Shutdown();

	if (m_Renderer) {
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
	if (m_Window) {
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}
	SDL_Quit();
}

void Game::Quit() { m_Quit = true; }