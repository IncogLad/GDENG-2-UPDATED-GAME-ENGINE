#pragma once
#include <iostream>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "AGameObject.h"

class EditorAction
{
public:
	typedef std::string String;

	EditorAction(AGameObject* gameObject);
	~EditorAction();

	String getOwnerName();
	Vector3D getStorePos();
	Vector3D getStoredRotation();
	Vector3D getStoredScale();
	Matrix4x4 getStoredMatrix();

private:
	String objectName;
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;
	Matrix4x4 localMatrix;
};
