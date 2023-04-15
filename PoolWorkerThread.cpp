#include "PoolWorkerThread.h"

#include "IWorkerAction.h"
#include "ThreadPool.h"

PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finishedTask)
{
	this->id = id;
	this->finishedTask = finishedTask;
	
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

IWorkerAction* PoolWorkerThread::getTask()
{
	return action;
}

void PoolWorkerThread::set_scene_based_mutex(Semaphore* mutex)
{
	this->sceneMutex = mutex;
}

void PoolWorkerThread::set_global_mutex(Semaphore* mutex)
{
	this->globalMutex = mutex;
}

void PoolWorkerThread::run()
{
	
	this->sceneMutex->acquire();
	if (globalMutex != nullptr)
		this->globalMutex->acquire();
	this->action->onStartTask();
	if (globalMutex != nullptr)
		this->globalMutex->release();
	this->sceneMutex->release();
	
	this->finishedTask->onFinished(id);
	
}
