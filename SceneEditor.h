#pragma once
#include <list>
#include "AUIScreen.h"

class SceneEditor : public AUIScreen
{
public:
	typedef std::string String;
	SceneEditor();
	~SceneEditor();

	void drawUI() override;

private:
	std::list<String> ObjectList;
	
};

