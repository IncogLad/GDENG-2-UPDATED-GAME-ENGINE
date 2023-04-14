#include "GDPARCMScreen.h"
#include "EngineTime.h"
#include "imgui/imgui.h"
#include "GameObjectManager.h"
#include <ctime>

GDPARCMScreen::GDPARCMScreen() : AUIScreen("GDPARCM_SCREEN")
{
	
}

GDPARCMScreen::~GDPARCMScreen()
{
}

void GDPARCMScreen::drawUI()
{
	ImGui::Begin("GDPARCM Controls", 0);

	double fps = (1.0 / EngineTime::getDeltaTime());
	if (fps > 60.0)
		fps = 60.0;

	ImGui::Text("FPS: %f", fps);

	ImGui::Text("");

	ImGui::Text("Scene 1");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[1]);

	if (currentlyViewingScene != 1)
	{
		if (ImGui::Button("View Scene"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[1] == 1)
			{
				currentlyViewingScene = 1;
			}
			else
			{
				//show bigger loading bar
			}
		}
	}
	

	if (GameObjectManager::getInstance()->SceneLoadingRatio[1] == 1)
	{
		ImGui::Button("Unload Scene");
	}
	else 
	{
		ImGui::Text("");
	}

	ImGui::Separator();

	ImGui::Text("Scene 2");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[2]);
	if (ImGui::Button("View Scene"))
	{
		if (GameObjectManager::getInstance()->SceneLoadingRatio[2] == 1)
		{

		}
		else
		{
			//show bigger loading bar
		}
	}

	if (GameObjectManager::getInstance()->SceneLoadingRatio[2] == 1)
	{
		ImGui::Button("Unload Scene");
	}
	else
	{
		ImGui::Text("");
	}

	ImGui::Separator();

	ImGui::Text("Scene 3");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[3]);
	if (ImGui::Button("View Scene"))
	{
		if (GameObjectManager::getInstance()->SceneLoadingRatio[3] == 1)
		{

		}
		else
		{
			//show bigger loading bar
		}
	}

	if (GameObjectManager::getInstance()->SceneLoadingRatio[3] == 1)
	{
		ImGui::Button("Unload Scene");
	}
	else
	{
		ImGui::Text("");
	}

	ImGui::Separator();

	ImGui::Text("Scene 4");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[4]);
	if (ImGui::Button("View Scene"))
	{
		if (GameObjectManager::getInstance()->SceneLoadingRatio[4] == 1)
		{

		}
		else
		{
			//show bigger loading bar
		}
	}

	if (GameObjectManager::getInstance()->SceneLoadingRatio[4] == 1)
	{
		ImGui::Button("Unload Scene");
	}
	else
	{
		ImGui::Text("");
	}

	ImGui::Separator();

	ImGui::Text("Scene 5");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[5]);
	if (ImGui::Button("View Scene"))
	{
		if (GameObjectManager::getInstance()->SceneLoadingRatio[5] == 1)
		{

		}
		else
		{
			//show bigger loading bar
		}
	}

	if (GameObjectManager::getInstance()->SceneLoadingRatio[5] == 1)
	{
		ImGui::Button("Unload Scene");
	}
	else
	{
		ImGui::Text("");
	}

	ImGui::Separator();

	if (ImGui::Button("View All Scenes"))
	{
		
	}

	ImGui::End();
}