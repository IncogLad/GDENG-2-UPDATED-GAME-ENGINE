#include "SceneEditor.h"

#include "GameObjectManager.h"
#include "InspectorWindow.h"
#include "UISystem.h"
#include "imgui/imgui.h"

SceneEditor::SceneEditor() : AUIScreen("SCENE_EDITOR")
{
   
}

SceneEditor::~SceneEditor()
{
}

void SceneEditor::drawUI()
{
    updateObjectList(GameObjectManager::getInstance()->getGameObjectList());

    ImGui::Begin("Scene Editor");
    int index = 0;
    for (String object : ObjectList)
    {
        const char* cc = object.c_str();
        if (ImGui::Button(cc))
        {
	        for (auto i : GameObjectManager::getInstance()->getGameObjectList())
	        {
                i->setSelected(false);
	        }
            GameObjectManager::getInstance()->getGameObjectTable()[object]->setSelected(true);
            
        }
    }

    ImGui::End();
}

void SceneEditor::updateObjectList(std::list<AGameObject*> objList)
{
    if (!this->ObjectList.empty())
		this->ObjectList.clear();
    for (auto const& i : GameObjectManager::getInstance()->getGameObjectList()) {
        this->ObjectList.push_back(i->getName());
    }

}



