#pragma once

#include <vector>

#include "Animation.h"
#include "Demon.h"
#include "Dragon.h"
#include "FindTarget.h"
#include "GameState.h"
#include "Image.h"
#include "PauseState.h"
#include "Samurai.h"
#include "SamuraiCommander.h"
#include "Samurai_Archer.h"
#include "SmallDragon.h"
#include "Lizard.h"
#include "Castle.h"

const std::map<std::string, std::string> avt_path = {
    {"Samurai", "resources/imgs/avt/samurai_avt.png"},
    {"Samurai Archer", "resources/imgs/avt/samurai_archer_avt.png"},
    {"Samurai Commander", "resources/imgs/avt/samurai_commander_avt.png"},
    {"Small Dragon", "resources/imgs/avt/small_dragon_avt.png"},
    {"Dragon", "resources/imgs/avt/dragon_avt.png"},
};

class PlayState : public GameState {
   private:
	// ui
	// pause button
	ImageButton* pauseBtn;
	ImageButton* SettingBtn;
	// hotbar
	std::vector<std::pair<std::string, SDL_Texture*>> avts;
	std::vector<std::pair<std::string, SDL_Texture*>> slots;
	int currentSlot = -1;
	bool showSelector = false;
	// all entities
	std::vector<IEntity*> knights;
	std::vector<IEntity*> enemies;
	std::vector<IEntity*> allEntities;

	// --- Bộ đếm thời gian tổng của game ---
    float gameTime = 0.0f;  // tổng thời gian kể từ lúc bắt đầu game (giây)

    //TIME SPAWN
    float demonTimer = 0.0f;
    float demonInterval = 5.0f;

    float lizardTimer = 0.0f;
    float lizardInterval = 3.0f;

    // --- Mốc thời gian mở khóa ---
    float unlockdemonTime = 60.0f;       // sau 60s (1 phút) mở khóa demon
    

    bool demonUnlocked = false;     //điều kiện mở quái
	// thành lũy (điều kiện win/lose)
	Castle* playerCastle;
    Castle* enemyCastle;


   public:
	PlayState(Game* game)
	    : slots(5, std::pair<std::string, SDL_Texture*>("None", nullptr)) {
		m_Game = game;
	}
	void Enter() override;
	void HandleEvent(const SDL_Event& event) override;
	void Update(float dt) override;
	void Render() override;
	void Exit() override;

	void SpawnEnemy(const std::string& type);
};