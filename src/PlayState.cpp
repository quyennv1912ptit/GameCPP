#include "PlayState.h"

void PlayState::Enter()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();

    pauseBtn = new ImageButton(renderer, "resources/imgs/ui/pauseBtn.png", "resources/imgs/ui/pauseBtn_hovered.png");
    pauseBtn->setPos({1200, 30});
    pauseBtn->setSize({50, 50});

    for (auto kn : avt_path)
    {

        SDL_Texture *texture = nullptr;

        texture = IMG_LoadTexture(renderer, kn.second.c_str());

        avts.push_back(texture);
    }
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

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    ImGui::NewFrame();

    ImGui::Begin("Hotbar");

    if (ImGui::BeginTable("buttons", slots.size(), ImGuiTableFlags_SizingFixedFit))
    {
        ImGui::TableNextRow();

        for (int i = 0; i < slots.size(); i++)
        {
            ImGui::TableSetColumnIndex(i);
            if (ImGui::ImageButton(("btn" + std::to_string(i)).c_str(), slots[i].second, ImVec2(64, 64)))
            {
                printf("clicked %d\n", i + 1);
                if (currentSlot == i)
                {
                    showSelector = !showSelector;
                }
                else
                {
                    currentSlot = i;
                    showSelector = true;
                }
            }
        }

        ImGui::TableNextRow();

        for (int i = 0; i < slots.size(); i++)
        {
            ImGui::TableSetColumnIndex(i);

            ImGui::Text(slots[i].first.c_str());
        }

        ImGui::TableNextRow();

        for (int col = 0; col < slots.size(); col++)
        {
            ImGui::TableSetColumnIndex(col);

            ImGui::Text("%d$", 500);
        }

        ImGui::EndTable();
    }

    ImGui::End();

    if (showSelector)
    {
        ImGui::Begin("Select Character", &showSelector, ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Text("Select character for slot %d", currentSlot + 1);
        if (ImGui::BeginTable("ch_sel", avts.size(), ImGuiTableFlags_SizingFixedFit))

            ImGui::TableNextRow();

        for (int i = 0; i < avts.size(); i++)
        {
            ImGui::TableSetColumnIndex(i);
            if (ImGui::ImageButton(("btn_avt" + std::to_string(i)).c_str(), avts[i], ImVec2(64, 64)))
            {
                slots[currentSlot].second = avts[i];
                showSelector = false;
            }
        }

        ImGui::EndTable();

        ImGui::End();
    }

    ImGui::Render();

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void PlayState::Exit()
{
    // SDL_DestroyTexture(texture);

    for (IEntity *k : knights)
    {
        delete k;
    }

    for (IEntity *e : enemies)
    {
        delete e;
    }
}