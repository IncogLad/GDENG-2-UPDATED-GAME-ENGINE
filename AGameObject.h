#pragma once
#include <string>
#include <unordered_map>
#include <reactphysics3d/decimal.h>

#include "AComponent.h"
#include "Matrix4x4.h"
#include "Vector3D.h"


struct vertex
{
	Vector3D position;
	Vector3D color;
};

struct vertexAnim
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

struct vertexCube
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};


__declspec(align(16)) struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

class AComponent;
class EditorAction;

class AGameObject
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, AComponent*> ComponentTable;
	typedef std::vector<AComponent*> ComponentList;

	virtual void initialize(std::string name);
	virtual void destroy();

	virtual void draw();

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	void setLocalMatrix(float* matrix);
	void setLocalMatrix(Matrix4x4 matrix);
	Matrix4x4 getLocalMatrix();
	reactphysics3d::decimal* getPhysicsLocalMatrix();

	std::string getName();
	bool isObjectSelected();
	void setSelected(bool value);

	void setTag(std::string tag);
	std::string getTag();

	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(String name);
	AComponent* findComponentByType(AComponent::ComponentType type, String name);
	ComponentList getComponentsOfType(AComponent::ComponentType type);
	ComponentList getComponentsOfTypeRecursive(AComponent::ComponentType type);

	void saveEditState();
	void restoreEditState();

	bool getActive();
	void setActive(bool isActive);

private:

protected:
	std::string name;
	std::string tag;
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;

	bool isSelected = false;
	bool isActive = true;

	Matrix4x4 localMatrix;
	reactphysics3d::decimal physicsLocalMatrix[4][4] = {};

	ComponentList component_list_;
	ComponentTable component_table_;

	EditorAction* lastEditState = nullptr;
};

