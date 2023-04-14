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

	ImGui::Text("Scene 1");
	ImGui::ProgressBar(1.0f);
	if (ImGui::Button("View Scene"))
	{
		
	}

	ImGui::Text("");

	ImGui::Text("Scene 2");
	ImGui::ProgressBar(1.0f);
	if (ImGui::Button("View Scene"))
	{
		
	}

	ImGui::Text("");

	ImGui::Text("Scene 3");
	ImGui::ProgressBar(1.0f);
	if (ImGui::Button("View Scene"))
	{
		
	}

	ImGui::Text("");

	ImGui::Text("Scene 4");
	ImGui::ProgressBar(1.0f);
	if (ImGui::Button("View Scene"))
	{
		
	}

	ImGui::Text("");

	ImGui::Text("Scene 5");
	ImGui::ProgressBar(1.0f);
	if (ImGui::Button("View Scene"))
	{
		
	}

	ImGui::Text("");

	if (ImGui::Button("View All Scenes"))
	{
		
	}

	ImGui::End();
}