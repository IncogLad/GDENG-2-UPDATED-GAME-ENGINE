#pragma once
#include "AUIScreen.h"

class InspectorWindow : public AUIScreen
{
public:
	typedef std::string String;
	InspectorWindow();
	~InspectorWindow();

	void drawUI() override;
};

