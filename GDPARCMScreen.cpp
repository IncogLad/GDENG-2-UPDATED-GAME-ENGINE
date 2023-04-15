#include "GDPARCMScreen.h"
#include "EngineTime.h"
#include "imgui/imgui.h"
#include "GameObjectManager.h"
#include <ctime>

GDPARCMScreen::GDPARCMScreen() : AUIScreen("GDPARCM_SCREEN")
{
	for (bool status : currentViewingScene)
	{
		status = false;
	}

	this->is_loading_bar_visible = false;
	this->scene_number = 0;
}

GDPARCMScreen::~GDPARCMScreen()
{
}

void GDPARCMScreen::drawUI()
{
	ImGui::Begin("GDPARCM Scene Loading Controls", 0);

	double fps = (1.0 / EngineTime::getDeltaTime());
	if (fps > 60.0)
		fps = 60.0;

	ImGui::Text("FPS: %f", fps);

	ImGui::Separator();

#pragma region Scene 1
	ImGui::Text("Scene 1");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[1]);
	
	if (!currentViewingScene[1])
	{
		if (ImGui::Button("View Scene 1"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[1] == 1)
			{
				currentViewingScene[1] = true;
				GameObjectManager::getInstance()->viewSceneMeshes(1);
				this->is_loading_bar_visible = false;
			}
			else
			{
				if (GameObjectManager::getInstance()->SceneIsLoading[1])
				{
					//show bigger loading bar
					this->is_loading_bar_visible = true;
					this->scene_number = 1;
				}
				else
				{
					GameObjectManager::getInstance()->LoadSceneMeshes(1, true);
					currentViewingScene[1] = true;
					this->is_loading_bar_visible = true;
					this->scene_number = 1;
				}
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
			currentViewingScene[1] = false;
		}
	}
	else 
	{
		ImGui::Text("");
	}
#pragma endregion

	ImGui::Separator();

#pragma region Scene 2
	ImGui::Text("Scene 2");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[2]);
	
	if (!currentViewingScene[2])
	{
		if (ImGui::Button("View Scene 2"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[2] == 1)
			{
				currentViewingScene[2] = true;
				GameObjectManager::getInstance()->viewSceneMeshes(2);
				this->is_loading_bar_visible = false;
			}
			else
			{
				if (GameObjectManager::getInstance()->SceneIsLoading[2])
				{
					//show bigger loading bar
					this->is_loading_bar_visible = true;
					this->scene_number = 2;
				}
				else
				{
					GameObjectManager::getInstance()->LoadSceneMeshes(2, true);
					currentViewingScene[2] = true;
					this->is_loading_bar_visible = true;
					this->scene_number = 2;
				}
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
			currentViewingScene[2] = false;
		}
	}
	else
	{
		ImGui::Text("");
	}
#pragma endregion

	ImGui::Separator();

#pragma region Scene 3
	ImGui::Text("Scene 3");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[3]);

	if (!currentViewingScene[3])
	{
		if (ImGui::Button("View Scene 3"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[3] == 1)
			{
				currentViewingScene[3] = true;
				GameObjectManager::getInstance()->viewSceneMeshes(3);
				this->is_loading_bar_visible = false;
			}
			else
			{
				if (GameObjectManager::getInstance()->SceneIsLoading[3])
				{
					//show bigger loading bar
					this->is_loading_bar_visible = true;
					this->scene_number = 3;
				}
				else
				{
					GameObjectManager::getInstance()->LoadSceneMeshes(3, true);
					currentViewingScene[3] = true;
					this->is_loading_bar_visible = true;
					this->scene_number = 3;
				}
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
			currentViewingScene[3] = false;
		}
	}
	else
	{
		ImGui::Text("");
	}
#pragma endregion

	ImGui::Separator();

#pragma region Scene 4
	ImGui::Text("Scene 4");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[4]);

	if (!currentViewingScene[4])
	{
		if (ImGui::Button("View Scene 4"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[4] == 1)
			{
				currentViewingScene[4] = true;
				GameObjectManager::getInstance()->viewSceneMeshes(4);
				this->is_loading_bar_visible = false;
			}
			else
			{
				if (GameObjectManager::getInstance()->SceneIsLoading[4])
				{
					//show bigger loading bar
					this->is_loading_bar_visible = true;
					this->scene_number = 4;
				}
				else
				{
					GameObjectManager::getInstance()->LoadSceneMeshes(4, true);
					currentViewingScene[4] = true;
					this->is_loading_bar_visible = true;
					this->scene_number = 4;
				}
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
			currentViewingScene[4] = false;
		}
	}
	else
	{
		ImGui::Text("");
	}
#pragma endregion

	ImGui::Separator();

#pragma region Scene 5
	ImGui::Text("Scene 5");
	ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[5]);

	if (!currentViewingScene[5])
	{
		if (ImGui::Button("View Scene 5"))
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[5] == 1)
			{
				currentViewingScene[5] = true;
				GameObjectManager::getInstance()->viewSceneMeshes(5);
				this->is_loading_bar_visible = false;
			}
			else
			{
				if (GameObjectManager::getInstance()->SceneIsLoading[5])
				{
					//show bigger loading bar
					this->is_loading_bar_visible = true;
					this->scene_number = 5;
				}
				else
				{
					GameObjectManager::getInstance()->LoadSceneMeshes(5, true);
					currentViewingScene[5] = true;
					this->is_loading_bar_visible = true;
					this->scene_number = 5;
				}
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
			currentViewingScene[5] = false;
		}
	}
	else
	{
		ImGui::Text("");
	}
#pragma endregion

	ImGui::Separator();

	if (ImGui::Button("View All Scenes"))
	{
		view_allClicked = true;
		for (int i = 1; i < 6; i++)
		{
			if (GameObjectManager::getInstance()->SceneLoadingRatio[i] == 1)
			{
				if (currentViewingScene[i])
				{
					this->is_loading_bar_visible = false;
				}
				else
				{
					GameObjectManager::getInstance()->viewSceneMeshes(i);
					currentViewingScene[i] = true;
					this->is_loading_bar_visible = false;
				}
			}
			else
			{
				GameObjectManager::getInstance()->LoadSceneMeshesLocked(i, true);
				GameObjectManager::getInstance()->updateLoadingStatus(i, true);
				currentViewingScene[i] = true;
				
			}
		}

		if (GameObjectManager::getInstance()->SceneIsLoading[1] || GameObjectManager::getInstance()->SceneIsLoading[2] || GameObjectManager::getInstance()->SceneIsLoading[3]
			|| GameObjectManager::getInstance()->SceneIsLoading[4] || GameObjectManager::getInstance()->SceneIsLoading[5])
		{
			//show big loading bar with (currently loaded items/ total items)
			this->is_loading_bar_visible = true;
			this->scene_number = 0;
		}
	}

	for (int i = 1; i < 6; i++)
	{
		if (GameObjectManager::getInstance()->SceneLoadingRatio[i] == 1)
		{
			GameObjectManager::getInstance()->updateLoadingStatus(i, false);
		}
	}


	if (this->is_loading_bar_visible)
	{
		std::cout << this->scene_number << std::endl;
		if (scene_number == 0)
		{
			GameObjectManager::getInstance()->updateAllSceneLoadingBar();
		}

		if (this->scene_number >= 0 && this->scene_number <= 5)
		{
			if (!ImGui::Begin("Loading Bar", &this->is_loading_bar_visible), ImGuiWindowFlags_NoResize)
			{
				ImGui::SetWindowSize(ImVec2(700, 55));
				ImGui::ProgressBar(GameObjectManager::getInstance()->SceneLoadingRatio[this->scene_number]);
				ImGui::End();
			}
			else
			{
				ImGui::End();
			}
		}
		

		if (GameObjectManager::getInstance()->SceneLoadingRatio[this->scene_number] == 1)
		{
			this->is_loading_bar_visible = false;
		}
		
	}

	ImGui::End();
}