#include "AUIScreen.h"

AUIScreen::AUIScreen(String name)
{
	this->name = name;
}

AUIScreen::~AUIScreen()
{
}

AUIScreen::String AUIScreen::getName()
{
	return this->name;
}
