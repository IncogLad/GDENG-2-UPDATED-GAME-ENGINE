#include "GDPARCMScreen.h"
#include "EngineTime.h"
#include "imgui/imgui.h"
#include <ctime>

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

	double fps = (1.0 / EngineTime::getDeltaTime());
	if (fps > 60.0)
		fps = 60.0;

	ImGui::Text("FPS: %f", fps);

	ImGui::Text("");

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