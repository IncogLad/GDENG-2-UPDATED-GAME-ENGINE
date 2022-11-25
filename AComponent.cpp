#include "AComponent.h"

AComponent::AComponent(String name, ComponentType type, AGameObject* owner)
{
	this->owner = owner;
	this->type = type;
	this->name = name;
}

AComponent::~AComponent()
{
}

void AComponent::attachOwner(AGameObject* owner)
{
	this->owner = owner;
}

void AComponent::detachOwner()
{
	this->owner = nullptr;
}

AGameObject* AComponent::getOwner()
{
	return owner;
}

AComponent::ComponentType AComponent::getType()
{
	return type;
}

AComponent::String AComponent::getName()
{
	return name;
}


