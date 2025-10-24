#pragma once

#include "SDL3/SDL.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "string"
#include "vector"

const std::vector<std::string> musicPaths = {
    "resources/musics/bg.ogg",        "resources/musics/Blaster.ogg",
    "resources/musics/Groove.ogg",    "resources/musics/Space.ogg",
    "resources/musics/Stellar.ogg",   "resources/musics/Victory.ogg",
    "resources/musics/Whimsical.ogg",
};

class Audio {
   private:
	int m_PlayingMusicIndex = 0;
	SDL_AudioSpec m_AudioSpec = {SDL_AUDIO_F32, 2, 48000};
	SDL_AudioDeviceID m_AudioDeviceID;
	MIX_Mixer *m_mixer = nullptr;
	MIX_Track *m_track = nullptr;
	std::vector<MIX_Audio *> m_MusicList;

   public:
	static Audio &Get() {
		static Audio m_Indtance;
		return m_Indtance;
	}

	Audio();
	~Audio();
	void Init();
	void LoadMusic(const char *path);
	void LoadVolume(int &volume);
	void PlayMusic(int index);
	void SetMusicVolume(int volume);

	void Shutdown();

	int GetMusicCount() { return m_MusicList.size(); }
};