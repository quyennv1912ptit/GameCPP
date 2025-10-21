#pragma once

#include <vector>
#include "GameState.h"
#include "PauseState.h"
#include "Animation.h"
#include "Image.h"
#include "Samurai.h"
#include "Samurai_Archer.h"
#include "Arrow.h"
#include "Demon.h"
#include "Jinn.h"
#include "Lizard.h"
#include "Medusa.h"
#include "Orc1.h"
#include "Orc2.h"
#include "Orc3.h"


class PlayState : public GameState
{
private:
    SamuraiArcher *e1 = nullptr;
    Demon *e2 = nullptr;
    std::vector<Arrow*> arrows;
    float arrowTimer = 0.0f;
     
private:
    //ui
    //pause button
    ImageButton* pauseBtn;
    //all entities
    std::vector<IEntity*> knights;
    std::vector<IEntity*> enemies; 

public:
    PlayState(Game *game) { m_Game = game; }
    void Enter() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render() override;
    void Exit() override;
};