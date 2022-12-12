#include "ActionsScreen.h"
#include "imgui/imgui.h"
#include "ActionHistory.h"
#include "EditorAction.h"
#include "GameObjectManager.h"

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
		EditorAction* undoAction = ActionHistory::getInstance()->undoAction();

		if (undoAction != nullptr)
		{
			for (auto i : GameObjectManager::getInstance()->getGameObjectList())
			{
				if (i->getName() == undoAction->getOwnerName())
				{
					i->setPosition(undoAction->getStorePos());
					i->setRotation(undoAction->getStoredRotation());
					i->setScale(undoAction->getStoredScale());
					i->setLocalMatrix(undoAction->getStoredMatrix());
				}
			}
		}
	}

	ImGui::SameLine();

	if (ImGui::Button("Redo"))
	{
		EditorAction* redoAction = ActionHistory::getInstance()->redoAction();

		if (redoAction != nullptr)
		{
			for (auto i : GameObjectManager::getInstance()->getGameObjectList())
			{
				if (i->getName() == redoAction->getOwnerName())
				{
					i->setPosition(redoAction->getStorePos());
					i->setRotation(redoAction->getStoredRotation());
					i->setScale(redoAction->getStoredScale());
					i->setLocalMatrix(redoAction->getStoredMatrix());
				}
			}
		}
	}

	ImGui::End();
}
