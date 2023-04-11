#pragma once

#include <string>
#include "IExecutionEvent.h"
#include "IWorkerAction.h"

class IWorkerAction;

class LoadingWorkerAction :public IWorkerAction
{
public:
	LoadingWorkerAction(std::string, IExecutionEvent*);
	~LoadingWorkerAction();

	void onStartTask() override;


private:
	std::string path;
	IExecutionEvent* execution_event_;

};

