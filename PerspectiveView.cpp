#include "PerspectiveView.h"

#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "UISystem.h"
#include "imgui/imgui.h"

PerspectiveView::PerspectiveView() :AUIScreen("PERSPECTIVE_VIEW")
{
    open = false;
}

PerspectiveView::~PerspectiveView()
{
}

void PerspectiveView::drawUI()
{
    if (open) {
        ImGui::Begin("Perspective View");
        ImGui::Image(GraphicsEngine::getInstance()->
            getRenderTextureOfType("PERSPECTIVE_CAMERA")->GetShaderResourceView(), ImVec2(UISystem::WINDOW_WIDTH / 2.f, UISystem::WINDOW_HEIGHT / 2.f));
        ImGui::End();
    }
}
