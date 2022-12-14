#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
	this->objectName = gameObject->getName();
	this->localPosition = gameObject->getLocalPosition();
	this->localRotation = gameObject->getLocalRotation();
	this->localScale = gameObject->getLocalScale();
	this->localMatrix = gameObject->getLocalMatrix();
}

EditorAction::~EditorAction()
{
}

AGameObject::String EditorAction::getOwnerName()
{
	return objectName;
}

Vector3D EditorAction::getStorePos()
{
	return localPosition;
}

Vector3D EditorAction::getStoredRotation()
{
	return localRotation;
}

Vector3D EditorAction::getStoredScale()
{
	return localScale;
}

Matrix4x4 EditorAction::getStoredMatrix()
{
	return localMatrix;
}
