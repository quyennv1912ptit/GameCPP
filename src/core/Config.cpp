#include "Config.h"

#include "iostream"

Vector2 Config::m_WindowSize;
int Config::m_MusicIndex;
int Config::m_MusicVolume;
int Config::m_BGIndex;
int Config::m_WindowPadding;

void Config::Init()
{
    mINI::INIFile file("config.ini");

    mINI::INIStructure ini;

    file.read(ini);

    m_WindowSize = {(float)std::stoi(ini["window"]["width"]), (float)std::stoi(ini["window"]["height"])};

    m_MusicIndex = std::stoi(ini["music"]["index"]);

    m_MusicVolume = std::stoi(ini["music"]["volume"]);

    m_BGIndex = std::stoi(ini["background"]["index"]);
}

void Config::UpdateMusic(int MusicIndex)
{
    if (MusicIndex == m_MusicIndex)
        return;

    m_MusicIndex = MusicIndex;

    mINI::INIFile file("config.ini");

    mINI::INIStructure ini;

    file.read(ini);

    ini["music"]["index"] = std::to_string(MusicIndex);

    file.write(ini);

    std::cout << "config written successfully\n";
}

void Config::UpdateVolume(int MusicVolume)
{
    if (m_MusicVolume == MusicVolume)
        return;

    m_MusicVolume = MusicVolume;

    mINI::INIFile file("config.ini");

    mINI::INIStructure ini;

    file.read(ini);

    ini["music"]["volume"] = std::to_string(MusicVolume);

    file.write(ini);

    std::cout << "config written successfully\n";
}

void Config::UpdateBackground(int BGIndex)
{
    if (m_BGIndex == BGIndex)
        return;

    m_BGIndex = BGIndex;

    mINI::INIFile file("config.ini");

    mINI::INIStructure ini;

    file.read(ini);

    ini["background"]["index"] = std::to_string(BGIndex);

    file.write(ini);

    std::cout << "config written successfully\n";
}