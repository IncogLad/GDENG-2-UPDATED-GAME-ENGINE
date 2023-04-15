#pragma once

#include <string>
#include "IExecutionEvent.h"
#include "IWorkerAction.h"

class IWorkerAction;

class LoadingWorkerAction :public IWorkerAction
{
public:
	LoadingWorkerAction(std::string, int sceneNum, IExecutionEvent*, Vector3D position, bool viewImmediate = false);
	~LoadingWorkerAction();

	void onStartTask() override;


private:
	std::string name;
	int sceneNum;
	bool viewImmediate;
	Vector3D position;
	IExecutionEvent* execution_event_;

};

