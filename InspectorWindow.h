#pragma once
#include "AGameObject.h"
#include "AUIScreen.h"

class InspectorWindow : public AUIScreen
{
public:
	typedef std::string String;
	InspectorWindow();
	~InspectorWindow();

	AGameObject* getSelectedObject();

	void drawUI() override;

private:
	bool hasObjectSelected;
	
	AGameObject* SelectedObject;

	friend class SceneEditor;
};

