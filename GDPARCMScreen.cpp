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
		if (ImGui::Button("View Scene 1"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[1] == 1)
			{
				currentlyViewingScene = 1;
				
				GameObjectManager::getInstance()->viewSceneMeshes(1);
			}
			else
			{
				//show bigger loading bar
			}
		}
	}
	

	if (GameObjectManager::getInstance()->SceneLoadingRatio[1] == 1)
	{
		if (ImGui::Button("Unload Scene 1"))
		{
			while (GameObjectManager::getInstance()->scene1MeshList.size() != 0)
			{
				GameObjectManager::getInstance()->unloadSceneMeshes(1);
			}
			currentlyViewingScene = 0;
		}
	}
	else 
	{
		ImGui::Text("");
	}

	ImGui::Separator();

	ImGui::Text("Scene 2");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[2]);
	
	if (currentlyViewingScene != 2)
	{
		if (ImGui::Button("View Scene 2"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[2] == 1)
			{
				currentlyViewingScene = 2;
				GameObjectManager::getInstance()->viewSceneMeshes(2);
			}
			else
			{
				//show bigger loading bar
			}
		}
	}

	if (GameObjectManager::getInstance()->SceneLoadingRatio[2] == 1)
	{
		if (ImGui::Button("Unload Scene 2"))
		{
			while (GameObjectManager::getInstance()->scene2MeshList.size() != 0)
			{
				GameObjectManager::getInstance()->unloadSceneMeshes(2);
			}
			currentlyViewingScene = 0;
		}
	}
	else
	{
		ImGui::Text("");
	}

	ImGui::Separator();

	ImGui::Text("Scene 3");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[3]);

	if (currentlyViewingScene != 3)
	{
		if (ImGui::Button("View Scene 3"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[3] == 1)
			{
				currentlyViewingScene = 3;
				GameObjectManager::getInstance()->viewSceneMeshes(3);
			}
			else
			{
				//show bigger loading bar
			}
		}
	}

	if (GameObjectManager::getInstance()->SceneLoadingRatio[3] == 1)
	{
		if (ImGui::Button("Unload Scene 3"))
		{
			while (GameObjectManager::getInstance()->scene3MeshList.size() != 0)
			{
				GameObjectManager::getInstance()->unloadSceneMeshes(3);
			}
			currentlyViewingScene = 0;
		}
	}
	else
	{
		ImGui::Text("");
	}

	ImGui::Separator();

	ImGui::Text("Scene 4");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[4]);

	if (currentlyViewingScene != 4)
	{
		if (ImGui::Button("View Scene 4"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[4] == 1)
			{
				currentlyViewingScene = 4;
				GameObjectManager::getInstance()->viewSceneMeshes(4);
			}
			else
			{
				//show bigger loading bar
			}
		}
	}

	if (GameObjectManager::getInstance()->SceneLoadingRatio[4] == 1)
	{
		if (ImGui::Button("Unload Scene 4"))
		{
			while (GameObjectManager::getInstance()->scene4MeshList.size() != 0)
			{
				GameObjectManager::getInstance()->unloadSceneMeshes(4);
			}
			currentlyViewingScene = 0;
		}
	}
	else
	{
		ImGui::Text("");
	}

	ImGui::Separator();

	ImGui::Text("Scene 5");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[5]);

	if (currentlyViewingScene != 5)
	{
		if (ImGui::Button("View Scene 5"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[5] == 1)
			{
				currentlyViewingScene = 5;
				GameObjectManager::getInstance()->viewSceneMeshes(5);
			}
			else
			{
				//show bigger loading bar
			}
		}
	}

	if (GameObjectManager::getInstance()->SceneLoadingRatio[5] == 1)
	{
		if (ImGui::Button("Unload Scene 5"))
		{
			while (GameObjectManager::getInstance()->scene5MeshList.size() != 0)
			{
				GameObjectManager::getInstance()->unloadSceneMeshes(5);
			}
			currentlyViewingScene = 0;
		}
	}
	else
	{
		ImGui::Text("");
	}
	

	ImGui::Separator();

	if (currentlyViewingScene != 6)
	{

		if (ImGui::Button("View All Scenes"))
		{
			currentlyViewingScene = 6;
		}
	}

	ImGui::End();
}