#include "GameView.h"
#include "imgui/imgui.h"
#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "UISystem.h"

GameView::GameView() :AUIScreen("GAME_VIEW")
{
    open = true;
}

GameView::~GameView()
{
}

void GameView::drawUI()
{
    if (open) {
        ImGui::Begin("Game View");
        ImGui::Image(GraphicsEngine::getInstance()->getRenderTextureOfType("SCENE_CAMERA")->GetShaderResourceView(), ImVec2(UISystem::WINDOW_WIDTH / 2.f, UISystem::WINDOW_HEIGHT / 2.f));
        ImGui::End();
    }
}
