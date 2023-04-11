#pragma once
#include <queue>
#include <string>
#include <unordered_map>
#include "IETThread.h"

class PoolWorkerThread;
class IWorkerAction;

class IFinishedTask 
{
public:
	virtual void onFinished(int threadID) = 0;
};


class ThreadPool : public IETThread, public IFinishedTask
{
private:
	typedef std::string String;
	typedef std::queue<PoolWorkerThread*> ThreadQueue;
	typedef std::unordered_map<int, PoolWorkerThread*> ThreadTable;
	typedef std::queue<IWorkerAction*> ActionQueue;

public:
	ThreadPool(String name, int numWorkers);
	~ThreadPool();
	void startScheduler();
	void stopScheduler();
	void scheduleTask(IWorkerAction* action);


private:
	void run() override;
	void onFinished(int threadID) override;

	String name;
	bool running = false;
	int numWorkers = 0;
	ThreadTable activeThreads;
	ThreadQueue inactiveThreads;
	ActionQueue pendingActions;

};

