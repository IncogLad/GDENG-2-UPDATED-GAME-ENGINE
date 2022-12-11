#pragma once
#include "AUIScreen.h"

class PlaybackScreen : public AUIScreen
{
public:
	typedef std::string String;
	PlaybackScreen();
	~PlaybackScreen();

	void drawUI() override;
};
