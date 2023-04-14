#include "GDPARCMScreen.h"
#include "imgui/imgui.h"

GDPARCMScreen::GDPARCMScreen() : AUIScreen("GDPARCM_SCREEN")
{
}

GDPARCMScreen::~GDPARCMScreen()
{
}

void GDPARCMScreen::drawUI()
{
	ImGui::Begin("GDPARCM Controls", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(200, 500));

	ImGui::End();
}