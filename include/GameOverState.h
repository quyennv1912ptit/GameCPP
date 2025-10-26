#pragma once

#include "Game.h"
#include "GameState.h"
#include "IEnitity.h"
#include "string"

static std::vector<std::pair<bool, std::string>> winConditions = {
    {false, "Defeat all monsters"},
    {false, "Castle HP remains above 50%"},
    {false, "Lose fewer knights than the monsters"},
};

class GameOverState : public GameState
{
private:
    bool m_IsWin = false;
    Vector2 m_MainDimensions = {800, 600};
    std::map<std::string, int> &m_DiedKinghts;
    std::map<std::string, int> &m_DiedEnemies;
    IEntity *m_PlayerCastle = nullptr;
    int m_StartCount = 0;

    SDL_Texture *checkTexure = nullptr;
    SDL_Texture *notCheckTexture = nullptr;
    SDL_Texture *greyStarTexture = nullptr;
    SDL_Texture *starTexture = nullptr;

public:
    GameOverState(Game *game, bool isWin, IEntity *playerCastle, std::map<std::string, int> &diedKnights, std::map<std::string, int> &diedEnemies);
    void Enter() override;
    void Exit() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render() override;
};