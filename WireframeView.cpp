#include "WireframeView.h"

#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "UISystem.h"
#include "imgui/imgui.h"

WireframeView::WireframeView() :AUIScreen("WIREFRAME_VIEW")
{
    open = false;
}

WireframeView::~WireframeView()
{
}

void WireframeView::drawUI()
{
    if (open) {
        ImGui::Begin("Wireframe View");
        ImGui::Image(GraphicsEngine::getInstance()->getRenderTextureOfType("WIREFRAME_CAMERA")->GetShaderResourceView(), ImVec2(UISystem::WINDOW_WIDTH/2.f, UISystem::WINDOW_HEIGHT/2.f));
        ImGui::End();
    }

}
