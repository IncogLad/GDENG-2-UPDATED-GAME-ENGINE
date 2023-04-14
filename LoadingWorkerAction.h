#pragma once

#include <string>
#include "IExecutionEvent.h"
#include "IWorkerAction.h"

class IWorkerAction;

class LoadingWorkerAction :public IWorkerAction
{
public:
	LoadingWorkerAction(std::string, int sceneNum, IExecutionEvent*);
	~LoadingWorkerAction();

	void onStartTask() override;


private:
	std::string name;
	int sceneNum;
	IExecutionEvent* execution_event_;

};

