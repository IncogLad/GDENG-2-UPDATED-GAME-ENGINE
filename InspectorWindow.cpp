#include "InspectorWindow.h"

#include "imgui/imgui.h"

InspectorWindow::InspectorWindow() : AUIScreen("INSPECTOR_WINDOW")
{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::drawUI()
{
    ImGui::Begin("Inspector Window");
    
    ImGui::End();
}
