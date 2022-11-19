#include "PhysicsComponent.h"
#include "PhysicsComponent.h"

#include "AComponent.h"
#include "AGameObject.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, AComponent::ComponentType::Physics, owner)
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physics_common = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physics_world = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	Vector3D scale = this->getOwner()->getLocalScale();
	Vector3D position = this->getOwner()->getLocalPosition();
	Vector3D rotation = this->getOwner()->getLocalRotation();

	//TODO: Find out what is getPhysicsObject in AGameObject
	Transform transform; //transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
	transform.setPosition(Vector3(position.m_x, position.m_y, position.m_z));
	
	transform.setOrientation(Quaternion::fromEulerAngles(Vector3(rotation.m_x, rotation.m_y, rotation.m_z)));

	BoxShape* box_shape = physics_common->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
	
	this->rigid_body_ = physics_world->createRigidBody(transform);
	this->rigid_body_->addCollider(box_shape, transform);
	this->rigid_body_->updateMassPropertiesFromColliders();
	this->rigid_body_->setMass(mass);
	this->rigid_body_->setType(BodyType::DYNAMIC);

	transform = this->rigid_body_->getTransform();
	Matrix4x4 matrix;
	transform.getOpenGLMatrix(*matrix.m_mat);
	
	/*for (int i : *matrix.m_mat)
	{
		std::cout << i << ". " << (float)*matrix.m_mat[i] << std::endl;
	}*/

	//this->getOwner()->setLocalMatrix(matrix);
	this->getOwner()->setRotation(Vector3D(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z));
	this->getOwner()->setPosition(Vector3D(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z));

}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigid_body_->getTransform();
	Matrix4x4 matrix;
	transform.getOpenGLMatrix(*matrix.m_mat);
	
	/*for (int i : *matrix.m_mat)
	{
		std::cout << i << ". " << (float)*matrix.m_mat[i] << std::endl;
	}*/

	//this->getOwner()->setLocalMatrix(matrix);
	this->getOwner()->setRotation(Vector3D(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z));
	this->getOwner()->setPosition(Vector3D(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z));
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return rigid_body_;
}
