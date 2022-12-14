#include "InspectorWindow.h"

#include "GameObjectManager.h"
#include "PhysicsComponent.h"
#include "imgui/imgui.h"
#include "ActionHistory.h"

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

        ImGui::Text("Enable/Disable Object");
        if (ImGui::Checkbox("Yes", &enableCheckBox))
        {
            if (SelectedObject->getTag() == "cube")
            {
	            objectType = cube;
            }
            else if (SelectedObject->getTag() == "sphere" || SelectedObject->getTag() == "capsule")
            {
	            objectType = mesh;
            }

            enableCheckBox = true;
            disableCheckBox = false;

            if (objectType == cube)
            {
	            GameObjectManager::getInstance()->enableCubes(SelectedObject->getName());
            }
            else
            {
	            GameObjectManager::getInstance()->enableMeshes(SelectedObject->getName());
            }
        }
    	else if (ImGui::Checkbox("No", &disableCheckBox))
        {
            if (SelectedObject->getTag() == "cube")
            {
	            objectType = cube;
            }
            else if (SelectedObject->getTag() == "sphere" || SelectedObject->getTag() == "capsule")
            {
	            objectType = mesh;

            }

            enableCheckBox = false;
            disableCheckBox = true;

            if (objectType == cube)
            {
	            GameObjectManager::getInstance()->disableCubes(SelectedObject->getName());
            }
            else
            {
	            GameObjectManager::getInstance()->disableMesh(SelectedObject->getName());
            }
            std::cout << SelectedObject << std::endl;
        }

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
        	ActionHistory::getInstance()->recordAction(this->SelectedObject);
        	SelectedObject->setPosition(position[0], position[1], position[2]);
        }
        if (ImGui::DragFloat3("Scale", scale))
        {
            ActionHistory::getInstance()->recordAction(this->SelectedObject);
	        SelectedObject->setScale(scale[0], scale[1], scale[2]);
        }
		if(ImGui::DragFloat3("Rotation", rotation))
        {
            ActionHistory::getInstance()->recordAction(this->SelectedObject);
            SelectedObject->setRotation(rotation[0], rotation[1], rotation[2]);
        }

        ImGui::Separator();

        ImGui::Text("Component");
        if (SelectedObject->getComponentsOfType(AComponent::Physics).empty())
        {
            if (ImGui::Button("Add Physics Component"))
            {

                PhysicsComponent* physics_component = new PhysicsComponent(SelectedObject->getName(), SelectedObject);
                SelectedObject->attachComponent(physics_component);

            }
        }
        else
        {
            PhysicsComponent* physics_component = static_cast<PhysicsComponent*>(SelectedObject->findComponentByType(AComponent::Physics, SelectedObject->getName()));
            if (physics_component->getRigidBody()->getType() == BodyType::DYNAMIC)
            {
                isDynamic = true;
                isStatic = false;
                isKinematic = false;
            }
            if (physics_component->getRigidBody()->getType() == BodyType::STATIC)
            {
                isDynamic = false;
                isStatic = true;
                isKinematic = false;
            }
            if (physics_component->getRigidBody()->getType() == BodyType::KINEMATIC)
            {
                isDynamic = false;
                isStatic = false;
                isKinematic = true;
            }
            
            if (ImGui::Checkbox("Dynamic", &isDynamic))
            {
                isDynamic = true;
                isStatic = false;
                isKinematic = false;
                physics_component->getRigidBody()->setType(BodyType::DYNAMIC);
            }
            if (ImGui::Checkbox("Static", &isStatic))
            {
                isDynamic = false;
                isStatic = true;
                isKinematic = false;

                physics_component->getRigidBody()->setType(BodyType::STATIC);
            }
            if (ImGui::Checkbox("Kinematic", &isKinematic))
            {
                isDynamic = false;
                isStatic = false;
                isKinematic = true;

                physics_component->getRigidBody()->setType(BodyType::KINEMATIC);
            }
        }
        
        //physics_component->getRigidBody()->setType(BodyType::DYNAMIC);
    }
    
    ImGui::End();

}

