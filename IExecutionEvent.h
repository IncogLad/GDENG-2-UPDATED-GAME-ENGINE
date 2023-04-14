#pragma once

class IExecutionEvent
{
public:
	virtual void onFinishedExecution(int num) = 0;

};

