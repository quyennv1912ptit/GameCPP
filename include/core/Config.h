#pragma once

#include "Vector2.h"
#include "mini/ini.h"

class Config
{
private:
    static Vector2 m_WindowSize;
    static int m_MusicIndex;
    static int m_BGIndex;
    static int m_MusicVolume;
    static int m_WindowPadding;

public:
    static void Init();
    static void UpdateMusic(int musicIndex);
    static void UpdateVolume(int musicVolume);
    static void UpdateBackground(int bgIndex);
    static Vector2 GetWindowSize()
    {
        return m_WindowSize;
    }

    static int GetMusic()
    {
        return m_MusicIndex;
    }
    static int GetBackground()
    {
        return m_BGIndex;
    }
    static int GetMusicVolume()
    {
        return m_MusicVolume;
    }
    static int GetWindowPadding()
    {
        return m_WindowPadding;
    }
};