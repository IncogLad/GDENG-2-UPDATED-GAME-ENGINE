#pragma once
#include "AUIScreen.h"

class GDPARCMScreen : public AUIScreen
{
public:
	typedef std::string String;

	GDPARCMScreen();
	~GDPARCMScreen();

	void drawUI() override;

private:

	int currentlyViewingScene = 0;
};