#include "PoolWorkerThread.h"

#include "IWorkerAction.h"
#include "ThreadPool.h"

PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finishedTask, Semaphore* mutex)
{
	this->id = id;
	this->finishedTask = finishedTask;
	this->mutex = mutex;
}

PoolWorkerThread::~PoolWorkerThread()
{
	
}

int PoolWorkerThread::getThreadID()
{
	return this->id;
}

void PoolWorkerThread::assignTask(IWorkerAction* action)
{
	this->action = action;
}

void PoolWorkerThread::run()
{
	this->mutex->acquire();
	this->action->onStartTask();
	this->mutex->release();
	this->finishedTask->onFinished(id);
	
}
