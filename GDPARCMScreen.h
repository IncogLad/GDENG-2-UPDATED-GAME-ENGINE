#pragma once
#include <vector>

#include "AUIScreen.h"

class GDPARCMScreen : public AUIScreen
{
public:
	typedef std::string String;

	GDPARCMScreen();
	~GDPARCMScreen();

	void drawUI() override;

private:
	std::vector<bool> currentViewingScene = std::vector<bool>(6);
};