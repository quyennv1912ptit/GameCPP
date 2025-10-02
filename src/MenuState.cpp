#include "MenuState.h"
#include "PlayState.h"

void MenuState::Enter()
{
    texture1 = IMG_LoadTexture(m_Game->GetRenderer(), "resources/imgs/Menu Buttons sprite (BnW).png");
    texture2 = IMG_LoadTexture(m_Game->GetRenderer(), "resources/imgs/Menu Buttons sprite (Colored).png");

    if (!texture1)
    {
        SDL_Log("IMG_LoadTexture Error: %s\n", SDL_GetError());
        m_Game->Quit();
        return;
    }

    if (!texture2)
    {
        SDL_Log("IMG_LoadTexture Error: %s\n", SDL_GetError());
        m_Game->Quit();
        SDL_DestroyTexture(texture1);
        return;
    }

    std::vector<ButtonID> ButtonIDs = {ButtonID::START, ButtonID::SETTINGS, ButtonID::QUIT};

    for (const ButtonID &ID : ButtonIDs)
    {
        MenuButton btn;
        btn.ID = ID;
        btn.src = srcRects.at(ID);
        btn.dest = destRects.at(ID);
        m_Buttons.push_back(btn);
    }
}

void MenuState::HandleEvent(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        for (MenuButton &btn : m_Buttons)
        {
            if (event.button.button == SDL_BUTTON_LEFT && btn.isHovered)
            {
                switch (btn.ID)
                {
                case ButtonID::START:
                    m_Game->ChangeState(new PlayState(m_Game));
                    break;
                case ButtonID::SETTINGS:
                    break;
                case ButtonID::QUIT:
                    m_Game->Quit();
                    break;
                }
            }
        }
    }
}

void MenuState::Update()
{

    for (MenuButton &btn : m_Buttons)
    {
        if (SDL_PointInRectFloat(m_Game->GetMousePos(), &btn.dest))
        {
            btn.isHovered = true;
            btn.texture = texture2;
        }
        else
        {
            btn.isHovered = false;
            btn.texture = texture1;
        }
    }
}

void MenuState::Render()
{
    SDL_SetRenderDrawColor(m_Game->GetRenderer(), 255, 30, 30, 255);

    SDL_RenderClear(m_Game->GetRenderer());

    for (const MenuButton &btn : m_Buttons)
    {
        SDL_RenderTexture(m_Game->GetRenderer(), btn.texture, &btn.src, &btn.dest);
    }

    SDL_RenderPresent(m_Game->GetRenderer());
}

void MenuState::Exit()
{
    if (texture1)
    {
        SDL_DestroyTexture(texture1);
        texture1 = nullptr;
    }
    if (texture2)
    {
        SDL_DestroyTexture(texture2);
        texture2 = nullptr;
    }
}