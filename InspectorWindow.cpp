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

        enableCheckBox = SelectedObject->getActive();
        disableCheckBox = !SelectedObject->getActive();

        ImGui::Text("Object Status");
        if (ImGui::Checkbox("Enable", &enableCheckBox))
        {
            SelectedObject->setActive(true);

            enableCheckBox = SelectedObject->getActive();
            disableCheckBox = !SelectedObject->getActive();
        }

        ImGui::SameLine();

        if (ImGui::Checkbox("Disable", &disableCheckBox))
        {
            SelectedObject->setActive(false);

            enableCheckBox = SelectedObject->getActive();
            disableCheckBox = !SelectedObject->getActive();
        }

        ImGui::Text("");

        if (ImGui::Button("Delete Object"))
        {
            GameObjectManager::getInstance()->deleteObject(SelectedObject);
            SelectedObject = nullptr;
        }

        ImGui::Separator();

        if (SelectedObject != nullptr)
        {
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
                if (enableCheckBox)
                {
                    ActionHistory::getInstance()->recordAction(this->SelectedObject);
                    SelectedObject->setPosition(position[0], position[1], position[2]);
                }
            }
            if (ImGui::DragFloat3("Scale", scale))
            {
                if (enableCheckBox)
                {
                    ActionHistory::getInstance()->recordAction(this->SelectedObject);
                    SelectedObject->setScale(scale[0], scale[1], scale[2]);
                }
            }
            if (ImGui::DragFloat3("Rotation", rotation))
            {
                if (enableCheckBox)
                {
                    ActionHistory::getInstance()->recordAction(this->SelectedObject);
                    SelectedObject->setRotation(rotation[0], rotation[1], rotation[2]);
                }
            }

            ImGui::Separator();

            ImGui::Text("Components");
            if (SelectedObject->getComponentsOfType(AComponent::Physics).empty())
            {
                if (ImGui::Button("Add Physics Component"))
                {
                    if (enableCheckBox)
                    {
                        PhysicsComponent* physics_component = new PhysicsComponent(SelectedObject->getName(), SelectedObject);
                        SelectedObject->attachComponent(physics_component);
                    }
                }
            }
            else
            {
                ImGui::Text("Rigidbody Types");
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
                    physics_component->setBodyType(BodyType::DYNAMIC);
                }
                if (ImGui::Checkbox("Static", &isStatic))
                {
                    isDynamic = false;
                    isStatic = true;
                    isKinematic = false;

                    physics_component->setBodyType(BodyType::STATIC);
                }
                if (ImGui::Checkbox("Kinematic", &isKinematic))
                {
                    isDynamic = false;
                    isStatic = false;
                    isKinematic = true;

                    physics_component->setBodyType(BodyType::KINEMATIC);
                }
            }
            ImGui::Separator();
            if (!SelectedObject->getTextureStatus()) {
                if (ImGui::Button("Add Texture Component"))
                {
                    if (enableCheckBox)
                    {
                        SelectedObject->setTextureStatus(true);
                    }
                }
            }
            else
            {
                ImGui::Text("Texture Types");
                brickCheckBox = false;
                wallCheckBox = false;
                woodCheckBox = false;
                grassCheckBox = false;
                asteroidCheckBox = false;
                sandCheckBox = false;

                if (textureName == "brick")brickCheckBox = true;
                if (textureName == "wall")wallCheckBox = true;
                if (textureName == "wood")woodCheckBox = true;
                if (textureName == "grass")grassCheckBox = true;
                if (textureName == "asteroid")asteroidCheckBox = true;
                if (textureName == "sand")sandCheckBox = true;

                if (ImGui::Checkbox("Set Brick Texture", &brickCheckBox))
                {
                    brickCheckBox = true;
                    textureName = "brick";
                    this->SelectedObject->setDedicatedTexture(textureName);
                }
                if (ImGui::Checkbox("Set Grass Texture", &grassCheckBox))
                {
                    grassCheckBox = true;
                    textureName = "grass";
                    this->SelectedObject->setDedicatedTexture(textureName);
                }
                if (ImGui::Checkbox("Set Wood Texture", &woodCheckBox))
                {
                    woodCheckBox = true;
                    textureName = "wood";
                    this->SelectedObject->setDedicatedTexture(textureName);
                }
                if (ImGui::Checkbox("Set Wall Texture", &wallCheckBox))
                {
                    wallCheckBox = true;
                    textureName = "wall";
                    this->SelectedObject->setDedicatedTexture(textureName);
                }
                if (ImGui::Checkbox("Set Asteroid Texture", &asteroidCheckBox))
                {
                    asteroidCheckBox = true;
                    textureName = "asteroid";
                    this->SelectedObject->setDedicatedTexture(textureName);
                }
                if (ImGui::Checkbox("Set Sand Texture", &sandCheckBox))
                {
                    sandCheckBox = true;
                    textureName = "sand";
                    this->SelectedObject->setDedicatedTexture(textureName);
                }
            }
        }
        //physics_component->getRigidBody()->setType(BodyType::DYNAMIC);
    }
    
    ImGui::End();

}

