#include "BaseComponentSystem.h"

#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::getInstance()
{
	return sharedInstance;
}

void BaseComponentSystem::initialize()
{
	sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::destroy()
{
	delete sharedInstance;
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
	return this->physics_system_;
}

BaseComponentSystem::BaseComponentSystem()
{
	physics_system_ = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
}
