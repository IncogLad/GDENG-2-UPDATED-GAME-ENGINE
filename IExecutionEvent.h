#pragma once
#include "Mesh.h"

class IExecutionEvent
{
public:
	virtual void onFinishedExecution(int num, Mesh* mesh) = 0;

};

