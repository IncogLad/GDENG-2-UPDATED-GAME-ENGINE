#pragma once
#include "AComponent.h"
#include "Vector3D.h"
#include "reactphysics3d/reactphysics3d.h"

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(String name, AGameObject* owner);
	~PhysicsComponent();

	void perform(float deltaTime) override;
	RigidBody* getRigidBody();
	BodyType getBodyType();
	void setBodyType(BodyType type);

	void setTransform(Vector3 position, Vector3 rotation);
	void setTransform(Transform transform);

	void updateBoxShape(Vector3D scale);

private:
	float mass = 1000.0f;
	RigidBody* rigid_body_;
	Collider* tempCollider;

	BoxShape* box_shape;
	BodyType bodyType;

	Transform transform;

	PhysicsCommon* physics_common;
	PhysicsWorld* physics_world;
};

