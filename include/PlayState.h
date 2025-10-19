#pragma once

#include <vector>
#include "GameState.h"
#include "PauseState.h"
#include "Animation.h"
#include "Image.h"
#include "Samurai.h"

const std::map<std::string, std::string> avt_path = {
    {"SAMURAI", "resources/imgs/avt/samurai_avt.png"},
    {"SAMURAI_ARCHER", "resources/imgs/avt/samurai_archer_avt.png"},
    {"SAMURAI_COMMANDER", "resources/imgs/avt/samurai_commander_avt.png"},
    {"SMALL_DRAGON", "resources/imgs/avt/small_dragon_avt.png"},
    {"DRAGON", "resources/imgs/avt/dragon_avt.png"},
};


class PlayState : public GameState
{
private:
    // ui
    // pause button
    ImageButton *pauseBtn;
    // hotbar
    std::vector<SDL_Texture *> avts;
    std::vector<std::pair<std::string, SDL_Texture *>> slots;
    int currentSlot = -1;
    bool showSelector = false;
    // all entities
    std::vector<IEntity *> knights;
    std::vector<IEntity *> enemies;

public:
    PlayState(Game *game) : slots(5, std::pair<std::string, SDL_Texture *>("None", nullptr)) { m_Game = game; }
    void Enter() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render() override;
    void Exit() override;
};