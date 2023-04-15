#include "ThreadPool.h"

#include "IWorkerAction.h"
#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(String name, int numWorkers)
{
	this->name = name;
	this->numWorkers = numWorkers;
	for (int i = 0; i < 5; i++)
	{
		this->sceneMutexList.emplace_back( new Semaphore(1));
	}
	

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

	//delete this->mutex;
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

Semaphore* ThreadPool::getSceneMutex(int index)
{
	return this->sceneMutexList[index];
}

void ThreadPool::run()
{
	while(running)
	{
		Mutex->acquire();
		if (pendingActions.empty() == false)
		{
			if (inactiveThreads.empty() == false)
			{
				PoolWorkerThread* worker_thread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[worker_thread->getThreadID()] = worker_thread;

				worker_thread->assignTask(this->pendingActions.front());
				worker_thread->set_scene_based_mutex(worker_thread->getTask()->sceneMutex);
				worker_thread->set_global_mutex(worker_thread->getTask()->globalMutex);
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
		Mutex->release();
	}
}

void ThreadPool::onFinished(int threadID)
{
	Mutex->acquire();
	if (this->activeThreads[threadID] != nullptr)
	{
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));

	}
	Mutex->release();
}
