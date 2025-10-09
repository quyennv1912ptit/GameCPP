#include "MenuState.h"
#include "PlayState.h"
#include "Button.h"

void MenuState::Enter()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();

    logoBox = new TextBox(renderer, "resources/fonts/mightysouly.ttf", "TOWER DEFENSE", 80);
    logoBox->setPos({(float)1280 / 2 - logoBox->getDims().size.x / 2, 100});

    startBtn = new TextButton(renderer, "resources/fonts/mightysouly.ttf", "START", 60, {255, 255, 255, 255}, {100, 100, 100, 255});
    startBtn->setPos({(float)1280 / 2 - startBtn->getDims().size.x / 2, 250});

    settingBtn = new TextButton(renderer, "resources/fonts/mightysouly.ttf", "SETTINGS", 60, {255, 255, 255, 255}, {100, 100, 100, 255});
    settingBtn->setPos({(float)1280 / 2 - settingBtn->getDims().size.x / 2, 350});

    exitBtn = new TextButton(renderer, "resources/fonts/mightysouly.ttf", "EXIT", 60, {255, 255, 255, 255}, {100, 100, 100, 255});
    exitBtn->setPos({(float)1280 / 2 - exitBtn->getDims().size.x / 2, 450});
}

void MenuState::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (startBtn->getIsHovered())
        {
            m_Game->ChangeState(new PlayState(m_Game));
        }
        else if (settingBtn->getIsHovered())
        {
        }
        else if (exitBtn->getIsHovered())
        {
            m_Game->Quit();
        }
    }
}

void MenuState::Update(float dt)
{
    startBtn->update(m_Game->GetMousePos());
    settingBtn->update(m_Game->GetMousePos());
    exitBtn->update(m_Game->GetMousePos());
}

void MenuState::Render()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();

    logoBox->render();

    startBtn->render();

    settingBtn->render();

    exitBtn->render();
}

void MenuState::Exit()
{
    delete logoBox;
    delete startBtn;
    delete settingBtn;
    delete exitBtn;

    logoBox = nullptr;
    startBtn = nullptr;
    settingBtn = nullptr;
    exitBtn = nullptr;
}
