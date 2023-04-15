#pragma once
#include <condition_variable>

#include "Mesh.h"

class MonitorSharedLoader
{
public:
	MonitorSharedLoader();
	~MonitorSharedLoader();

	void loadMesh(Mesh* mesh);
private:
	typedef std::condition_variable Condition;
	typedef std::mutex Mutex;
	typedef std::unique_lock<std::mutex> UniqueLock;

	Condition* condition;
	Mutex* guard;

	Mesh* mesh;
	bool loadingDone = false;

	void tryDisplay();
	void reportLoadDone();

};

