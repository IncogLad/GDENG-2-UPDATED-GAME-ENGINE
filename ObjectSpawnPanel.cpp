#include "ObjectSpawnPanel.h"

#include "GameObjectManager.h"
#include "imgui/imgui.h"

ObjectSpawnPanel::ObjectSpawnPanel() :AUIScreen("OBJECT_SPAWN_PANEL")
{
    open = false;
}

ObjectSpawnPanel::~ObjectSpawnPanel()
{
}

void ObjectSpawnPanel::drawUI()
{
    if (open) {
        ImGui::Begin("Object Spawner");
        

        if (ImGui::Checkbox("Cube", &cubeCheckBox))
        {
            objectType = cube;
            cubeCheckBox = true;
            planeCheckBox = false;
            sphereCheckBox = false;
            capsuleCheckBox = false;
        }
        else if (ImGui::Checkbox("Plane", &planeCheckBox))
        {
            objectType = plane;
            cubeCheckBox = false;
            planeCheckBox = true;
            sphereCheckBox = false;
            capsuleCheckBox = false;
        }
        else if (ImGui::Checkbox("Sphere", &sphereCheckBox))
        {
            objectType = sphere;
            cubeCheckBox = false;
            planeCheckBox = false;
            sphereCheckBox = true;
            capsuleCheckBox = false;
        }
        else if (ImGui::Checkbox("Capsule", &capsuleCheckBox))
        {
            objectType = capsule;
            cubeCheckBox = false;
            planeCheckBox = false;
            sphereCheckBox = false;
            capsuleCheckBox = true;
        }

        ImGui::InputInt("Object Count:", &objectCount);

        if (ImGui::Button("Spawn"))
        {
            if (cubeCheckBox)
            {
                
                
	            for (int i = 0; i < objectCount; i++)
	            {
                    ObjectName = "cube";
                    ObjectName = ObjectName + std::to_string(latestCubeCount);
                    GameObjectManager::getInstance()->initializeCube(ObjectName, 0);

                    latestCubeCount++;
	            }
            }
            else if (planeCheckBox)
            {
                
                for (int i = 0; i < objectCount; i++)
                {
                    ObjectName = "plane";
                    ObjectName = ObjectName + std::to_string(latestPlaneCount);
                    GameObjectManager::getInstance()->initializeCube(ObjectName, 1);
                    latestPlaneCount++;
                }
            }
            else if (sphereCheckBox)
            {
                
                for (int i = 0; i < objectCount; i++)
                {
                    ObjectName = "sphere";
                    ObjectName = ObjectName + std::to_string(latestSphereCount);

                    GameObjectManager::getInstance()->initializeSphere(ObjectName);

                    latestSphereCount++;
                }
            }
            else if (capsuleCheckBox)
            {
                for (int i = 0; i < objectCount; i++)
                {

                    ObjectName = "capsule";
                    ObjectName = ObjectName + std::to_string(latestCapsuleCount);

                    GameObjectManager::getInstance()->initializeCapsule(ObjectName);

                    latestCapsuleCount++;
                }
            }

        	open = false;
        }
        
        ImGui::End();
    }
}
