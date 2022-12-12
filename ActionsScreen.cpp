#include "ActionsScreen.h"
#include "imgui/imgui.h"
#include "ActionHistory.h"

ActionsScreen::ActionsScreen() : AUIScreen("ACTIONS_SCREEN")
{
}

ActionsScreen::~ActionsScreen()
{
}

void ActionsScreen::drawUI()
{
	ImGui::Begin("Actions", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(205, 75));
	ImGui::SameLine();

	if (ImGui::Button("Undo"))
	{
		if (ActionHistory::getInstance()->hasRemainingUndoActions())
		{
			
		}
	}

	ImGui::SameLine();

	if (ImGui::Button("Redo"))
	{
		if (ActionHistory::getInstance()->hasRemainingRedoActions())
		{
			
		}
	}

	ImGui::End();
}
