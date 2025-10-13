#include "PlayState.h"
#include <Demon.h>


void PlayState::Enter()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();
    Samurai *e1 = new Samurai();
    e1->setState(renderer, SamuraiState::ATTACK1);
    e1->setPos(100, 100);
    e1->control = ControlType::PLAYER_WASD;
    knights.push_back(e1);

    Demon *demon= new Demon();
    demon->setState(renderer, DemonState::ATTACK);
    demon->setPos(400,105);
    demon->control = ControlType::PLAYER_ARROW;
    enemies.push_back(demon);

    pauseBtn = new ImageButton(renderer, "resources/imgs/ui/pauseBtn.png", "resources/imgs/ui/pauseBtn_hovered.png");
    pauseBtn->setPos({1200, 30});
    pauseBtn->setSize({50, 50});
}

void PlayState::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (pauseBtn->getIsHovered())
        {
            m_Game->PushState(new PauseState(m_Game));
        }
    }
}

void PlayState::Update(float dt)
{
    pauseBtn->update(m_Game->GetMousePos());
    for (IEntity *k : knights)
    {
        k->update();
    }

    for (IEntity *e : enemies)
    {
        e->update();
    }
}

void PlayState::Render()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();
    // ui
    pauseBtn->render();

    // entities
    for (IEntity *k : knights)
    {
        k->render(renderer);
    }

    for (IEntity *e : enemies)
    {
        e->render(renderer);
    }
}

void PlayState::Exit()
{
    for (IEntity *k : knights)
    {
        delete k;
    }

    for (IEntity *e : enemies)
    {
        delete e;
    }
}