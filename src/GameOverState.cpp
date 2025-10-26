#include "GameOverState.h"

#include "Config.h"
#include "IEnitity.h"
#include "MenuState.h"
#include "PlayState.h"
#include "iostream"

GameOverState::GameOverState(Game *game, bool isWin, IEntity *playerCastle, std::map<std::string, int> &diedKnights, std::map<std::string, int> &diedEnemies)
    : m_IsWin(isWin),
      m_PlayerCastle(playerCastle),
      m_DiedKinghts(diedKnights),
      m_DiedEnemies(diedEnemies)
{
    m_Game = game;
}

void GameOverState::Enter()
{
    winConditions[0].first = m_IsWin;

    winConditions[1].first = (m_PlayerCastle->getCurHP() / m_PlayerCastle->getMaxHP()) >= 0.5f;

    int cnt1 = -0, cnt2 = -0;

    for (auto it = m_DiedKinghts.begin(); it != m_DiedKinghts.end(); ++it)
    {
        cnt1 += it->second;
    }

    for (auto it = m_DiedEnemies.begin(); it != m_DiedEnemies.end(); ++it)
    {
        cnt2 += it->second;
    }
    std::cout << cnt1 << " " << cnt2 << std::endl;
    winConditions[2].first = cnt1 <= cnt2;

    for (int i = 0; i < winConditions.size(); i++)
    {
        m_StartCount += winConditions[i].first;
    }

    checkTexure = IMG_LoadTexture(m_Game->GetRenderer(), "resources/imgs/ui/check.png");
    notCheckTexture = IMG_LoadTexture(m_Game->GetRenderer(), "resources/imgs/ui/notCheck.png");
    greyStarTexture = IMG_LoadTexture(m_Game->GetRenderer(), "resources/imgs/ui/greyStar.png");
    starTexture = IMG_LoadTexture(m_Game->GetRenderer(), "resources/imgs/ui/star.png");
}

void GameOverState::Update(float dt) {}

void GameOverState::HandleEvent(const SDL_Event &event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void GameOverState::Render()
{
    SDL_Renderer *renderer = m_Game->GetRenderer();

    ImGui::SetNextWindowPos(
        ImVec2(Config::GetWindowSize().x * 0.5f -
                   m_MainDimensions.x * 0.5f,
               Config::GetWindowSize().y * 0.5f -
                   m_MainDimensions.y * 0.5f),
        ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(m_MainDimensions.x, m_MainDimensions.y));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin("GaemOver", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove);

    const char *label = (m_IsWin ? "-VICTORY-" : "-DEFEATED-");

    ImVec2 labelSize = ImGui::CalcTextSize(label);

    ImGui::SetCursorPosX((m_MainDimensions.x - labelSize.x) * 0.5f);

    ImGui::Text("%s", label);

    float starSize = 48.0f;
    int count = winConditions.size();
    float tableWidth = starSize * count;
    ImGui::SetCursorPosX((m_MainDimensions.x - tableWidth) * 0.5f);

    if (ImGui::BeginTable("Stars", winConditions.size(), ImGuiTableFlags_None))
    {
        for (int i = 0; i < winConditions.size(); i++)
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, starSize);
        ImGui::TableNextRow();
        for (int i = 0; i < m_StartCount; i++)
        {
            ImGui::TableSetColumnIndex(i);
            ImGui::Image(starTexture, ImVec2(starSize, starSize));
        }
        for (int i = m_StartCount; i < winConditions.size(); i++)
        {
            ImGui::TableSetColumnIndex(i);
            ImGui::Image(greyStarTexture, ImVec2(starSize, starSize));
        }
        ImGui::EndTable();
    }

    if (ImGui::BeginTable("Table", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Image", ImGuiTableColumnFlags_WidthFixed, 80.0f);
        ImGui::TableSetupColumn("Text", ImGuiTableColumnFlags_WidthStretch);
        for (int i = 0; i < winConditions.size(); i++)
        {
            SDL_Texture *tex = (winConditions[i].first ? checkTexure : notCheckTexture);
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Image(tex, {64, 64});
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", winConditions[i].second.c_str());
        }

        ImGui::EndTable();
    }

    float groupWidth = ImGui::GetItemRectSize().x;
    ImGui::SetCursorPosX((m_MainDimensions.x - groupWidth) * 0.5f);

    ImVec2 restartBtnDim = {200, 40};
    ImGui::SetCursorPosX((m_MainDimensions.x - restartBtnDim.x) * 0.5f);
    if (ImGui::Button("Restart", restartBtnDim))
    {
        m_Game->PopState();
        m_Game->PopState();
        m_Game->ChangeState(new PlayState(m_Game));
    }

    ImVec2 quitBtnDim = {200, 40};
    ImGui::SetCursorPosX((m_MainDimensions.x - quitBtnDim.x) * 0.5f);

    if (ImGui::Button("Quit", quitBtnDim))
    {
        m_Game->PopState();
        m_Game->ChangeState(new MenuState(m_Game));
    }
    ImGui::End();

    ImGui::PopStyleVar();
}

void GameOverState::Exit() { std::cout << "GameOverState unloaded\n"; }