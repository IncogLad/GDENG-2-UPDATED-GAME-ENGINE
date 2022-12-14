#include "GameView.h"
#include "imgui/imgui.h"
#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "UISystem.h"
#include <iostream>
#include "CameraHandler.h"

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
        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow))
        {
            CameraHandler::getInstance()->setCurrentCamera("SCENE_CAMERA");
            CameraHandler::getInstance()->update();
            UISystem::getInstance()->UpdateDebugWindow("GameViewFocus");
            //std::cout << "lalal";
        }
        ImGui::End();
    }
}
