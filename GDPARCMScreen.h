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

	bool is_loading_bar_visible;
	int scene_number;

	int total_numerator;
	int total_denominator;

	bool view_allClicked = false;
};