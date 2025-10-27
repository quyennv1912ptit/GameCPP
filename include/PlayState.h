#pragma once

#include <vector>

#include "Animation.h"
#include "Castle.h"
#include "Demon.h"
#include "Dragon.h"
#include "FindTarget.h"
#include "GameState.h"
#include "Image.h"
#include "Jinn.h"
#include "Lizard.h"
#include "Medusa.h"
#include "Orc1.h"
#include "Orc2.h"
#include "Orc3.h"
#include "PauseState.h"
#include "Samurai.h"

#include "SamuraiCommander.h"
#include "Samurai_Archer.h"
#include "SmallDragon.h"

const std::map<std::string, std::string> avt_path = {
    {"Samurai", "resources/imgs/avt/samurai_avt.png"},
    {"Samurai Archer", "resources/imgs/avt/samurai_archer_avt.png"},
    {"Samurai Commander", "resources/imgs/avt/samurai_commander_avt.png"},
    {"Small Dragon", "resources/imgs/avt/small_dragon_avt.png"},
    {"Dragon", "resources/imgs/avt/dragon_avt.png"},
};

const std::map<std::string, int> cost_map = {
    {"None", 0},
    {"Samurai", 35},
    {"Small Dragon", 100},
    {"Samurai Commander", 70},
    {"Samurai Archer", 50},
    {"Dragon", 160},
    {"Demon", 50},
    {"Lizard", 25},
    {"Jinn", 20},
    {"Orc1", 5},
    {"Orc2", 7},
    {"Orc3", 9}};

static std::map<std::string, std::pair<float, float>> timeInterval = {
    {"Demon", {15, 0}},
    {"Lizard", {7.5, 0}},
    {"Jinn", {10, 0}},
    {"Orc1", {3, 0}},
    {"Orc2", {5, 0}},
    {"Orc3", {6, 0}}
};

const std::map<std::string, std::pair<float, float>> wave = {
    {"Demon", {100, 1e9}},
    {"Lizard", {80, 240}},
    {"Jinn", {75, 300}},
    {"Orc1", {0, 60}},
    {"Orc2", {5, 120}},
    {"Orc3", {10, 200}}
};

class PlayState : public GameState
{
private:
    // ui
    // pause button
    ImageButton *pauseBtn;
    ImageButton *SettingBtn;
    // hotbar
    std::vector<std::pair<std::string, SDL_Texture *>> avts;
    std::vector<std::pair<std::string, SDL_Texture *>> slots;
    int currentSlot = -1;
    bool showSelector = false;
    // all entities
    std::vector<IEntity *> knights;
    std::vector<IEntity *> enemies;
    std::vector<IEntity *> allEntities;

    const int addCoin = 10;
    const float addCoinTime = 4.0f;
    float addCoinTimer = 0.0f;

    std::map<std::string, int> diedKnights;
    std::map<std::string, int> diedEnemies;

    float gameTime = 0.0f;

    Castle *playerCastle;
    Castle *enemyCastle;

    int Coin = 150;
    std::string strCoin;

    TextBox *coinTextBox = nullptr;

public:
    PlayState(Game *game) : slots(5, std::pair<std::string, SDL_Texture *>("None", nullptr))
    {
        m_Game = game;
    }
    void Enter() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render() override;
    void Exit() override;

    void SpawnEnemy(std::string type);
};
