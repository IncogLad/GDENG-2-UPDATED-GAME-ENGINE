#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace reactphysics3d;
class PhysicsComponent;

class PhysicsSystem
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
	typedef std::vector<PhysicsComponent*> ComponentList;



	PhysicsSystem();
	~PhysicsSystem();

	void registerComponent(PhysicsComponent* component);
	void unregisterComponent(PhysicsComponent* component);
	void unregisterComponentByName(String name);
	PhysicsComponent* findComponentByName(String name);
	ComponentList getAllComponents();

	void updateAllComponents();
	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

private:
	ComponentTable component_table_;
	ComponentList component_list_;

	PhysicsCommon* physics_common_;
	PhysicsWorld* physics_world_;

};

