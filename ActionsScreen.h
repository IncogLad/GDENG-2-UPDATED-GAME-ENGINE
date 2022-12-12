#pragma once
#include "AUIScreen.h"

class ActionsScreen : public AUIScreen
{
public:
	typedef std::string String;
	ActionsScreen();
	~ActionsScreen();

	void drawUI() override;
};
