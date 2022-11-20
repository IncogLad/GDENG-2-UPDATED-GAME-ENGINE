#include "TopdownView.h"

#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "UISystem.h"
#include "imgui/imgui.h"

TopdownView::TopdownView() :AUIScreen("TOPDOWN_VIEW")
{
    open = false;
}

TopdownView::~TopdownView()
{
}

void TopdownView::drawUI()
{
    if (open) {
        ImGui::Begin("Topdown View");
        ImGui::Image(GraphicsEngine::getInstance()->getRenderTextureOfType("TOPDOWN_CAMERA")->GetShaderResourceView(), ImVec2(UISystem::WINDOW_WIDTH / 2.f, UISystem::WINDOW_HEIGHT / 2.f));
        ImGui::End();
        
    }
}
