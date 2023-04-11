#include "ThreadPool.h"

#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(String name, int numWorkers)
{
	this->name = name;
	this->numWorkers = numWorkers;

	for(int i = 0; i < this->numWorkers; i++)
	{
		this->inactiveThreads.push(new PoolWorkerThread(i, this));

	}
}

ThreadPool::~ThreadPool()
{
	this->stopScheduler();

	this->activeThreads.clear();
	while(this->inactiveThreads.empty() == false)
	{
		this->inactiveThreads.pop();

	}
}

void ThreadPool::startScheduler()
{
	this->running = true;
	this->start();
}

void ThreadPool::stopScheduler()
{
	this->running = false;

}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->pendingActions.push(action);
}

void ThreadPool::run()
{
	while(running)
	{
		if (pendingActions.empty() == false)
		{
			if (inactiveThreads.empty() == false)
			{
				PoolWorkerThread* worker_thread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[worker_thread->getThreadID()] = worker_thread;

				worker_thread->assignTask(this->pendingActions.front());
				worker_thread->start();
				this->pendingActions.pop();

			}
			else
			{
				
			}
		}
		else
		{
			
		}
	}
}

void ThreadPool::onFinished(int threadID)
{
	if (this->activeThreads[threadID] != nullptr)
	{
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));
	}
}
