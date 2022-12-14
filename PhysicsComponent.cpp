#include "PhysicsComponent.h"
#include "PhysicsComponent.h"

#include "AComponent.h"
#include "AGameObject.h"
#include "BaseComponentSystem.h"
#include "EngineBackend.h"
#include "PhysicsSystem.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, AComponent::ComponentType::Physics, owner)
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	physics_common = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	physics_world = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	Vector3D scale = this->getOwner()->getLocalScale();
	Vector3D position = this->getOwner()->getLocalPosition();
	Vector3D rotation = this->getOwner()->getLocalRotation();

	//TODO: Find out what is getPhysicsObject in AGameObject
	Transform initTransform; //transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
	initTransform.setPosition(Vector3(position.m_x, position.m_y, position.m_z));
	
	initTransform.setOrientation(Quaternion::fromEulerAngles(Vector3(rotation.m_x, rotation.m_y, rotation.m_z)));
	this->transform = initTransform;

	if (owner->getTag() == "cube")
		box_shape = physics_common->createBoxShape(Vector3(scale.m_x *2, scale.m_y, scale.m_z *2));
	if (owner->getTag() == "plane")
		box_shape = physics_common->createBoxShape(Vector3(scale.m_x * 10, scale.m_y/10, scale.m_z * 10));
	
	this->rigid_body_ = physics_world->createRigidBody(transform);
	this->tempCollider = this->rigid_body_->addCollider(box_shape, transform);
	this->rigid_body_->updateMassPropertiesFromColliders();
	this->rigid_body_->setMass(mass);
	this->rigid_body_->setType(BodyType::DYNAMIC);

	transform = this->rigid_body_->getTransform();
	//Matrix4x4 matrix;
	//transform.getOpenGLMatrix(*matrix.m_mat);
	
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
	
	if (EngineBackend::getInstance()->getMode() == EngineBackend::PLAY || EngineBackend::getInstance()->getMode() == EngineBackend::PAUSED) {
		transform = rigid_body_->getTransform();
		
		this->getOwner()->setRotation(Vector3D(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z));
		this->getOwner()->setPosition(Vector3D(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z));

	}

	
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return rigid_body_;
}

BodyType PhysicsComponent::getBodyType()
{
	return bodyType;
}

void PhysicsComponent::setBodyType(BodyType type)
{
	rigid_body_->setType( type);

}

void PhysicsComponent::setTransform(Vector3 position, Vector3 rotation)
{
	this->transform.setPosition(position);
	this->transform.setOrientation(Quaternion::fromEulerAngles(rotation));
}

void PhysicsComponent::setTransform(Transform transform)
{
	this->transform = transform;
}

