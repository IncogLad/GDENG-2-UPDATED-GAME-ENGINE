#pragma once
#include "AUIScreen.h"
class WireframeView :public AUIScreen
{
public:
	typedef std::string String;
	WireframeView();
	~WireframeView() override;


	void drawUI() override;
};

