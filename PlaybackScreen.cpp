#include "PlaybackScreen.h"
#include "EngineBackend.h"
#include "imgui/imgui.h"

PlaybackScreen::PlaybackScreen() : AUIScreen("PLAYBACK_SCREEN")
{
}

PlaybackScreen::~PlaybackScreen()
{
}

void PlaybackScreen::drawUI()
{
	EngineBackend* backend = EngineBackend::getInstance();

	ImGui::Begin("Scene Play Options", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(205, 75));
	ImGui::SameLine();

	if (backend->getMode() == EngineBackend::EDITOR)
	{
		if (ImGui::Button("Play")) { EngineBackend::getInstance()->setMode(EngineBackend::PLAY); }
	}
	else if (backend->getMode() != EngineBackend::EDITOR)
	{
		if (ImGui::Button("Stop")) { EngineBackend::getInstance()->setMode(EngineBackend::EDITOR); }
	}

	ImGui::SameLine();

	if (backend->getMode() == EngineBackend::PLAY)
	{
		if (ImGui::Button("Pause")) { EngineBackend::getInstance()->setMode(EngineBackend::PAUSED); }
	}
	else if (backend->getMode() == EngineBackend::PAUSED)
	{
		if (ImGui::Button("Resume")) { EngineBackend::getInstance()->setMode(EngineBackend::PLAY); }
	}

	ImGui::SameLine();
	if (backend->getMode() == EngineBackend::PAUSED && ImGui::Button("Frame Step")) { EngineBackend::getInstance()->startFrameStep(); }
	ImGui::End();
}