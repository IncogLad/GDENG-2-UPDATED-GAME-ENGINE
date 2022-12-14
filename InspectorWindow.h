#pragma once
#include "AGameObject.h"
#include "AUIScreen.h"

class InspectorWindow : public AUIScreen
{
public:
	enum ObjectType { cube = 0, mesh = 1 };
	typedef std::string String;
	InspectorWindow();
	~InspectorWindow();

	AGameObject* getSelectedObject();

	void drawUI() override;

private:
	bool hasObjectSelected;

	ObjectType objectType;
	bool enableCheckBox = true;
	bool disableCheckBox = false;

	bool isDynamic = false;
	bool isKinematic = false;
	bool isStatic = false;

	AGameObject* SelectedObject;

	friend class SceneEditor;
};

