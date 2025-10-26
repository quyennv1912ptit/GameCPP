#include "Audio.h"

#include "Config.h"
#include "iostream"

Audio::Audio() {}

Audio::~Audio() {}

void Audio::Init()
{
    m_AudioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &m_AudioSpec);
    m_mixer = MIX_CreateMixerDevice(m_AudioDeviceID, &m_AudioSpec);
    m_track = MIX_CreateTrack(m_mixer);
    for (const std::string &path : musicPaths)
        LoadMusic(path.c_str());
}

void Audio::LoadMusic(const char *path)
{
    MIX_Audio *music = MIX_LoadAudio(m_mixer, path, false);
    m_MusicList.push_back(music);
}

void Audio::PlayMusic(int index)
{
    if (index < 0 || index >= m_MusicList.size())
    {
        std::cout << "Index out of range\n";
        return;
    }

    SDL_PropertiesID props = SDL_CreateProperties();

    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);

    MIX_SetTrackAudio(m_track, m_MusicList[index]);
    MIX_PlayTrack(m_track, props);

    SDL_DestroyProperties(props);

    Config::UpdateMusic(index);
}

void Audio::LoadVolume(int &volume)
{
    volume = Config::GetMusicVolume();
    SetMusicVolume(volume);
}

void Audio::SetMusicVolume(int volume)
{
    MIX_SetTrackGain(m_track, (float)volume / 100.0f);
    Config::UpdateVolume(volume);
}

void Audio::Shutdown()
{
    MIX_DestroyTrack(m_track);
    MIX_DestroyMixer(m_mixer);
    for (MIX_Audio *music : m_MusicList)
        MIX_DestroyAudio(music);
    m_MusicList.clear();
    MIX_Quit();
}