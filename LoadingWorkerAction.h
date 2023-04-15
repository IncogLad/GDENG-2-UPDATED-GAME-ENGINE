#pragma once

#include <string>
#include "IExecutionEvent.h"
#include "IWorkerAction.h"

class IWorkerAction;

class LoadingWorkerAction :public IWorkerAction
{
public:
	LoadingWorkerAction(std::string, int sceneNum, IExecutionEvent*, bool viewImmediate = false);
	~LoadingWorkerAction();

	void onStartTask() override;


private:
	std::string name;
	int sceneNum;
	bool viewImmediate;
	IExecutionEvent* execution_event_;

};

