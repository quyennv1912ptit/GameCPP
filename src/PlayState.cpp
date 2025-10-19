#include "PlayState.h"



void PlayState::Enter()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();
    Samurai *e1 = new Samurai();
    e1->setState(renderer, SamuraiState::ATTACK1);
    e1->setPos(100, 100);
   
    knights.push_back(e1);

    Demon *demon= new Demon();
    demon->setState(renderer, DemonState::ATTACK);
    demon->setPos(550,250);
    
    enemies.push_back(demon);

    pauseBtn = new ImageButton(renderer, "resources/imgs/ui/pauseBtn.png", "resources/imgs/ui/pauseBtn_hovered.png");
    pauseBtn->setPos({1200, 30});
    pauseBtn->setSize({50, 50});
}

void PlayState::HandleEvent(const SDL_Event &event)
{
    if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        // 1️⃣ Kiểm tra nút pause trước
        if(pauseBtn->getIsHovered())
        {
            m_Game->PushState(new PauseState(m_Game));
            return; // không xử lý di chuyển nếu click nút
        }

        // 2️⃣ Nếu không click nút pause, di chuyển Samurai
        if(!knights.empty())
        {
            Samurai* player = dynamic_cast<Samurai*>(knights[0]);
            player->setTargetPos((float)mouseX, (float)mouseY); 
            // ưu tiên chuột
            player->mouseControlActive = true;
        }
    }
}


void PlayState::Update(float dt)
{
    pauseBtn->update(m_Game->GetMousePos());
    // --- Cập nhật knights ---
    for(IEntity* k : knights)
{
    k->update();  // di chuyển theo chuột hoặc update khác

    Samurai* player = dynamic_cast<Samurai*>(k);
    if(player)
    {
        // 1️⃣ tìm target gần nhất
        player->attackTarget = TargetingSystem::FindNearestTarget(player, enemies, player->attackRange);

        // 2️⃣ di chuyển tới target nếu có trong phạm vi
        TargetingSystem::MoveToTarget(player, 1.0f);  // dt = 1.0 hoặc deltaTime
    }
}

    for(IEntity* e : enemies)
{
    e->update();

    Demon* demon = dynamic_cast<Demon*>(e);
    if(demon)
    {
        demon->attackTarget = TargetingSystem::FindNearestTarget(demon, knights, demon->attackRange);
        TargetingSystem::MoveToTarget(demon, 1.0f);
    }
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