#pragma once
#include "IETThread.h"
#include "Semaphore.h"
class IWorkerAction;
class IFinishedTask;

class PoolWorkerThread: public IETThread
{
public:
	PoolWorkerThread(int id, IFinishedTask* finishedTask, Semaphore* mutex);
	~PoolWorkerThread();

	int getThreadID();
	void assignTask(IWorkerAction* action);

private:
	void run() override;

	int id;
	IWorkerAction* action;
	IFinishedTask* finishedTask;
	Semaphore* mutex;
	
};

