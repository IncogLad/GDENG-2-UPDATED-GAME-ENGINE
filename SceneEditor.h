#pragma once
#include <list>

#include "AGameObject.h"
#include "AUIScreen.h"
class InspectorWindow;

class GameObjectManager;

class SceneEditor : public AUIScreen
{
public:
	typedef std::string String;
	SceneEditor();
	~SceneEditor();

	void drawUI() override;
	void updateObjectList(std::list<AGameObject*> objList);

private:
	std::list<String> ObjectList;

private:
	friend class InspectorWindow;
};

