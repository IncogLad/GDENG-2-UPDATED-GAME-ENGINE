#include "TopdownView.h"

#include "GraphicsEngine.h"
#include "RenderTexture.h"
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
        ImGui::Image(GraphicsEngine::getInstance()->getRenderTextureOfType("TOPDOWN_CAMERA")->GetShaderResourceView(), ImVec2(512, 512));
        ImGui::End();
        
    }
}
