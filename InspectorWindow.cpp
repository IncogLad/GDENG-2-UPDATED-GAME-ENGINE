#include "InspectorWindow.h"

#include "GameObjectManager.h"
#include "PhysicsComponent.h"
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
    static float position[4];
    static float scale[4];
    static float rotation[4];

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
        position[0] = SelectedObject->getLocalPosition().m_x;
        position[1] = SelectedObject->getLocalPosition().m_y;
        position[2] = SelectedObject->getLocalPosition().m_z;
        position[3] = 1.f;

        scale[0] = SelectedObject->getLocalScale().m_x;
        scale[1] = SelectedObject->getLocalScale().m_y;
        scale[2] = SelectedObject->getLocalScale().m_z;
        scale[3] = 1.f;

        rotation[0] = SelectedObject->getLocalRotation().m_x;
        rotation[1] = SelectedObject->getLocalRotation().m_y;
        rotation[2] = SelectedObject->getLocalRotation().m_z;
        rotation[3] = 1.f;
        

        if (ImGui::DragFloat3("Position", position))
        {
            SelectedObject->setPosition(position[0], position[1], position[2]);
        }
        if (ImGui::DragFloat3("Scale", scale))
        {
	        SelectedObject->setScale(scale[0], scale[1], scale[2]);
        }
		if(ImGui::DragFloat3("Rotation", rotation))
        {
            SelectedObject->setRotation(rotation[0], rotation[1], rotation[2]);
        }

        ImGui::Separator();

        ImGui::Text("Component");
        if (ImGui::Button("Add Physics Component"))
        {
            PhysicsComponent* physics_component =  new PhysicsComponent(SelectedObject->getName(),SelectedObject);
	        
        }

    }
    
    ImGui::End();

}
