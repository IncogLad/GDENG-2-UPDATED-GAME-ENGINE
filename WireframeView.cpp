#include "WireframeView.h"

#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "UISystem.h"
#include "imgui/imgui.h"
#include "CameraHandler.h"

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
        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow))
        {
            CameraHandler::getInstance()->setCurrentCamera("WIREFRAME_CAMERA");
            CameraHandler::getInstance()->update();
        }
        ImGui::End();
    }

}
