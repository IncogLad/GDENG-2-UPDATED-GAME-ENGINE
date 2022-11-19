#include "PhysicsSystem.h"

#include "EngineTime.h"
#include "PhysicsComponent.h"

PhysicsSystem::PhysicsSystem()
{
	this->physics_common_ = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);
	this->physics_world_ = this->physics_common_->createPhysicsWorld(settings);
	
}

PhysicsSystem::~PhysicsSystem()
{
	delete this->physics_common_;
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	this->component_table_[component->getName()] = component;
	this->component_list_.push_back(component);
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
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
		std::cout << "Component " << component->getName() << " not registered in physics component" << std::endl;
	}
}

void PhysicsSystem::unregisterComponentByName(String name)
{
	if (this->component_table_[name] != NULL)
	{
		this->component_table_.erase(name);
		int index = -1;
		for (int i = 0; i < this->component_list_.size(); i++)
		{
			if (this->component_list_[i]->getName() == name)
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
		std::cout << "Component " << name << " not registered in physics component" << std::endl;
	}
}

PhysicsComponent* PhysicsSystem::findComponentByName(String name)
{
	return component_table_[name];
}

PhysicsSystem::ComponentList PhysicsSystem::getAllComponents()
{
	return component_list_;
}

void PhysicsSystem::updateAllComponents()
{
	if (EngineTime::getDeltaTime() > 0.0f)
	{
		this->physics_world_->update(EngineTime::getDeltaTime());
		for (int i = 0; i <  this->component_list_.size(); i++)
		{
			this->component_list_[i]->perform(EngineTime::getDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return physics_world_;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return physics_common_;
}
