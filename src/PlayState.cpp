#include "PlayState.h"

void PlayState::Enter()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();
    Samurai *e1 = new Samurai();
    e1->setState(renderer, SamuraiState::ATTACK1);
    e1->setPos(100, 100);

    knights.push_back(e1);

    Demon *demon = new Demon();
    demon->setState(renderer, DemonState::ATTACK);
    demon->setPos(550, 250);

    enemies.push_back(demon);

    pauseBtn = new ImageButton(renderer, "resources/imgs/ui/pauseBtn.png", "resources/imgs/ui/pauseBtn_hovered.png");
    pauseBtn->setPos({1200, 30});
    pauseBtn->setSize({50, 50});

    for (auto kn : avt_path)
    {

        SDL_Texture *texture = nullptr;

        texture = IMG_LoadTexture(renderer, kn.second.c_str());

        std::pair<std::string, SDL_Texture *> p = {kn.first, texture};

        avts.push_back(p);
    }
}

void PlayState::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        // 1️⃣ Kiểm tra nút pause
        if (pauseBtn->getIsHovered())
        {
            m_Game->PushState(new PauseState(m_Game));
        }
    }
}

void PlayState::Update(float dt)
{
    // const bool *keys = SDL_GetKeyboardState(NULL);

    SDL_Renderer *renderer = m_Game->GetRenderer();

    pauseBtn->update(m_Game->GetMousePos());
    for (auto it = knights.begin(); it != knights.end();)
    {
        IEntity *k = *it;

        if (!k->getIsAlive())
        {
            delete k;
            it = knights.erase(it);
            continue;
        }
        // Transform &transform = k->getTransform();
        // if (keys[SDL_SCANCODE_W])
        // {
        //     transform.pos.y -= 0.5;
        // }
        // if (keys[SDL_SCANCODE_A])
        // {
        //     transform.pos.x -= 0.5;
        // }
        // if (keys[SDL_SCANCODE_S])
        // {
        //     transform.pos.y += 0.5;
        // }
        // if (keys[SDL_SCANCODE_D])
        // {
        //     transform.pos.x += 0.5;
        // }

        TargetingSystem::FindNearestTarget(k, enemies);

        TargetingSystem::MoveToTarget(renderer, k, knights, dt);

        k->update();

        ++it;
    }

    for (auto it = enemies.begin(); it != enemies.end();)
    {
        IEntity *e = *it;

        if (!e->getIsAlive())
        {
            delete e;
            it = enemies.erase(it);

            Demon *demon = new Demon();
            demon->setState(renderer, DemonState::WALK);
            int x_min = 0, x_max = 1280;
            int y_min = 0, y_max = 720;

            int x = x_min + rand() % (x_max - x_min + 1);
            int y = y_min + rand() % (y_max - y_min + 1);

            demon->setPos(x, y);

            enemies.push_back(demon);

            continue;
        }

        TargetingSystem::FindNearestTarget(e, knights);

        TargetingSystem::MoveToTarget(renderer, e, enemies, dt);

        e->update();

        ++it;
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

    ImGui::Begin("Hotbar", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::BeginTable("buttons", slots.size(), ImGuiTableFlags_SizingFixedFit))
    {
        ImGui::TableNextRow();

        for (int i = 0; i < slots.size(); i++)
        {
            ImGui::TableSetColumnIndex(i);
            if (ImGui::ImageButton(("btn" + std::to_string(i)).c_str(), slots[i].second, ImVec2(64, 64)))
            {
                printf("clicked %d\n", i + 1);
                if (slots[i].second == nullptr)
                {
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
                else
                {
                    IEntity *e;

                    std::string name = slots[i].first;

                    if (name == "Samurai")
                    {
                        e = new Samurai();
                        e->setState(renderer, SamuraiState::ATTACK1);
                    }
                    else if (name == "Samurai Archer")
                    {
                        e = new SamuraiArcher();
                        e->setState(renderer, SamuraiArcherState::ATTACK1);
                    }
                    else if (name == "Samurai Commander")
                    {
                        e = new SamuraiCommander();
                        e->setState(renderer, SamuraiCommanderState::ATTACK1);
                    }
                    else if (name == "Dragon")
                    {
                        e = new Dragon();
                        e->setState(renderer, DragonState::ATTACK);
                    }
                    else if (name == "Small Dragon")
                    {
                        e = new SmallDragon();
                        e->setState(renderer, SmallDragonState::ATTACK);
                    }

                    int x_min = 0, x_max = 1280;
                    int y_min = 0, y_max = 720;

                    int x = x_min + rand() % (x_max - x_min + 1);
                    int y = y_min + rand() % (y_max - y_min + 1);

                    e->setPos(x, y);

                    knights.push_back(e);
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
            if (ImGui::ImageButton(("btn_avt" + std::to_string(i)).c_str(), avts[i].second, ImVec2(64, 64)))
            {
                slots[currentSlot] = avts[i];
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