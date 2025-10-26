#pragma once
#include "MenuState.h"
#include "PlayState.h"

class PlayState;

class PauseState : public GameState
{
private:
    Game *m_Game;
    // ui
    CombinedButton *quitBtn, *restartBtn, *resumeBtn;

    std::vector<CombinedButton *> buttons;

    TextBox *title;
    TextBox *level;

    SDL_FRect bgRect = {1280 / 2 - 300, 50, 600, 400};

    Transform dims;

public:
    PauseState(Game *game)
    {
        m_Game = game;
    }
    void Enter() override;
    void Exit() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render() override;
};