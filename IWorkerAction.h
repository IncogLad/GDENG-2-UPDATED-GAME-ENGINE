#pragma once
#include "IETThread.h"

class IWorkerAction 
{
public:
	virtual void onStartTask() = 0;
};

