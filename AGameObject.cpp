#include "AGameObject.h"

#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "EditorAction.h"
#include "PhysicsComponent.h"
#include "reactphysics3d/reactphysics3d.h"

void AGameObject::initialize(std::string name)
{
	this->name = name;
	this->localRotation = Vector3D::zeros();
	this->localPosition = Vector3D::zeros();
	this->localScale = Vector3D::ones();
	this->localMatrix.setIdentity();
	//this->localMatrix.setTranslation(Vector3D(0, 0, -2));

	physicsLocalMatrix[0][0] = localMatrix.m_mat[0][0];
	physicsLocalMatrix[0][1] = localMatrix.m_mat[0][1];
	physicsLocalMatrix[0][2] = localMatrix.m_mat[0][2];
	physicsLocalMatrix[0][3] = localMatrix.m_mat[0][3];

	physicsLocalMatrix[1][0] = localMatrix.m_mat[1][0];
	physicsLocalMatrix[1][1] = localMatrix.m_mat[1][1];
	physicsLocalMatrix[1][2] = localMatrix.m_mat[1][2];
	physicsLocalMatrix[1][3] = localMatrix.m_mat[1][3];

	physicsLocalMatrix[2][0] = localMatrix.m_mat[2][0];
	physicsLocalMatrix[2][1] = localMatrix.m_mat[2][1];
	physicsLocalMatrix[2][2] = localMatrix.m_mat[2][2];
	physicsLocalMatrix[2][3] = localMatrix.m_mat[2][3];

	physicsLocalMatrix[3][0] = localMatrix.m_mat[3][0];
	physicsLocalMatrix[3][1] = localMatrix.m_mat[3][1];
	physicsLocalMatrix[3][2] = localMatrix.m_mat[3][2];
	physicsLocalMatrix[3][3] = localMatrix.m_mat[3][3];
}

void AGameObject::destroy()
{
	//this->localPosition = nullptr;
	//this->localRotation = nullptr;
	//this->localScale = nullptr;
	delete this;
}

void AGameObject::draw()
{

}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

void AGameObject::setLocalMatrix(float* matrix)
{
	localMatrix = matrix;
}

void AGameObject::setLocalMatrix(Matrix4x4 matrix)
{
	localMatrix = matrix;
}

Matrix4x4 AGameObject::getLocalMatrix()
{
	return this->localMatrix;
}

decimal* AGameObject::getPhysicsLocalMatrix()
{
	
	return *this->localMatrix.m_mat;
}


std::string AGameObject::getName()
{
	return this->name;
}

bool AGameObject::isObjectSelected()
{
	return this->isSelected;
}

void AGameObject::setSelected(bool value)
{
	isSelected = value;
}

void AGameObject::setTag(std::string tag)
{
	this->tag = tag;
}

std::string AGameObject::getTag()
{
	return this->tag;
}

void AGameObject::attachComponent(AComponent* component)
{
	component->attachOwner(this);
	component_list_.push_back(component);
	component_table_[component->getName()] = component;
	
}

void AGameObject::detachComponent(AComponent* component)
{
	component->detachOwner();

	if (this->component_table_[component->getName()] != NULL)
	{
		this->component_table_.erase(component->getName());
		int index = -1;
		for (int i = 0; i < this->component_list_.size(); i++)
		{
			if (this->component_list_[i] == component)
			{
				index = i;
				break;
			}
			if (index != -1)
			{
				this->component_list_.erase(this->component_list_.begin() + index);
			}
		}
	}
	else
	{
		std::cout << "Component " << component->getName() << " not attached in Game Object" << std::endl;
	}
}

AComponent* AGameObject::findComponentByName(String name)
{
	return component_table_[name];
}

AComponent* AGameObject::findComponentByType(AComponent::ComponentType type, String name)
{
	if (component_table_[name]->getType() == type)
	{
		return component_table_[name];
	}
	else
	{
		std::cout << "Component " << name << " does not have matching type" << std::endl;
		return nullptr;
	}
}

AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList component_list;
	for (int i = 0; i < component_list_.size(); i++)
	{
		if (component_list_[i]->getType() == type)
		{
			component_list.push_back(component_list_[i]);
		}
	}

	return component_list;
}

AGameObject::ComponentList AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	ComponentList component_list;
	for (int i = 0; i < component_list_.size(); i++)
	{
		if (component_list_[i]->getType() == type)
		{
			component_list.push_back(component_list_[i]);
		}
	}

	return component_list;
}

void AGameObject::saveEditState()
{
	if (this->lastEditState == nullptr)
	{
		this->lastEditState = new EditorAction(this);
	}
}

void AGameObject::restoreEditState()
{
	if (this->lastEditState != nullptr)
	{
		this->setPosition(lastEditState->getStorePos());
		this->setRotation(lastEditState->getStoredRotation());
		this->setScale(lastEditState->getStoredScale());
		this->setLocalMatrix(lastEditState->getStoredMatrix());

		this->lastEditState = nullptr;
	}
}

bool AGameObject::getActive()
{
	return this->isActive;
}

void AGameObject::setActive(bool isActive)
{
	this->isActive = isActive;
}
