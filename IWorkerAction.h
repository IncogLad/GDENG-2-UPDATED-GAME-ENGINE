#pragma once
#include "IETThread.h"
#include "Semaphore.h"

class IWorkerAction 
{
public:
	virtual void onStartTask() = 0;
	Semaphore* sceneMutex;
};

