#include "Game.h"

void Game::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    if (!SDL_CreateWindowAndRenderer("GameCPP", 1280, 720, 0, &m_Window, &m_Renderer))
    {
        SDL_Log("SDL_CreateWindowAndRenderer Error: %s\n", SDL_GetError());
        return;
    }

    if (!TTF_Init())
    {
        SDL_Log("TTF_Init Error: %s\n", SDL_GetError());
        return;
    }

    if (!MIX_Init())
    {
        SDL_Log("MIX_Init %s\n", SDL_GetError());
        return;
    }

    SDL_AudioSpec desired_spec;
    SDL_zero(desired_spec);
    desired_spec.freq = 48000;
    desired_spec.format = SDL_AUDIO_F32;
    desired_spec.channels = 2;

    m_AudioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &desired_spec);
    if (!m_AudioDevice)
    {
        SDL_Log("SDL_OpenAudioDevice failed: %s", SDL_GetError());
        MIX_Quit();
        SDL_Quit();
        return;
    }

    m_Mixer = MIX_CreateMixerDevice(m_AudioDevice, &desired_spec);
    if (!m_Mixer)
    {
        SDL_Log("MIX_CreateMixerDevice failed: %s", SDL_GetError());
        SDL_CloseAudioDevice(m_AudioDevice);
        MIX_Quit();
        SDL_Quit();
        return;
    }

    const char *musicPath = "resources/musics/bg.ogg";
    m_BGMAudio = MIX_LoadAudio(m_Mixer, musicPath, true);

    if (!m_BGMAudio)
    {
        SDL_Log("MIX_LoadAudio failed: %s", SDL_GetError());
        return;
    }

    m_BGMTrack = MIX_CreateTrack(m_Mixer);
    MIX_SetTrackAudio(m_BGMTrack, m_BGMAudio);

    props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);

    if (!MIX_PlayTrack(m_BGMTrack, props))
    {
        SDL_Log("MIX_PlayTrack failed: %s", SDL_GetError());
        SDL_DestroyProperties(props);
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplSDL3_InitForSDLRenderer(m_Window, m_Renderer);
    ImGui_ImplSDLRenderer3_Init(m_Renderer);

    m_Quit = false;

    ChangeState(new MenuState(this));
}

void Game::Run()
{
    SDL_Event event;
    while (!m_Quit)
    {
        NOW = SDL_GetPerformanceCounter();

        m_DeltaTime = (float)(NOW - LAST) / (float)SDL_GetPerformanceFrequency();

        LAST = NOW;

        SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
        if (!states.empty())
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    Quit();
                }
                else
                {
                    states.back()->HandleEvent(event);
                }

                ImGui_ImplSDL3_ProcessEvent(&event);
            }
            states.back()->Update(m_DeltaTime);

            SDL_SetRenderDrawColor(m_Renderer, 200, 200, 200, 255);
            SDL_RenderClear(m_Renderer);

            for (auto state : states)
                state->Render();

            SDL_RenderPresent(m_Renderer);
        }
    }

    Cleanup();
}

void Game::ChangeState(GameState *newState)
{
    if (!states.empty())
    {
        states.back()->Exit();
        delete states.back();
        states.pop_back();
    }

    states.push_back(newState);

    states.back()->Enter();
}

void Game::PushState(GameState *state)
{
    states.push_back(state);
    states.back()->Enter();
}

void Game::PopState()
{
    if (!states.empty())
    {
        states.back()->Exit();
        delete states.back();
        states.pop_back();
    }
}

void Game::Cleanup()
{
    if (m_BGMTrack)
        MIX_DestroyTrack(m_BGMTrack);
    if (m_BGMAudio)
        MIX_DestroyAudio(m_BGMAudio);
    if (m_Mixer)
        MIX_DestroyMixer(m_Mixer);
    if (m_AudioDevice)
        SDL_CloseAudioDevice(m_AudioDevice);

    SDL_DestroyProperties(props);

    MIX_Quit();

    if (!states.empty())
    {
        for (auto state : states)
        {
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

    if (m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }
    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }
    SDL_Quit();
}

void Game::Quit()
{
    m_Quit = true;
}