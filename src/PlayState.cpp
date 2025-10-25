#include "PlayState.h"

#include "SettingsState.h"

void PlayState::Enter() {
	SDL_Renderer* renderer = m_Game->GetRenderer();

	// ✅ Thêm castle 2 bên
	playerCastle = new Castle(false);
	playerCastle->setPos(0, -50);  // bên trái
	playerCastle->setState(renderer, (EntityState)CastleState::IDLE);
	knights.push_back(playerCastle);

	// ✅ Castle của kẻ địch
	enemyCastle = new Castle(true);
	enemyCastle->setPos(1050, -50);
	enemyCastle->setState(renderer, (EntityState)CastleState::IDLE);
	enemies.push_back(enemyCastle);

	pauseBtn = new ImageButton(renderer, "resources/imgs/ui/pauseBtn.png",
	                           "resources/imgs/ui/pauseBtn_hovered.png");
	pauseBtn->setPos({1200, 30});
	pauseBtn->setSize({50, 50});

	SettingBtn = new ImageButton(renderer, "resources/imgs/ui/settingBtn.png",
	                             "resources/imgs/ui/settingBtn_hovered.png");
	SettingBtn->setPos({1155, 35});
	SettingBtn->setSize({40, 40});

	for (auto kn : avt_path) {
		SDL_Texture* texture = nullptr;

		texture = IMG_LoadTexture(renderer, kn.second.c_str());

		std::pair<std::string, SDL_Texture*> p = {kn.first, texture};

		avts.push_back(p);
	}
}

void PlayState::HandleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		int mouseX = event.button.x;
		int mouseY = event.button.y;

		// 1️⃣ Kiểm tra nút pause
		if (pauseBtn->getIsHovered()) {
			m_Game->PushState(new PauseState(m_Game));
		}
		if (SettingBtn->getIsHovered()) {
			m_Game->PushState(new SettingsState(m_Game));
		}
	}
}

void PlayState::Update(float dt) {
	SDL_Renderer* renderer = m_Game->GetRenderer();

	pauseBtn->update(m_Game->GetMousePos());
	SettingBtn->update(m_Game->GetMousePos());

	// cập nhật knights
	for (auto it = knights.begin(); it != knights.end();) {
		IEntity* k = *it;

		if (!k->getIsAlive()) {
			delete k;
			it = knights.erase(it);
			continue;
		}

		TargetingSystem::FindNearestTarget(k, enemies);

		TargetingSystem::MoveToTarget(renderer, k, knights, dt);

		k->update();

		++it;
	}

	// chỉnh spawn quái

	// --- Bộ đếm thời gian sinh quái ---
	static float gameTime = 0.0f;  // Tổng thời gian đã trôi qua trong game
	gameTime += dt;
	// --- Bộ đếm thời gian sinh quái ---
	demonTimer += dt;
	lizardTimer += dt;
	// Demon sinh mỗi 3 giây
	// if (gameTime >= 60.0f) {
	// 	if (demonTimer >= demonInterval) {
	// 		demonTimer = 0.0f;
	// 		SpawnEnemy("Demon");
	// 	}
	// }

	// if (lizardTimer >= lizardInterval) {
	// 	lizardTimer = 0.0f;
	// 	SpawnEnemy("Lizard");
	// }

	// cập nhật enemies
	for (auto it = enemies.begin(); it != enemies.end();) {
		IEntity* e = *it;
		if (!e->getIsAlive()) {
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

void PlayState::Render() {
	SDL_Renderer* renderer = m_Game->GetRenderer();
	// ui
	pauseBtn->render();
	SettingBtn->render();
	// entities
	allEntities.clear();
	allEntities.insert(allEntities.end(), knights.begin(), knights.end());
	allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());
	std::sort(allEntities.begin(), allEntities.end(),
	          [](IEntity* a, IEntity* b) {
		          return a->getTransform().pos.y < b->getTransform().pos.y;
	          });

	for (IEntity* e : allEntities) e->render(renderer);

	ImGui::Begin("Hotbar", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::BeginTable("buttons", slots.size(),
	                      ImGuiTableFlags_SizingFixedFit)) {
		ImGui::TableNextRow();

		for (int i = 0; i < slots.size(); i++) {
			ImGui::TableSetColumnIndex(i);
			if (ImGui::ImageButton(("btn" + std::to_string(i)).c_str(),
			                       slots[i].second, ImVec2(64, 64))) {
				if (slots[i].second == nullptr) {
					if (currentSlot == i) {
						showSelector = !showSelector;
					} else {
						currentSlot = i;
						showSelector = true;
					}
				} else {
					IEntity* e;

					std::string name = slots[i].first;

					if (name == "Samurai") {
						e = new Samurai();
						e->setState(renderer, SamuraiState::ATTACK1);
					} else if (name == "Samurai Archer") {
						e = new SamuraiArcher();
						e->setState(renderer, SamuraiArcherState::ATTACK1);
					} else if (name == "Samurai Commander") {
						e = new SamuraiCommander();
						e->setState(renderer, SamuraiCommanderState::ATTACK1);
					} else if (name == "Dragon") {
						e = new Dragon();
						e->setState(renderer, DragonState::ATTACK);
					} else if (name == "Small Dragon") {
						e = new SmallDragon();
						e->setState(renderer, SmallDragonState::ATTACK);
					}

					// Vị trí xuất hiện của người chơi (bên trái màn hình)
					int x_min = 200, x_max = 630;
					int y_min = 0, y_max = 720;

					int x = x_min + rand() % (x_max - x_min + 1);
					int y = y_min + rand() % (y_max - y_min + 1);

					e->setPos(x, y);

					knights.push_back(e);
				}
			}
		}

		ImGui::TableNextRow();

		for (int i = 0; i < slots.size(); i++) {
			ImGui::TableSetColumnIndex(i);

			ImGui::Text(slots[i].first.c_str());
		}

		ImGui::TableNextRow();

		for (int col = 0; col < slots.size(); col++) {
			ImGui::TableSetColumnIndex(col);

			ImGui::Text("%d$", 500);
		}

		ImGui::EndTable();
	}

	ImGui::End();

	if (showSelector) {
		ImGui::Begin("Select Character", &showSelector,
		             ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Text("Select character for slot %d", currentSlot + 1);
		if (ImGui::BeginTable("ch_sel", avts.size(),
		                      ImGuiTableFlags_SizingFixedFit))

			ImGui::TableNextRow();

		for (int i = 0; i < avts.size(); i++) {
			ImGui::TableSetColumnIndex(i);
			if (ImGui::ImageButton(("btn_avt" + std::to_string(i)).c_str(),
			                       avts[i].second, ImVec2(64, 64))) {
				slots[currentSlot] = avts[i];
				showSelector = false;
			}
		}

		ImGui::EndTable();

		ImGui::End();
	}
}

void PlayState::Exit() {
	// SDL_DestroyTexture(texture);

	for (IEntity* k : knights) {
		delete k;
	}

	for (IEntity* e : enemies) {
		delete e;
	}
}

void PlayState::SpawnEnemy(const std::string& type) {
	SDL_Renderer* renderer = m_Game->GetRenderer();
	IEntity* enemy = nullptr;

	if (type == "Demon") {
		Demon* d = new Demon();
		d->setState(renderer, DemonState::IDLE);

		enemy = d;
	}

	else if (type == "Lizard") {
		Lizard* l = new Lizard();
		l->setState(renderer, LizardState::IDLE);
		enemy = l;
	}

	if (enemy) {
		// Kích thước sprite trung bình
		const float enemyWidth = 64.0f;
		const float enemyHeight = 64.0f;

		// Giới hạn spawn trong nửa phải màn hình, không vượt biên
		float spawnX = 640 + rand() % int(1280 - 640 - enemyWidth);
		float spawnY = rand() % int(720 - enemyHeight);

		// Đặt vị trí
		enemy->getTransform().pos = {spawnX, spawnY};

		enemies.push_back(enemy);
	}
}