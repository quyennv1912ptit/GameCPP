#include "PauseState.h"

void PauseState::Enter()
{
    // ui
    SDL_Renderer *renderer = m_Game->GetRenderer();
    // title
    title = new TextBox(renderer, "resources/fonts/mightysouly.ttf", "-Game Paused-", 50);
    Transform titleDims = title->getDims();
    title->setPos({1280.0f / 2 - titleDims.size.x / 2, 100});

    // level
    level = new TextBox(renderer, "resources/fonts/mightysouly.ttf", "level 1", 30);
    level->setPos({450, 165});

    // resume
    resumeBtn = new CombinedButton(renderer, "resources/imgs/ui/playBtn.png", "resources/imgs/ui/playBtn_hovered.png", 50.0f, 50.0f, "resources/fonts/mightysouly.ttf", "Resume", 30.0f, {255, 255, 255, 255}, {100, 100, 100, 255});
    Transform resumeDims = resumeBtn->getDims();
    resumeBtn->setPos({1280.0f / 2 - resumeDims.size.x / 2, 200});
    buttons.push_back(resumeBtn);

    // restart
    restartBtn = new CombinedButton(renderer, "resources/imgs/ui/restartBtn.png", "resources/imgs/ui/restartBtn_hovered.png", 40.0f, 40.0f, "resources/fonts/mightysouly.ttf", "Restart", 30.0f, {255, 255, 255, 255}, {100, 100, 100, 255});
    Transform restartDims = restartBtn->getDims();
    restartBtn->setPos({1280.0f / 2 - restartDims.size.x / 2, 275});
    buttons.push_back(restartBtn);

    // quit
    quitBtn = new CombinedButton(renderer, "resources/imgs/ui/quitBtn.png", "resources/imgs/ui/quitBtn_hovered.png", 40.0f, 40.0f, "resources/fonts/mightysouly.ttf", "Quit", 30.0f, {255, 255, 255, 255}, {100, 100, 100, 255});
    Transform quitDims = quitBtn->getDims();
    quitBtn->setPos({1280.0f / 2 - quitDims.size.x / 2, 350});
    buttons.push_back(quitBtn);
}

void PauseState::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (resumeBtn->getIsHovered())
        {
            m_Game->PopState();
        }
        else if (quitBtn->getIsHovered())
        {
            m_Game->PopState();
            m_Game->PopState();
            m_Game->PushState(new MenuState(m_Game));
        }
        else if (restartBtn->getIsHovered())
        {
            m_Game->PopState();
            m_Game->PopState();
            m_Game->PushState(new PlayState(m_Game));
        }
    }
}

void PauseState::Update(float dt)
{
    for (auto button : buttons)
    {
        button->update(m_Game->GetMousePos());
    }
}

void PauseState::Render()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderFillRect(renderer, &bgRect);
    title->render();
    level->render();
    for (auto button : buttons)
    {
        button->render();
    }
}

void PauseState::Exit()
{
    delete title;
    delete level;
    for (auto btn : buttons)
        delete btn;
    buttons.clear();
}