#include "SettingsState.h"

#include "Audio.h"
#include "Config.h"

SettingsState::SettingsState(Game* game) { m_Game = game; }

void SettingsState::Enter() { m_MusicVolume = Config::GetMusicVolume(); }

void SettingsState::Update(float dt) {}

void SettingsState::HandleEvent(const SDL_Event& event) {}

void SettingsState::Render() {
	SDL_Renderer* renderer = m_Game->GetRenderer();

	ImGui::SetNextWindowPos(
	    ImVec2(Config::GetWindowSize().x * 0.5f - Config::GetWindowPadding() -
	               m_MainDimension.x * 0.5f + m_ButtonXAdditive,
	           Config::GetWindowSize().y * 0.5f - Config::GetWindowPadding() -
	               m_MainDimension.y * 0.5f + m_ButtonXAdditive),
	    ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(m_MainDimension.x, m_MainDimension.y));
	ImGui::SetNextWindowBgAlpha(0.0f);

	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::Begin("Audio Menu", nullptr,
	             ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
	                 ImGuiWindowFlags_NoMove);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);

	float comboWidth = 400.0f;
	float comboHeight = 70.0f;
	float sliderWidth = 400.0f;
	float sliderHeight = 70.0f;

	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - comboWidth) * 0.5f);
	ImGui::SetNextItemWidth(comboWidth);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
	                    ImVec2(style.FramePadding.x,
	                           (comboHeight - ImGui::GetFontSize()) / 2.0f));
	m_CurrentMusicIndex = Config::GetMusic();
	std::string currentMusic =
	    "MUSIC " + std::to_string(m_CurrentMusicIndex + 1);
	if (ImGui::BeginCombo("##Music", currentMusic.c_str())) {
		for (int i = 0; i < Audio::Get().GetMusicCount(); i++) {
			std::string itemName = "MUSIC " + std::to_string(i + 1);
			bool isSelected = (i == m_CurrentMusicIndex);
			if (ImGui::Selectable(itemName.c_str(), isSelected)) {
				m_CurrentMusicIndex = i;
				Audio::Get().PlayMusic(i);
			}
			if (isSelected) ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::PopStyleVar();

	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - sliderWidth) * 0.5f);
	ImGui::SetNextItemWidth(sliderWidth);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
	                    ImVec2(style.FramePadding.x,
	                           (sliderHeight - ImGui::GetFontSize()) / 2.0f));

	if (ImGui::SliderInt("##Volume", &m_MusicVolume, 0, 100, "%d %%")) {
		Audio::Get().SetMusicVolume(m_MusicVolume);
	}

	ImGui::SameLine();
	ImGui::TextUnformatted("VOLUME");

	ImGui::PopStyleVar();

	float buttonWidth = 400.0f;
	float buttonHeight = 70.0f;
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) * 0.5f);
	if (ImGui::Button("BACK", ImVec2(buttonWidth, buttonHeight))) {
		m_Game->PopState();
	}

	ImGui::PopStyleVar(1);
	ImGui::End();
	ImGui::PopStyleVar(1);
}

void SettingsState::Exit() { SDL_Log("SettingsState Unloaded\n"); }