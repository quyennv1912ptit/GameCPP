#include "PlayState.h"

#include "GameOverState.h"
#include "SettingsState.h"
#include "iostream"

float timer = 0;

void PlayState::Enter()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();

    playerCastle = new Castle(false);
    playerCastle->setPos(0, 0);
    playerCastle->setState(renderer, (EntityState)CastleState::IDLE);
    knights.push_back(playerCastle);

    enemyCastle = new Castle(true);
    enemyCastle->setPos(1000, 0);
    enemyCastle->setState(renderer, (EntityState)CastleState::IDLE);
    enemies.push_back(enemyCastle);

    pauseBtn = new ImageButton(renderer, "resources/imgs/ui/pauseBtn.png", "resources/imgs/ui/pauseBtn_hovered.png");
    pauseBtn->setPos({1200, 30});
    pauseBtn->setSize({50, 50});

    SettingBtn =
        new ImageButton(renderer, "resources/imgs/ui/settingBtn.png", "resources/imgs/ui/settingBtn_hovered.png");
    SettingBtn->setPos({1155, 35});
    SettingBtn->setSize({40, 40});

    strCoin = std::to_string(Coin) + "$";
    coinTextBox = new TextBox(renderer, "resources/fonts/mightysouly.ttf", strCoin, 80);
    coinTextBox->setPos({300, 50});
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

        if (pauseBtn->getIsHovered())
        {
            m_Game->PushState(new PauseState(m_Game));
        }
        if (SettingBtn->getIsHovered())
        {
            m_Game->PushState(new SettingsState(m_Game));
        }
    }
}

void PlayState::Update(float dt)
{
    SDL_Renderer *renderer = m_Game->GetRenderer();

    pauseBtn->update(m_Game->GetMousePos());
    SettingBtn->update(m_Game->GetMousePos());
    strCoin = std::to_string(Coin) + "$";
    coinTextBox->setText(strCoin);

    for (auto it = knights.begin(); it != knights.end();)
    {
        IEntity *k = *it;

        if (!k->getIsAlive())
        {
            diedKnights[k->getName()]++;
            if (k->getName() == "Castle")
                m_Game->PushState(new GameOverState(m_Game, false, 0, playerCastle->getMaxHP(), diedKnights, diedEnemies));
            delete k;
            it = knights.erase(it);
            continue;
        }
        SamuraiArcher *archer = dynamic_cast<SamuraiArcher *>(k);
        if (archer)
        {
            archer->update(enemies, renderer, dt);
        }
        else
        {
            TargetingSystem::FindNearestTarget(k, enemies);

            TargetingSystem::MoveToTarget(renderer, k, knights, dt);

            k->update();
        }

        ++it;
    }

    gameTime += dt;

    for (auto &m : timeInterval)
    {
        std::string name = m.first;
        float &interval = m.second.first;
        float &timer = m.second.second;
        if (gameTime >= wave.at(name).first && gameTime <= wave.at(name).second)
        {
            timer += dt;
            if (timer >= interval)
            {
                timer = 0;
                SpawnEnemy(m.first);
            }
        }
    }

    addCoinTimer += dt;

    if (addCoinTimer >= addCoinTime)
    {
        addCoinTimer = 0.0f;
        Coin += addCoin;
    }

    for (auto it = enemies.begin(); it != enemies.end();)
    {
        IEntity *e = *it;
        if (!e->getIsAlive())
        {
            diedEnemies[e->getName()]++;
            if (e->getName() == "Castle")
                m_Game->PushState(new GameOverState(m_Game, true, playerCastle->getCurHP(), playerCastle->getMaxHP(), diedKnights, diedEnemies));
            else
                Coin += cost_map.at(e->getName());
            delete e;
            it = enemies.erase(it);
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

    // entities
    allEntities.clear();
    allEntities.insert(allEntities.end(), knights.begin(), knights.end());
    allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());
    std::sort(allEntities.begin(), allEntities.end(),
              [](IEntity *a, IEntity *b)
              { return a->getTransform().pos.y < b->getTransform().pos.y; });

    // entities
    allEntities.clear();
    allEntities.insert(allEntities.end(), knights.begin(), knights.end());
    allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());
    std::sort(allEntities.begin(), allEntities.end(),
              [](IEntity *a, IEntity *b)
              {
                  return a->getTransform().pos.y < b->getTransform().pos.y;
              });
    for (IEntity *e : allEntities)
        e->render(renderer);

    ImGui::Begin("Hotbar", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::BeginTable("buttons", slots.size(), ImGuiTableFlags_SizingFixedFit))
    {
        ImGui::TableNextRow();

        for (int i = 0; i < slots.size(); i++)
        {
            ImGui::TableSetColumnIndex(i);
            if (ImGui::ImageButton(("btn" + std::to_string(i)).c_str(), slots[i].second, ImVec2(64, 64)))
            {
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

                    if (Coin >= cost_map.at(name))
                    {
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

                        int x_min = 200, x_max = 350;
                        int y_min = 200, y_max = 500;

                        int x = x_min + rand() % (x_max - x_min + 1);
                        int y = y_min + rand() % (y_max - y_min + 1);

                        e->setPos(x, y);

                        knights.push_back(e);

                        Coin -= cost_map.at(name);
                    }
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

        for (int i = 0; i < slots.size(); i++)
        {
            ImGui::TableSetColumnIndex(i);
            std::string name = slots[i].first;

            int coin = cost_map.at(name);

            ImGui::Text("%d$", coin);
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

    // ui
    pauseBtn->render();
    SettingBtn->render();
    coinTextBox->render();
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

void PlayState::SpawnEnemy(std::string type)
{
    SDL_Renderer *renderer = m_Game->GetRenderer();
    IEntity *enemy = nullptr;

    if (type == "Demon")
    {
        Demon *d = new Demon();
        d->setState(renderer, EntityState::IDLE);

        enemy = d;
    }
    else if (type == "Lizard")
    {
        Lizard *l = new Lizard();
        l->setState(renderer, EntityState::IDLE);

        enemy = l;
    }
    else if (type == "Jinn")
    {
        Jinn *j = new Jinn();
        j->setState(renderer, EntityState::IDLE);

        enemy = j;
    }
    else if (type == "Orc1")
    {
        Orc1 *o1 = new Orc1();
        o1->setState(renderer, EntityState::IDLE);

        enemy = o1;
    }
    else if (type == "Orc2")
    {
        Orc2 *o2 = new Orc2();
        o2->setState(renderer, EntityState::IDLE);

        enemy = o2;
    }
    else if (type == "Orc3")
    {
        Orc3 *o3 = new Orc3();
        o3->setState(renderer, EntityState::IDLE);
        enemy = o3;
    }

    if (enemy)
    {
        int y_min = 200, y_max = 500;

        int x = enemyCastle->GetHitPos().x - 100;
        int y = y_min + rand() % (y_max - y_min + 1);

        enemy->setPos(x, y);

        enemies.push_back(enemy);
    }
}