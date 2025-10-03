#pragma once

#include <string>
#include <vector>
#include <map>

#include "GameState.h"
#include "Game.h"
#include <SDL3_image/SDL_image.h>

enum class ButtonID
{
    START,
    SETTINGS,
    QUIT
};

const std::map<ButtonID, SDL_FRect> srcRects = {
    {ButtonID::START, {609, 0, 600, 200}},
    {ButtonID::SETTINGS, {609, 417, 600, 200}},
    {ButtonID::QUIT, {609, 625, 600, 200}}};

const std::map<ButtonID, SDL_FRect> destRects = {
    {ButtonID::START, {1200 / 2 - 300 / 2, 250, 300, 100}},
    {ButtonID::SETTINGS, {1200 / 2 - 300 / 2, 400, 300, 100}},
    {ButtonID::QUIT, {1200 / 2 - 300 / 2, 550, 300, 100}}};

struct MenuButton
{
    ButtonID ID;
    SDL_FRect src;
    SDL_FRect dest;
    bool isHovered = false;
    SDL_Texture *texture = nullptr;
};

class MenuState : public GameState
{
private:
    std::vector<MenuButton> m_Buttons;
    SDL_Texture *texture1 = nullptr;
    SDL_Texture *texture2 = nullptr;

public:
    MenuState(Game *game) { m_Game = game; }
    void Enter() override;
    void Exit() override;
    void HandleEvent(const SDL_Event& event) override;
    void Update(float dt) override;
    void Render() override;
};