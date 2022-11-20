#include "InspectorWindow.h"

#include "GameObjectManager.h"
#include "imgui/imgui.h"

InspectorWindow::InspectorWindow() : AUIScreen("INSPECTOR_WINDOW")
{
}

InspectorWindow::~InspectorWindow()
{
}

AGameObject* InspectorWindow::getSelectedObject()
{
    for (auto i : GameObjectManager::getInstance()->getGameObjectList())
    {
        if (i->isObjectSelected())
        {
            hasObjectSelected = true;
            return i;
        }

    }
    hasObjectSelected = false;
    return nullptr;
}

void InspectorWindow::drawUI()
{
    SelectedObject = getSelectedObject();

    ImGui::Begin("Inspector Window");
    if (!hasObjectSelected)
    {
        ImGui::Text("No Object Selected!");
        ImGui::TextWrapped("Please select an object in the Scene Editor.");
    }
    else
    {
        ImGui::Text(SelectedObject->getName().c_str());
        ImGui::Separator();

        ImGui::Text("Transform");
        
        static float position[4] = { SelectedObject->getLocalPosition().m_x, SelectedObject->getLocalPosition().m_y, SelectedObject->getLocalPosition().m_z, 1.0f };
        static float scale[4] = { SelectedObject->getLocalScale().m_x, SelectedObject->getLocalScale().m_y, SelectedObject->getLocalScale().m_z, 1.0f };
        static float rotation[4] = { SelectedObject->getLocalRotation().m_x, SelectedObject->getLocalRotation().m_y, SelectedObject->getLocalRotation().m_z, 1.0f };

        ImGui::DragFloat3("Position", position);
        ImGui::DragFloat3("Scale", scale);
        ImGui::DragFloat3("Rotation", rotation);

        SelectedObject->setPosition(position[0], position[1], position[2]);
        SelectedObject->setScale(scale[0], scale[1], scale[2]);
        SelectedObject->setRotation(rotation[0], rotation[1], rotation[2]);

    }
    
    ImGui::End();
}
