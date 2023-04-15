#pragma once
#include "IETThread.h"
#include "Semaphore.h"
class IWorkerAction;
class IFinishedTask;

class PoolWorkerThread: public IETThread
{
public:
	PoolWorkerThread(int id, IFinishedTask* finishedTask);
	~PoolWorkerThread();

	int getThreadID();
	void assignTask(IWorkerAction* action);
	IWorkerAction* getTask();
	void set_scene_based_mutex(Semaphore* mutex);

private:
	void run() override;

	int id;
	IWorkerAction* action;
	IFinishedTask* finishedTask;
	Semaphore* sceneMutex;
	
};

